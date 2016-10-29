/*********************************************************************/
/*                                                                   */
/*             Optimized BLAS libraries                              */
/*                     By Kazushige Goto <kgoto@tacc.utexas.edu>     */
/*                                                                   */
/* Copyright (c) The University of Texas, 2009. All rights reserved. */
/* UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING  */
/* THIS SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF      */
/* MERCHANTABILITY, FITNESS FOR ANY PARTICULAR PURPOSE,              */
/* NON-INFRINGEMENT AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY  */
/* THAT MIGHT OTHERWISE ARISE FROM COURSE OF DEALING OR USAGE OF     */
/* TRADE. NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH RESPECT TO   */
/* THE USE OF THE SOFTWARE OR DOCUMENTATION.                         */
/* Under no circumstances shall University be liable for incidental, */
/* special, indirect, direct or consequential damages or loss of     */
/* profits, interruption of business, or related expenses which may  */
/* arise from use of Software or Documentation, including but not    */
/* limited to those resulting from defects in Software and/or        */
/* Documentation, or loss or inaccuracy of data of any kind.         */
/*********************************************************************/

#undef  DEBUG

#include "common.h"

#ifdef OS_WINDOWS
#define ALLOC_WINDOWS
#ifndef MEM_LARGE_PAGES
#define MEM_LARGE_PAGES  0x20000000
#endif
#else
#define ALLOC_MMAP
#define ALLOC_MALLOC
#endif

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef OS_WINDOWS
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#endif

#include <sys/types.h>

#ifdef OS_LINUX
#include <sys/sysinfo.h>
#include <sched.h>
#include <errno.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#endif

#if defined(OS_FreeBSD) || defined(OS_Darwin)
#include <sys/sysctl.h>
#endif

#if defined(OS_WINDOWS) && (defined(__MINGW32__) || defined(__MINGW64__))
#include <conio.h>
#undef  printf
#define printf	_cprintf
#endif

#ifdef OS_LINUX

#ifndef MPOL_PREFERRED
#define MPOL_PREFERRED  1
#endif

#endif

#if (defined(PPC440) || !defined(OS_LINUX) || defined(HPL)) && !defined(NO_WARMUP)
#define NO_WARMUP
#endif

#ifdef ALLOC_HUGETLB
#define SHM_HUGETLB 04000
#endif

#ifndef FIXED_PAGESIZE
#define FIXED_PAGESIZE 4096
#endif

#define BITMASK(a, b, c) ((((a) >> (b)) & (c)))

#define CONSTRUCTOR	__attribute__ ((constructor)) 
#define DESTRUCTOR	__attribute__ ((destructor)) 

#ifdef DYNAMIC_ARCH
gotoblas_t *gotoblas = NULL;
#endif

#ifndef SMP

#define blas_cpu_number 1
#define blas_num_threads 1

/* Dummy Function */
int  goto_get_num_procs  (void) { return 1;};
void goto_set_num_threads(int num_threads) {};

#else

#ifdef OS_LINUX
#ifndef NO_AFFINITY
int get_num_procs(void);
#else
int get_num_procs(void) {
  static int nums = 0;
  if (!nums) nums = get_nprocs();
  return nums;
}
#endif
#endif

#ifdef OS_WINDOWS

int get_num_procs(void) {
  
  static int nums = 0;

  if (nums == 0) {

    SYSTEM_INFO sysinfo;
    
    GetSystemInfo(&sysinfo);

    nums = sysinfo.dwNumberOfProcessors;
  }
  
  return nums;
}

#endif

#if defined(OS_FreeBSD) || defined(OS_Darwin)

int get_num_procs(void) {
  
  static int nums = 0;

  int m[2];
  size_t len;
  
  if (nums == 0) {
    m[0] = CTL_HW;
    m[1] = HW_NCPU;
    len = sizeof(int);
    sysctl(m, 2, &nums, &len, NULL, 0);
  }

  return nums;
}

#endif

int blas_cpu_number  = 0;
int blas_num_threads = 0;

int  goto_get_num_procs  (void) {
  return blas_cpu_number;
}

int blas_get_cpu_number(void){
  char *p;
#if defined(OS_LINUX) || defined(OS_WINDOWS) || defined(OS_FreeBSD) || defined(OS_Darwin)
  int max_num;
#endif
  int blas_goto_num   = 0;
  int blas_omp_num    = 0;

  if (blas_num_threads) return blas_num_threads;

#if defined(OS_LINUX) || defined(OS_WINDOWS) || defined(OS_FreeBSD) || defined(OS_Darwin)
  max_num = get_num_procs();
#endif

  blas_goto_num = 0;
#ifndef USE_OPENMP
  p = getenv("GOTO_NUM_THREADS");
  if (p) blas_goto_num = atoi(p);
  if (blas_goto_num < 0) blas_goto_num = 0;
#endif

  blas_omp_num = 0;
  p = getenv("OMP_NUM_THREADS");
  if (p) blas_omp_num = atoi(p);
  if (blas_omp_num < 0) blas_omp_num = 0;

  if (blas_goto_num > 0) blas_num_threads = blas_goto_num;
  else if (blas_omp_num > 0) blas_num_threads = blas_omp_num;
  else blas_num_threads = MAX_CPU_NUMBER;

#if defined(OS_LINUX) || defined(OS_WINDOWS) || defined(OS_FreeBSD) || defined(OS_Darwin)
  if (blas_num_threads > max_num) blas_num_threads = max_num;
#endif

  if (blas_num_threads > MAX_CPU_NUMBER) blas_num_threads = MAX_CPU_NUMBER;

#ifdef DEBUG
  printf( "Adjusted number of threads : %3d\n", blas_num_threads);
#endif
  
  blas_cpu_number = blas_num_threads;  

  return blas_num_threads;
}
#endif

struct release_t {
  void *address;
  void (*func)(struct release_t *);
  long attr;
};

int hugetlb_allocated = 0;

static struct release_t release_info[NUM_BUFFERS];
static int release_pos = 0;

#if defined(OS_LINUX) && !defined(NO_WARMUP)
static int hot_alloc = 0;
#endif

#ifdef ALLOC_MMAP

static void alloc_mmap_free(struct release_t *release){

  if (munmap(release -> address, BUFFER_SIZE)) {
    printf("GotoBLAS : munmap failed\n");
  }
}

#ifdef NO_WARMUP

static void *alloc_mmap(void *address){
  void *map_address;

  if (address){
    map_address = mmap(address, 
		       BUFFER_SIZE, 
		       MMAP_ACCESS, MMAP_POLICY | MAP_FIXED, -1, 0);
  } else {
    map_address = mmap(address, 
		       BUFFER_SIZE, 
		       MMAP_ACCESS, MMAP_POLICY, -1, 0);
  }

  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].func    = alloc_mmap_free;
    release_pos ++;
  }

#ifdef OS_LINUX
  my_mbind(map_address, BUFFER_SIZE, MPOL_PREFERRED, NULL, 0, 0);
#endif

  return map_address;
}

#else

#define BENCH_ITERATION 4
#define SCALING		2

static inline BLASULONG run_bench(BLASULONG address, long size) {

  BLASULONG original, *p;
  BLASULONG start, stop, min;
  int iter, i, count;
  
  min = (BLASULONG)-1;

  original = *(BLASULONG *)(address + size - PAGESIZE);

  *(BLASULONG *)(address + size - PAGESIZE) = (BLASULONG)address;

  for (iter = 0; iter < BENCH_ITERATION; iter ++ ) {

    p = (BLASULONG *)address;
    
    count = size / PAGESIZE;
    
    start = rpcc();
    
    for (i = 0; i < count; i ++) {
      p = (BLASULONG *)(*p);
    }
    
    stop = rpcc();
    
    if (min > stop - start) min = stop - start;
  }
  
  *(BLASULONG *)(address + size - PAGESIZE +  0) = original;
  *(BLASULONG *)(address + size - PAGESIZE +  8) = (BLASULONG)p;

  return min;
}

static void *alloc_mmap(void *address){
  void *map_address, *best_address;
  BLASULONG best, start, current;
  BLASULONG allocsize;

  if (address){
    /* Just give up use advanced operation */
    map_address = mmap(address, BUFFER_SIZE, MMAP_ACCESS, MMAP_POLICY | MAP_FIXED, -1, 0);

#ifdef OS_LINUX
    my_mbind(map_address, BUFFER_SIZE, MPOL_PREFERRED, NULL, 0, 0);
#endif

  } else {
#if defined(OS_LINUX) && !defined(NO_WARMUP)
    if (hot_alloc == 0) {
      map_address = mmap(NULL, BUFFER_SIZE, MMAP_ACCESS, MMAP_POLICY, -1, 0);

#ifdef OS_LINUX
      my_mbind(map_address, BUFFER_SIZE, MPOL_PREFERRED, NULL, 0, 0);
#endif

    } else {
#endif

      map_address = mmap(NULL, BUFFER_SIZE * SCALING, 
			 MMAP_ACCESS, MMAP_POLICY, -1, 0);
      
      if (map_address != (void *)-1) {
	
#ifdef OS_LINUX
	my_mbind(map_address, BUFFER_SIZE * SCALING, MPOL_PREFERRED, NULL, 0, 0);
#endif

	allocsize = DGEMM_P * DGEMM_Q * sizeof(double);
	
	start   = (BLASULONG)map_address;
	current = (SCALING - 1) * BUFFER_SIZE;
	
	while(current > 0) {
	  *(long *)start = (long)start + PAGESIZE;
	  start += PAGESIZE;
	  current -= PAGESIZE;
	}
	
	*(long *)(start - PAGESIZE) = (BLASULONG)map_address;
	
	start = (BLASULONG)map_address;
	
	best = (BLASULONG)-1;
	best_address = map_address;
	
	while ((start + allocsize  < (BLASULONG)map_address + (SCALING - 1) * BUFFER_SIZE)) {
	  
	  current = run_bench(start, allocsize);
	  
	  if (best > current) {
	    best = current;
	    best_address = (void *)start;
	  }
	  
	  start += PAGESIZE;
	  
	}
	
      if ((BLASULONG)best_address > (BLASULONG)map_address)
	munmap(map_address,  (BLASULONG)best_address - (BLASULONG)map_address);
      
      munmap((void *)((BLASULONG)best_address + BUFFER_SIZE), (SCALING - 1) * BUFFER_SIZE + (BLASULONG)map_address - (BLASULONG)best_address);
      
      map_address = best_address;
      
#if defined(OS_LINUX) && !defined(NO_WARMUP)
      hot_alloc = 2;
#endif
      }
    }
#if defined(OS_LINUX) && !defined(NO_WARMUP)
  }
#endif

  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].func    = alloc_mmap_free;
    release_pos ++;
  }

  return map_address;
}

#endif

#endif


#ifdef ALLOC_MALLOC

static void alloc_malloc_free(struct release_t *release){

  free(release -> address);

}

static void *alloc_malloc(void *address){

  void *map_address;

  map_address = (void *)malloc(BUFFER_SIZE + FIXED_PAGESIZE);

  if (map_address == (void *)NULL) map_address = (void *)-1;

  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].func    = alloc_malloc_free;
    release_pos ++;
  }

  return map_address;

}

#endif

#ifdef ALLOC_QALLOC

void *qalloc(int flags, size_t bytes);
void *qfree (void *address);

#define QNONCACHE 0x1
#define QCOMMS    0x2
#define QFAST     0x4

static void alloc_qalloc_free(struct release_t *release){

  qfree(release -> address);

}

static void *alloc_qalloc(void *address){
  void *map_address;

  map_address = (void *)qalloc(QCOMMS | QFAST, BUFFER_SIZE + FIXED_PAGESIZE);

  if (map_address == (void *)NULL) map_address = (void *)-1;

  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].func    = alloc_qalloc_free;
    release_pos ++;
  }

  return (void *)(((BLASULONG)map_address + FIXED_PAGESIZE - 1) & ~(FIXED_PAGESIZE - 1));
}

#endif

#ifdef ALLOC_WINDOWS

static void alloc_windows_free(struct release_t *release){

  VirtualFree(release -> address, BUFFER_SIZE, MEM_DECOMMIT);

}

static void *alloc_windows(void *address){
  void *map_address;

  map_address  = VirtualAlloc(address,
			      BUFFER_SIZE,
			      MEM_RESERVE | MEM_COMMIT,
			      PAGE_READWRITE);

  if (map_address == (void *)NULL) map_address = (void *)-1;

  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].func    = alloc_windows_free;
    release_pos ++;
  }

  return map_address;
}

#endif

#ifdef ALLOC_DEVICEDRIVER
#ifndef DEVICEDRIVER_NAME
#define DEVICEDRIVER_NAME "/dev/mapper"
#endif

static void alloc_devicedirver_free(struct release_t *release){

  if (munmap(release -> address, BUFFER_SIZE)) {
    printf("GotoBLAS : Bugphysarea unmap failed.\n");
  }

  if (close(release -> attr)) {
    printf("GotoBLAS : Bugphysarea close failed.\n");
  }

}

static void *alloc_devicedirver(void *address){
  
  int fd;
  void *map_address;

  if ((fd = open(DEVICEDRIVER_NAME, O_RDWR | O_SYNC)) < 0) {

    return (void *)-1;

  }

  map_address = mmap(address, BUFFER_SIZE,
		     PROT_READ | PROT_WRITE,
		     MAP_FILE | MAP_SHARED,
		     fd, 0);
  
  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].attr    = fd;
    release_info[release_pos].func    = alloc_devicedirver_free;
    release_pos ++;
  }

  return map_address;
}

#endif

#ifdef ALLOC_SHM

static void alloc_shm_free(struct release_t *release){

  if (shmdt(release -> address)) {
    printf("GotoBLAS : Shared memory unmap failed.\n");
    }
}

static void *alloc_shm(void *address){
  void *map_address;
  int shmid;
  
  shmid = shmget(IPC_PRIVATE, BUFFER_SIZE,IPC_CREAT | 0600);
  
  map_address = (void *)shmat(shmid, address, 0);

  if (map_address != (void *)-1){

#ifdef OS_LINUX
    my_mbind(map_address, BUFFER_SIZE, MPOL_PREFERRED, NULL, 0, 0);
#endif

    shmctl(shmid, IPC_RMID, 0);

    release_info[release_pos].address = map_address;
    release_info[release_pos].attr    = shmid;
    release_info[release_pos].func    = alloc_shm_free;
    release_pos ++;
  }

  return map_address;
}

#endif

#if defined OS_LINUX  || defined OS_AIX  || defined __sun__  || defined OS_WINDOWS

static void alloc_hugetlb_free(struct release_t *release){

#if defined(OS_LINUX) || defined(OS_AIX)
  if (shmdt(release -> address)) {
    printf("GotoBLAS : Hugepage unmap failed.\n");
  }
#endif

#ifdef __sun__

  munmap(release -> address, BUFFER_SIZE);

#endif

#ifdef OS_WINDOWS

  VirtualFree(release -> address, BUFFER_SIZE, MEM_LARGE_PAGES | MEM_DECOMMIT);

#endif

}

static void *alloc_hugetlb(void *address){

  void *map_address = (void *)-1;

#if defined(OS_LINUX) || defined(OS_AIX)
  int shmid;
  
  shmid = shmget(IPC_PRIVATE, BUFFER_SIZE,
#ifdef OS_LINUX
		 SHM_HUGETLB |
#endif
#ifdef OS_AIX
		 SHM_LGPAGE | SHM_PIN |
#endif
		 IPC_CREAT | SHM_R | SHM_W);
  
  if (shmid != -1) {
    map_address = (void *)shmat(shmid, address, SHM_RND);
    
#ifdef OS_LINUX
    my_mbind(map_address, BUFFER_SIZE, MPOL_PREFERRED, NULL, 0, 0);
#endif

    if (map_address != (void *)-1){
      shmctl(shmid, IPC_RMID, 0);
    }
  }
#endif

#ifdef __sun__
  struct memcntl_mha mha;
  
  mha.mha_cmd = MHA_MAPSIZE_BSSBRK;
  mha.mha_flags = 0;
  mha.mha_pagesize = HUGE_PAGESIZE;
  memcntl(NULL, 0, MC_HAT_ADVISE, (char *)&mha, 0, 0);

  map_address = (BLASULONG)memalign(HUGE_PAGESIZE, BUFFER_SIZE);
#endif

#ifdef OS_WINDOWS

  HANDLE hToken;
  TOKEN_PRIVILEGES tp;

  if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) != TRUE) return (void *) -1;

  tp.PrivilegeCount = 1;
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  
  if (LookupPrivilegeValue(NULL, SE_LOCK_MEMORY_NAME, &tp.Privileges[0].Luid) != TRUE) return (void *) -1;

  if (AdjustTokenPrivileges(hToken, FALSE, (PTOKEN_PRIVILEGES)&tp, 0, NULL, NULL) != TRUE) return (void *) -1;

  map_address  = (void *)VirtualAlloc(address,
				      BUFFER_SIZE,
				      MEM_LARGE_PAGES | MEM_RESERVE | MEM_COMMIT,
				      PAGE_READWRITE);

  AdjustTokenPrivileges(hToken, TRUE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, NULL);

  if (map_address == (void *)NULL) map_address = (void *)-1;
  
#endif

  if (map_address != (void *)-1){
    release_info[release_pos].address = map_address;
    release_info[release_pos].func    = alloc_hugetlb_free;
    release_pos ++;
  }

  return map_address;
}
#endif

#ifdef  ALLOC_HUGETLBFILE

static int hugetlb_pid = 0;

static void alloc_hugetlbfile_free(struct release_t *release){

  if (munmap(release -> address, BUFFER_SIZE)) {
    printf("GotoBLAS : HugeTLBfs unmap failed.\n");
  }

  if (close(release -> attr)) {
    printf("GotoBLAS : HugeTLBfs close failed.\n");
  }
}

static void *alloc_hugetlbfile(void *address){

  void *map_address = (void *)-1;
  int fd;
  char filename[64];

  if (!hugetlb_pid) hugetlb_pid = getpid();

  sprintf(filename, "%s/gotoblas.%d", HUGETLB_FILE_NAME, hugetlb_pid);

  if ((fd = open(filename, O_RDWR | O_CREAT, 0700)) < 0) {
    return (void *)-1;
  }

  unlink(filename);

  map_address = mmap(address, BUFFER_SIZE,
		     PROT_READ | PROT_WRITE,
		     MAP_SHARED,
		     fd, 0);
  
  if (map_address != (void *)-1) {
    release_info[release_pos].address = map_address;
    release_info[release_pos].attr    = fd;
    release_info[release_pos].func    = alloc_hugetlbfile_free;
    release_pos ++;
  }

  return map_address;
}
#endif

/* Global lock for memory allocation */

#if   defined(USE_PTHREAD_LOCK)
static pthread_mutex_t    alloc_lock = PTHREAD_MUTEX_INITIALIZER;
#elif defined(USE_PTHREAD_SPINLOCK)
static pthread_spinlock_t alloc_lock = 0;
#else
static BLASULONG  alloc_lock = 0UL;
#endif

#ifdef SEEK_ADDRESS
static BLASULONG base_address      = 0UL;
#else
static BLASULONG base_address      = BASE_ADDRESS;
#endif

static volatile struct {
  BLASULONG lock;
  void *addr;
#if defined(WHEREAMI) && !defined(USE_OPENMP)
  int   pos;
#endif
  int used;
#ifndef __64BIT__
  char dummy[48];
#else
  char dummy[40];
#endif

} memory[NUM_BUFFERS];

static int memory_initialized = 0;
static void gotoblas_memory_init(void);

/*       Memory allocation routine           */
/* procpos ... indicates where it comes from */
/*                0 : Level 3 functions      */
/*                1 : Level 2 functions      */
/*                2 : Thread                 */

void *blas_memory_alloc(int procpos){
  
  int position;
#if defined(WHEREAMI) && !defined(USE_OPENMP)
  int mypos;
#endif

  void *map_address;

  void *(*memoryalloc[])(void *address) = {
#ifdef ALLOC_DEVICEDRIVER
    alloc_devicedirver,
#endif
#if defined OS_LINUX  || defined OS_AIX  || defined __sun__  || defined OS_WINDOWS
    alloc_hugetlb,
#endif
#ifdef ALLOC_SHM
    alloc_shm,
#endif
#ifdef ALLOC_MMAP
    alloc_mmap,
#endif
#ifdef ALLOC_QALLOC
    alloc_qalloc,
#endif
#ifdef ALLOC_WINDOWS
    alloc_windows,
#endif
#ifdef ALLOC_MALLOC
    alloc_malloc,
#endif
    NULL,
  };
  void *(**func)(void *address);

  if (!memory_initialized) {
    
    LOCK_COMMAND(&alloc_lock);
    
    if (!memory_initialized) {
      
#if defined(WHEREAMI) && !defined(USE_OPENMP)
      for (position = 0; position < NUM_BUFFERS; position ++){
	memory[position].addr   = (void *)0;
	memory[position].pos    = -1;
	memory[position].used   = 0;
	memory[position].lock   = 0;
      }
#endif
      
#ifdef DYNAMIC_ARCH
      gotoblas_dynamic_init();
#endif

#if defined(SMP) && defined(OS_LINUX) && !defined(NO_AFFINITY)
      gotoblas_affinity_init();
#endif
      
#ifdef SMP
      if (!blas_num_threads) blas_cpu_number = blas_get_cpu_number();
#endif
      
#if defined(ARCH_X86) || defined(ARCH_X86_64) || defined(ARCH_IA64)
#ifndef DYNAMIC_ARCH
      blas_set_parameter();
#endif
#endif

      memory_initialized = 1;
    }

    UNLOCK_COMMAND(&alloc_lock);
  }

#ifdef DEBUG
  printf("Alloc Start ...\n");
#endif

#if defined(WHEREAMI) && !defined(USE_OPENMP)

  mypos = WhereAmI();

  position = mypos;
  while (position > NUM_BUFFERS) position >>= 1;

  do {
    if (!memory[position].used && (memory[position].pos == mypos)) {
      
      blas_lock(&memory[position].lock);
      
      if (!memory[position].used) goto allocation;
      
      blas_unlock(&memory[position].lock);
    }
    
    position ++;
    
  } while (position < NUM_BUFFERS);


#endif

  position = 0;

  do {
    if (!memory[position].used) {
      
      blas_lock(&memory[position].lock);

      if (!memory[position].used) goto allocation;
      
      blas_unlock(&memory[position].lock);
    }
    
    position ++;
    
  } while (position < NUM_BUFFERS);
  
  goto error;

  allocation :

#ifdef DEBUG
  printf("  Position -> %d\n", position);
#endif

  memory[position].used = 1;

  blas_unlock(&memory[position].lock);

  if (!memory[position].addr) {
    do {
#ifdef DEBUG
      printf("Allocation Start : %lx\n", base_address);
#endif

      map_address = (void *)-1;

      func = &memoryalloc[0];

      while ((func != NULL) && (map_address == (void *) -1)) {

	map_address = (*func)((void *)base_address);

#ifdef ALLOC_DEVICEDRIVER
	if ((*func ==  alloc_devicedirver) && (map_address == (void *)-1)) {
	    fprintf(stderr, "GotoBLAS Warning ... Physically contigous allocation was failed.\n");
	}
#endif

#ifdef ALLOC_HUGETLBFILE
	if ((*func == alloc_hugetlbfile) && (map_address == (void *)-1)) {
#ifndef OS_WINDOWS
	    fprintf(stderr, "GotoBLAS Warning ... HugeTLB(File) allocation was failed.\n");
#endif
	}
#endif

#if defined OS_LINUX  || defined OS_AIX  || defined __sun__  || defined OS_WINDOWS
	if ((*func == alloc_hugetlb) && (map_address != (void *)-1)) hugetlb_allocated = 1;
#endif

	func ++;
      }

#ifdef DEBUG
      printf("  Success -> %08lx\n", map_address);
#endif
      if (((BLASLONG) map_address) == -1) base_address = 0UL;

      if (base_address) base_address += BUFFER_SIZE + FIXED_PAGESIZE;

    } while ((BLASLONG)map_address == -1);

    memory[position].addr = map_address; 

#ifdef DEBUG
    printf("  Mapping Succeeded. %p(%d)\n", (void *)alloc_area[position], position);
#endif
  }
 
#if defined(WHEREAMI) && !defined(USE_OPENMP)

  if (memory[position].pos == -1) memory[position].pos = mypos;

#endif

#ifdef DYNAMIC_ARCH

  if (memory_initialized == 1) {
    
    LOCK_COMMAND(&alloc_lock);
    
    if (memory_initialized == 1) {
      
      if (!gotoblas) gotoblas_dynamic_init();
      
      memory_initialized = 2;
    }
    
    UNLOCK_COMMAND(&alloc_lock);
    
  }
#endif


#ifdef DEBUG
  printf("Mapped   : %p  %3d\n\n",
	  (void *)alloc_area[position], position);
#endif  
  
  return (void *)memory[position].addr;

 error:
  printf("BLAS : Program is Terminated. Because you tried to allocate too many memory regions.\n");

  return NULL;
}

void blas_memory_free(void *free_area){

  int position;

#ifdef DEBUG
  printf("Unmapped Start : %p ...\n", free_area);
#endif  
 
  position = 0;

  while ((memory[position].addr != free_area)
	 && (position < NUM_BUFFERS)) position++;

  if (memory[position].addr != free_area) goto error;

#ifdef DEBUG
  printf("  Position : %d\n", position);
#endif  

  memory[position].used = 0;

#ifdef DEBUG
  printf("Unmap Succeeded.\n\n");
#endif  

  return;
  
 error:
  printf("BLAS : Bad memory unallocation! : %4d  %p\n", position,  free_area);

#ifdef DEBUG
  for (position = 0; position < NUM_BUFFERS; position++) 
    printf("%4ld  %p : %d\n", position, alloc_area[position], alloc_used[position]);
#endif

  return;
}

void blas_shutdown(void){

  int pos;

#ifdef SMP
  BLASFUNC(blas_thread_shutdown)();
#endif

  LOCK_COMMAND(&alloc_lock);

  for (pos = 0; pos < release_pos; pos ++) {
    release_info[pos].func(&release_info[pos]);
  }
  
#ifdef SEEK_ADDRESS
  base_address      = 0UL;
#else
  base_address      = BASE_ADDRESS;
#endif

  for (pos = 0; pos < NUM_BUFFERS; pos ++){
    memory[pos].addr   = (void *)0;
    memory[pos].used   = 0;
#if defined(WHEREAMI) && !defined(USE_OPENMP)
    memory[pos].pos    = -1;
#endif
    memory[pos].lock   = 0;
  }

  UNLOCK_COMMAND(&alloc_lock);

  return;
}

#if defined(OS_LINUX) && !defined(NO_WARMUP)
 
#ifdef SMP
#if   defined(USE_PTHREAD_LOCK)
static pthread_mutex_t    init_lock = PTHREAD_MUTEX_INITIALIZER;
#elif defined(USE_PTHREAD_SPINLOCK)
static pthread_spinlock_t init_lock = 0;
#else
static BLASULONG   init_lock = 0UL;
#endif
#endif

static void _touch_memory(blas_arg_t *arg, BLASLONG *range_m, BLASLONG *range_n, 
			  void *sa, void *sb, BLASLONG pos) {

#ifndef ARCH_POWER

  long size;
  BLASULONG buffer;

  size   = BUFFER_SIZE - PAGESIZE;
  buffer = (BLASULONG)sa + GEMM_OFFSET_A;

#if defined(OS_LINUX) && !defined(NO_WARMUP)
    if (hot_alloc != 2) {
#endif

#ifdef SMP
  LOCK_COMMAND(&init_lock);
#endif

  while (size > 0) {
    *(int *)buffer = size;
    buffer  += PAGESIZE;
    size    -= PAGESIZE;
  }

#ifdef SMP
  UNLOCK_COMMAND(&init_lock);
#endif

  size = MIN((BUFFER_SIZE - PAGESIZE), L2_SIZE);
  buffer = (BLASULONG)sa + GEMM_OFFSET_A;

  while (size > 0) {
    *(int *)buffer = size;
    buffer  += 64;
    size    -= 64;
  }

#if defined(OS_LINUX) && !defined(NO_WARMUP)
    }
#endif

#endif
}

#ifdef SMP

static void _init_thread_memory(void *buffer) {

  blas_queue_t queue[MAX_CPU_NUMBER];
  int num_cpu;

  for (num_cpu = 0; num_cpu < blas_num_threads; num_cpu++) {

    blas_queue_init(&queue[num_cpu]);
    queue[num_cpu].mode    = BLAS_DOUBLE | BLAS_REAL;
    queue[num_cpu].routine = &_touch_memory;
    queue[num_cpu].args    = NULL;
    queue[num_cpu].next    = &queue[num_cpu + 1];
  }

  queue[num_cpu - 1].next = NULL;
  queue[0].sa = buffer;
  
  exec_blas(num_cpu, queue);

}
#endif

static void gotoblas_memory_init(void) {

  void *buffer;

  hot_alloc = 1;

  buffer = (void *)blas_memory_alloc(0);

#ifdef SMP
  if (blas_cpu_number == 0) blas_get_cpu_number();
#ifdef SMP_SERVER
  if (blas_server_avail == 0) blas_thread_init();
#endif
    
  _init_thread_memory((void *)((BLASULONG)buffer + GEMM_OFFSET_A));
  
#else
  
  _touch_memory(NULL, NULL, NULL, (void *)((BLASULONG)buffer + GEMM_OFFSET_A), NULL, 0);
  
#endif
  
  blas_memory_free(buffer);
}
#endif

/* Initialization for all function; this function should be called before main */

static int gotoblas_initialized = 0;

void CONSTRUCTOR gotoblas_init(void) {

  if (gotoblas_initialized) return;

#ifdef PROFILE
   moncontrol (0);
#endif

#ifdef DYNAMIC_ARCH
   gotoblas_dynamic_init();
#endif

#if defined(SMP) && defined(OS_LINUX) && !defined(NO_AFFINITY)
   gotoblas_affinity_init();
#endif

#if defined(OS_LINUX) && !defined(NO_WARMUP)
   gotoblas_memory_init();
#endif

#ifdef SMP
  if (blas_cpu_number == 0) blas_get_cpu_number();
#ifdef SMP_SERVER
  if (blas_server_avail == 0) blas_thread_init();
#endif
#endif

#ifdef FUNCTION_PROFILE
   gotoblas_profile_init();
#endif

   gotoblas_initialized = 1;

#ifdef PROFILE
   moncontrol (1);
#endif

}

void DESTRUCTOR gotoblas_quit(void) {

  if (gotoblas_initialized == 0) return;

#ifdef PROFILE
   moncontrol (0);
#endif

#ifdef FUNCTION_PROFILE
   gotoblas_profile_quit();
#endif

#if defined(SMP) && defined(OS_LINUX) && !defined(NO_AFFINITY)
   gotoblas_affinity_quit();
#endif

#ifdef DYNAMIC_ARCH
   gotoblas_dynamic_quit();
#endif

   gotoblas_initialized = 0;

#ifdef PROFILE
   moncontrol (1);
#endif

}

#if (defined(C_PGI) || (!defined(C_SUN) && defined(F_INTERFACE_SUN))) && (defined(ARCH_X86) || defined(ARCH_X86_64))
/* Don't call me; this is just work around for PGI / Sun bug */
void gotoblas_dummy_for_PGI(void) {

  gotoblas_init();
  gotoblas_quit();

#if 0
  asm ("\t.section\t.ctors,\"aw\",@progbits; .align 8; .quad gotoblas_init; .section .text");
  asm ("\t.section\t.dtors,\"aw\",@progbits; .align 8; .quad gotoblas_quit; .section .text");
#else
  asm (".section .init,\"ax\"; call gotoblas_init@PLT; .section .text");
  asm (".section .fini,\"ax\"; call gotoblas_quit@PLT; .section .text");
#endif
}
#endif

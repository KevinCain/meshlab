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

#ifndef COMMON_H
#define COMMON_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif

#ifndef __USE_SVID
#define __USE_SVID
#endif

#ifdef BUILD_KERNEL
#include "config_kernel.h"
#else
#include "config.h"
#endif

#undef ENABLE_SSE_EXCEPTION

#if defined(SMP_SERVER) || defined(SMP_ONDEMAND)
#define SMP
#endif

#if defined(OS_WINNT) || defined(OS_CYGWIN_NT) || defined(OS_Interix)
#define WINDOWS_ABI
#define OS_WINDOWS

#ifdef DOUBLE
#define DOUBLE_DEFINED DOUBLE
#undef  DOUBLE
#endif
#endif

#if !defined(NOINCLUDE) && !defined(ASSEMBLER)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef OS_LINUX
#include <malloc.h>
#include <sched.h>
#endif

#ifdef OS_WINDOWS
#ifdef  ATOM
#define GOTO_ATOM ATOM
#undef  ATOM
#endif
#include <windows.h>
#include <math.h>
#ifdef  GOTO_ATOM
#define ATOM GOTO_ATOM
#undef  GOTO_ATOM
#endif
#else
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#ifdef SMP
#include <pthread.h>
#endif
#endif

#if defined(OS_SUNOS)
#include <thread.h>
#endif

#ifdef __DECC
#include <c_asm.h>
#include <machine/builtins.h>
#endif

#if defined(ARCH_IA64) && defined(ENABLE_SSE_EXCEPTION)
#include <fenv.h>
#endif

#endif

#if defined(OS_WINDOWS) && defined(DOUBLE_DEFINED)
#define DOUBLE DOUBLE_DEFINED
#undef DOUBLE_DEFINED
#endif

#undef DEBUG_INFO
#define SMP_DEBUG
#undef MALLOC_DEBUG
#undef SMP_ALLOC_DEBUG

#ifndef ZERO
#ifdef XDOUBLE
#define ZERO  0.e0L
#elif defined DOUBLE
#define ZERO  0.e0
#else
#define ZERO  0.e0f
#endif
#endif

#ifndef ONE
#ifdef XDOUBLE
#define ONE  1.e0L
#elif defined DOUBLE
#define ONE  1.e0
#else
#define ONE  1.e0f
#endif
#endif

#define BITMASK(a, b, c) ((((a) >> (b)) & (c)))

#define ALLOCA_ALIGN 63UL

#define NUM_BUFFERS (MAX_CPU_NUMBER * 2)

#ifdef NEEDBUNDERSCORE
#define BLASFUNC(FUNC) FUNC##_
#else
#define BLASFUNC(FUNC) FUNC
#endif

#undef	USE_PTHREAD_LOCK
#undef	USE_PTHREAD_SPINLOCK

#if defined(USE_PTHREAD_LOCK) && defined(USE_PTHREAD_SPINLOCK)
#error "You can't specify both LOCK operation!"
#endif

#ifdef SMP
#define USE_PTHREAD_LOCK
#undef	USE_PTHREAD_SPINLOCK
#endif

#ifdef OS_WINDOWS
#undef	USE_PTHREAD_LOCK
#undef	USE_PTHREAD_SPINLOCK
#endif

#if   defined(USE_PTHREAD_LOCK)
#define   LOCK_COMMAND(x)   pthread_mutex_lock(x)
#define UNLOCK_COMMAND(x)   pthread_mutex_unlock(x)
#elif defined(USE_PTHREAD_SPINLOCK)
#ifndef ASSEMBLER
typedef volatile int pthread_spinlock_t;
int pthread_spin_lock (pthread_spinlock_t *__lock);
int pthread_spin_unlock (pthread_spinlock_t *__lock);
#endif
#define   LOCK_COMMAND(x)   pthread_spin_lock(x)
#define UNLOCK_COMMAND(x)   pthread_spin_unlock(x)
#else
#define   LOCK_COMMAND(x)   blas_lock(x)
#define UNLOCK_COMMAND(x)   blas_unlock(x)
#endif

#define GOTO_SHMID	0x510510

#if 0
#ifndef __CUDACC__
#define __global__
#define __device__
#define __host__
#define __shared__
#endif
#endif

#ifndef ASSEMBLER

#ifdef QUAD_PRECISION
typedef struct {
  unsigned long x[2];
}  xdouble;
#elif defined EXPRECISION
#define xdouble long double
#else
#define xdouble double
#endif

#if defined(OS_WINDOWS) && defined(__64BIT__)
typedef long long BLASLONG;
typedef unsigned long long BLASULONG;
#else
typedef long BLASLONG;
typedef unsigned long BLASULONG;
#endif

#ifdef USE64BITINT
typedef BLASLONG blasint;
#else
typedef int blasint;
#endif
#else
#ifdef USE64BITINT
#define INTSHIFT	3
#define INTSIZE		8
#else
#define INTSHIFT	2
#define INTSIZE		4
#endif
#endif

#ifdef XDOUBLE
#define FLOAT	xdouble
#ifdef QUAD_PRECISION
#define XFLOAT	xidouble
#endif
#ifdef QUAD_PRECISION
#define SIZE	32
#define  BASE_SHIFT 5
#define ZBASE_SHIFT 6
#else
#define SIZE	16
#define  BASE_SHIFT 4
#define ZBASE_SHIFT 5
#endif
#elif defined(DOUBLE)
#define FLOAT	double
#define SIZE	8
#define  BASE_SHIFT 3
#define ZBASE_SHIFT 4
#else
#define FLOAT	float
#define SIZE    4
#define  BASE_SHIFT 2
#define ZBASE_SHIFT 3
#endif

#ifndef XFLOAT
#define XFLOAT	FLOAT
#endif

#ifndef COMPLEX
#define COMPSIZE  1
#else
#define COMPSIZE  2
#endif

#if defined(C_PGI) || defined(C_SUN)
#define CREAL(X)	(*((FLOAT *)&X + 0))
#define CIMAG(X)	(*((FLOAT *)&X + 1))
#else
#define CREAL	__real__
#define CIMAG	__imag__
#endif

#define Address_H(x) (((x)+(1<<15))>>16)
#define Address_L(x) ((x)-((Address_H(x))<<16))

#ifndef MAX_CPU_NUMBER
#define MAX_CPU_NUMBER 2
#endif

#if defined(OS_SUNOS)
#define YIELDING	thr_yield()
#endif

#if defined(OS_WINDOWS)
#define YIELDING	SwitchToThread()
#endif

#ifndef YIELDING
#define YIELDING	sched_yield()
#endif

#ifdef QUAD_PRECISION
#include "common_quad.h"
#endif

#ifdef ARCH_ALPHA
#include "common_alpha.h"
#endif

#ifdef ARCH_X86
#include "common_x86.h"
#endif

#ifdef ARCH_X86_64
#include "common_x86_64.h"
#endif

#ifdef ARCH_IA64
#include "common_ia64.h"
#endif

#ifdef ARCH_POWER
#include "common_power.h"
#endif

#ifdef sparc
#include "common_sparc.h"
#endif

#ifdef ARCH_MIPS64
#include "common_mips64.h"
#endif

#ifdef OS_LINUX
#include "common_linux.h"
#endif

#define MMAP_ACCESS (PROT_READ | PROT_WRITE)
#define MMAP_POLICY (MAP_PRIVATE | MAP_ANONYMOUS)

#include "param.h"
#include "common_param.h"

#ifndef STDERR
#define STDERR stderr
#endif

#ifndef MASK
#define MASK(a, b) (((a) + ((b) - 1)) & ~((b) - 1))
#endif

#if defined(XDOUBLE) || defined(DOUBLE)
#define FLOATRET	FLOAT
#else
#ifdef NEED_F2CCONV
#define FLOATRET	double
#else
#define FLOATRET	float
#endif
#endif

#ifndef IFLUSH
#define IFLUSH
#endif

#ifndef IFLUSH_HALF
#define IFLUSH_HALF
#endif

#if defined(C_GCC) && (( __GNUC__ <= 3) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 2)))
#ifdef USE_OPENMP
#undef USE_OPENMP
#endif
#endif

#ifndef ASSEMBLER

#ifndef MIN
#define MIN(a,b)   (a>b? b:a)
#endif

#ifndef MAX
#define MAX(a,b)   (a<b? b:a)
#endif

#define TOUPPER(a) {if ((a) > 0x60) (a) -= 0x20;}

#if defined(__FreeBSD__) || defined(__APPLE__)
#define MAP_ANONYMOUS MAP_ANON
#endif

/* Common Memory Management Routine */
void  blas_set_parameter(void);
int   blas_get_cpu_number(void);
void *blas_memory_alloc  (int);
void  blas_memory_free   (void *);

int  get_num_procs (void);

#if defined(OS_LINUX) && defined(SMP) && !defined(NO_AFFINITY)
int  get_num_nodes (void);
int get_num_proc   (int);
int get_node_equal (void);
#endif

void goto_set_num_threads(int);

void gotoblas_affinity_init(void);
void gotoblas_affinity_quit(void);
void gotoblas_dynamic_init(void);
void gotoblas_dynamic_quit(void);
void gotoblas_profile_init(void);
void gotoblas_profile_quit(void);

#ifdef USE_OPENMP
int omp_in_parallel(void);
int omp_get_num_procs(void);
#else
#ifdef __ELF__
int omp_in_parallel  (void) __attribute__ ((weak));
int omp_get_num_procs(void) __attribute__ ((weak));
#endif
#endif

static __inline void blas_unlock(volatile BLASULONG *address){
  MB;
  *address = 0;
}

static __inline int readenv(char *env) {

  char *p;

  p = getenv(env);

  if (p == NULL) return 0; else return atoi(p);
}


#if !defined(XDOUBLE) || !defined(QUAD_PRECISION)

static __inline void compinv(FLOAT *b, FLOAT ar, FLOAT ai){

#ifndef UNIT
  FLOAT ratio, den;
      
  if (
#ifdef XDOUBLE
      (fabsl(ar)) >= (fabsl(ai))
#elif defined DOUBLE
      (fabs (ar)) >= (fabs (ai))
#else
      (fabsf(ar)) >= (fabsf(ai))
#endif
      ) {
    ratio = ai / ar;
    den   = (FLOAT)(ONE / (ar * (ONE + ratio * ratio)));
    ar =  den;
    ai = -ratio * den;
  } else {
    ratio = ar / ai;
    den   = (FLOAT)(ONE /(ai * (ONE + ratio * ratio)));
    ar =  ratio * den;
    ai = -den;
  }
  b[0] = ar;
  b[1] = ai;
#else
  b[0] = ONE;
  b[1] = ZERO;
#endif
  
}
#endif

#ifdef MALLOC_DEBUG
void *blas_debug_alloc(int);
void *blas_debug_free(void *);
#undef malloc
#undef free
#define malloc(a) blas_debug_alloc(a)
#define free(a)   blas_debug_free (a)
#endif

#ifndef COPYOVERHEAD
#define GEMMRETTYPE  int
#else

typedef struct {
  double outercopy;
  double innercopy;
  double kernel;
  double mflops;
} copyoverhead_t;

#define GEMMRETTYPE  copyoverhead_t
#endif
#endif

#ifndef BUILD_KERNEL
#define KNAME(A, B) A
#else
#define KNAME(A, B) A##B
#endif

#include "common_interface.h"
#ifdef SANITY_CHECK
#include "common_reference.h"
#endif
#include "common_macro.h"
#include "common_level1.h"
#include "common_level2.h"
#include "common_level3.h"
#include "common_lapack.h"
#ifdef CBLAS
#include "cblas.h"
#endif

#ifndef ASSEMBLER
#if 0
#include "symcopy.h"
#endif

#if defined(SMP_SERVER) && defined(SMP_ONDEMAND)
#error Both SMP_SERVER and SMP_ONDEMAND are specified.
#endif

#if defined(SMP_SERVER) || defined(SMP_ONDEMAND)
#include "common_thread.h"
#endif

#endif

#define INFO_NUM 99

#ifndef DEFAULT_CPU_NUMBER
#define DEFAULT_CPU_NUMBER 4
#endif

#ifndef IDEBUG_START
#define IDEBUG_START
#endif

#ifndef IDEBUG_END
#define IDEBUG_END
#endif

#if !defined(ASSEMBLER) && defined(FUNCTION_PROFILE)

typedef struct {
  int func;
  unsigned long long calls, fops, area, cycles, tcycles;
} func_profile_t;

extern func_profile_t function_profile_table[];
extern int gotoblas_profile;

#ifdef XDOUBLE
#define NUMOPT	QNUMOPT
#elif defined DOUBLE
#define NUMOPT	DNUMOPT
#else
#define NUMOPT	SNUMOPT
#endif

#define FUNCTION_PROFILE_START() { unsigned long long profile_start = rpcc(), profile_end;
#ifdef SMP
#define FUNCTION_PROFILE_END(COMP, AREA, OPS) \
	if (gotoblas_profile) { \
	profile_end = rpcc(); \
	function_profile_table[PROFILE_FUNC_NAME].calls ++; \
	function_profile_table[PROFILE_FUNC_NAME].area    += SIZE * COMPSIZE * (AREA); \
	function_profile_table[PROFILE_FUNC_NAME].fops    += (COMP) * (OPS) / NUMOPT; \
	function_profile_table[PROFILE_FUNC_NAME].cycles  += (profile_end - profile_start); \
	function_profile_table[PROFILE_FUNC_NAME].tcycles += blas_cpu_number * (profile_end - profile_start); \
	} \
	}
#else
#define FUNCTION_PROFILE_END(COMP, AREA, OPS) \
	if (gotoblas_profile) { \
	profile_end = rpcc(); \
	function_profile_table[PROFILE_FUNC_NAME].calls ++; \
	function_profile_table[PROFILE_FUNC_NAME].area    += SIZE * COMPSIZE * (AREA); \
	function_profile_table[PROFILE_FUNC_NAME].fops    += (COMP) * (OPS) / NUMOPT; \
	function_profile_table[PROFILE_FUNC_NAME].cycles  += (profile_end - profile_start); \
	function_profile_table[PROFILE_FUNC_NAME].tcycles += (profile_end - profile_start); \
	} \
	}
#endif

#else
#define FUNCTION_PROFILE_START()
#define FUNCTION_PROFILE_END(COMP, AREA, OPS)
#endif

#if 1
#define PRINT_DEBUG_CNAME
#define PRINT_DEBUG_NAME
#else
#define PRINT_DEBUG_CNAME if (readenv("GOTO_DEBUG")) fprintf(stderr, "GotoBLAS : %s\n", CHAR_CNAME)
#define PRINT_DEBUG_NAME  if (readenv("GOTO_DEBUG")) fprintf(stderr, "GotoBLAS : %s\n", CHAR_NAME)
#endif

#endif

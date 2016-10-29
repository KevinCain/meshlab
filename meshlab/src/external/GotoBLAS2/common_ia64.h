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

#ifndef COMMON_IA64
#define COMMON_IA64

#ifndef ASSEMBLER

#ifndef MAP_WRITECOMBINED
#define MAP_WRITECOMBINED 0x10000
#endif

#define MB
#define WMB

#ifdef __ECC
#include <ia64intrin.h>
#endif

#define RPCC64BIT

#ifndef __ECC
static __inline void blas_lock(volatile unsigned long *address){

  unsigned long ret;
  
  do {
    while (*address) {YIELDING;};
    
    __asm__ __volatile__ ("mov ar.ccv=r0\n;;\n"
			  "cmpxchg4.acq %0=[%2],%1,ar.ccv\n"
			  : "=r"(ret) : "r"(1), "r"(address)
			  : "ar.ccv", "memory");
  } while (ret);
}

static __inline unsigned long rpcc(void) {
  unsigned long clocks;

  __asm__ __volatile__ ("mov %0=ar.itc" : "=r"(clocks));
  return clocks;
}


static __inline unsigned long stmxcsr(void){
  unsigned long fp;

   __asm__ __volatile__ ("mov.m %0=ar.fpsr" : "=r" (fp));

   return fp;
}

static __inline void ldmxcsr(unsigned long fp) {

   __asm__ __volatile__ ("mov.m ar.fpsr=%0" :: "r" (fp));

}

#define GET_IMAGE(res) asm __volatile__("mov %0 = f9" : "=f"(res)  : : "memory")

#else

static __inline void blas_lock(volatile unsigned long *address){
  while (*address || _InterlockedCompareExchange((volatile int *) address,1,0))
    ;
}

static __inline unsigned int rpcc(void) {
  return __getReg(_IA64_REG_AR_ITC);
}

static __inline unsigned int stmxcsr(void) {
  return __getReg(_IA64_REG_AR_FPSR);
}

static __inline void ldmxcsr(unsigned long fp) {

  return __setReg(_IA64_REG_AR_FPSR, fp);

}

#ifdef DOUBLE
#define GET_IMAGE(res) __stfd(&res, 9)
#else
#define GET_IMAGE(res) __stfs(&res, 9)
#endif

#endif

#define GET_IMAGE_CANCEL

#ifdef ENABLE_SSE_EXCEPTION

#define IDEBUG_START \
  { \
    unsigned long fp_sse_mode, new_fp_mode; \
	fp_sse_mode = stmxcsr();\
	new_fp_mode = (fp_sse_mode & ~(FE_UNDERFLOW | FE_OVERFLOW | FE_UNNORMAL | FE_INVALID));\
	ldmxcsr(new_fp_mode);

#define IDEBUG_END \
	ldmxcsr(fp_sse_mode); \
	}

#endif

#ifdef SMP

#ifdef USE64BITINT

/* 64bit version */

extern unsigned long blas_quick_divide_table[];

#ifndef __ECC
static __inline long blas_quickdivide(unsigned long int x, unsigned long int y){
  unsigned long ret;

  if (y <= 1) return x;

  __asm__ __volatile__("setf.sig f6 = %1\n\t"
	       "ldf8     f7 = [%2];;\n\t"
	       "xmpy.hu f6= f6, f7;;\n\t"
	       "getf.sig %0 = f6;;\n"
	       : "=r"(ret)
	       : "r"(x), "r"(&blas_quick_divide_table[y]) : "f6", "f7"
	       );

  return ret;
}
#else
/* Using Intel Compiler */
static __inline long blas_quickdivide(unsigned long int x, unsigned long int y){
  if (y <= 1) return x;
  return _m64_xmahu(x, blas_quick_divide_table[y], 0);
}
#endif

#else
 /* 32bit version */
extern unsigned int  blas_quick_divide_table[];

static __inline int blas_quickdivide(unsigned int x, unsigned int y){
  if (y <= 1) return x;
  return (int)((x * (unsigned long)blas_quick_divide_table[y]) >> 32);
}
#endif
#endif

#endif

#if 0
#ifdef DOUBLE
#define   GEMM_NCOPY	dgemm_ncopy
#define   GEMM_TCOPY	dgemm_tcopy
#define  ZGEMM_NCOPY	zgemm_ncopy
#define  ZGEMM_TCOPY	zgemm_tcopy
#define   GEMM_KERNEL	dgemm_kernel

#if defined(NN) || defined(NT) || defined(TN) || defined(TT)
#define ZGEMM_KERNEL zgemm_kernel_n
#endif
#if defined(CN) || defined(CT) || defined(RN) || defined(RT)
#define ZGEMM_KERNEL zgemm_kernel_l
#endif
#if defined(NC) || defined(TC) || defined(NR) || defined(TR)
#define ZGEMM_KERNEL zgemm_kernel_r
#endif
#if defined(CC) || defined(CR) || defined(RC) || defined(RR)
#define ZGEMM_KERNEL zgemm_kernel_b
#endif

#else
#define   GEMM_NCOPY	sgemm_ncopy
#define   GEMM_TCOPY	sgemm_tcopy
#define  ZGEMM_NCOPY	cgemm_ncopy
#define  ZGEMM_TCOPY	cgemm_tcopy
#define   GEMM_KERNEL	sgemm_kernel

#if defined(NN) || defined(NT) || defined(TN) || defined(TT)
#define ZGEMM_KERNEL cgemm_kernel_n
#endif
#if defined(CN) || defined(CT) || defined(RN) || defined(RT)
#define ZGEMM_KERNEL cgemm_kernel_l
#endif
#if defined(NC) || defined(TC) || defined(NR) || defined(TR)
#define ZGEMM_KERNEL cgemm_kernel_r
#endif
#if defined(CC) || defined(CR) || defined(RC) || defined(RR)
#define ZGEMM_KERNEL cgemm_kernel_b
#endif

#endif
#endif

#ifdef USE64BITINT
#define LDINT		ld8
#define INTSIZE		8
#define CMP4GE		cmp.ge
#define CMP4NE		cmp.ge
#define CMP4EQ		cmp.eq
#else
#define LDINT		ld4
#define INTSIZE		4
#define CMP4GE		cmp4.ge
#define CMP4NE		cmp4.ne
#define CMP4EQ		cmp4.eq
#endif

#define HALT		mov r0 = 0

#ifdef XDOUBLE
#define LD8		ld8
#define ST8		st8
#define LDFD		ldfe
#define LDFPD		ldfpe
#define LDFD_T1		ldfe.t1
#define LDFD_NT1	ldfe.nt1
#define LDFD_NT2	ldfe.nt2
#define LDFD_NTA	ldfe.nta
#define LDFPD_NT1	ldfpe.nt1
#define LDFPD_NT2	ldfpe.nt2
#define LDFPD_NTA	ldfpe.nta
#define STFD		stfe
#define STFD_NTA	stfe.nta
#define FADD		fadd
#define FSUB		fsub
#define FMPY		fmpy
#define FMA		fma
#define FMS		fms
#define FNMA		fnma
#define FPMA		fpma
#define SETF		setf.d
#elif defined(DOUBLE)
#define LD8		ld8
#define ST8		st8
#define LDF8		ldf8
#define LDF8_NT1	ldf8.nt1
#define LDF8_NTA	ldf8.nta
#define STF8		stf8
#define STF8_NTA	stf8.nta
#define LDFD		ldfd
#define LDFPD		ldfpd
#define LDFD_T1		ldfd.t1
#define LDFD_NT1	ldfd.nt1
#define LDFD_NT2	ldfd.nt2
#define LDFD_NTA	ldfd.nta
#define LDFPD_NT1	ldfpd.nt1
#define LDFPD_NT2	ldfpd.nt2
#define LDFPD_NTA	ldfpd.nta
#define STFD		stfd
#define STFD_NTA	stfd.nta
#define FADD		fadd.d
#define FSUB		fsub.d
#define FMPY		fmpy.d
#define FMA		fma.d
#define FMS		fms.d
#define FNMA		fnma.d
#define FPMA		fpma.d
#define SETF		setf.d
#else
#define LD8		ld4
#define ST8		st4
#define LDF8		ldfs
#define LDF8_NT1	ldfs.nt1
#define LDF8_NTA	ldfs.nta
#define STF8		stfs
#define STF8_NTA	stfs.nta
#define LDFD		ldfs
#define LDFPD		ldfps
#define LDFD_T1		ldfs.t1
#define LDFD_NT1	ldfs.nt1
#define LDFD_NT2	ldfs.nt2
#define LDFD_NTA	ldfs.nta
#define LDFPD_NT1	ldfps.nt1
#define LDFPD_NT2	ldfps.nt2
#define LDFPD_NTA	ldfps.nta
#define STFD		stfs
#define STFD_NTA	stfs.nta
#if 0
#define FADD		fadd.s
#define FSUB		fsub.s
#define FMPY		fmpy.s
#define FMA		fma.s
#define FMS		fms.s
#define FNMA		fnma.s
#define FPMA		fpma.s
#else
#define FADD		fadd
#define FSUB		fsub
#define FMPY		fmpy
#define FMA		fma
#define FMS		fms
#define FNMA		fnma
#define FPMA		fpma
#endif
#define SETF		setf.s
#endif

#ifndef F_INTERFACE
#define REALNAME ASMNAME
#else
#define REALNAME ASMFNAME
#endif

#ifdef F_INTERFACE_G77
#define RETURN_BY_STACK
#endif

#ifdef F_INTERFACE_G95
#define RETURN_BY_STACK
#endif

#ifdef F_INTERFACE_GFORT
#define RETURN_BY_REGS
#endif

#ifdef F_INTERFACE_INTEL
#define RETURN_BY_STACK
#endif

#define PROLOGUE \
	.explicit; \
	.text; \
	.align 128; \
	.global REALNAME; \
	.proc REALNAME; \
REALNAME:


#ifdef PROFILE
#define PROFCODE \
	.data; \
	.align 8; \
.LP0:; \
	data8	0; \
	.text; \
	alloc	out0 = ar.pfs, 8, 0, 4, 0; \
	mov	out1 = r1; \
	mov	out2 = b0; \
	addl	out3 = @ltoff(.LP0), r1;;; \
	br.call.sptk.many b0 = _mcount;;
#else
#define PROFCODE
#endif

#define EPILOGUE \
	.endp REALNAME

#define START_ADDRESS 0x20000fc800000000UL

#undef SEEK_ADDRESS

#if 0
#ifdef CONFIG_IA64_PAGE_SIZE_4KB
#define SEEK_ADDRESS
#endif

#ifdef CONFIG_IA64_PAGE_SIZE_8KB
#define SEEK_ADDRESS
#endif
#endif

#define BUFFER_SIZE	(128 << 20)

#ifndef PAGESIZE
#define PAGESIZE	(16UL << 10)
#endif
#define HUGE_PAGESIZE	(  4 << 20)

#define BASE_ADDRESS (START_ADDRESS - (BLASULONG)BUFFER_SIZE * MAX_CPU_NUMBER)

#endif

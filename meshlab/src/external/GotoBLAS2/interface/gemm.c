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

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#ifdef FUNCTION_PROFILE
#include "functable.h"
#endif

#ifndef COMPLEX
#ifdef XDOUBLE
#define ERROR_NAME "QGEMM "
#elif defined(DOUBLE)
#define ERROR_NAME "DGEMM "
#else
#define ERROR_NAME "SGEMM "
#endif
#else
#ifndef GEMM3M
#ifdef XDOUBLE
#define ERROR_NAME "XGEMM "
#elif defined(DOUBLE)
#define ERROR_NAME "ZGEMM "
#else
#define ERROR_NAME "CGEMM "
#endif
#else
#ifdef XDOUBLE
#define ERROR_NAME "XGEMM3M "
#elif defined(DOUBLE)
#define ERROR_NAME "ZGEMM3M "
#else
#define ERROR_NAME "CGEMM3M "
#endif
#endif
#endif

static int (*gemm[])(blas_arg_t *, BLASLONG *, BLASLONG *, FLOAT *, FLOAT *, BLASLONG) = {
#ifndef GEMM3M
  GEMM_NN, GEMM_TN, GEMM_RN, GEMM_CN,
  GEMM_NT, GEMM_TT, GEMM_RT, GEMM_CT,
  GEMM_NR, GEMM_TR, GEMM_RR, GEMM_CR,
  GEMM_NC, GEMM_TC, GEMM_RC, GEMM_CC,
#if defined(SMP) && !defined(USE_SIMPLE_THREADED_LEVEL3)
  GEMM_THREAD_NN, GEMM_THREAD_TN, GEMM_THREAD_RN, GEMM_THREAD_CN,
  GEMM_THREAD_NT, GEMM_THREAD_TT, GEMM_THREAD_RT, GEMM_THREAD_CT,
  GEMM_THREAD_NR, GEMM_THREAD_TR, GEMM_THREAD_RR, GEMM_THREAD_CR,
  GEMM_THREAD_NC, GEMM_THREAD_TC, GEMM_THREAD_RC, GEMM_THREAD_CC,
#endif
#else
  GEMM3M_NN, GEMM3M_TN, GEMM3M_RN, GEMM3M_CN,
  GEMM3M_NT, GEMM3M_TT, GEMM3M_RT, GEMM3M_CT,
  GEMM3M_NR, GEMM3M_TR, GEMM3M_RR, GEMM3M_CR,
  GEMM3M_NC, GEMM3M_TC, GEMM3M_RC, GEMM3M_CC,
#if defined(SMP) && !defined(USE_SIMPLE_THREADED_LEVEL3)
  GEMM3M_THREAD_NN, GEMM3M_THREAD_TN, GEMM3M_THREAD_RN, GEMM3M_THREAD_CN,
  GEMM3M_THREAD_NT, GEMM3M_THREAD_TT, GEMM3M_THREAD_RT, GEMM3M_THREAD_CT,
  GEMM3M_THREAD_NR, GEMM3M_THREAD_TR, GEMM3M_THREAD_RR, GEMM3M_THREAD_CR,
  GEMM3M_THREAD_NC, GEMM3M_THREAD_TC, GEMM3M_THREAD_RC, GEMM3M_THREAD_CC,
#endif
#endif
};

#ifndef CBLAS

void NAME(char *TRANSA, char *TRANSB,
	  blasint *M, blasint *N, blasint *K,
	  FLOAT *alpha,
	  FLOAT *a, blasint *ldA,
	  FLOAT *b, blasint *ldB,
	  FLOAT *beta,
	  FLOAT *c, blasint *ldC){
  
  blas_arg_t args;

  int transa, transb, nrowa, nrowb;
  blasint info;

  char transA, transB;
  FLOAT *buffer;
  FLOAT *sa, *sb;

#ifdef SMP
#ifndef COMPLEX
#ifdef XDOUBLE
  int mode  =  BLAS_XDOUBLE | BLAS_REAL;
#elif defined(DOUBLE)
  int mode  =  BLAS_DOUBLE  | BLAS_REAL;
#else
  int mode  =  BLAS_SINGLE  | BLAS_REAL;
#endif  
#else
#ifdef XDOUBLE
  int mode  =  BLAS_XDOUBLE | BLAS_COMPLEX;
#elif defined(DOUBLE)
  int mode  =  BLAS_DOUBLE  | BLAS_COMPLEX;
#else
  int mode  =  BLAS_SINGLE  | BLAS_COMPLEX;
#endif  
#endif
#endif

#if defined(SMP) && !defined(NO_AFFINITY) && !defined(USE_SIMPLE_THREADED_LEVEL3)
  int nodes;
#endif

  PRINT_DEBUG_NAME;

  args.m = *M;
  args.n = *N;
  args.k = *K;

  args.a = (void *)a;
  args.b = (void *)b;
  args.c = (void *)c;

  args.lda = *ldA;
  args.ldb = *ldB;
  args.ldc = *ldC;

  args.alpha = (void *)alpha;
  args.beta  = (void *)beta;

  transA = *TRANSA;
  transB = *TRANSB;

  TOUPPER(transA);
  TOUPPER(transB);

  transa = -1;
  transb = -1;

  if (transA == 'N') transa = 0;
  if (transA == 'T') transa = 1;
#ifndef COMPLEX
  if (transA == 'R') transa = 0;
  if (transA == 'C') transa = 1;
#else
  if (transA == 'R') transa = 2;
  if (transA == 'C') transa = 3;
#endif

  if (transB == 'N') transb = 0;
  if (transB == 'T') transb = 1;
#ifndef COMPLEX
  if (transB == 'R') transb = 0;
  if (transB == 'C') transb = 1;
#else
  if (transB == 'R') transb = 2;
  if (transB == 'C') transb = 3;
#endif

  nrowa = args.m;
  if (transa & 1) nrowa = args.k;
  nrowb = args.k;
  if (transb & 1) nrowb = args.n;

  info = 0;

  if (args.ldc < args.m) info = 13;
  if (args.ldb < nrowb)  info = 10;
  if (args.lda < nrowa)  info =  8; 
  if (args.k < 0)        info =  5;
  if (args.n < 0)        info =  4;
  if (args.m < 0)        info =  3;
  if (transb < 0)        info =  2;
  if (transa < 0)        info =  1;

  if (info){
    BLASFUNC(xerbla)(ERROR_NAME, &info, sizeof(ERROR_NAME));
    return;
  }

#else

void CNAME(enum CBLAS_ORDER order, enum CBLAS_TRANSPOSE TransA, enum CBLAS_TRANSPOSE TransB,
	   blasint m, blasint n, blasint k,
#ifndef COMPLEX
	   FLOAT alpha,
#else
	   FLOAT *alpha,
#endif
	   FLOAT *a, blasint lda,
	   FLOAT *b, blasint ldb, 
#ifndef COMPLEX
	   FLOAT beta,
#else
	   FLOAT *beta,
#endif
	   FLOAT *c, blasint ldc) {

  blas_arg_t args;
  int transa, transb;
  blasint nrowa, nrowb, info;

  XFLOAT *buffer;
  XFLOAT *sa, *sb;

#ifdef SMP
#ifndef COMPLEX
#ifdef XDOUBLE
  int mode  =  BLAS_XDOUBLE | BLAS_REAL;
#elif defined(DOUBLE)
  int mode  =  BLAS_DOUBLE  | BLAS_REAL;
#else
  int mode  =  BLAS_SINGLE  | BLAS_REAL;
#endif  
#else
#ifdef XDOUBLE
  int mode  =  BLAS_XDOUBLE | BLAS_COMPLEX;
#elif defined(DOUBLE)
  int mode  =  BLAS_DOUBLE  | BLAS_COMPLEX;
#else
  int mode  =  BLAS_SINGLE  | BLAS_COMPLEX;
#endif  
#endif
#endif

#if defined(SMP) && !defined(NO_AFFINITY) && !defined(USE_SIMPLE_THREADED_LEVEL3)
  int nodes;
#endif

  PRINT_DEBUG_CNAME;

#ifndef COMPLEX
  args.alpha = (void *)&alpha;
  args.beta  = (void *)&beta;
#else
  args.alpha = (void *)alpha;
  args.beta  = (void *)beta;
#endif

  transa = -1;
  transb = -1;
  info   =  0;

  if (order == CblasColMajor) {
    args.m = m;
    args.n = n;
    args.k = k;
    
    args.a = (void *)a;
    args.b = (void *)b;
    args.c = (void *)c;
    
    args.lda = lda;
    args.ldb = ldb;
    args.ldc = ldc;
    
    if (TransA == CblasNoTrans)     transa = 0;
    if (TransA == CblasTrans)       transa = 1;
#ifndef COMPLEX
    if (TransA == CblasConjNoTrans) transa = 0;
    if (TransA == CblasConjTrans)   transa = 1;
#else
    if (TransA == CblasConjNoTrans) transa = 2;
    if (TransA == CblasConjTrans)   transa = 3;
#endif
    if (TransB == CblasNoTrans)     transb = 0;
    if (TransB == CblasTrans)       transb = 1;
#ifndef COMPLEX
    if (TransB == CblasConjNoTrans) transb = 0;
    if (TransB == CblasConjTrans)   transb = 1;
#else
    if (TransB == CblasConjNoTrans) transb = 2;
    if (TransB == CblasConjTrans)   transb = 3;
#endif
    
    nrowa = args.m;
    if (transa & 1) nrowa = args.k;
    nrowb = args.k;
    if (transb & 1) nrowb = args.n;

    info = -1;

    if (args.ldc < args.m) info = 13;
    if (args.ldb < nrowb)  info = 10;
    if (args.lda < nrowa)  info =  8; 
    if (args.k < 0)        info =  5;
    if (args.n < 0)        info =  4;
    if (args.m < 0)        info =  3;
    if (transb < 0)        info =  2;
    if (transa < 0)        info =  1;
  }

  if (order == CblasRowMajor) {
    args.m = n;
    args.n = m;
    args.k = k;
    
    args.a = (void *)b;
    args.b = (void *)a;
    args.c = (void *)c;
    
    args.lda = ldb;
    args.ldb = lda;
    args.ldc = ldc;

    if (TransB == CblasNoTrans)     transa = 0;
    if (TransB == CblasTrans)       transa = 1;
#ifndef COMPLEX
    if (TransB == CblasConjNoTrans) transa = 0;
    if (TransB == CblasConjTrans)   transa = 1;
#else
    if (TransB == CblasConjNoTrans) transa = 2;
    if (TransB == CblasConjTrans)   transa = 3;
#endif
    if (TransA == CblasNoTrans)     transb = 0;
    if (TransA == CblasTrans)       transb = 1;
#ifndef COMPLEX
    if (TransA == CblasConjNoTrans) transb = 0;
    if (TransA == CblasConjTrans)   transb = 1;
#else
    if (TransA == CblasConjNoTrans) transb = 2;
    if (TransA == CblasConjTrans)   transb = 3;
#endif
    
    nrowa = args.m;
    if (transa & 1) nrowa = args.k;
    nrowb = args.k;
    if (transb & 1) nrowb = args.n;

    info = -1;

    if (args.ldc < args.m) info = 13;
    if (args.ldb < nrowb)  info = 10;
    if (args.lda < nrowa)  info =  8; 
    if (args.k < 0)        info =  5;
    if (args.n < 0)        info =  4;
    if (args.m < 0)        info =  3;
    if (transb < 0)        info =  2;
    if (transa < 0)        info =  1;

  }

  if (info >= 0) {
    BLASFUNC(xerbla)(ERROR_NAME, &info, sizeof(ERROR_NAME));
    return;
  }

#endif

  if ((args.m == 0) || (args.n == 0)) return;

#if 0
  fprintf(stderr, "m = %4d  n = %d  k = %d  lda = %4d  ldb = %4d  ldc = %4d\n",
	 args.m, args.n, args.k, args.lda, args.ldb, args.ldc);
#endif

  IDEBUG_START;

  FUNCTION_PROFILE_START();

  buffer = (XFLOAT *)blas_memory_alloc(0);
  
  sa = (XFLOAT *)((BLASLONG)buffer +GEMM_OFFSET_A);
  sb = (XFLOAT *)(((BLASLONG)sa + ((GEMM_P * GEMM_Q * COMPSIZE * SIZE + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
  
#ifdef SMP
  mode |= (transa << BLAS_TRANSA_SHIFT);
  mode |= (transb << BLAS_TRANSB_SHIFT);

  args.common = NULL;
  args.nthreads = num_cpu_avail(3);

 if (args.nthreads == 1) {
#endif
    
    (gemm[(transb << 2) | transa])(&args, NULL, NULL, sa, sb, 0);
    
#ifdef SMP
    
  } else {
    
#ifndef USE_SIMPLE_THREADED_LEVEL3

#ifndef NO_AFFINITY
      nodes = get_num_nodes();
      
      if ((nodes > 1) && get_node_equal()) {
	
	args.nthreads /= nodes;
	
	gemm_thread_mn(mode, &args, NULL, NULL, gemm[16 | (transb << 2) | transa], sa, sb, nodes);
	
      } else {
#endif

	(gemm[16 | (transb << 2) | transa])(&args, NULL, NULL, sa, sb, 0);

#else

	GEMM_THREAD(mode, &args, NULL, NULL, gemm[(transb << 2) | transa], sa, sb, args.nthreads);
	
#endif
	
#ifndef USE_SIMPLE_THREADED_LEVEL3
#ifndef NO_AFFINITY
      }
#endif
#endif
    
#endif
    
#ifdef SMP
  }
#endif
  
 blas_memory_free(buffer);

  FUNCTION_PROFILE_END(COMPSIZE * COMPSIZE, args.m * args.k + args.k * args.n + args.m * args.n, 2 * args.m * args.n * args.k);

  IDEBUG_END;

  return;
}

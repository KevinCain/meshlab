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
#include "common.h"
#ifdef FUNCTION_PROFILE
#include "functable.h"
#endif

#ifndef CBLAS

void NAME(blasint *N, FLOAT *ALPHA, FLOAT *x, blasint *INCX){
  
  blasint n    = *N;
  blasint incx = *INCX;

#ifndef SSCAL
  FLOAT *alpha=ALPHA;
#else
  FLOAT alpha[2] = {ALPHA[0], ZERO};
#endif

#else

#ifndef SSCAL
void CNAME(blasint n, FLOAT *ALPHA, FLOAT *x, blasint incx){

  FLOAT *alpha=ALPHA;
#else
void CNAME(blasint n, FLOAT alpha_r, FLOAT *x, blasint incx){

  FLOAT alpha[2] = {alpha_r, ZERO};
#endif
#endif

#ifdef SMP
  int mode;
  int nthreads;
#endif

#ifndef CBLAS
  PRINT_DEBUG_NAME;
#else
  PRINT_DEBUG_CNAME;
#endif

  if (incx <= 0 || n <= 0) return;

  if ((alpha[0] == ONE) && (alpha[1] == ZERO)) return;

  IDEBUG_START;

  FUNCTION_PROFILE_START();

#ifdef SMP
  nthreads = num_cpu_avail(1);

  if (nthreads == 1) {
#endif

  SCAL_K(n, 0, 0, alpha[0], alpha[1], x, incx, NULL, 0, NULL, 0);

#ifdef SMP
  } else {
#ifdef DOUBLE
    mode  =  BLAS_DOUBLE | BLAS_COMPLEX;
#else
    mode  =  BLAS_SINGLE | BLAS_COMPLEX;
#endif  
    
    blas_level1_thread(mode, n, 0, 0,  alpha, x, incx, NULL, 0, NULL, 0, (void *)SCAL_K, nthreads);

  }
#endif

  FUNCTION_PROFILE_END(4, n, n);

  IDEBUG_END;

  return;
  
}

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
#include <ctype.h>
#include "common.h"

const static FLOAT dm1 = -1.;

#ifdef CONJ
#define GEMM_KERNEL   GEMM_KERNEL_R
#if (!defined(TRANSA) && defined(UPPER)) || (defined(TRANSA) && !defined(UPPER))
#define TRSM_KERNEL   TRSM_KERNEL_RR
#else
#define TRSM_KERNEL   TRSM_KERNEL_RC
#endif
#else
#define GEMM_KERNEL   GEMM_KERNEL_N
#if (!defined(TRANSA) && defined(UPPER)) || (defined(TRANSA) && !defined(UPPER))
#define TRSM_KERNEL   TRSM_KERNEL_RN
#else
#define TRSM_KERNEL   TRSM_KERNEL_RT
#endif
#endif

#if 0
#undef GEMM_P
#undef GEMM_Q
#undef GEMM_R

#define GEMM_P 16
#define GEMM_Q 20
#define GEMM_R 24
#endif

int CNAME(blas_arg_t *args, BLASLONG *range_m, BLASLONG *range_n, FLOAT *sa, FLOAT *sb, BLASLONG dummy) {

  BLASLONG m, n, lda, ldb;
  FLOAT *beta, *a, *b;
  BLASLONG ls, is, js;
  BLASLONG min_l, min_i, min_j;
  BLASLONG jjs, min_jj;

  m = args -> m;
  n = args -> n;

  a = (FLOAT *)args -> a;
  b = (FLOAT *)args -> b;

  lda = args -> lda;
  ldb = args -> ldb;

  beta  = (FLOAT *)args -> beta;

  if (range_m) {
    BLASLONG m_from = *(((BLASLONG *)range_m) + 0);
    BLASLONG m_to   = *(((BLASLONG *)range_m) + 1);

    m = m_to - m_from;

    b += m_from * COMPSIZE;
  }

  if (beta) {
#ifndef COMPLEX
    if (beta[0] != ONE)
      GEMM_BETA(m, n, 0, beta[0], NULL, 0, NULL, 0, b, ldb);
    if (beta[0] == ZERO) return 0;
#else
    if ((beta[0] != ONE) || (beta[1] != ZERO))
      GEMM_BETA(m, n, 0, beta[0], beta[1], NULL, 0, NULL, 0, b, ldb);
    if ((beta[0] == ZERO) && (beta[1] == ZERO)) return 0;
#endif
  }

#if (defined(UPPER) && !defined(TRANSA)) || (!defined(UPPER) && defined(TRANSA))
  for(js = 0; js < n; js += GEMM_R){
    min_j = n - js;
    if (min_j > GEMM_R) min_j = GEMM_R;
    
    for(ls = 0; ls < js; ls += GEMM_Q){
      min_l = js - ls;
      if (min_l > GEMM_Q) min_l = GEMM_Q;
      min_i = m;
      if (min_i > GEMM_P) min_i = GEMM_P;
     
      GEMM_ITCOPY(min_l, min_i, b + (ls * ldb) * COMPSIZE, ldb, sa);
      
      for(jjs = js; jjs < js + min_j; jjs += min_jj){
	min_jj = min_j + js - jjs;
	if (min_jj > GEMM_UNROLL_N) min_jj = GEMM_UNROLL_N;

#ifndef TRANSA
	GEMM_ONCOPY(min_l, min_jj, a + (ls + jjs * lda) * COMPSIZE, lda, sb + min_l * (jjs - js) * COMPSIZE);
#else
	GEMM_OTCOPY(min_l, min_jj, a + (jjs + ls * lda) * COMPSIZE, lda, sb + min_l * (jjs - js) * COMPSIZE);
#endif

	GEMM_KERNEL(min_i, min_jj, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, sb + min_l * (jjs - js) * COMPSIZE,
		    b + (jjs * ldb) * COMPSIZE, ldb); 
      }

      for(is = min_i; is < m; is += GEMM_P){
	min_i = m - is;
	if (min_i > GEMM_P) min_i = GEMM_P;
	
	GEMM_ITCOPY(min_l, min_i, b + (is + ls * ldb) * COMPSIZE, ldb, sa);
	
	GEMM_KERNEL(min_i, min_j, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, sb, b + (is + js * ldb) * COMPSIZE, ldb); 
      }
    }

    for(ls = js; ls < js + min_j; ls += GEMM_Q){
      min_l = js + min_j - ls;
      if (min_l > GEMM_Q) min_l = GEMM_Q;
      min_i = m;
      if (min_i > GEMM_P) min_i = GEMM_P;

      GEMM_ITCOPY(min_l, min_i, b + (ls * ldb) * COMPSIZE, ldb, sa);
      
#ifndef TRANSA
      TRSM_OUNCOPY(min_l, min_l, a + (ls + ls * lda) * COMPSIZE, lda, 0, sb);
#else
      TRSM_OLTCOPY(min_l, min_l, a + (ls + ls * lda) * COMPSIZE, lda, 0, sb);
#endif
      
      TRSM_KERNEL(min_i, min_l, min_l, dm1,
#ifdef COMPLEX
		  ZERO,
#endif
		  sa,
		  sb, 
		  b + (ls * ldb) * COMPSIZE, ldb, 0);
      
      for(jjs = 0; jjs < min_j - min_l - ls + js; jjs += min_jj){
	min_jj = min_j - min_l - ls + js - jjs;
	if (min_jj > GEMM_UNROLL_N) min_jj = GEMM_UNROLL_N;
	
#ifndef TRANSA
      GEMM_ONCOPY (min_l, min_jj, a + (ls + (ls + min_l + jjs) * lda) * COMPSIZE, lda,
		   sb + min_l * (min_l + jjs) * COMPSIZE);
#else
      GEMM_OTCOPY (min_l, min_jj, a + ((ls + min_l + jjs) + ls * lda) * COMPSIZE, lda,
		   sb + min_l * (min_l + jjs) * COMPSIZE);
#endif

      GEMM_KERNEL(min_i, min_jj, min_l, dm1, 
#ifdef COMPLEX
		  ZERO,
#endif
		  sa, 
		  sb + min_l * (min_l + jjs) * COMPSIZE,
		  b + (min_l + ls + jjs) * ldb * COMPSIZE, ldb); 
      }

      for(is = min_i; is < m; is += GEMM_P){
	min_i = m - is;
	if (min_i > GEMM_P) min_i = GEMM_P;
	
	GEMM_ITCOPY(min_l, min_i, b + (is + ls * ldb) * COMPSIZE, ldb, sa);
	
	TRSM_KERNEL(min_i, min_l, min_l, dm1,
#ifdef COMPLEX
		    ZERO,
#endif
		    sa,
		    sb, 
		    b + (is + ls * ldb) * COMPSIZE, ldb, 0);
	
	GEMM_KERNEL(min_i, min_j - min_l + js - ls, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, 
		    sb + min_l * min_l * COMPSIZE,
		    b + (is + ( min_l + ls) * ldb) * COMPSIZE, ldb); 
      }
    }
  }

#else
  BLASLONG start_ls;

  for(js = n; js > 0; js -= GEMM_R){
    min_j = js;
    if (min_j > GEMM_R) min_j = GEMM_R;

    for (ls = js; ls < n; ls += GEMM_Q) {
      min_l = n - ls;
      if (min_l > GEMM_Q) min_l = GEMM_Q;
      min_i = m;
      if (min_i > GEMM_P) min_i = GEMM_P;

      GEMM_ITCOPY(min_l, min_i, b + (ls * ldb) * COMPSIZE, ldb, sa);
      
      for(jjs = js; jjs < js + min_j; jjs += min_jj){
	min_jj = min_j + js - jjs;
	if (min_jj > GEMM_UNROLL_N) min_jj = GEMM_UNROLL_N;
	
#ifndef TRANSA
	GEMM_ONCOPY(min_l, min_jj, a + (ls + (jjs - min_j) * lda) * COMPSIZE, lda, sb + min_l * (jjs - js) * COMPSIZE);
#else
	GEMM_OTCOPY(min_l, min_jj, a + ((jjs - min_j) + ls * lda) * COMPSIZE, lda, sb + min_l * (jjs - js) * COMPSIZE);
#endif

	GEMM_KERNEL(min_i, min_jj, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, sb + min_l * (jjs - js) * COMPSIZE,
		    b + (jjs - min_j) * ldb * COMPSIZE, ldb); 
      }

      for(is = min_i; is < m; is += GEMM_P){
	min_i = m - is;
	if (min_i > GEMM_P) min_i = GEMM_P;
	
	GEMM_ITCOPY(min_l, min_i, b + (is + ls * ldb) * COMPSIZE, ldb, sa);
	
	GEMM_KERNEL(min_i, min_j, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, sb, b + (is + (js - min_j) * ldb) * COMPSIZE, ldb); 
      }
    }

    start_ls = js - min_j;
    while (start_ls + GEMM_Q < js) start_ls += GEMM_Q;
    
    for(ls = start_ls; ls >= js - min_j; ls -= GEMM_Q){
      min_l = js - ls;
      if (min_l > GEMM_Q) min_l = GEMM_Q;
      min_i = m;
      if (min_i > GEMM_P) min_i = GEMM_P;
      
      GEMM_ITCOPY(min_l, min_i, b + (ls * ldb) * COMPSIZE, ldb, sa);

#ifndef TRANSA
      TRSM_OLNCOPY(min_l, min_l,           a + (ls + ls * lda) * COMPSIZE, lda,
		   0, sb + min_l * (min_j - js + ls) * COMPSIZE);
#else
      TRSM_OUTCOPY(min_l, min_l,           a + (ls + ls * lda) * COMPSIZE, lda,
		   0, sb + min_l * (min_j - js + ls) * COMPSIZE);
#endif
      
      TRSM_KERNEL(min_i, min_l, min_l, dm1,
#ifdef COMPLEX
		  ZERO,
#endif
		  sa,
		  sb + min_l * (min_j - js + ls) * COMPSIZE, 
		  b + (ls * ldb) * COMPSIZE, ldb, 0);
      
      for(jjs = 0; jjs < min_j - js + ls; jjs += min_jj){
	min_jj = min_j - js + ls - jjs;
	if (min_jj > GEMM_UNROLL_N) min_jj = GEMM_UNROLL_N;
	
#ifndef TRANSA
	GEMM_ONCOPY (min_l, min_jj, a + (ls + (js - min_j + jjs) * lda) * COMPSIZE, lda,
		     sb + min_l * jjs * COMPSIZE);
#else
	GEMM_OTCOPY (min_l, min_jj, a + ((js - min_j + jjs) + ls * lda) * COMPSIZE, lda, 
		     sb + min_l * jjs * COMPSIZE);
#endif
	
	GEMM_KERNEL(min_i, min_jj, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, 
		    sb + min_l * jjs * COMPSIZE,
		    b + (js - min_j + jjs) * ldb * COMPSIZE, ldb); 
      }

      for(is = min_i; is < m; is += GEMM_P){
	min_i = m - is;
	if (min_i > GEMM_P) min_i = GEMM_P;
	
	GEMM_ITCOPY(min_l, min_i, b + (is + ls * ldb) * COMPSIZE, ldb, sa);
	
	TRSM_KERNEL(min_i, min_l, min_l, dm1,
#ifdef COMPLEX
		    ZERO,
#endif
		    sa,
		    sb + min_l * (min_j - js + ls) * COMPSIZE, 
		    b + (is + ls * ldb) * COMPSIZE, ldb, 0);
	
	GEMM_KERNEL(min_i, min_j - js + ls, min_l, dm1, 
#ifdef COMPLEX
		    ZERO,
#endif
		    sa, 
		    sb,
		    b + (is + (js - min_j) * ldb) * COMPSIZE, ldb); 
      }

    }
  }
  
#endif
     
  return 0;
}

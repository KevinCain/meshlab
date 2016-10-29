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

int CNAME(BLASLONG m, BLASLONG n, FLOAT *a, BLASLONG lda, FLOAT *b){

  BLASLONG i, j;

  FLOAT *a_offset, *a_offset1, *a_offset2, *a_offset3, *a_offset4;
  FLOAT *b_offset, *b_offset1, *b_offset2, *b_offset3;
  FLOAT  ctemp1,  ctemp2,  ctemp3,  ctemp4;
  FLOAT  ctemp5,  ctemp6,  ctemp7,  ctemp8;
  FLOAT  ctemp9, ctemp10, ctemp11, ctemp12;
  FLOAT ctemp13, ctemp14, ctemp15, ctemp16;

  a_offset   = a;
  b_offset   = b;

  b_offset2  = b + m  * (n & ~3);
  b_offset3  = b + m  * (n & ~1);

  j = (m >> 2);
  if (j > 0){
    do{
      a_offset1  = a_offset;
      a_offset2  = a_offset1 + lda;
      a_offset3  = a_offset2 + lda;
      a_offset4  = a_offset3 + lda;
      a_offset  += 4 * lda;
      
      b_offset1  = b_offset;
      b_offset  += 16;

      i = (n >> 2);
      if (i > 0){
	do{
	  ctemp1  = *(a_offset1 + 0);
	  ctemp2  = *(a_offset1 + 1);
	  ctemp3  = *(a_offset1 + 2);
	  ctemp4  = *(a_offset1 + 3);
	  
	  ctemp5  = *(a_offset2 + 0);
	  ctemp6  = *(a_offset2 + 1);
	  ctemp7  = *(a_offset2 + 2);
	  ctemp8  = *(a_offset2 + 3);
	  
	  ctemp9  = *(a_offset3 + 0);
	  ctemp10 = *(a_offset3 + 1);
	  ctemp11 = *(a_offset3 + 2);
	  ctemp12 = *(a_offset3 + 3);
	  
	  ctemp13 = *(a_offset4 + 0);
	  ctemp14 = *(a_offset4 + 1);
	  ctemp15 = *(a_offset4 + 2);
	  ctemp16 = *(a_offset4 + 3);

	  a_offset1 += 4;
	  a_offset2 += 4;
	  a_offset3 += 4;
	  a_offset4 += 4;
	
	  *(b_offset1 +  0) = ctemp1;
	  *(b_offset1 +  1) = ctemp2;
	  *(b_offset1 +  2) = ctemp3;
	  *(b_offset1 +  3) = ctemp4;
	
	  *(b_offset1 +  4) = ctemp5;
	  *(b_offset1 +  5) = ctemp6;
	  *(b_offset1 +  6) = ctemp7;
	  *(b_offset1 +  7) = ctemp8;
	  
	  *(b_offset1 +  8) = ctemp9;
	  *(b_offset1 +  9) = ctemp10;
	  *(b_offset1 + 10) = ctemp11;
	  *(b_offset1 + 11) = ctemp12;
	  
	  *(b_offset1 + 12) = ctemp13;
	  *(b_offset1 + 13) = ctemp14;
	  *(b_offset1 + 14) = ctemp15;
	  *(b_offset1 + 15) = ctemp16;
	  
	  b_offset1 += m * 4;
	  i --;
	}while(i > 0);
      }

      if (n & 2) {
	ctemp1  = *(a_offset1 + 0);
	ctemp2  = *(a_offset1 + 1);

	ctemp3  = *(a_offset2 + 0);
	ctemp4  = *(a_offset2 + 1);
	
	ctemp5  = *(a_offset3 + 0);
	ctemp6  = *(a_offset3 + 1);
	
	ctemp7  = *(a_offset4 + 0);
	ctemp8  = *(a_offset4 + 1);
	
	a_offset1 += 2;
	a_offset2 += 2;
	a_offset3 += 2;
	a_offset4 += 2;
	
	*(b_offset2 +  0) = ctemp1;
	*(b_offset2 +  1) = ctemp2;
	*(b_offset2 +  2) = ctemp3;
	*(b_offset2 +  3) = ctemp4;
	
	*(b_offset2 +  4) = ctemp5;
	*(b_offset2 +  5) = ctemp6;
	*(b_offset2 +  6) = ctemp7;
	*(b_offset2 +  7) = ctemp8;
	
	b_offset2 += 8;
      }

      if (n & 1) {
	ctemp1  = *(a_offset1 + 0);
	ctemp2  = *(a_offset2 + 0);
	ctemp3  = *(a_offset3 + 0);
	ctemp4  = *(a_offset4 + 0);
	
	*(b_offset3 +  0) = ctemp1;
	*(b_offset3 +  1) = ctemp2;
	*(b_offset3 +  2) = ctemp3;
	*(b_offset3 +  3) = ctemp4;
	
	b_offset3 += 4;
      }

      j--;
    }while(j > 0);
  }

  if (m & 2){
    a_offset1  = a_offset;
    a_offset2  = a_offset1 + lda;
    a_offset  += 2 * lda;
    
    b_offset1  = b_offset;
    b_offset  += 8;
    
    i = (n >> 2);
    if (i > 0){
      do{
	ctemp1  = *(a_offset1 + 0);
	ctemp2  = *(a_offset1 + 1);
	ctemp3  = *(a_offset1 + 2);
	ctemp4  = *(a_offset1 + 3);
	
	ctemp5  = *(a_offset2 + 0);
	ctemp6  = *(a_offset2 + 1);
	ctemp7  = *(a_offset2 + 2);
	ctemp8  = *(a_offset2 + 3);
	
	a_offset1 += 4;
	a_offset2 += 4;
	
	*(b_offset1 +  0) = ctemp1;
	*(b_offset1 +  1) = ctemp2;
	*(b_offset1 +  2) = ctemp3;
	*(b_offset1 +  3) = ctemp4;
	
	*(b_offset1 +  4) = ctemp5;
	*(b_offset1 +  5) = ctemp6;
	*(b_offset1 +  6) = ctemp7;
	*(b_offset1 +  7) = ctemp8;

	b_offset1 += m * 4;
	i --;
      }while(i > 0);
    }

    if (n & 2) {
      ctemp1  = *(a_offset1 + 0);
      ctemp2  = *(a_offset1 + 1);
      
      ctemp3  = *(a_offset2 + 0);
      ctemp4  = *(a_offset2 + 1);
      
      a_offset1 += 2;
      a_offset2 += 2;
      
      *(b_offset2 +  0) = ctemp1;
      *(b_offset2 +  1) = ctemp2;
      *(b_offset2 +  2) = ctemp3;
      *(b_offset2 +  3) = ctemp4;
      
      b_offset2 += 4;
    }
    
    if (n & 1) {
      ctemp1  = *(a_offset1 + 0);
      ctemp2  = *(a_offset2 + 0);
      
      *(b_offset3 +  0) = ctemp1;
      *(b_offset3 +  1) = ctemp2;
      b_offset3 += 2;
    }
  }

  if (m & 1){
    a_offset1  = a_offset;
    b_offset1  = b_offset;
    
    i = (n >> 2);
    if (i > 0){
      do{
	ctemp1  = *(a_offset1 + 0);
	ctemp2  = *(a_offset1 + 1);
	ctemp3  = *(a_offset1 + 2);
	ctemp4  = *(a_offset1 + 3);
	
	a_offset1 += 4;
	
	*(b_offset1 +  0) = ctemp1;
	*(b_offset1 +  1) = ctemp2;
	*(b_offset1 +  2) = ctemp3;
	*(b_offset1 +  3) = ctemp4;

	b_offset1 += 4 * m;

	i --;
      }while(i > 0);
    }

    if (n & 2) {
      ctemp1  = *(a_offset1 + 0);
      ctemp2  = *(a_offset1 + 1);
      a_offset1 += 2;
      
      *(b_offset2 +  0) = ctemp1;
      *(b_offset2 +  1) = ctemp2;
    }
    
    if (n & 1) {
      ctemp1  = *(a_offset1 + 0);
      *(b_offset3 +  0) = ctemp1;
    }
  }

  return 0;
}

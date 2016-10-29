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

int CNAME(BLASLONG m, BLASLONG n, FLOAT *a, BLASLONG lda, BLASLONG posX, BLASLONG posY, FLOAT *b){

  BLASLONG i, js;
  BLASLONG X;

  FLOAT data1, data2, data3, data4, data5, data6, data7, data8;

  FLOAT *ao1, *ao2;

  lda += lda;

  js = (n >> 1);

  if (js > 0){
    do {
      X = posX;

      if (posX <= posY) {
	ao1 = a + posY * 2 + (posX + 0) * lda;
	ao2 = a + posY * 2 + (posX + 1) * lda;
      } else {
	ao1 = a + posX * 2 + (posY + 0) * lda;
	ao2 = a + posX * 2 + (posY + 1) * lda;
      }

      i = (m >> 1);
      if (i > 0) {
	do {
	  if (X > posY) {
	    ao1 += 4;
	    ao2 += 4;
	    b += 8;

	  } else 
	    if (X < posY) {
	      data1 = *(ao1 + 0);
	      data2 = *(ao1 + 1);
	      data3 = *(ao1 + 2);
	      data4 = *(ao1 + 3);
	      
	      data5 = *(ao2 + 0);
	      data6 = *(ao2 + 1);
	      data7 = *(ao2 + 2);
	      data8 = *(ao2 + 3);
	      
	      b[ 0] = data1;
	      b[ 1] = data2;
	      b[ 2] = data3;
	      b[ 3] = data4;
	      b[ 4] = data5;
	      b[ 5] = data6;
	      b[ 6] = data7;
	      b[ 7] = data8;
	      
	      ao1 += 2 * lda;
	      ao2 += 2 * lda;
	      b += 8;

	    } else {
#ifdef UNIT
	      data3 = *(ao1 + 2);
	      data4 = *(ao1 + 3);
 
	      b[ 0] = ONE;
	      b[ 1] = ZERO;
	      b[ 2] = data3;
	      b[ 3] = data4;
	      b[ 4] = ZERO;
	      b[ 5] = ZERO;
	      b[ 6] = ONE;
	      b[ 7] = ZERO;
#else
	      data1 = *(ao1 + 0);
	      data2 = *(ao1 + 1);
	      data3 = *(ao1 + 2);
	      data4 = *(ao1 + 3);
	      
	      data7 = *(ao2 + 2);
	      data8 = *(ao2 + 3);
 
	      b[ 0] = data1;
	      b[ 1] = data2;
	      b[ 2] = data3;
	      b[ 3] = data4;
	      b[ 4] = ZERO;
	      b[ 5] = ZERO;
	      b[ 6] = data7;
	      b[ 7] = data8;
#endif	      
	      ao1 += 4;
	      ao2 += 4;
	      b += 8;
	    }

	  X += 2;
	  i --;
	} while (i > 0);
      }

      if (m & 1) {
      
	if (X > posY) {
	  ao1 += 2;
	  ao2 += 2;
	  b += 4;
	  
	} else 
	  if (X < posY) {
	    data1 = *(ao1 + 0);
	    data2 = *(ao1 + 1);
	    data3 = *(ao1 + 2);
	    data4 = *(ao1 + 3);
	    
	    b[ 0] = data1;
	    b[ 1] = data2;
	    b[ 2] = data3;
	    b[ 3] = data4;

	    ao1 += lda;
	    b += 4;
	  } else {
#ifdef UNIT
	    data3 = *(ao1 + 2);
	    data4 = *(ao1 + 3);

	    b[ 0] = ONE;
	    b[ 1] = ZERO;
	    b[ 2] = data3;
	    b[ 3] = data4;
#else
	    data1 = *(ao1 + 0);
	    data2 = *(ao1 + 1);
	    data3 = *(ao1 + 2);
	    data4 = *(ao1 + 3);

	    b[ 0] = data1;
	    b[ 1] = data2;
	    b[ 2] = data3;
	    b[ 3] = data4;
#endif
	    b += 4;
	  }
      }

      posY += 2;
      js --;
    } while (js > 0);
  } /* End of main loop */


  if (n & 1){
      X = posX;

      if (posX <= posY) {
	ao1 = a + posY * 2 + (posX + 0) * lda;
      } else {
	ao1 = a + posX * 2 + (posY + 0) * lda;
      }

      i = m;
      if (i > 0) {
	do {
	  if (X > posY) {
	    b += 2;
	    ao1 += 2;
	  } else
	    if (X < posY) {
	      data1 = *(ao1 + 0);
	      data2 = *(ao1 + 1);
	      
	      b[ 0] = data1;
	      b[ 1] = data2;
	      b += 2;
	      ao1 += lda;
	    } else {
#ifdef UNIT
	      b[ 0] = ONE;
	      b[ 1] = ZERO;
#else
	      data1 = *(ao1 + 0);
	      data2 = *(ao1 + 1);
	      
	      b[ 0] = data1;
	      b[ 1] = data2;
#endif
	      b += 2;
	      ao1 += 2;
	    }

	  X ++;
	  i --;
	} while (i > 0);
      }

      posY += 1;
  }

  return 0;
}

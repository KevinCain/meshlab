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

#ifndef MINUS
#define a2	(a1 + 1)
#define a4	(a3 + 1)
#define a6	(a5 + 1)
#define a8	(a7 + 1)
#else
#define a2	(a1 - 1)
#define a4	(a3 - 1)
#define a6	(a5 - 1)
#define a8	(a7 - 1)
#endif

int CNAME(BLASLONG n, BLASLONG k1, BLASLONG k2, FLOAT dummy1, FLOAT *a, BLASLONG lda, 
	 FLOAT *dummy2, BLASLONG dumy3, blasint *ipiv, BLASLONG incx){

  BLASLONG i, j, ip1, ip2;
  blasint *piv;
  FLOAT *a1, *a3, *a5, *a7;
  FLOAT *b1, *b2, *b3, *b4;
  FLOAT *b5, *b6, *b7, *b8;
  FLOAT A1, A2, B1, B2, A3, A4, B3, B4;
  FLOAT A5, A6, B5, B6, A7, A8, B7, B8;
  
  a--;
  k1 --;

#ifndef MINUS
 ipiv += k1
;
#else
  ipiv -= (k2 - 1) * incx;
#endif

  if (n  <= 0) return 0;

  j = (n >> 2);
  if (j > 0) {
    do {
      piv = ipiv;

#ifndef MINUS
      a1 = a + k1 + 1;
#else
      a1 = a + k2;
#endif
      
      a3 = a1 + 1 * lda;
      a5 = a1 + 2 * lda;
      a7 = a1 + 3 * lda;

      ip1 = *piv;
      piv += incx;
      ip2 = *piv;
      piv += incx;
      
      b1 = a + ip1;
      b2 = a + ip2;
	  
      b3 = b1 + 1 * lda;
      b4 = b2 + 1 * lda;
      b5 = b1 + 2 * lda;
      b6 = b2 + 2 * lda;
      b7 = b1 + 3 * lda;
      b8 = b2 + 3 * lda;

      i = ((k2 - k1) >> 1);
      
      if (i > 0) {
	do {
	  A1 = *a1;
	  A2 = *a2;
	  A3 = *a3;
	  A4 = *a4;
	  A5 = *a5;
	  A6 = *a6;
	  A7 = *a7;
	  A8 = *a8;

	  B1 = *b1;
	  B2 = *b2;
	  B3 = *b3;
	  B4 = *b4;
	  B5 = *b5;
	  B6 = *b6;
	  B7 = *b7;
	  B8 = *b8;
	  
	  ip1 = *piv;
	  piv += incx;
	  ip2 = *piv;
	  piv += incx;
	  
	if (b1 == a1) {
	  if (b2 == a1) {
	    *a1 = A2;
	    *a2 = A1;
	    *a3 = A4;
	    *a4 = A3;
	    *a5 = A6;
	    *a6 = A5;
	    *a7 = A8;
	    *a8 = A7;
	  } else 
	    if (b2 != a2) {
	      *a2 = B2;
	      *b2 = A2;
	      *a4 = B4;
	      *b4 = A4;
	      *a6 = B6;
	      *b6 = A6;
	      *a8 = B8;
	      *b8 = A8;
	    }
	} else 
	  if (b1 == a2) {
	    if (b2 != a1) {
	      if (b2 == a2) {
		*a1 = A2;
		*a2 = A1;
		*a3 = A4;
		*a4 = A3;
		*a5 = A6;
		*a6 = A5;
		*a7 = A8;
		*a8 = A7;
	      } else {
		*a1 = A2;
		*a2 = B2;
		*b2 = A1;
		*a3 = A4;
		*a4 = B4;
		*b4 = A3;
		*a5 = A6;
		*a6 = B6;
		*b6 = A5;
		*a7 = A8;
		*a8 = B8;
		*b8 = A7;
	      }
	    }
	  } else {
	    if (b2 == a1) {
	      *a1 = A2;
	      *a2 = B1;
	      *b1 = A1;
	      *a3 = A4;
	      *a4 = B3;
	      *b3 = A3;
	      *a5 = A6;
	      *a6 = B5;
	      *b5 = A5;
	      *a7 = A8;
	      *a8 = B7;
	      *b7 = A7;
	    } else 
	      if (b2 == a2) {
		*a1 = B1;
		*b1 = A1;
		*a3 = B3;
		*b3 = A3;
		*a5 = B5;
		*b5 = A5;
		*a7 = B7;
		*b7 = A7;
	      } else 
		if (b2 == b1) {
		  *a1 = B1;
		  *a2 = A1;
		  *b1 = A2;
		  *a3 = B3;
		  *a4 = A3;
		  *b3 = A4;
		  *a5 = B5;
		  *a6 = A5;
		  *b5 = A6;
		  *a7 = B7;
		  *a8 = A7;
		  *b7 = A8;
		} else {
		  *a1 = B1;
		  *a2 = B2;
		  *b1 = A1;
		  *b2 = A2;
		  *a3 = B3;
		  *a4 = B4;
		  *b3 = A3;
		  *b4 = A4;
		  *a5 = B5;
		  *a6 = B6;
		  *b5 = A5;
		  *b6 = A6;
		  *a7 = B7;
		  *a8 = B8;
		  *b7 = A7;
		  *b8 = A8;
		}
	  }
	
	  b1 = a + ip1;
	  b2 = a + ip2;
	  
	  b3 = b1 + 1 * lda;
	  b4 = b2 + 1 * lda;
	  b5 = b1 + 2 * lda;
	  b6 = b2 + 2 * lda;
	  b7 = b1 + 3 * lda;
	  b8 = b2 + 3 * lda;
	  
#ifndef MINUS
	  a1 += 2;
	  a3 += 2;
	  a5 += 2;
	  a7 += 2;
#else
	  a1 -= 2;
	  a3 -= 2;
	  a5 -= 2;
	  a7 -= 2;
#endif
	i --;
	} while (i > 0);
      }
      
      i = ((k2 - k1) & 1);
      
      if (i > 0) {
	A1 = *a1;
	B1 = *b1;
	A3 = *a3;
	B3 = *b3;
	A5 = *a5;
	B5 = *b5;
	A7 = *a7;
	B7 = *b7;

	*a1 = B1;
	*b1 = A1;
	*a3 = B3;
	*b3 = A3;
	*a5 = B5;
	*b5 = A5;
	*a7 = B7;
	*b7 = A7;
      }
      
      a += 4 * lda;
      
      j --;
    } while (j > 0);
  }

  if (n & 2) {
    piv = ipiv;

#ifndef MINUS
    a1 = a + k1 + 1;
#else
    a1 = a + k2;
#endif
      
    a3 = a1 + 1 * lda;

    ip1 = *piv;
    piv += incx;
    ip2 = *piv;
    piv += incx;
    
    b1 = a + ip1;
    b2 = a + ip2;
    
    b3 = b1 + 1 * lda;
    b4 = b2 + 1 * lda;
    
    i = ((k2 - k1) >> 1);
    
    if (i > 0) {
      do {
	A1 = *a1;
	A2 = *a2;
	A3 = *a3;
	A4 = *a4;
	
	B1 = *b1;
	B2 = *b2;
	B3 = *b3;
	B4 = *b4;
	
	ip1 = *piv;
	piv += incx;
	ip2 = *piv;
	piv += incx;
	
	if (b1 == a1) {
	  if (b2 == a1) {
	    *a1 = A2;
	    *a2 = A1;
	    *a3 = A4;
	    *a4 = A3;
	  } else 
	    if (b2 != a2) {
	      *a2 = B2;
	      *b2 = A2;
	      *a4 = B4;
	      *b4 = A4;
	    }
	} else 
	  if (b1 == a2) {
	    if (b2 != a1) {
	      if (b2 == a2) {
		*a1 = A2;
		*a2 = A1;
		*a3 = A4;
		*a4 = A3;
	      } else {
		*a1 = A2;
		*a2 = B2;
		*b2 = A1;
		*a3 = A4;
		*a4 = B4;
		*b4 = A3;
	      }
	    }
	  } else {
	    if (b2 == a1) {
	      *a1 = A2;
	      *a2 = B1;
	      *b1 = A1;
	      *a3 = A4;
	      *a4 = B3;
	      *b3 = A3;
	    } else 
	      if (b2 == a2) {
		*a1 = B1;
		*b1 = A1;
		*a3 = B3;
		*b3 = A3;
	      } else 
		if (b2 == b1) {
		  *a1 = B1;
		  *a2 = A1;
		  *b1 = A2;
		  *a3 = B3;
		  *a4 = A3;
		  *b3 = A4;
		} else {
		  *a1 = B1;
		  *a2 = B2;
		  *b1 = A1;
		  *b2 = A2;
		  *a3 = B3;
		  *a4 = B4;
		  *b3 = A3;
		  *b4 = A4;
		}
	  }
	
	b1 = a + ip1;
	b2 = a + ip2;
	
	b3 = b1 + 1 * lda;
	b4 = b2 + 1 * lda;
	
#ifndef MINUS
	a1 += 2;
	a3 += 2;
#else
	a1 -= 2;
	a3 -= 2;
#endif
	i --;
      } while (i > 0);
    }
    
    i = ((k2 - k1) & 1);
    
    if (i > 0) {
      A1 = *a1;
      B1 = *b1;
      A3 = *a3;
      B3 = *b3;
      *a1 = B1;
      *b1 = A1;
      *a3 = B3;
      *b3 = A3;
    }
    
    a += 2 * lda;
  }

  if (n & 1) {
    piv = ipiv;

#ifndef MINUS
    a1 = a + k1 + 1;
#else
    a1 = a + k2;
#endif
    
    ip1 = *piv;
    piv += incx;
    ip2 = *piv;
    piv += incx;
    
    b1 = a + ip1;
    b2 = a + ip2;
    
    i = ((k2 - k1) >> 1);
    
    if (i > 0) {
      do {
	A1 = *a1;
	A2 = *a2;
	B1 = *b1;
	B2 = *b2;
	
	ip1 = *piv;
	piv += incx;
	ip2 = *piv;
	piv += incx;
	
	if (b1 == a1) {
	  if (b2 == a1) {
	    *a1 = A2;
	    *a2 = A1;
	  } else 
	    if (b2 != a2) {
	      *a2 = B2;
	      *b2 = A2;
	    }
	} else 
	  if (b1 == a2) {
	    if (b2 != a1) {
	      if (b2 == a2) {
		*a1 = A2;
		*a2 = A1;
	      } else {
		*a1 = A2;
		*a2 = B2;
		*b2 = A1;
	      }
	    }
	  } else {
	    if (b2 == a1) {
	      *a1 = A2;
	      *a2 = B1;
	      *b1 = A1;
	    } else 
	      if (b2 == a2) {
		*a1 = B1;
		*b1 = A1;
	      } else 
		if (b2 == b1) {
		  *a1 = B1;
		  *a2 = A1;
		  *b1 = A2;
		} else {
		  *a1 = B1;
		  *a2 = B2;
		  *b1 = A1;
		  *b2 = A2;
		}
	  }
	
	b1 = a + ip1;
	b2 = a + ip2;
	
#ifndef MINUS
	a1 += 2;
#else
	a1 -= 2;
#endif
	i --;
      } while (i > 0);
    }
    
    i = ((k2 - k1) & 1);
    
    if (i > 0) {
      A1 = *a1;
      B1 = *b1;
      *a1 = B1;
      *b1 = A1;
    }
  }

  return 0;
} 


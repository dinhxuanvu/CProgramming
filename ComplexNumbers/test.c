/********************************************************************
 ** COMPLEX module test
 **
 ** Licensing: This code is distributed under the GNU LGPL license.  
 ** Modified: 06 November 2010 , 09 September 2014 (JC)
 ** Author: John Burkardt (modified and adapted by J.C. Cockburn)
 **
 *********************************************************************/
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# include "complex.h"

/* variables for timing */
clock_t CPUstart, CPUstop, CPUelapsed;

/** function prototypes **/
void test01 ( void );
void test03 ( void );

/************************************************************************/
int main ( void )
{
  printf ( "\n" );
  printf ( "Test of complex arithmetic module -- ANSI C89 version\n" );
  printf ( "Uses custom \"complex.h\" .\n" );
/*
  Single precision complex numbers: "complex".
*/
  CPUstart = clock();
  test01 ( );
  CPUstop = clock();
  
  test03 ( );

  printf ( "\n" );
  printf ( "Test concluded\n" );

  return 0; /* 0 means everything good */
}
/******************************************************************************/

/******************************************************************************
 **
 ** test01 - demonstrates declaration and assignment of complex variables.
 **
 ** Licensing: This code is distributed under the GNU LGPL license.
 ** Modified: 06 November 2010
 ** Author: John Burkardt
 ******************************************************************************/
void test01 ( void )
{
 complex a;
 complex b[3];
 complex c[2][2];
  int i,j;  /* temporary counters */

  printf ( "\n" );
  printf ( "test01: complex declarations and assignments\n" );
/*
  Assign values to A, B, and C.
*/
   a = Complex(1.0,2.0);

  b[0] = Complex(1.0,2.0);
  b[1] = Complex(3.0,4.0);
  b[2] = Complex(5.0,6.0);

  c[0][0] = Complex(1.0,0.1);
  c[0][1] = Complex(1.0,0.2);
  c[1][0] = Complex(2.0,0.1);
  c[1][1] = Complex(2.0,0.2);

/*
  output results to stdio
*/
  printf ( "\n  Scalar a:\n" );
  printf ( "  %g %+g i\n", a.r, a.i);

  printf ( "\n  Vector B:\n" );
  for ( i = 0; i < 3; i++ )  {
    printf ( " [ %g %+g i ] \n", b[i].r, b[i].i );
  }

  printf ( "\n  Array C:\n" );
  for ( i = 0; i < 2; i++ )  {
    printf ( "[" );
    for ( j = 0; j < 2; j++ )  {
      printf ( "  %g %+g i ", c[i][j].r, c[i][j].i );
    }
    printf ( "]\n" );
  }

  return;
}
/******************************************************************************/

/******************************************************************************
 **
 ** test03 - intrinsic functions for complex variables.
 **
 ** Licensing: This code is distributed under the GNU LGPL license.
 ** Modified: 05 November 2010
 ** Author: John Burkardt
 ******************************************************************************/
void test03 ( void )
{
  complex z,a = Complex(1.0,2.0);

  printf ( "test03: Operations on Complex Numbers\n" );
  printf ( "\n" );
  
  printf ("      a  = %4.6g %+4.6g i\n",a.r,a.i );
  printf ( "** Complex Numbers Manipulations:\n" );    
  printf (" cabs(a) = %4.6g\n",Cabs(a) );
  printf (" carg(a) = %4.6g\n",Carg(a) );
  printf (" creal(a) = %4.6g\n",Creal(a) );
  printf (" cimag(a) = %4.6g\n",Cimag(a) );
  z=Cconj(a);
  printf (" conj(a) = %4.6g %+4.6g i\n",z.r,z.i );
  
  printf ( "** Complex Arithmetic:\n" );    
  printf ("      a  = %4.6g %+4.6g i\n",a.r,a.i );
  z=Cadd( a, Complex(3,0));
  printf ("  a + 3  = %4.6g %+4.6g i\n",z.r,z.i );
  z=Cadd( a, Complex(0,5));
  printf ("  a + 5i = %4.6g %+4.6g i\n",z.r,z.i );
  z=Rmul( a , 4.0);
  printf ("  4 * a  = %4.6g %+4.6g i\n",z.r,z.i );
  z=Rdiv( a , 3.0);
  printf ("  a / 3 = %4.6g %+4.6g i\n",z.r,z.i );
  z=Cdiv( a, Complex(8,0));
  printf ("  a / 8  = %4.6g %+4.6g i\n",z.r,z.i );
  z=Cmul( a, a);
  printf ("  a * a  = %4.6g %+4.6g i\n",z.r,z.i );
  z=Cdiv( Complex(1,0),a);
  printf ("  1/a    = %4.6g %+4.6g i\n",z.r,z.i );
  
  printf ( "** Complex Functions:\n" );      
  z=Csqrt(a);
  printf ("csqrt(a) = %4.6g %+4.6g i\n",z.r,z.i );
  z=Cpow(a,3);
  printf ("cpow(a,3) = %4.6g %+4.6g i\n",z.r,z.i );
  
  return;
}

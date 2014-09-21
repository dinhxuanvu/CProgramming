/**
 ** COMPLEX.H
 ** Header for complex arithmetic module COMPLEX.C
 ** Uses double precision arithmetic (C doubles)
 **/

#ifndef _COMPLEX1_H_
#define _COMPLEX1_H_

/** libraries **/
#include <math.h>

/** constants **/
#define EPS 2.2E-16

/** complex "data type" typemark **/
typedef struct {
   double r;  /*real part*/
   double i;  /*imaginary part*/
} complex;

/** function prototypes **/

/* manipulation and creation of complex numbers */
complex Complex(double re, double im);/*create a complex number */
double Creal(complex z); 	      /* real part */
double Cimag(complex z); 	      /* imaginary part */
double Cabs(complex z); 	      /* magnitude */
double Carg(complex z); 	      /* angle or argument - radians */
complex Cconj(complex z); 	    /* conjugate */
/* arithmetic operation */
complex Cadd(complex a, complex b); /* add      */
complex Csub(complex a, complex b); /* subtract */
complex Cmul(complex a, complex b); /* multiply */
complex Cdiv(complex a, complex b); /* divide   */
complex Rmul(complex a, double x);   /* complex * real */
complex Rdiv(complex a, double x);   /* complex / real */

/* mathematical functions */
complex Cpow(complex z, int n);     /* n^th power  */
complex Csqrt(complex z);           /* square root */

#endif

/********************************************************************
 ** Complex Number Module
 **
 ** The program contains multiple functions to create or manilpulate
 ** complex numbers. In addition, the program is able to perform
 ** arithmetic operations and mathematical functions for complex
 ** numbers.
 **
 ** Author: Vu Dinh (vxd9797)
 ** Date: September 12 2014
 **
 *********************************************************************/
#include <math.h>
#include <stdlib.h>
#include "complex.h"

/* Manipulation and creation of complex numbers */

/*
 * Create a complex number
 */
complex Complex(double re, double im)
{
    complex cnumber;
    cnumber.r = re;
    cnumber.i = im;
    return cnumber;
}

/* 
 * Get real part of a complex number
 */
double Creal(complex z)
{
    double real;
    real = z.r;
    return real;
}

/* 
 * Get imaginary part of a complex number
 */
double Cimag(complex z)
{
    double imaginary;
    imaginary = z.i;
    return imaginary;
}

/*
 * Calculate magnitude of a complex number
 * Formula: Sqrt((real^2) + (imaginary^2))
 */
double Cabs(complex z)
{
    double magnitude;
    magnitude = sqrt(pow(z.r,2) + pow(z.i,2));
    return magnitude;
}

/* 
 * Calculate angle or argument of a complex number in radians
 * Formula: arctangent(real,imaginary)
 */
double Carg(complex z)
{
    double arg;
    arg = atan2(z.i,z.r);
    return arg;
}

/* 
 * Calculate conjugate of a complex number
 */
complex Cconj(complex z)
{
    complex c1;
    c1.r = z.r;
    c1.i = -z.i;
    return c1;
}

/* Arithmetic operation */

/* 
 * Add 2 complex numbers
 */
complex Cadd(complex a, complex b)
{
    complex c2;
    c2.r = a.r + b.r;
    c2.i = a.i + b.i;
    return c2;
}

/* 
 * Subtract 2 complex numbers
 */
complex Csub(complex a, complex b)
{
    complex c3;
    c3.r = a.r - b.r;
    c3.i = a.i - b.i;
    return c3;
}

/* 
 * Muliply 2 complex numbers 
 */
complex Cmul(complex a, complex b)
{
    complex c4;
    c4.r = (a.r*b.r) - (a.i*b.i);
    c4.i = (a.r*b.i) + (a.r*b.i);
    return c4;
}

/* 
 * Divide 2 complex numbers 
 */
complex Cdiv(complex a, complex b)
{
    complex c5;
    /* Real part calculation */
    c5.r = ((a.r*b.r) + (a.i*b.i))/(pow(b.r,2) + pow(b.i,2));
    /* Imaginary part calculation */
    c5.i = ((a.i*b.r) - (a.r*b.i))/(pow(b.r,2) + pow(b.i,2));
    return c5;
}

/* 
 * Multiply a complex number with a real number
 */
complex Rmul(complex a, double x)
{
    complex c6;
    c6.r = x*a.r;
    c6.i = x*a.i;
    return c6;
}

/*
 * Divide a complex number to a real number
 */
complex Rdiv(complex a, double x)
{
    complex c7;
    c7.r = (1/x)*a.r;
    c7.i = (1/x)*a.i;
    return c7;
}

/* Mathematical functions */

/* 
 * Calculate the n^th power of a complex number
 *
 * Used functions:
 * Cabs - Calculate absolute value of complex number
 * Carg - Calculate argument of complex number
 */
complex Cpow(complex z, int n)
{
    complex c8;
    c8.r = (pow(Cabs(z),n)) * (cos(n*Carg(z)));
    c8.i = (pow(Cabs(z),n)) * (sin(n*Carg(z)));
    return c8;
}

/* 
 * Calculate square root of a complex number
 */
complex Csqrt(complex z)
{
    complex c9;
    /* Imaginary part is zero (0) */
    if (z.i == 0) {
        /* If real part is larger or equal to zero */
        if (z.r >= 0) {
            c9.r = sqrt(z.r);
            c9.i = 0.0;
            return c9;
        }
        /* If real part is negative */
        else {
            c9.r = 0.0;
            c9.i = sqrt(abs(z.i));
            return c9;
        }
    }
    /* Imaginary part is NOT zero (0) */
    else {
        c9.r = (1/sqrt(2))*sqrt(sqrt(pow(z.r,2)+pow(z.i,2))+z.r);
        /* Imaginary part is positive */
        if (z.i > 0) {
            c9.i = (1/sqrt(2))*sqrt(sqrt(pow(z.r,2)+pow(z.i,2))-z.r);
        }
        /* Imaginary part is negative */
        else {
            c9.i = ((-1)/sqrt(2))*sqrt(sqrt(pow(z.r,2)+pow(z.i,2))-z.r);
        }
        return c9;
    }
}
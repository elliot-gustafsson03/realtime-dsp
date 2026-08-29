#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <complex.h>

void convolution(float *sigA, float *sigB, float *result, int lenA, int lenB);

void fft(double complex *buf, int n);

void ifft(double complex *buf, int n);

#endif
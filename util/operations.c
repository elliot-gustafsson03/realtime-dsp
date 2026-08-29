#include <complex.h>
#include "operations.h"
#include "../constants.h"

void fft(double complex *buf, int n)
{
    if (n <= 1)
    {
        return;
    }

    double complex even[n / 2];
    double complex odd[n / 2];
    for (int i = 0; i < n / 2; i++)
    {
        even[i] = buf[2 * i];
        odd[i] = buf[2 * i + 1];
    }

    fft(even, n / 2);
    fft(odd, n / 2);

    for (int k = 0; k < n / 2; k++)
    {
        double complex t = cexp(-2.0 * I * PI * k / n) * odd[k];
        buf[k] = even[k] + t;
        buf[k + n / 2] = even[k] - t;
    }
}

void ifft(double complex *buf, int n)
{
    for (int i = 0; i < n; i++)
    {
        buf[i] = conj(buf[i]);
    }

    fft(buf, n);

    for (int i = 0; i < n; i++)
    {
        buf[i] = conj(buf[i]) / n;
    }
}

void convolution(float *sigA, float *sigB, float *result, int lenA, int lenB)
{
    int resultLen = lenA + lenB - 1;
    for (int i = 0; i < resultLen; i++)
    {
        for (int j = 0; j < lenB; j++)
        {
            if (i - j >= 0 && i - j < lenA)
            {
                result[i] += sigA[i - j] * sigB[j];
            }
        }
    }
}
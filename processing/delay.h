#ifndef DELAY_H
#define DELAY_H

typedef struct
{
    float A;
    int d;
    int N;
    float *buffer;
} DelayState;

DelayState *delay_create(float A, float t, int N);

void delay_process(void *state, const float *in, float *out, unsigned long nSamples);

void delay_destroy(DelayState *state);

#endif

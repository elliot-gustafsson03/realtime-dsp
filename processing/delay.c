#include <stdlib.h>
#include <math.h>
#include "delay.h"
#include "../constants.h"

DelayState *delay_create(float A, float t, int N)
{
    DelayState *state = (DelayState *)malloc(sizeof(DelayState));
    if (state)
    {
        state->A = A;
        state->d = (int)(SAMPLE_RATE * t);
        state->N = N;
        state->buffer = malloc(sizeof(float) * state->d * state->N);
        for (int i = 0; i < state->d * state->N; i++)
        {
            state->buffer[i] = 0.0f;
        }
    }

    return state;
}

void delay_process(void *state, const float *in, float *out, unsigned long nSamples)
{
    DelayState *s = (DelayState *)state;
    int total_size = s->d * s->N;

    for (int i = 0; i < total_size - nSamples; i++)
    {
        s->buffer[i] = s->buffer[i + nSamples];
    }

    for (int i = 0; i < nSamples; i++)
    {
        s->buffer[total_size - nSamples + i] = in[i];
    }

    for (int n = 0; n < nSamples; n++)
    {
        out[n] = in[n];

        for (int i = 1; i <= s->N; i++)
        {
            int delay_amount = s->d * i;
            int read_index = total_size - nSamples + n - delay_amount;

            if (read_index >= 0)
            {
                out[n] += pow(s->A, i) * s->buffer[read_index];
            }
        }
    }
}

void delay_destroy(DelayState *state)
{
    free(state->buffer);
    free(state);
}
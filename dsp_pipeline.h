#ifndef DSP_PIPELINE_H
#define DSP_PIPELINE_H

typedef void (*ProcessFunc)(void *state, const float *in, float *out, unsigned long nSamples);

typedef struct
{
    void *state;
    ProcessFunc process;
} EffectNode;

#endif

#ifndef TREMOLO_H
#define TREMOLO_H

typedef struct
{
    float a;
    float c;
    float deltaPhi;
    float phi;
} TremoloState;

TremoloState *tremolo_create(float depth, float frequency, float sample_rate);

void tremolo_process(void *state, const float *in, float *out, unsigned long nSamples);

void tremolo_destroy(TremoloState *state);

#endif

#include <stdlib.h>
#include <math.h>
#include "tremolo.h"
#include "../constants.h"

TremoloState *tremolo_create(float depth, float frequency, float sample_rate)
{
    TremoloState *t = (TremoloState *)malloc(sizeof(TremoloState));
    if (t)
    {
        t->a = depth / 2.0f;
        t->c = 1.0f - (depth / 2.0f);
        t->deltaPhi = 2.0f * PI * frequency / sample_rate;
        t->phi = 0.0f;
    }
    return t;
}

void tremolo_process(void *state, const float *in, float *out, unsigned long nSamples)
{
    TremoloState *t = (TremoloState *)state;

    for (unsigned long i = 0; i < nSamples; i++)
    {
        float lfo = t->a * sinf(t->phi) + t->c;

        out[i] = in[i] * lfo;

        t->phi += t->deltaPhi;
        if (t->phi > 2.0f * PI)
        {
            t->phi -= 2.0f * PI;
        }
    }
}

void tremolo_destroy(TremoloState *state)
{
    free(state);
}

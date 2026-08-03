#include "processor.h"

void process_audio_chain(EffectNode *pipeline, int num_effects,
                         const float *in, float *out, unsigned long nSamples)
{
    // Bypass if no effects
    if (num_effects == 0)
    {

        for (unsigned long i = 0; i < nSamples; i++)
        {
            out[i] = in[i];
        }
        return;
    }

    pipeline[0].process(pipeline[0].state, in, out, nSamples);

    for (int i = 1; i < num_effects; i++)
    {
        pipeline[i].process(pipeline[i].state, out, out, nSamples);
    }
}

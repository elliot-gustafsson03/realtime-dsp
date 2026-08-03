#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../dsp_pipeline.h"

void process_audio_chain(EffectNode *pipeline, int num_effects,
                         const float *in, float *out, unsigned long nSamples);

#endif

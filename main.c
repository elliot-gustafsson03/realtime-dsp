#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <portaudio.h>

#include "constants.h"
#include "dsp_pipeline.h"
#include "processing/processor.h"
#include "processing/tremolo.h"
#include "processing/delay.h"

typedef struct
{
    EffectNode *pipeline;
    int num_effects;

    int is_recording;
    float *rec_buffer;
    unsigned long rec_capacity;
    unsigned long rec_index;
} AppState;

static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData)
{
    float *in = (float *)inputBuffer;
    float *out = (float *)outputBuffer;
    AppState *state = (AppState *)userData;

    if (in == NULL)
    {
        for (unsigned int i = 0; i < framesPerBuffer; i++)
            out[i] = 0.0f;
        return paContinue;
    }

    process_audio_chain(state->pipeline, state->num_effects, in, out, framesPerBuffer);

    if (state->is_recording)
    {
        for (unsigned long i = 0; i < framesPerBuffer; i++)
        {
            if (state->rec_index < state->rec_capacity)
            {
                state->rec_buffer[state->rec_index++] = out[i];
            }
            else
            {
                state->is_recording = 0;
                break;
            }
        }
    }

    return paContinue;
}

int main(int argc, char *argv[])
{
    char *record_filename = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--record") == 0 && i + 1 < argc)
        {
            record_filename = argv[i + 1];
            i++;
        }
    }

    DelayState *delay1 = delay_create(0.4, 0.3, 5);

    EffectNode pedalboard[] = {
        {.state = delay1, .process = delay_process}};
    int num_effects = sizeof(pedalboard) / sizeof(EffectNode);

    AppState state;
    state.pipeline = pedalboard;
    state.num_effects = num_effects;
    state.is_recording = (record_filename != NULL);
    state.rec_capacity = SAMPLE_RATE * 300;
    state.rec_index = 0;

    if (state.is_recording)
    {
        state.rec_buffer = (float *)malloc(state.rec_capacity * sizeof(float));
    }

    Pa_Initialize();

    PaStream *stream;
    Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE,
                         FRAMES_PER_BUFFER, audioCallback, &state);

    Pa_StartStream(stream);

    printf("Audio pipeline active with %d effects.\n", num_effects);
    printf("Press ENTER to quit.\n");
    getchar();

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    delay_destroy(delay1);

    if (state.is_recording || (record_filename != NULL && state.rec_index > 0))
    {
        printf("Saving recording...\n");
        free(state.rec_buffer);
    }

    return 0;
}

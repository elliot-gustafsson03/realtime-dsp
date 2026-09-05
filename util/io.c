#include <stdio.h>
#include <stdlib.h>
#include "io.h"

float *read_samples_from_file(const char *filepath, size_t *out_count)
{
    if (filepath == NULL || out_count == NULL)
    {
        return NULL;
    }

    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        *out_count = 0;
        return NULL;
    }

    size_t count = 0;
    float dummy;
    while (fscanf(file, "%f", &dummy) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        fclose(file);
        *out_count = 0;
        return NULL;
    }

    rewind(file);

    float *samples = (float *)malloc(count * sizeof(float));
    if (samples == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        *out_count = 0;
        return NULL;
    }

    size_t i = 0;
    while (fscanf(file, "%f", &samples[i]) == 1 && i < count)
    {
        i++;
    }

    fclose(file);
    *out_count = count;
    return samples;
}
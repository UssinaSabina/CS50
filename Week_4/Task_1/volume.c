// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // an array of bytes to store the data from the WAV file header that we’ll read from the input file
    uint8_t header[HEADER_SIZE];
    // Copy header from input file to output file
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // we can use the int16_t type to represent a sample of a WAV file
    int16_t sample;
    // continue reading a sample, updating its volume, and writing the updated sample to the output file while there are still samples left to read.
    while (fread(&sample, sizeof(int16_t), 1, input) != 0)
    {
        // update volume of a sample
        sample *= factor;
        // write updated data to output file
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}

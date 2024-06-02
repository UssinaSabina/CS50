#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

// digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B)
int unit = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recorever FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // If the forensic image cannot be opened for reading
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    BYTE buffer[unit];

    // counts the number of JPEGs
    int counter = 0;

    // allocate 8 bytes for a string that will store .jpg file names
    char *filename = malloc(8);     // xxx.jpg (7) + null character (1) = (8) characters

    // a pointer to .jpg file
    FILE* img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(BYTE), unit, card) == unit)
    {
        // if it's a new JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // close the previous img.jpg file
            if (img != NULL)
            {
                fclose(img);
            }
            // create a filename in format like "xxx.jpg"
            sprintf(filename, "%03i.jpg", counter);
            // open a "xxx.jpg" file
            img = fopen(filename, "w");
            counter++;
        }

        // write bytes to jpeg file
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), unit, img);
        }

    }

    free(filename);

    // close last opened img.jpg
    if (img != NULL)
    {
        fclose(img);
    }

    // close input file (forensic image)
    fclose(card);
}

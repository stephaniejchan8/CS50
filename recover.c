#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
bool signature(BYTE data0, BYTE data1, BYTE data2, BYTE data3);

int main(int argc, char *argv[])
{
    // Program accepts one command line argument only
    if (argc != 2)
    {
        printf("Usage: ./recover [infile]\n");
        return 1;
    }

    // Open forensic file
    FILE *infile = fopen(argv[1], "r");

    // Terminate program if insufficient memory
    if (infile == NULL)
    {
        printf("Unable to allocate memory for forensic file.\n");
        fclose(infile);
        return 1;
    }

    // Create a FAT buffer
    BYTE *FAT = malloc(512 * sizeof(BYTE));

    // Terminate program if insufficient memory
    if (FAT == NULL)
    {
        printf("Could not allocate memory for FAT buffer.\n");
        fclose(infile);
        free(FAT);
        return 2;
    }

    // Outfile naming protocol
    char name[9];
    int n = 0;
    sprintf(name, "%03i.jpg", n);
    // Create outfile
    FILE *outfile = fopen(name, "w");
    // Terminate program if insufficient memory
    if (outfile == NULL)
    {
        printf("Insufficient memory for outfile\n");
        fclose(outfile);
        fclose(infile);
        free(FAT);
        return 2;
    }

    // Search infile for first instance of jpg signature
    do
    {
        fread(FAT, sizeof(BYTE), 512, infile);
    }
    while (!signature(FAT[0], FAT[1], FAT[2], FAT[3]));

    // Write first FAT of jpg
    fwrite(FAT, sizeof(BYTE), 512, outfile);

    // Continue copying jpg
    while (fread(FAT, sizeof(BYTE), 512, infile))
    {
        // Check if this FAT has jpg signature, indicating new jpg
        if (signature(FAT[0], FAT[1], FAT[2], FAT[3]))
        {
            fclose(outfile);
            // Follow outfile naming protocol
            n++;
            sprintf(name, "%03i.jpg", n);
            outfile = fopen(name, "w");
        }
        fwrite(FAT, sizeof(BYTE), 512, outfile);
    }

    // Finished looking at infile
    fclose(infile);
    fclose(outfile);
    free(FAT);
    return 0;

}

// Function to check for jpg signature
bool signature(BYTE data0, BYTE data1, BYTE data2, BYTE data3)
{
    if (data0 == 0xff && data1 == 0xd8 && data2 == 0xff && data3 >= 0xe0 && data3 <= 0xef)
    {
        return true;
    }
    else
    {
        return false;
    }
}
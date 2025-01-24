#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check command-line arguments
    if(argc !=2){
        printf("Usage: ./recover FILE\n");
        return 1;
    }

     // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if(card==NULL){
        printf("Couldn't open the file\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];

     // Variables to manage output files
    FILE *img = NULL;         // Pointer to the current JPEG file
    char filename[8];         // To store filenames like "000.jpg"
    int file_count = 0;       // Number of JPEGs found

    // While there's still data left to read from the memory card
    while(fread(buffer, 1, 512,card)==512){
        // Create JPEGs from the data
        // Check if the block indicates the start of a new JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new filename for the new JPEG
            sprintf(filename, "%03i.jpg", file_count);
            file_count++;

            // Open a new file for writing
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output file.\n");
                fclose(card);
                return 1;
            }
        }

        // If a JPEG is open, write the buffer to the file
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;


}

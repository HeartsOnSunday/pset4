// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy multiplier infile outfile\n");
        return 1;
    }

    if (atoi(argv[1]) <= 1 || atoi(argv[1]) > 100)
    {
        fprintf(stderr, "Multiplier must be an integer greater than 1 and less than 100\n");
        return 2;
    }

    //initialize resize factor
    int multiplier = atoi(argv[1]);
    // remember filenames
    //char *infile = argv[2];
    //char *outfile = argv[3];

    //printf("The Factor is: %c\n", *factor);
    printf("The multiplier is: %i\n", multiplier);

}



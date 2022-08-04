#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *streamIn = fopen("images/cameraman.bmp", "rb"); //open and read file cameraman.bmp
    FILE *fo = fopen("images/cameraman_copy.bmp", "wb"); //write bmp wb

    if(streamIn == (FILE*)0)
    {
        printf("Cannot open file\n");
    }
    unsigned char header[54];
    unsigned char colorTable[1024];

    for(int i=0; i<54; i++)
    {
        header[i] = getc(streamIn); //image header stored in array(header)
    }

    //Extract image width, height, bit 
    //18 of the image hearder, 22 for the image height, 28 for the bit depth

    int width = *(int *) &header[18]; //read width from the image header array, indicates the offset 18 (bitmap header table)
    int height = *(int *) &header[22];
    int bitDepth = *(int *) &header[28];

    //check if the bit depth is less than or equal to 8bit 
    if(bitDepth <=8)
    {
        fread(colorTable, sizeof(unsigned char), 1024, streamIn);
    }

    //done with width, height, depth -> write parameters to cameraman_copy
    fwrite(header, sizeof(unsigned char), 54, fo);
    //create buffer to store the image data, actual pixels
    unsigned char buf[height * width];
    fread(buf, sizeof(unsigned char), (height * width), streamIn);

    if(bitDepth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), 1024, fo);
    }
        fwrite(buf, sizeof(unsigned char), (height * width), fo);
        fclose(fo);
        fclose(streamIn);

        printf("Succes\n");
        printf("width: %d\n", width);
        printf("height: %d\n", height);
    return 0;
} 
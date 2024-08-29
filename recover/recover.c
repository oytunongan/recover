#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File %s could not open\n", argv[1]);
        return 1;
    }
    uint8_t buffer[512];
    char *newfile = malloc(8);
    FILE *img = NULL;
    int count = 0;
    while (fread(buffer, 1, 512, file) == 512)
    {
        if ((buffer[0] == 255) && (buffer[1] == 216) && (buffer[2] == 255))
        {
            int first = 224;
            for (int i = 0; i < 16; i++)
            {
                first += i;
                if (buffer[3] == first)
                {
                    sprintf(newfile, "%03i.jpg", count);
                    count++;
                    if (img != NULL)
                    {
                        fclose(img);
                    }
                    img = fopen(newfile, "w");
                    break;
                }
            }
        }
        if (count != 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    free(newfile);
    fclose(img);
    fclose(file);
    return 0;
}
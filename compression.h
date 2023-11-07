#include "Structures.h"

int compression(FILE *read, FILE *write, DICTIONARY *dictionary)
{
    char c;
    int index = 0;
    int i;
    int bytes2 = 0;
    unsigned char z = 0b00000000;
 
    while ((c = fgetc(read)) != EOF)
    {
        i = 0;
        while (i < dictionary[c - '\n'].size)
        {
            index++;
            z = z << 1;
            if (dictionary[c - '\n'].bit[i] == 1)
                z = z | 0b00000001;
            i++;

            if (index % 8 == 0 && index != 0)
            {
                fwrite(&z, sizeof(unsigned char), 1, write);
                bytes2++;
                index = 0;
                z = 0b00000000;
            }
        }
    }

    if (index != 0)
    {
        z = z << (8 - index);
        fwrite(&z, sizeof(char), 1, write);
        bytes2++;
    }

    fclose(read);
    fclose(write);
    return bytes2;
}
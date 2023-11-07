#include "compression.h"
#include "FrequencyData.h"
#include "FrequencyList.h"
#include "FrequencyListTree.h"
#include "decompression.h"
#include <string.h>

float printCompressionRate(int byte1, int byte2)
{
    return (float)byte1 / (float)byte2;
}

int main()
{
    int choice;
    printf("Enter your choice:\n");
    while (1)
    {
        printf("1. Encode\n2. Decode\n3. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            FILE *f1, *f2;
            char fname1[100], fname2[100];
            int *data = initData();

            printf("Enter input filename: ");
            scanf("%s", fname1);
            printf("Enter output filename: ");
            scanf("%s", fname2);

            f1 = fopen(fname1, "r");
            if (f1 == NULL)
            {
                printf("Input file does not exist. Try again\n");
                break;
            }

            int bytes = charactersFrequency(data, f1);
            LIST *list = initList(data);
            sortList(list);
            NODE *top = sortedFrequencyToTree(list);
            int *arr = malloc(113 * sizeof(int));
            DICTIONARY *dictionary = malloc(113 * sizeof(DICTIONARY));
            convertHuffCodes(top, arr, 0, dictionary, false);

            FILE *file2 = fopen(fname1, "r");
            FILE *file1 = fopen(fname2, "wb");
            int bytes2 = compression(file2, file1, dictionary);
            float cr = printCompressionRate(bytes, bytes2);
            char prefix[100] = "encoded";
            char newoutfile[100];
            strcpy(newoutfile, prefix);
            strcat(newoutfile, fname2);
            FILE *f = fopen(newoutfile, "w");
            dataToFile(data, f, cr);

            free(data);
            free(list);
            free(top);
            free(arr);
            free(dictionary);

            printf("Compression successful\n");
            printf("%f\n", cr);
            break;
        }

        case 2:
        {
            char fname1[100], fname2[100];
            int *data = initData();

            printf("Enter input (encoded) filename: ");
            scanf("%s", fname1);
            printf("Enter output (decoded) filename: ");
            scanf("%s", fname2);

            FILE *file1 = fopen(fname1, "rb");
            if (file1 == NULL)
            {
                printf("infile does not exist\n");
                continue;
            }

            FILE *file2 = fopen(fname2, "w");
            char prefix[100] = "encoded";
            char newoutfile[100];
            strcpy(newoutfile, prefix);
            strcat(newoutfile, fname1);

            FILE *f = fopen(newoutfile, "r");
            if (f == NULL)
            {
                printf("Encoded file not here. Please re-encode the desired file\n");
                continue;
            }

            fileToData(data, f);
            LIST *list = initList(data);
            sortList(list);
            NODE *top = sortedFrequencyToTree(list);
            decompress(file1, file2, top);

            free(data);
            free(list);
            free(top);

            printf("Decompression successful\n");
            break;
        }

        case 3:
        {
            printf("Exiting program\n");
            return 1;
        }

        default:
            printf("Entered invalid choice! Try again\n");
        }
    }
}
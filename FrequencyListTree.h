#include <stdbool.h>
#include <math.h>

NODE *sortedFrequencyToTree(LIST *list);
void printTree(NODE *node);
void printArray(int arr[], int n);
void convertHuffCodes(NODE *top, int bitsArray[], int etage, DICTIONARY *dictionary, int print);
void putInDictionary(int arr[], int etage, DICTIONARY *dictionary, char character);

void printHuffCodesV2(NODE *top, int arr[], int etage,DICTIONARY* dictionary);

NODE *sortedFrequencyToTree(LIST *list) {
    NODE* nodesOfList = list->first;
    while (list->size > 1) {
        NODE *node = malloc(sizeof(NODE));
        node->character = '1';
        node->frequency = nodesOfList->frequency + nodesOfList->next->frequency;
        node->left = nodesOfList;
        node->right = nodesOfList->next;
        appendNode(list, node);
        sortList(list);
        removeHead(list);
        removeHead(list);
        nodesOfList = list->first;
    }
    return list->first;
}

void printTree(NODE *top){
    if (top == NULL)
        return;
    printTree(top->left);

    if(top->character != '1') {
        if (top->character == '\n')
            printf("\\n : %d\n", top->frequency);
        else
            printf("%c : %d\n", top->character, top->frequency);
    }
    printTree(top->right);
}

void convertHuffCodes(NODE *top, int bitsArray[], int etage, DICTIONARY *dictionary, int print) {
    if (top == NULL)
        return;

    bitsArray[etage] = 0;
    convertHuffCodes(top->left, bitsArray, etage + 1, dictionary,print);

    if(top->character != '1') {
        if(print) {
            if (top->character == '\n')
                printf("\\n   | ");
            else
                printf("%c   | ", top->character);
            printArray(bitsArray, etage );
            printf("\n");
        }
        putInDictionary(bitsArray, etage, dictionary, top->character);
    }
    bitsArray[etage] = 1;
    convertHuffCodes(top->right, bitsArray, etage + 1, dictionary,print);
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
}

void putInDictionary(int arr[], int etage, DICTIONARY *dictionary, char character) {
    int index = character-'\n';
    dictionary[index].size = etage;
    dictionary[index].bit = malloc(etage * sizeof(int));

    for (int i = 0; i < etage; ++i)
        dictionary[index].bit[i] = arr[i];
}
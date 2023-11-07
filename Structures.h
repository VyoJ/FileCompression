#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE NODE;
typedef struct _DOUBLYLINKEDLIST LIST;
typedef struct _DICTIONARY DICTIONARY;

struct _NODE
{
    char character;
    int frequency;
    NODE *next;
    NODE *prev;
    NODE *left;
    NODE *right;
};

struct _DOUBLYLINKEDLIST
{
    NODE *first;
    NODE *last;
    int size;
};

struct _DICTIONARY
{
    int size;
    int *bit;
};
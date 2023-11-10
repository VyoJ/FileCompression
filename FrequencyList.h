void appendToList(LIST *list, char character, int frequency);
LIST *initList(int *data);
void sortList(LIST *list);
void removeHead(LIST *list);
void appendNode(LIST *list, NODE *node);

LIST *initList(int *data)
{
    LIST *list = malloc(sizeof(LIST));
    list->size = 0;

    for (int i = 0; i < 113; i++)
        appendToList(list, (char)(i + '\n'), data[i]);
    return list;
}

void appendToList(LIST *list, char character, int frequency)
{
    NODE *node = malloc(sizeof(NODE));

    if (character != '1')
    {
        node->left = NULL;
        node->right = NULL;
    }

    if (frequency == 0)
        return;

    node->character = character;
    node->frequency = frequency;

    if (list->size == 0)
    {
        list->first = node;
        list->last = node;
        list->first->prev = NULL;
        list->last->next = NULL;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
        list->last->next = NULL;
    }
    list->size++;
}

void sortList(LIST *list)
{
    int swapped, i;
    NODE *ptr1;
    NODE *lptr = NULL;

    if (list->first == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = list->first;

        while (ptr1->next != lptr)
        {
            if (ptr1->frequency > ptr1->next->frequency)
            {
                int frequency = ptr1->frequency;
                char character = ptr1->character;
                NODE *left = ptr1->left;
                NODE *right = ptr1->right;

                ptr1->frequency = ptr1->next->frequency;
                ptr1->character = ptr1->next->character;
                ptr1->left = ptr1->next->left;
                ptr1->right = ptr1->next->right;

                ptr1->next->frequency = frequency;
                ptr1->next->character = character;
                ptr1->next->left = left;
                ptr1->next->right = right;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void removeHead(LIST *list)
{
    NODE *node = list->first;
    list->first = node->next;
    list->first->prev = NULL;
    node->next = NULL;
    node->prev = NULL;
    list->size--;
}

void appendNode(LIST *list, NODE *node)
{
    if (list->size == 0)
    {
        list->first = node;
        list->last = node;
        list->first->prev = NULL;
        list->last->next = NULL;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
        list->last->next = NULL;
    }
    list->size++;
}
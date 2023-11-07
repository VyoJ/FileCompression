int charactersFrequency(int *data, FILE *file);
int *initData();
void printData(int *data);
void dataToFile(const int *data, FILE *read, float cr);
float fileToData(int *data, FILE *read);

int *initData()
{
    int *dictonary = malloc(sizeof(int) * 113);
    for (int i = 0; i < 113; i++)
    {
        dictonary[i] = 0;
    }
    return dictonary;
}

int charactersFrequency(int *data, FILE *file)
{
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        data[c - '\n'] = data[c - '\n'] + 1;
        i++;
    }
    fclose(file);
    return i;
}

void printData(int *data)
{
    for (int i = 0; i < 113; i++)
        printf("%c : %d\n", i + '\n', data[i]);
}

void dataToFile(const int *data, FILE *write, float cr)
{
    fprintf(write, "%f\n", cr);
    for (int i = 0; i < 113; i++)
    {
        int temp = data[i];
        fprintf(write, "%d\n", temp);
    }
    fclose(write);
}

float fileToData(int *data, FILE *read)
{
    char line[100];
    int num;
    float cr;
    int index = 0;
    while (fgets(line, sizeof(line), read))
    {
        if (index == 0)
        {
            sscanf(line, "%f", &cr);
            index++;
            continue;
        }
        sscanf(line, "%d", &num);
        data[index - 1] = num;
        index++;
    }
    fclose(read);
    return cr;
}
void decompress(FILE* read, FILE* write, NODE* top) {
    NODE* temp = top;
    int readchar;
    while((readchar = fgetc(read)) != EOF) {
        for (int m = 7; m >= 0; m--) {
            if(((readchar >> m) & 1) == 0)
                top = top->left;
            else
                top = top->right;
            if(top->character != '1') {
                fwrite(&top->character, sizeof(char), 1, write);
                top = temp;
            }
        }
    }
    fclose(write);
    fclose(read);
}
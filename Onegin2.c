#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

int size_file (char* name);
int my_fread (char* text_file, FILE* output, int fsize);

int main()
{
    FILE* output = fopen ("file.txt", "r");

    char text_str[10000] = {};

    int len_file = 0, full_len_file = 0;
    full_len_file = size_file("file.txt");
    len_file = my_fread (text_str, output, full_len_file);
    text_str[len_file] = '\0';
    len_file++;

    char* text_dynstr = (char*) calloc (len_file, sizeof (char));

    strcpy (text_dynstr, text_str);

    int i = 0, num_str = 1;
    while (text_dynstr[i] != '\0')
    {
        if (text_dynstr[i] == '\n')
            num_str++;
        i++;
    }

    char** text = (char**) calloc (num_str + 2, sizeof(char*));

    num_str = 1;
    i = 0;
    text[num_str] = text_dynstr;

    while (text_dynstr[i] != EOF)
    {
        if (text_dynstr[i] == '\n')
        {
            num_str++;
            text[num_str] = text_dynstr + i + 1;
        }
        i++;
    }

    free(text_dynstr);
    fclose (output);

    return 0;
}

int size_file (char* name)
{
    struct stat inf_file = {};
    if (stat (name, &inf_file) == -1)
        printf ("File not found");
    return inf_file.st_size;
}

int my_fread (char* text_file, FILE* output, int fsize)
{
    int file_size = 0;
    while (!feof(output) && file_size < fsize)
    {
        text_file[file_size] = fgetc (output);
        file_size++;
    }
    return file_size;
}

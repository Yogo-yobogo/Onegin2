#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

int size_file (char* name);
int my_fread (char* text_file, FILE* output, int fsize);

int main()
{
    char file_name[] = "file.txt";
    FILE* output = fopen ("file.txt", "r");

    int len_file = 0, full_len_file = 0;
    full_len_file = size_file(file_name);
    len_file++;

    char* text_dynstr = (char*) calloc (len_file, sizeof (char));


    len_file = my_fread (text_dynstr, output, full_len_file);
    text_dynstr[len_file] = '\0';

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
            text_dynstr[i] = '\0';
            num_str++;
            text[num_str] = text_dynstr + i + 1;
        }
        i++;
    }


    for (i = 0; i < num_str; i++)
        printf ("%s\n", text[i]);

    free (text);
    free (text_dynstr);
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

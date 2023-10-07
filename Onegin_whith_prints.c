 #include <stdio.h> #include <stdlib.h> #include <ctype.h> #include <string.h> #include <sys/stat.h>

int size_file (char* name); int my_fread (char* text_file, FILE* output, int fsize); void print_text (char string[]); void print_asci_text (char string[]); void print_str (char strint[]);

int main() { FILE* output = fopen ("file.txt", "r");

char text_str[10000] = {};

int len_file = 0, full_len_file = 0;
full_len_file = size_file("file.txt");
len_file = my_fread (text_str, output, full_len_file);
text_str[len_file] = '\0';
len_file++;

char* text_dynstr = (char*) calloc (len_file, sizeof (char));

strcpy (text_dynstr, text_str);

printf ("len_file = %d, new len_file = %d\n", len_file, full_len_file);

printf ("Value of text_str(in file):\n");
printf ("%s", text_dynstr);
print_text (text_str);

printf ("\nValue of text_str with ASCI cod of every symbol (in file):\n");
print_asci_text (text_str);

printf ("\nValue of text_dynstr(dynamic memory):\n");
print_text (text_dynstr);

printf ("\nValue of text_dynstr with ASCI cod of every symbol (dynamic memory):\n");
print_asci_text (text_dynstr);

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

printf ("\nNumber of strings in file: %d\n", num_str);

for (i = 1; i <= num_str; i++)
{
    print_str(text[i]);
    printf ("\n");
}


free(text_dynstr);
fclose (output);

return 0;
}

void print_text (char string[]) { int i = 0; while (string[i] != '\0') { printf ("%c", string[i]); i++; } }

void print_asci_text (char string[]) { int i = 0; while (string[i] != '\0') { printf ("%c(%03d)", string[i], string[i]); i++; } }

void print_str (char string[]) { int j = 0; while (string[j] != '\n' && string[j] != '\0' && string[j] != EOF) { printf ("%c", string[j]); j++; } }

int size_file (char* name) { struct stat inf_file = {}; if (stat (name, &inf_file) == -1) printf ("File not found"); return inf_file.st_size; }

int my_fread (char* text_file, FILE* output, int fsize) { int file_size = 0; while (!feof(output) && file_size < fsize) { text_file[file_size] = fgetc (output); file_size++; } return file_size; }

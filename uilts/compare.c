#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFF_SIZE 256

char *stobs(char *s, int n)
{
    char *ret = malloc(BUFF_SIZE * 8 + 1);
    int i = 0;
    while (n--)
    {
        char binary[8]; // Array to store the binary representation of each character
        int num = s[i];
        for (int j = 7; j >= 0; j--)
        {
            binary[7 - j] = ((num >> j) & 1) + '0';
        }
        strcpy(ret + (i * 8), binary);
        i++;
    }
    ret[i * 8] = '\0'; // Null-terminate the result array
    return ret;
}

int main(int argc, char *argv[])
{
    char *file1 = NULL, *file2 = NULL;

    if (argc < 3 || argc > 5)
    {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    file1 = argv[1];
    file2 = argv[2];

    int f1 = open(file1, O_RDONLY);
    int f2 = open(file2, O_RDONLY);

    if (f1 == -1 || f2 == -1)
    {
        printf("Error opening files\n");
        return 1;
    }

    char *line1 = malloc(sizeof(char) * BUFF_SIZE);
    char *line2 = malloc(sizeof(char) * BUFF_SIZE);
    int line = 1, s = 0;

    while ((s = read(f1, line1, BUFF_SIZE)) && read(f2, line2, BUFF_SIZE))
    {
        if (strcmp(line1, line2) != 0)
        {
            printf("Line %d\n", s);
            printf("Files differ at line %d\n", line);
            printf("File 1: %s\n", stobs(line1, s));
            printf("File 2: %s\n", stobs(line2, s));
        }
        line++;
        getchar();
    }

    close(f1);
    close(f2);

    return 0;
}

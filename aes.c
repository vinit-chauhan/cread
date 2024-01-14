#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 4096

void encrypt(int infile, int outfile, char *key)
{
    __uint8_t buf[BUF_SIZE];
    int key_len = strlen(key);
    int len;
    while ((len = read(infile, buf, BUF_SIZE)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            buf[i] = buf[i] ^ key[i % key_len];
        }
        write(outfile, buf, len);
    }
}

void decrypt(int infile, int outfile, char *key)
{
    char buf[BUF_SIZE];
    int key_len = strlen(key);
    int len;
    while ((len = read(infile, buf, BUF_SIZE)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            buf[i] = buf[i] ^ key[i % key_len];
        }
        write(outfile, buf, len);
    }
}
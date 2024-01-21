#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE_BYTES 128 / 8
#define KEY_SIZE_BYTES 128 / 8

int do_aes_encrypt(__uint8_t *key, __uint8_t *input, __uint8_t *output);
int do_aes_decrypt(__uint8_t *key, __uint8_t *input, __uint8_t *output);

__uint8_t *expand_key(char *key)
{
    int key_len = strlen(key);

    __uint8_t *new_key = (__uint8_t *)malloc(KEY_SIZE_BYTES);

    for (int i = 0; i < KEY_SIZE_BYTES; i++)
    {
        new_key[i] = key[i % key_len];
    }

    return new_key;
}

void encrypt(int infile, int outfile, char *key)
{
    __uint8_t buf[BUF_SIZE_BYTES];
    int key_len = strlen(key);
    int len;
    while ((len = read(infile, buf, BUF_SIZE_BYTES)) > 0)
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
    __uint8_t buf[BUF_SIZE_BYTES];
    int key_len = strlen(key);
    int len;
    while ((len = read(infile, buf, BUF_SIZE_BYTES)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            buf[i] = buf[i] ^ key[i % key_len];
        }
        write(outfile, buf, len);
    }
}

int do_aes_encrypt(__uint8_t *key, __uint8_t *input, __uint8_t *output)
{
    return 0;
}
int do_aes_decrypt(__uint8_t *key, __uint8_t *input, __uint8_t *output)
{
    return 0;
}

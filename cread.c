/***********************************************************************************
 *
 * Created by: Vinit Chauhan (vinit-chauhan)
 * Created on: 2023-12-23
 * Description: A simple program that encrypts and decrypts files using XOR cipher.
 *
 ***********************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "aes.h"

#define PROGRAM_NAME "cread"

#define BUF_SIZE 4096

typedef enum
{
    NONE = -1,
    READ,
    WRITE,
    WRITE_WITH_DEST,
    READ_WITH_DEST,
} prog_mode_t;

prog_mode_t prog_mode = NONE;
char *dest_file = NULL;

static char const *const short_options = "e:d:o:";
static struct option const long_options[] = {
    {"decrypt", required_argument, NULL, 'd'},
    {"encrypt", required_argument, NULL, 'e'},
    {"output", required_argument, NULL, 'o'},
    {"help", no_argument, NULL, 'h'}, // TODO: remove h flag
    {NULL, 0, NULL, 0}};

void print_usage()
{
    printf("Usage: %s [OPTION] <filename> \n", PROGRAM_NAME);

    fputs("OPTIONS:\n"
          "-d, --decrypt        Decrypt the file with given password and read encrypted file\n"
          "-e, --encrypt        Encrypt the file with given password to filename provided by --output\n"
          "-o, --output         Destination file for -e or -d option (if not provided, program will create same file with .enc extension)\n"
          "    --help           Print this help message\n",
          stdout);

    printf(
        "Examples:\n"
        "\t%s -d file.txt\n"
        "\t%s -e file.txt -o encrypted.txt\n",
        PROGRAM_NAME, PROGRAM_NAME);
}

char *password_prompt()
{
    char *password = getpass("Enter passphrase: ");
    return password;
}

// TODO:
// 1 create md5 hash of password
// 2 use md5 hash as key
// 3 encrypt/decrypt using key
// 3.1 if encrypting, store md5 hash in file header
// 3.2 if decrypting, read md5 hash from file header
// 4 store md5 hash in file header
// 5 check if md5 hash in file header matches the password provided by user

int main(int argc, char *argv[])
{
    char *key = NULL, *src_file = NULL;
    int infile, outfile;

    if (argc < 3 || argc > 5)
    {
        print_usage();
        return 1;
    }

    key = password_prompt();

    __uint8_t *key_expanded = expand_key(key);

    int err = 0;
    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'd':
            prog_mode = READ;
            src_file = optarg;
            break;
        case 'e':
            if (prog_mode == READ)
            {
                fprintf(stderr, "%s: cannot specify both -r and -w\n", PROGRAM_NAME);
                return 1;
            }
            prog_mode = WRITE;
            src_file = optarg;
            break;
        case 'o':
            if (prog_mode == WRITE)
            {
                prog_mode = WRITE_WITH_DEST;
            }
            else if (prog_mode == READ)
            {
                prog_mode = READ_WITH_DEST;
            }
            else
            {
                fprintf(stderr, "%s: cannot specify output file without -w or -r\n", PROGRAM_NAME);
                return 1;
            }
            dest_file = optarg;
            break;
        case 'h':
        default:
            print_usage();
            break;
        }
    }

    if (prog_mode == WRITE)
    {
        dest_file = malloc(strlen(src_file) + 5);
        strcpy(dest_file, src_file);
        strcat(dest_file, ".enc");
    }

    // open the files for reading and writing
    if ((infile = open(src_file, O_RDONLY)) < 0)
    {
        fprintf(stderr, "%s: cannot open source file %s\n", PROGRAM_NAME, src_file);
        return -1;
    }

    if ((prog_mode != READ) && (outfile = open(dest_file, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
    {
        fprintf(stderr, "%s: cannot open destination file %s\n", PROGRAM_NAME, dest_file);
        return 1;
    }

    switch (prog_mode)
    {
    case READ:
        outfile = STDOUT_FILENO;
    case READ_WITH_DEST:
        decrypt(infile, outfile, key_expanded);
        break;
    case WRITE:
    case WRITE_WITH_DEST:
        encrypt(infile, outfile, key_expanded);
        break;
    default:
        write(STDERR_FILENO, "Invalid option\n", 15);
        break;
    }

    return 0;
}
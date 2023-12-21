#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <locale.h>
#include <unistd.h>

#define PROGRAM_NAME "cread"

#define BUF_SIZE 4096
#define nullptr NULL

typedef enum
{
    READ,
    WRITE
} prog_mode_t;

int r_flag, w_flag, d_flag;
char *dest_file = NULL;

char buf[BUF_SIZE];

static char const *const short_options = "rwd:";
static struct option const long_options[] = {
    {"read", no_argument, NULL, 'r'},
    {"write", no_argument, NULL, 'w'},
    {"dest", required_argument, NULL, 'd'},
    {"help", no_argument, NULL, 'h'}, // TODO: remove h flag
    {NULL, 0, NULL, 0}};

void print_usage()
{
    printf("Usage: %s [OPTION] <filename> \n", PROGRAM_NAME);

    fputs("OPTIONS:\n"
          "-r, --read         Decrypt the file with given password and read encrypted file\n"
          "-w, --write        Encrypt the file with given password to filename provided by --dest\n"
          "-d, --dest         Destination file for -w option (if not provided, program will create same file with .enc extension)\n"
          "    --help         Print this help message\n",
          stdout);

    printf(
        "Examples:\n"
        "\t%s -r file.txt\n"
        "\t%s -w -d encrypted.txt file.txt\n",
        PROGRAM_NAME, PROGRAM_NAME);
}

char *password_prompt()
{
    char *password = getpass("Enter key: ");
    return password;
}

void encrypt(int infile, int outfile, char *key)
{
    int key_len = strlen(key);
    int len;
    while ((len = read(infile, buf, BUF_SIZE)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            if (buf[i] == '\0')
            {
                break;
            }
            buf[i] = buf[i] ^ key[i % key_len];
        }
        write(outfile, buf, len);
    }
}

void decrypt(int infile, char *key)
{
    int key_len = strlen(key);
    int len;
    while ((len = read(infile, buf, BUF_SIZE)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            buf[i] = buf[i] ^ key[i % key_len];
        }
        write(STDOUT_FILENO, buf, len);
    }
    write(STDOUT_FILENO, "\n", 1);
}

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

    src_file = argv[argc - 1];

    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1)
    {
        switch (opt)
        {
        case 'r':
            r_flag = 1;
            break;
        case 'w':
            w_flag = 1;
            break;
        case 'd':
            d_flag = 1;
            dest_file = optarg;
            break;
        default:
            print_usage();
            break;
        }
    }

    // check if the user specified either -r or -w
    if ((r_flag && w_flag) || (!r_flag && !w_flag))
    {
        fprintf(stderr, "%s: must specify either -r or -w\n", PROGRAM_NAME);
        return 1;
    }

    // check if the user specified -w but not -d
    if (w_flag && !d_flag)
    {
        dest_file = strcat(src_file, ".enc");
    }

    // open the files for reading and writing
    if ((infile = open(src_file, O_RDONLY)) < 0)
    {
        fprintf(stderr, "%s: cannot open file %s\n", PROGRAM_NAME, src_file);
        return -1;
    }

    printf("src_file: %s\n", src_file);
    printf("%d\n", d_flag);

    if (d_flag && (outfile = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        fprintf(stderr, "%s: cannot open file %s\n", PROGRAM_NAME, dest_file);
        return 1;
    }

    // encrypt or decrypt the file
    if (r_flag)
    {
        printf("decrypting...\n");
        decrypt(infile, key);
    }
    else if (w_flag)
    {
        printf("encrypting...\n");
        encrypt(infile, outfile, key);
    }

    return 0;
}
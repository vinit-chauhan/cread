#ifndef AES_H
#define AES_H

/*
 * infile: input file descriptor
 * outfile: output file descriptor
 * key: encryption key
 */
void encrypt(int infile, int outfile, __uint8_t *key);

/*
 * infile: input file descriptor
 * outfile: output file descriptor
 * key: encryption key
 */
void decrypt(int infile, int outfile, __uint8_t *key);

/*
 * return: expanded key ( 128 bits )
 * key: encryption key
 */
__uint8_t *expand_key(char *key);

#endif

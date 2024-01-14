#ifndef AES_H
#define AES_H

/*
 return: staus
*/
void encrypt(int infile, int outfile, char *key);

/*
 return: staus
*/
void decrypt(int infile, int outfile, char *key);

#endif
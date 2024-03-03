# cread : simple linux utility to easily Encrypt and Decrypt files

## Overview

This C program provides a simple file encryption and decryption tool using the XOR cipher. The XOR cipher is a basic symmetric key algorithm that operates by bitwise XORing each byte of the plaintext with a corresponding byte of the key.
Note: We are re-creating the utility in Rust to leverage Memory-safety, and With the rust implementation, we will be incorporating more encryption algorithms. 

## Usage

### Compilation

Compile the program using build script (GCC):
( Make sure the script has appropriate permission for execution )

```bash
./build.sh -bc
```

### Execution

Run the program with the desired options:

- To encrypt a file:

  ```bash
  ./cread -e <filename> -o <output_filename>
  ```

- To decrypt a file:

  ```bash
  ./cread -d <filename> -o <output_filename>
  ```

- To see the help message:

  ```bash
  ./cread --help
  ```

### Options

- `-e, --encrypt`: Encrypt the specified file with a passphrase.
- `-d, --decrypt`: Decrypt the specified file with a passphrase.
- `-o, --output`: Specify the output file. If not provided, the program will create a file with a .enc extension.
- `--help`: Display the help message.

### Examples

- Encrypt a file:

  ```bash
  ./cread -e file.txt -o encrypted.txt
  ```

- Decrypt a file:

  ```bash
  ./cread -d encrypted.txt -o decrypted.txt
  ```

## Encryption Process

1. The user is prompted to enter a passphrase.
2. The program reads the input file and XORs each byte with the corresponding byte from the passphrase.
3. The encrypted data is written to the output file.

## Decryption Process

1. The user is prompted to enter the passphrase used for encryption.
2. The program reads the encrypted file and XORs each byte with the corresponding byte from the passphrase.
3. The decrypted data is written to the output file.

## Notes

- The program supports reading from and writing to files, and it can also use standard input/output.
- If the output file is not provided for encryption, the program appends ".enc" to the input file and creates a new encrypted file.
- If the output file is not provided for decryption, the output will be shown to the console.
- The program checks for valid combinations of options and provides error messages accordingly.
- The XOR key used for encryption and decryption is derived from the passphrase.

## Future Improvements

- Currently, the program uses a basic XOR cipher. Future scope will be to enhance security by incorporating a more robust encryption algorithm.
- Implement password hashing to securely store and verify passphrases.

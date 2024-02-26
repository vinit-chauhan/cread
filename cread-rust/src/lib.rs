use anyhow::anyhow;

const PROGRAM_NAME: &'static str = "cread";

#[derive(Debug)]
enum CryptType {
    CAESAR,
    SHA256,
}

#[derive(Debug)]
pub struct UserInput {
    is_encrypt: bool,
    is_decrypt: bool,
    is_help: bool,
    output_file: Option<String>,

    #[allow(dead_code)]
    algo: CryptType,
}

impl UserInput {
    pub fn new() -> UserInput {
        UserInput {
            is_decrypt: false,
            is_encrypt: false,
            is_help: true,
            output_file: None,
            algo: CryptType::CAESAR,
        }
    }

    pub fn print_usage() {
        let menu_blob: String = format!(
"
Usage: {PROGRAM_NAME} [OPTION] <filename> 
OPTIONS:
    -d, --decrypt        Decrypt the file with given password and read encrypted file
    -e, --encrypt        Encrypt the file with given password to filename provided by --output
    -o, --output         Destination file for -e or -d option (if not provided, program will create same file with .enc extension)
        --help           Print this help message
Examples:
    {PROGRAM_NAME} -d file.txt
    {PROGRAM_NAME} -e file.txt -o encrypted.txt"
        );

        println!("{menu_blob}");
    }

    pub fn set_user_input(&mut self, args: Vec<String>) {
        let mut is_last_arg_output: bool = false;
        for arg in args {
            if is_last_arg_output == true {
                self.output_file = Some(arg);
                is_last_arg_output = false;
                continue;
            }

            match &arg[..] {
                "-e" | "--encrypt" => {
                    self.is_encrypt = true;
                    self.is_help = false
                }
                "-d" | "--decrypt" => {
                    self.is_decrypt = true;
                    self.is_help = false
                }
                "-o" | "--output" => {
                    is_last_arg_output = true;
                    self.is_help = false;
                }
                _ => self.is_help = true,
            }
        }
    }

    pub fn validate(&self) -> Result<bool, anyhow::Error> {
        // Update the return type
        if self.is_encrypt && self.is_decrypt {
            return Err(anyhow!("Invalid input"));
        }

        let file: bool = match &self.output_file {
            Some(path) => std::path::Path::new(&path).is_file(),
            None => true,
        };

        if file {
            Ok(file)
        } else {
            Err(anyhow!("Unable to open file."))
        }
    }
}

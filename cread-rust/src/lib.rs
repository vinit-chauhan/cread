#[derive(Debug)]
pub struct UserInput {
    is_encrypt: bool,
    is_decrypt: bool,
    is_help: bool,
    output_file: Option<String>,
}

impl UserInput {
    pub fn new() -> UserInput {
        UserInput {
            is_decrypt: false,
            is_encrypt: false,
            is_help: true,
            output_file: None,
        }
    }

    pub fn set_user_input(&mut self, args: Vec<String>) {
        let mut is_last_arg_output: bool = false;
        for arg in args {
            if is_last_arg_output == true {
                self.output_file = Some(arg);
                is_last_arg_output = false;
                continue;
            }
            if let Some(opt) = arg.strip_prefix("-") {
                if opt == "e" || opt == "encrypt" {
                    self.is_encrypt = true;
                    self.is_help = false;
                } else if opt == "d" || opt == "decrypt" {
                    self.is_decrypt = true;
                    self.is_help = false;
                } else if opt == "help" {
                    self.is_help = true;
                } else if opt == "o" || opt == "output" {
                    is_last_arg_output = true;
                    self.is_help = false;
                }
            }
        }
    }
}

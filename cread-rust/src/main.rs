extern crate cread_rust;
use std::{env, process::ExitCode};

use crate::cread_rust::UserInput;

const BUFF_SIZE: usize = 4096;

fn main() -> ExitCode {
    let mut _buff: [i8; BUFF_SIZE] = [0; BUFF_SIZE];
    let args: Vec<String> = env::args().collect();
    let mut input: UserInput = UserInput::new();

    input.set_user_input(args);

    if let Err(e) = input.validate() {
        println!("[ERROR]: {}", e.to_string());
        return ExitCode::FAILURE;
    }

    ExitCode::SUCCESS
}

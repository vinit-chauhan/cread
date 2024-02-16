extern crate cread_rust;
use std::env;

use cread_rust::UserInput;

const BUFF_SIZE: usize = 4096;

fn main() {
    let mut _buff: [i8; BUFF_SIZE] = [0; BUFF_SIZE];
    let args: Vec<String> = env::args().collect();
    let mut input: UserInput = UserInput::new();

    input.set_user_input(args);

    println!("{input:?}");
}

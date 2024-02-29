use std::collections::HashMap;

pub mod caesar;
pub mod caesar_test;

pub trait Symmetric {
    fn generate_keys(seed: usize) -> HashMap<char, char>;
    fn encrypt(key: HashMap<char, char>, text: String) -> String;
    fn decrypt(rev_key: HashMap<char, char>, text: String) -> String;
}

pub trait Asymmetric {
    fn generate_keys(seed: usize) -> HashMap<char, char>;
    fn encrypt(key: HashMap<char, char>, text: String) -> String;
    fn decrypt(rev_key: HashMap<char, char>, text: String) -> String;
}

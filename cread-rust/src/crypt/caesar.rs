use std::collections::HashMap;

pub fn generate_keys(seed: usize) -> HashMap<char, char> {
    let char_set: String =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ,.~!@#$%^&*()_+{}:\"<>".to_string();
    let char_set_size: usize = char_set.chars().count();

    let mut new_char_set: HashMap<char, char> = HashMap::new();

    for (i, ch) in char_set.chars().enumerate() {
        let new_ch = char_set
            .chars()
            .nth((i + seed) % char_set_size)
            .expect("Error extracting characters from default set");

        new_char_set.insert(ch, new_ch);
    }

    new_char_set
}

pub fn encrypt(key: HashMap<char, char>, text: String) -> String {
    let mut enc_text = String::with_capacity(text.bytes().count());

    for ch in text.chars() {
        enc_text.push(
            key.get(&ch)
                .expect(format!("char {} not found in the map.", ch).as_str())
                .clone(),
        );
    }

    enc_text.to_string()
}

pub fn decrypt(rev_key: HashMap<char, char>, text: String) -> String {
    let mut key: HashMap<char, char> = HashMap::new();

    for (k, v) in rev_key {
        key.insert(v, k);
    }

    let mut enc_text = String::with_capacity(text.bytes().count());

    for ch in text.chars() {
        enc_text.push(
            key.get(&ch)
                .expect(format!("char {} not found in the map.", ch).as_str())
                .clone(),
        );
    }

    enc_text.to_string()
}

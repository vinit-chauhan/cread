#[cfg(test)]
mod tests {
    use super::super::caesar::{decrypt, encrypt, generate_keys};

    #[test]
    fn test_encrypt() {
        // Add test cases for the encrypt function here
        let key = generate_keys(12usize);

        let test1 = "klmnopqrstuvwxyzABC".to_string();
        let ans1 = "wxyzABCDEFGHIJKLMNO".to_string();
        assert!(encrypt(key.clone(), test1).eq(&ans1));

        println!("Test Passed.");
    }

    #[test]
    fn test_decrypt() {
        // Add test cases for the decrypt function here
        let key = generate_keys(12usize);

        let ans1 = "klmnopqrstuvwxyzABC".to_string();
        let test1 = "wxyzABCDEFGHIJKLMNO".to_string();
        assert!(decrypt(key.clone(), test1).eq(&ans1));

        println!("Test Passed.");
    }

    #[test]
    fn test_generate_keys() {
        // Add test cases for the generate_keys function here
    }
}

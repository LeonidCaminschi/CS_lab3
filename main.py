def vigenere_encrypt(plaintext, key):
    romanian_alphabet = "AĂÂBCDEFGHIÎJKLMNOPQRSȘTȚUVWXYZ"
    ciphertext = ""
    key_length = len(key)

    for i in range(len(plaintext)):
        plain_char = plaintext[i]
        key_char = key[i % key_length]

        if plain_char in romanian_alphabet:
            index = romanian_alphabet.index(plain_char)
            encrypted_char = romanian_alphabet[(index + romanian_alphabet.index(key_char)) % len(romanian_alphabet)]
            ciphertext += encrypted_char
        else:
            ciphertext += plain_char

    return ciphertext

def vigenere_decrypt(ciphertext, key):
    romanian_alphabet = "AĂÂBCDEFGHIÎJKLMNOPQRSȘTȚUVWXYZ"
    plaintext = ""
    key_length = len(key)

    for i in range(len(ciphertext)):
        cipher_char = ciphertext[i]
        key_char = key[i % key_length]

        if cipher_char in romanian_alphabet:
            index = romanian_alphabet.index(cipher_char)
            decrypted_char = romanian_alphabet[(index - romanian_alphabet.index(key_char) + len(romanian_alphabet)) % len(romanian_alphabet)]
            plaintext += decrypted_char
        else:
            plaintext += cipher_char

    return plaintext

def match_string(result):
    return result.replace(' ', '').upper()

def main():
    import sys
    if len(sys.argv) < 4 or len(sys.argv) > 5:
        print("Please input 3 arguments")
        print("./lab3 <method> <number> \"<input_text>\"")
        print("<method> - is 'e' for encryption and 'd' for decryption")
        print("\"<key>\" - is the key used to encrypt the message")
        print("\"<input_text>\" must be a text and can include spaces and any other English alphabet letters")
        return 1

    method = sys.argv[1]
    key = sys.argv[2]
    input_text = sys.argv[3]

    if method != 'e' and method != 'd':
        print("Invalid argument. Please check your method to be 'd' or 'e'.")
        return 1

    if len(key) < 7:
        print("Invalid length of the key. Please make sure that the key size is not less than 7")
        return 1

    final_text = input_text.upper()
    final_key = key.upper()

    result = ""
    if len(sys.argv) == 4:
        if method == 'e':
            result = vigenere_encrypt(final_text, final_key)
            print("Encrypted text:", match_string(result))
        else:
            result = vigenere_decrypt(final_text, final_key)
            print("Decrypted text:", match_string(result))

if __name__ == "__main__":
    main()
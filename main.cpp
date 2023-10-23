#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

const wstring romanianAlphabet = L"AĂÂBCDEFGHIÎJKLMNOPQRSȘTȚUVWXYZ";

wstring vigenereEncrypt(const wstring & plaintext, const wstring& key) {
    wstring ciphertext = L"";
    int keyLength = key.length();

    for (int i = 0; i < plaintext.length(); i++) {
        wchar_t plainChar = plaintext[i];
        wchar_t keyChar = key[i % keyLength];

        // Check if the character is in the Romanian alphabet
        size_t index = romanianAlphabet.find(plainChar);
        cout << int(index) << " " << romanianAlphabet.find(keyChar) << endl;
        if (index != wstring::npos) {
            wchar_t encryptedChar = romanianAlphabet[(index + romanianAlphabet.find(keyChar)) % romanianAlphabet.length()];
            ciphertext += encryptedChar;
        } else {
            // If the character is not in the Romanian alphabet, leave it unchanged
            ciphertext += plainChar;
        }
    }

    return ciphertext;
}

wstring vigenereDecrypt(const wstring& ciphertext, const wstring& key) {
    wstring plaintext = L"";
    int keyLength = key.length();

    for (int i = 0; i < ciphertext.length(); i++) {
        wchar_t cipherChar = ciphertext[i];
        wchar_t keyChar = key[i % keyLength];

        // Check if the character is in the Romanian alphabet
        size_t index = romanianAlphabet.find(cipherChar);
        if (index != wstring::npos) {
            wchar_t decryptedChar = romanianAlphabet[(index - romanianAlphabet.find(keyChar) + romanianAlphabet.length()) % romanianAlphabet.length()];
            plaintext += decryptedChar;
        } else {
            // If the character is not in the Romanian alphabet, leave it unchanged
            plaintext += cipherChar;
        }
    }

    return plaintext;
}

wstring matchstring(wstring result) {
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    wstring final_str;
    for (int i=0; i<result.size(); i++) {
        final_str += toupper(result[i]);
    }
    return final_str;
}

int main(int argc, char* argv[]) {
    std::locale::global(std::locale("C"));

    if (argc < 4 || argc > 5) {
        cout << "Please input 3 arguments" << endl;
        cout << "./lab3 <method> <number> \"<input_text>\"" << endl;
        cout << "<method> - is 'e' for encryption and 'd' for decryption" << endl;
        cout << "\"<key>\" - is the key used to encrypt the message" << endl;
        cout << "\"<input_text>\" must be a text could include spaces and any other English alphabet letters" << endl;
        return 1;
    }

    char method = argv[1][0];
    wstring key = L"";
    key = wstring(argv[2], argv[2] + strlen(argv[2]));
    wstring inputText = L"";
    inputText = wstring(argv[3], argv[3] + strlen(argv[3]));

    if (method != 'e' && method != 'd') {
        cout << "Invalid argument. Please check your method to be 'd' or 'e'." << endl;
        return 1;
    }

    if (key.size() < 7) {
        cout << "Invalid length of the key. Please make sure that the key size is not less than 7" << endl;
        return 1;
    }

//    for (int i=0; i<inputText.size(); i++) {
//        if (romanianAlphabet.find(inputText[i]) == std::string::npos) {
//            cout << "Please use only romanian alphabet it being: " << endl;
//            for (int j=0; j<romanianAlphabet.size(); j++) {
//                cout << romanianAlphabet[j] << " ";
//            }
//            return 0;
//        }
//    }

    wstring final_text = L"";
    wstring final_key = L"";
    for (auto c : inputText) {
        final_text += toupper(c);
    }
    for (auto c : key) {
        final_key += toupper(c);
    }

    wcout << key << endl;
    wcout << final_text << endl;

    wstring result;
    if (argc == 4) {
        if (method == 'e') {
            result = vigenereEncrypt(final_text, final_key);
            wcout << L"Encrypted text: " << matchstring(result) << endl;
        } else {
            result = vigenereDecrypt(final_text, final_key);
            wcout << L"Decrypted text: " << matchstring(result) << endl;
        }
    }

    return 0;
}

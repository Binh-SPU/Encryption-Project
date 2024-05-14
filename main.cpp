#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

std::string encryptTransposition(const std::string& plaintext, const std::string& key) {
    // Step 1: Create a matrix based on the key
    std::vector<std::vector<char>> matrix((plaintext.length() + key.length() - 1) / key.length(), std::vector<char>(key.length(), '*'));

    // Step 2: Fill the matrix with the plaintext row by row
    int index = 0;
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[row].size(); col++) {
            if (index < plaintext.length()) {
                matrix[row][col] = plaintext[index++];
            }
        }
    }

    // Step 3: Rearrange the columns of the matrix based on the key
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    std::string ciphertext;
    for (char k : sortedKey) {
        int col = key.find(k);
        for (int row = 0; row < matrix.size(); row++) {
            ciphertext += matrix[row][col];
        }
    }
    return ciphertext;
}

std::string decryptTransposition(const std::string& ciphertext, const std::string& key) {
    // Step 1: Create a matrix based on the key
    std::vector<std::vector<char>> matrix((ciphertext.length() + key.length() - 1) / key.length(), std::vector<char>(key.length(), '*'));

    // Step 2: Rearrange the columns of the matrix based on the key
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    int index = 0;
    for (char k : sortedKey) {
        int col = key.find(k);
        for (int row = 0; row < matrix.size(); row++) {
            if (index < ciphertext.length()) {
                matrix[row][col] = ciphertext[index++];
            }
        }
    }

    // Step 3: Read the matrix row by row to get the plaintext
    std::string plaintext;
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[row].size(); col++) {
            plaintext += matrix[row][col];
        }
    }

    std::string filteredPlaintext;
    for (char ch : plaintext) {
        if (ch != '*') {
            filteredPlaintext += ch;
        }
    }
    return filteredPlaintext;
}

int main() {
    bool encryption_done = false;
    srand(time(0));
    while (!encryption_done) {
        string plaintext;
        cout << "Please enter a plaintext:";
        cin >> plaintext;

        int encryption_method;
        cout << "Please enter an encryption method (1 for XOR Encryption, 2 for Transposition Cipher):";
        cin >> encryption_method;
        if (encryption_method != 1 && encryption_method != 2) {
            cout << "Invalid encryption method. Please try again." << endl;
            continue;
        }

        if (encryption_method == 1) {
            string key = "";
            string key_choice;
            cout << "Do you want to enter a key or randomly auto-generated? (1 for yes, 0 for auto-generated):";
            cin >> key_choice;
            if (key_choice == "1") {
                cout << "Please enter a key:";
                cin >> key;
            } else {
                for (size_t i = 0; i < plaintext.size(); ++i) {
                    int random = rand() % 62; // Generate random number between 0 and 61
                    char random_char;
                    if (random < 26) {
                        random_char = 'A' + random; // Characters from 'A' to 'Z'
                    } else if (random < 52) {
                        random_char = 'a' + random - 26; // Characters from 'a' to 'z'
                    } else {
                        random_char = '0' + random - 52; // Characters from '0' to '9'
                    }
                    key += random_char;
                }
                cout << "Generated key: " << key << endl;
            }

            string ciphertext = plaintext;
            for (size_t i = 0; i < plaintext.size(); ++i) {
                ciphertext[i] = plaintext[i] ^ key[i];
            }
            cout << "Ciphertext: " << ciphertext << endl;

            string decrypted_text = ciphertext;
            for (size_t i = 0; i < ciphertext.size(); ++i) {
                decrypted_text[i] = decrypted_text[i] ^ key[i];
            }
            cout << "Decrypted text: " << decrypted_text << endl << endl;
            cout << "Do you want to try another encryption method? (1 for yes, 0 for no):";

            int do_we_continue;
            do {
                cin >> do_we_continue;
            } while (do_we_continue != 0 && do_we_continue != 1);
            if (do_we_continue == 0) {
                encryption_done = true;
            }
        }
        else if (encryption_method == 2) {
            string key = "";
            string key_choice;
            cout << "Do you want to enter a key or randomly auto-generated? (1 for yes, 0 for auto-generated):";
            cin >> key_choice;
            if (key_choice == "1") {
                cout << "Please enter a key:";
                cin >> key;
            } else {
                for (size_t i = 0; i < 4; ++i) {
                    int random = rand() % 62; // Generate random number between 0 and 61
                    char random_char;
                    if (random < 26) {
                        random_char = 'A' + random; // Characters from 'A' to 'Z'
                    } else if (random < 52) {
                        random_char = 'a' + random - 26; // Characters from 'a' to 'z'
                    } else {
                        random_char = '0' + random - 52; // Characters from '0' to '9'
                    }
                    key += random_char;
                }
                cout << "Generated key: " << key << endl;
            }

            // Encryption
            std::string ciphertext = encryptTransposition(plaintext, "HIDE");
            std::cout << "Ciphertext: " << ciphertext << std::endl;

            // Decryption
            std::string decryptedText = decryptTransposition(ciphertext, "HIDE");
            std::cout << "Decrypted Text: " << decryptedText << std::endl;
        }
    }




    return 0;
}

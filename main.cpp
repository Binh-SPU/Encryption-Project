#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

/**
 * This function is to encrypt the plaintext using XOR encryption method
 * @param plaintext is the text that the user wants to encrypt
 * @param key is the key that the user wants to use to encrypt the plaintext
 * @return the encrypted text
 *
 * Some part of the code under here was taken out of an old project I done at Digipen and with the Help of the a student teacher there -Zhi
 *
 */
string encryptTransposition(const string& plaintext, const string& key) {
    // Step 1: Create a matrix based on the key
    vector<vector<char>> matrix((plaintext.length() + key.length() - 1) / key.length(), vector<char>(key.length(), '*'));

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
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());

    string ciphertext;
    for (char k : sortedKey) {
        int col = key.find(k);
        for (int row = 0; row < matrix.size(); row++) {
            ciphertext += matrix[row][col];
        }
    }
    return ciphertext;
}

/**
 * This function is to decrypt the ciphertext using XOR encryption method
 * @param ciphertext is the text that the user wants to decrypt
 * @param key is the key that the user wants to use to decrypt the ciphertext
 * @return the decrypted text
 */
string decryptTransposition(const string& ciphertext, const string& key) {
    // Step 1: Create a matrix based on the key
    vector<vector<char>> matrix((ciphertext.length() + key.length() - 1) / key.length(), vector<char>(key.length(), '*'));

    // Step 2: Rearrange the columns of the matrix based on the key
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());

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
    string plaintext;
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[row].size(); col++) {
            plaintext += matrix[row][col];
        }
    }

    string filteredPlaintext;
    for (char ch : plaintext) {
        if (ch != '*') {
            filteredPlaintext += ch;
        }
    }
    return filteredPlaintext;
}

/**
 * This function is to ask the user if they want to try another encryption method or not
 * @param encryption_done is the flag to check if the user wants to try another encryption method or not
 */
void TryAgainOrNot(bool& encryption_done) {
    cout << "Do you want to try another encryption method? (1 for yes, 0 for no):";

    int do_we_continue;
    do {
        cin >> do_we_continue;
    } while (do_we_continue != 0 && do_we_continue != 1);
    if (do_we_continue == 0) {
        encryption_done = true;
    }
}

/**
 * This function is to generate a random key for the both encryption method
 * @param encryption_method is the method that the user chooses
 * @return the generated key
 */
string GenerateRandomKey(int& encryption_method) {
    string key = "";
    unsigned int loop_cap = encryption_method == 2 ? 4 : 62;
    for (size_t i = 0; i < loop_cap; ++i) {
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
    return key;
}

int main() {
    bool encryption_done = false;
    srand(time(0));
    // Main loop to navigate the user to choose the encryption method and the encryption cycle.
    while (!encryption_done) {
        string plaintext;
        int plaintext_choice;
        cout << "Please choose which method of entering the plaintext you want to use (1 for manual entry, otherwise for file entry):";
        cin >> plaintext_choice;
        if (plaintext_choice == 1) {
            cout << "Please enter a plaintext:";
            getline(cin, plaintext);
        } else {
            cout << "Please enter the file name:";
            string file_name;
            cin >> file_name;
            // Read the file and store the content in the plaintext
            ifstream file(file_name);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    plaintext += line + "\n";  // Add each line and a newline character
                }
                file.close();
            } else {
                cout << "Unable to open the file. Please try again." << endl;
                continue;
            }
        }

        // Choose the encryption method
        int encryption_method;
        cout << "Please enter an encryption method (1 for XOR Encryption, 2 for Transposition Cipher):";
        cin >> encryption_method;
        if (encryption_method != 1 && encryption_method != 2) {
            cout << "Invalid encryption method. Please try again." << endl;
            continue;
        }

        // XOR Encryption
        if (encryption_method == 1) {
            string key = "";
            string key_choice;
            cout << "Do you want to enter a key or randomly auto-generated? (1 for manually entered, otherwise for auto-generated):";
            cin >> key_choice;
            if (key_choice == "1") {
                cout << "Please enter a key:";
                cin >> key;
            } else {
                key = GenerateRandomKey(encryption_method);
                cout << "Generated key: " << key << endl;
            }

            // XOR Encryption
            string ciphertext = plaintext;
            for (size_t i = 0; i < plaintext.size(); ++i) {
                ciphertext[i] = plaintext[i] ^ key[i];
            }
            cout << "Ciphertext: " << ciphertext << endl << endl;

            // XOR Decryption
            string decrypted_text = ciphertext;
            for (size_t i = 0; i < ciphertext.size(); ++i) {
                decrypted_text[i] = decrypted_text[i] ^ key[i];
            }
            cout << "Decrypted text: " << decrypted_text << endl << endl;

            TryAgainOrNot(encryption_done);
        }
            // Transposition Cipher
        else if (encryption_method == 2) {
            string key = "";
            string key_choice;
            cout << "Do you want to enter a key or randomly auto-generated? (1 for manually entered, otherwise for auto-generated):";
            cin >> key_choice;
            if (key_choice == "1") {
                cout << "Please enter a key:";
                cin >> key;
            } else {
                key = GenerateRandomKey(encryption_method);
                cout << "Generated key: " << key << endl;
            }

            // Encryption
            std::string ciphertext = encryptTransposition(plaintext, key);
            std::cout << "Ciphertext: " << ciphertext << endl << endl;

            // Decryption
            std::string decryptedText = decryptTransposition(ciphertext, key);
            std::cout << "Decrypted Text: " << decryptedText << endl << endl;

            TryAgainOrNot(encryption_done);
        }
    }




    return 0;
}
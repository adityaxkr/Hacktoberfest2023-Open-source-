#include <iostream>
#include <string>
#include <vector>
#include <openssl/aes.h>

using namespace std;

// Key and IV for AES encryption
static const unsigned char aes_key[] = "MySecretKey12345";
static const unsigned char aes_iv[] = "InitializationV";

struct PasswordEntry {
    string username;
    string encryptedPassword;
};

class PasswordManager {
private:
    string masterPassword;
    vector<PasswordEntry> entries;

    string encrypt(const string& data) {
        AES_KEY aesKey;
        AES_set_encrypt_key(aes_key, 128, &aesKey);
        unsigned char encryptedData[data.size()];
        AES_encrypt((unsigned char*)data.c_str(), encryptedData, &aesKey);
        return string((char*)encryptedData, data.size());
    }

    string decrypt(const string& encryptedData) {
        AES_KEY aesKey;
        AES_set_decrypt_key(aes_key, 128, &aesKey);
        unsigned char decryptedData[encryptedData.size()];
        AES_decrypt((unsigned char*)encryptedData.c_str(), decryptedData, &aesKey);
        return string((char*)decryptedData, encryptedData.size());
    }

public:
    PasswordManager(const string& password) : masterPassword(password) {}

    bool authenticate(const string& password) {
        return password == masterPassword;
    }

    void addPassword(const string& username, const string& password) {
        string encryptedPassword = encrypt(password);
        entries.push_back({username, encryptedPassword});
        cout << "Password entry added." << endl;
    }

    void showPasswords() {
        for (const PasswordEntry& entry : entries) {
            cout << "Username: " << entry.username << endl;
            cout << "Password: " << decrypt(entry.encryptedPassword) << endl;
            cout << "-------------------" << endl;
        }
    }
};

int main() {
    string password;
    cout << "Enter the master password: ";
    cin >> password;

    PasswordManager manager(password);

    while (true) {
        cout << "Password Manager" << endl;
        cout << "1. Authenticate" << endl;
        cout << "2. Add Password Entry" << endl;
        cout << "3. Show Passwords" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string enteredPassword;
                cout << "Enter the master password: ";
                cin >> enteredPassword;
                if (manager.authenticate(enteredPassword)) {
                    cout << "Authentication successful." << endl;
                } else {
                    cout << "Authentication failed. Please try again." << endl;
                }
                break;
            }
            case 2: {
                if (manager.authenticate(password)) {
                    string username, newPassword;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> newPassword;
                    manager.addPassword(username, newPassword);
                } else {
                    cout << "Authentication required to add a password entry." << endl;
                }
                break;
            }
            case 3: {
                if (manager.authenticate(password)) {
                    manager.showPasswords();
                } else {
                    cout << "Authentication required to view passwords." << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

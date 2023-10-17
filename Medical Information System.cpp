#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <openssl/evp.h>
#include <openssl/aes.h>

using namespace std;

class Patient {
private:
    string username;
    string password;  // In practice, you should use a strong password hashing function
    map<string, string> medicalData;  // Store medical data as key-value pairs

public:
    Patient(string uname, string pwd) : username(uname), password(pwd) {}

    bool authenticate(string uname, string pwd) {
        return (uname == username && pwd == password);
    }

    void addMedicalData(string key, string value) {
        medicalData[key] = value;
    }

    string getMedicalData(string key) {
        if (medicalData.find(key) != medicalData.end()) {
            return medicalData[key];
        } else {
            return "Data not found.";
        }
    }
};

vector<Patient> patients;  // In-memory storage for patient records

// AES Encryption and Decryption Functions
string encrypt(string data, string key) {
    AES_KEY aesKey;
    AES_set_encrypt_key((unsigned char*)key.c_str(), 128, &aesKey);
    unsigned char encryptedData[data.size()];
    AES_encrypt((unsigned char*)data.c_str(), encryptedData, &aesKey);
    return string((char*)encryptedData, data.size());
}

string decrypt(string data, string key) {
    AES_KEY aesKey;
    AES_set_decrypt_key((unsigned char*)key.c_str(), 128, &aesKey);
    unsigned char decryptedData[data.size()];
    AES_decrypt((unsigned char*)data.c_str(), decryptedData, &aesKey);
    return string((char*)decryptedData, data.size());
}

int main() {
    while (true) {
        cout << "Medical Information System" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string uname, pwd;
                cout << "Enter a username: ";
                cin >> uname;
                cout << "Enter a password: ";
                cin >> pwd;
                patients.push_back(Patient(uname, pwd));
                cout << "Registration successful." << endl;
                break;
            }
            case 2: {
                string uname, pwd;
                cout << "Enter your username: ";
                cin >> uname;
                cout << "Enter your password: ";
                cin >> pwd;

                for (const Patient &patient : patients) {
                    if (patient.authenticate(uname, pwd)) {
                        cout << "Authentication successful." << endl;
                        while (true) {
                            cout << "1. Add Medical Data" << endl;
                            cout << "2. Get Medical Data" << endl;
                            cout << "3. Logout" << endl;

                            int subChoice;
                            cout << "Enter your choice: ";
                            cin >> subChoice;

                            if (subChoice == 1) {
                                string key, value;
                                cout << "Enter data key: ";
                                cin >> key;
                                cout << "Enter data value: ";
                                cin >> value;
                                string encryptedValue = encrypt(value, pwd);
                                patient.addMedicalData(key, encryptedValue);
                            } else if (subChoice == 2) {
                                string key;
                                cout << "Enter data key: ";
                                cin >> key;
                                string encryptedValue = patient.getMedicalData(key);
                                string decryptedValue = decrypt(encryptedValue, pwd);
                                cout << "Decrypted Data: " << decryptedValue << endl;
                            } else if (subChoice == 3) {
                                cout << "Logged out." << endl;
                                break;
                            } else {
                                cout << "Invalid choice. Please try again." << endl;
                            }
                        }
                        break;
                    }
                }
                cout << "Authentication failed. Please try again." << endl;
                break;
            }
            case 3:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

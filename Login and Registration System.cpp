#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
};

vector<User> users; // In-memory storage for registered users

void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    // Check if the username is already taken
    for (const User& user : users) {
        if (user.username == username) {
            cout << "Username already taken. Please choose a different one." << endl;
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> password;

    // Save the user information to a file (e.g., username.txt)
    ofstream userFile(username + ".txt");
    userFile << "Username: " << username << endl;
    userFile << "Password: " << password << endl;
    userFile.close();

    // Create a user object and add it to the in-memory storage
    User newUser;
    newUser.username = username;
    newUser.password = password;
    users.push_back(newUser);

    cout << "Registration successful. User file created." << endl;
}

int main() {
    while (true) {
        cout << "Login and Registration System" << endl;
        cout << "1. Register" << endl;
        cout << "2. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

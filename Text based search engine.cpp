#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Document {
    string title;
    string content;
};

vector<Document> database;

void addDocument(const string& title, const string& content) {
    Document doc;
    doc.title = title;
    doc.content = content;
    database.push_back(doc);
}

void searchDocuments(const string& keyword) {
    cout << "Search results for keyword '" << keyword << "':" << endl;
    for (const Document& doc : database) {
        if (doc.title.find(keyword) != string::npos || doc.content.find(keyword) != string::npos) {
            cout << "Title: " << doc.title << endl;
            cout << "Content: " << doc.content << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

int main() {
    addDocument("Document 1", "This is the content of document 1.");
    addDocument("Document 2", "Another document with some content.");
    addDocument("Document 3", "A third document for testing purposes.");

    while (true) {
        cout << "Search Engine" << endl;
        cout << "1. Search" << endl;
        cout << "2. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string keyword;
                cout << "Enter a keyword to search: ";
                cin.ignore();  // Clear the input buffer
                getline(cin, keyword);
                transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);  // Convert the keyword to lowercase for case-insensitive search
                searchDocuments(keyword);
                break;
            }
            case 2:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

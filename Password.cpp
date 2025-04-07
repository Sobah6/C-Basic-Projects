#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const string DATA_FILE = "passwords.db";
const int SHIFT = 5; // Caesar cipher shift

string encrypt(const string& text) {
    string result = text;
    for (char& c : result) c += SHIFT;
    return result;
}

string decrypt(const string& text) {
    string result = text;
    for (char& c : result) c -= SHIFT;
    return result;
}

string hashMasterPassword(const string& password) {
    int sum = 0;
    for (char c : password) sum += c;
    return to_string(sum * SHIFT); // Not real hashing, just a mock
}

struct Entry {
    string website;
    string username;
    string password;
};

vector<Entry> entries;

void saveToFile(const string& hashedMaster) {
    ofstream out(DATA_FILE);
    out << hashedMaster << "\n";
    for (const auto& e : entries) {
        out << encrypt(e.website) << ',' << encrypt(e.username) << ',' << encrypt(e.password) << "\n";
    }
    out.close();
}

bool loadFromFile(string& storedHash) {
    ifstream in(DATA_FILE);
    if (!in.is_open()) return false;

    getline(in, storedHash);
    string line;
    while (getline(in, line)) {
        istringstream ss(line);
        string w, u, p;
        if (getline(ss, w, ',') && getline(ss, u, ',') && getline(ss, p)) {
            entries.push_back({decrypt(w), decrypt(u), decrypt(p)});
        }
    }
    in.close();
    return true;
}

void addEntry() {
    Entry e;
    cout << "Website: "; getline(cin, e.website);
    cout << "Username: "; getline(cin, e.username);
    cout << "Password: "; getline(cin, e.password);
    entries.push_back(e);
    cout << "✅ Entry added.\n";
}

void listEntries() {
    if (entries.empty()) {
        cout << "No saved entries.\n";
        return;
    }

    cout << "\nStored Entries:\n";
    for (size_t i = 0; i < entries.size(); ++i) {
        cout << i + 1 << ". " << entries[i].website << " | " << entries[i].username << " | " << entries[i].password << "\n";
    }
}

void deleteEntry() {
    listEntries();
    if (entries.empty()) return;

    cout << "Enter entry number to delete: ";
    int idx;
    cin >> idx;
    cin.ignore();
    if (idx < 1 || idx > static_cast<int>(entries.size())) {
        cout << "Invalid index.\n";
        return;
    }
    entries.erase(entries.begin() + idx - 1);
    cout << "🗑️ Entry deleted.\n";
}

int main() {
    cout << "🔐 Simple C++ Password Manager\n";
    cout << "(Don't use for real passwords!)\n";

    string masterPassword;
    cout << "Enter master password: ";
    getline(cin, masterPassword);
    string enteredHash = hashMasterPassword(masterPassword);

    string storedHash;
    if (loadFromFile(storedHash)) {
        if (enteredHash != storedHash) {
            cout << "❌ Incorrect master password!\n";
            return 1;
        }
    } else {
        cout << "No database found. Creating new one.\n";
        storedHash = enteredHash;
    }

    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Entry\n";
        cout << "2. View Entries\n";
        cout << "3. Delete Entry\n";
        cout << "4. Save & Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addEntry(); break;
            case 2: listEntries(); break;
            case 3: deleteEntry(); break;
            case 4:
                saveToFile(storedHash);
                cout << "🔒 Saved and exiting.\n";
                break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}

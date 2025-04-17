#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int total_saving_accounts = 0;
int total_current_accounts = 0;

class account {
public:
    string name_of_account_holder;
    string name_of_joint_account_holder;
    long long int account_number;
    int balance;
    string type_of_account;
    string pin;

    // Single holder constructor
    account(string accholdername, int bal, string typeofacc, string pc) {
        account_number = rand() % 100000 + 1000000000;
        name_of_account_holder = accholdername;
        balance = bal;
        type_of_account = typeofacc;
        pin = pc;
        name_of_joint_account_holder = "No Joint Holder in this account";
    }

    // Joint holder constructor
    account(string accholdername, string jointholdername, int bal, string typeofacc, string pc) {
        account_number = rand() % 100000 + 1000000000;
        name_of_account_holder = accholdername;
        name_of_joint_account_holder = jointholdername;
        balance = bal;
        type_of_account = typeofacc;
        pin = pc;
    }
};

vector<account> accts;
long long int accnumber;

void display_details(long long int accnum) {
    bool acc_exists = false;
    for (auto& it : accts) {
        if (it.account_number == accnum) {
            acc_exists = true;
            cout << "\nAccount Number        : " << it.account_number;
            cout << "\nAccount Holder Name   : " << it.name_of_account_holder;
            cout << "\nJoint Holder Name     : " << it.name_of_joint_account_holder;
            cout << "\nBalance               : " << it.balance;
            cout << "\nType of Account       : " << it.type_of_account << endl;
            break;
        }
    }
    if (!acc_exists) {
        cout << "Account doesn't exist with the given Account Number.\n";
    }
}

bool create_account(vector<account>& accts) {
    system("cls");
    string accholder_name, str, joint_holder = "N/A", pin, typeofacc;
    int balance, choice;

    cout << "\nENTER YOUR DETAILS:\n";
    cout << "Name of Account Holder: ";
    cin >> accholder_name;
    cout << "Do you want a joint account? (YES/NO): ";
    cin >> str;

    bool is_joint = (str == "YES");
    if (is_joint) {
        cout << "Enter Joint Holder's Name: ";
        cin >> joint_holder;
    }

    cout << "Enter a PIN: ";
    cin >> pin;

    cout << "\nAccount Type:\n1 - Savings Account\n2 - Current Account\nEnter choice: ";
    cin >> choice;

    typeofacc = (choice == 1) ? "Savings" : "Current";

    cout << "Initial Balance: ";
    cin >> balance;

    if (typeofacc == "Current" && balance < 10000) {
        cout << "\n\t\t|-----------------------------------------------|\n";
        cout << "\t\t|     INSUFFICIENT BALANCE FOR CURRENT ACCOUNT  |\n";
        cout << "\t\t|-----------------------------------------------|\n";
        return false;
    }

    account ob = is_joint ?
        account(accholder_name, joint_holder, balance, typeofacc, pin) :
        account(accholder_name, balance, typeofacc, pin);

    accts.push_back(ob);
    if (typeofacc == "Savings") total_saving_accounts++;
    else total_current_accounts++;

    cout << "\n\t\t|-----------------------------------------------|\n";
    cout << "\t\t|     ACCOUNT CREATED SUCCESSFULLY              |\n";
    cout << "\t\t|-----------------------------------------------|\n";
    display_details(ob.account_number);
    return true;
}

bool change_pin() {
    long long int accnum;
    cout << "Enter your account number: ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            string oldpin, newpin;
            cout << "Enter old PIN: ";
            cin >> oldpin;

            if (oldpin == it.pin) {
                cout << "Enter new PIN: ";
                cin >> newpin;
                it.pin = newpin;
                display_details(it.account_number);
                accnumber = it.account_number;
                return true;
            } else {
                cout << "Invalid PIN.\n";
                return false;
            }
        }
    }

    cout << "Account not found.\n";
    return false;
}

bool deposit_into_account() {
    long long int accnum;
    cout << "Enter account number: ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            string pin;
            cout << "Enter PIN: ";
            cin >> pin;
            if (pin == it.pin) {
                int deposit_amount;
                cout << "Amount to deposit: ";
                cin >> deposit_amount;
                it.balance += deposit_amount;
                display_details(it.account_number);
                return true;
            } else {
                cout << "Invalid PIN.\n";
                return false;
            }
        }
    }
    cout << "Account not found.\n";
    return false;
}

bool withdraw_from_account() {
    long long int accnum;
    cout << "Enter account number: ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            string pin;
            cout << "Enter PIN: ";
            cin >> pin;
            if (pin == it.pin) {
                int amount;
                cout << "Amount to withdraw: ";
                cin >> amount;
                if (it.balance >= amount) {
                    it.balance -= amount;
                    display_details(it.account_number);
                    return true;
                } else {
                    cout << "Insufficient balance.\n";
                    return false;
                }
            } else {
                cout << "Invalid PIN.\n";
                return false;
            }
        }
    }
    cout << "Account not found.\n";
    return false;
}

bool balance_inquiry() {
    long long int accnum;
    cout << "Enter account number: ";
    cin >> accnum;

    for (auto& it : accts) {
        if (it.account_number == accnum) {
            cout << "Balance: " << it.balance << endl;
            return true;
        }
    }
    cout << "Account not found.\n";
    return false;
}

bool close_account() {
    long long int accnum;
    cout << "Enter account number to close: ";
    cin >> accnum;

    for (size_t i = 0; i < accts.size(); ++i) {
        if (accts[i].account_number == accnum) {
            accts.erase(accts.begin() + i);
            cout << "Account closed successfully.\n";
            return true;
        }
    }
    cout << "Account not found.\n";
    return false;
}

bool view_account_details() {
    for (auto& it : accts) {
        display_details(it.account_number);
        cout << "-----------------------------------\n";
    }
    return true;
}

void admin_menu() {
    system("cls");
    int option;
    cout << "\n1. View Total Number of Accounts\n2. View All Account Details\nEnter option: ";
    cin >> option;
    switch (option) {
        case 1:
            cout << "Total Accounts: " << accts.size() << endl;
            break;
        case 2:
            view_account_details();
            break;
        default:
            cout << "Invalid Option.\n";
    }
}

void user_menu() {
    int choice;
    do {
        system("cls");
        cout << "\nUSER MENU\n";
        cout << "1. Create New Account\n";
        cout << "2. Change PIN\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Balance Inquiry\n";
        cout << "6. Close Account\n";
        cout << "7. Display Account Details\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: create_account(accts); break;
            case 2: change_pin(); break;
            case 3: deposit_into_account(); break;
            case 4: withdraw_from_account(); break;
            case 5: balance_inquiry(); break;
            case 6: close_account(); break;
            case 7: {
                long long int accno;
                cout << "Enter account number: ";
                cin >> accno;
                display_details(accno);
                break;
            }
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
        system("pause");
    } while (choice != 8);
}

void welcome() {
    int choice;
    do {
        system("cls");
        cout << "\nWELCOME TO HBL BANKING SYSTEM\n";
        cout << "1. Administrator\n";
        cout << "2. User\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: admin_menu(); system("pause"); break;
            case 2: user_menu(); break;
            case 3: exit(0);
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

int main() {
    welcome();
    return 0;
}

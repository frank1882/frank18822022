#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account {
private:
    int accountNumber;
    char name[50];
    double deposit;
    double withdraw;
    char accountType;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, sizeof(name));

        cout << "Enter Initial Deposit: ";
        cin >> deposit;

        cout << "Enter Account Type (Savings - 'S' or Current - 'C'): ";
        cin >> accountType;
    }

    void displayAccount() const {
        cout << setw(20) << "Account Number: " << accountNumber << endl;
        cout << setw(20) << "Name: " << name << endl;
        cout << setw(20) << "Balance: ksh" << deposit << endl;
        cout << setw(20) << "Account Type: " << accountType << endl;
    }

    void depositAmount() {
        double amount;
        cout << "Enter Deposit Amount: ";
        cin >> amount;
        deposit += amount;
        cout << "Deposit Successful. Current Balance: Ksh" << deposit << endl;
    }

    void withdrawalAmount(){
        double amount;
        cout << "Enter Withdrawal Amount: ";
        cin >> amount;
        if (amount <= deposit) {
            deposit -= amount;
            cout << "Withdrawal Successful. Current Balance: ksh" << deposit << endl;
        } else {
            cout << "Insufficient Funds!\n";
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    char getAccountType() const {
        return accountType;
    }
};

void writeAccount(const Account& account) {
    ofstream outFile("bank_data.bin", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&account), sizeof(Account));
    outFile.close();
}

void displayAllAccounts() {
    ifstream inFile("bank_data.bin", ios::binary);
    Account account;

    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        account.displayAccount();
        cout << "---------------------------\n";
    }

    inFile.close();
}

void displayAccountDetails(int accNumber) {
    ifstream inFile("bank_data.bin", ios::binary);
    Account account;

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        if (account.getAccountNumber() == accNumber) {
            account.displayAccount();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "Account not found.\n";
    }
}

void modifyAccount(int accNumber) {
    fstream file("bank_data.bin", ios::binary |ios::in | ios::out);
    Account account;

    bool found = false;
    while (file.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        if (account.getAccountNumber() == accNumber) {
            account.displayAccount();
            found = true;

            // Update account details
            cout << "Enter new details:\n";
            account.createAccount();

            // Move the file pointer back to the beginning of the record
            file.seekp(-static_cast<ios::off_type>(sizeof(Account)), ios::cur);

            // Write the updated record
            file.write(reinterpret_cast<const char*>(&account), sizeof(Account));
            cout << "Account details updated successfully.\n";
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Account not found.\n";
    }
}

void deleteAccount(int accNumber) {
    ifstream inFile("bank_data.bin", ios::binary);
    Account account;

    ofstream outFile("temp.bin", ios::binary);

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        if (account.getAccountNumber() == accNumber) {
            account.displayAccount();
            found = true;
            cout << "Account deleted successfully.\n";
        } else {
            outFile.write(reinterpret_cast<const char*>(&account), sizeof(Account));
        }
    }

    inFile.close();
    outFile.close();

    // Rename temp file to the original file
    remove("bank_data.bin");
    rename("temp.bin", "bank_data.bin");

    if (!found) {
        cout << "Account not found.\n";
    }
}

int main() {
    int choice;
    int accNumber;

    do {
        cout << "\n1. Create New Account\n";
        cout << "2. Deposit Amount\n";
        cout << "3. Withdraw Amount\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Display Account Details\n";
        cout << "6. Modify Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    Account account;
                    account.createAccount();
                    writeAccount(account);
                    cout << "Account created successfully.\n";
                }
                break;
            case 2:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                displayAccountDetails(accNumber);
                // Deposit amount
                break;
            case 3:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                displayAccountDetails(accNumber);
                // Withdraw amount
                break;
            case 4:
                displayAllAccounts();
                break;
            case 5:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                displayAccountDetails(accNumber);
                break;
            case 6:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                modifyAccount(accNumber);
                break;
            case 7:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                deleteAccount(accNumber);
                break;
            case 8:
                cout << "Exiting the program.\n";
                break;
            default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}

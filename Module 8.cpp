#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class BankAccount {
private:
    double balance;

public:
    BankAccount() { balance = 0.0; }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
        saveTransaction("Deposit", amount);
    }

    void makePurchase(const string &item, double cost) {
        if (cost > balance) {
            cout << "Insufficient funds for " << item << endl;
            saveTransaction("FAILED Purchase - " + item, cost);
        } else {
            balance -= cost;
            cout << "Purchased: " << item << " for $" << cost << endl;
            saveTransaction("Purchase - " + item, cost);
        }
    }
    void displayBalance() {
        cout << "Current Balance: $" << balance << endl;
    }

    void saveTransaction(const string &type, double amount) {
        ofstream file("transactions.txt", ios::app);
        if (file.is_open()) {
            file << type << ": $" << amount << endl;
            file.close();
        }
    }
};

// helper: print the transactions.txt to console
void printTransactionsFile() {
    ifstream file("transactions.txt");
    if (!file.is_open()) {
        cout << "No transactions file found." << endl;
        return;
    }
    cout << "\n--- transactions.txt contents ---\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    cout << "---------------------------------\n";
    file.close();
}

int main() {
    // Remove old transactions file for a clean run (optional)
    // Comment out the next two lines if you want to append to previous runs:
    std::remove("transactions.txt");

    BankAccount myAccount;
    cout << "=== Bank Account Simulation ===" << endl;

    myAccount.deposit(200.00);                 // Starting deposit
    myAccount.makePurchase("Coffee", 5.25);    // Purchase 1
    myAccount.makePurchase("Shoes", 49.99);    // Purchase 2
    myAccount.displayBalance();                // Print final balance

    cout << "Transactions saved to transactions.txt" << endl;

    // Print the transactions file contents so you can screenshot it
    printTransactionsFile();

    return 0;
}

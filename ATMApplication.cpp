#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
using namespace std;

// Bank Account class
class BankAccount {
public:
	int accNumber;
	double balance;
	char accountType;
public:
	BankAccount(int, char, double);
	void addDeposit(double amount); //Mandatory Methods
	void subWdrawal(double amount); //Mandatory Methods
	void displayFunction(); //Mandatory Method
};

// Constructor function
BankAccount::BankAccount(int aN, char aT, double bal) {
	accNumber = aN;
	balance = bal;
	accountType = aT;
}

// Savings Account class
class SavingsAccount: public BankAccount {
private:
	float interestRate;
public:
	SavingsAccount(int, char, double);
	void addDeposit(double);
	void subWdrawal(double);
	void interestCalculation(float);
	void displayFunction(float iRate);
};

// Constructor function
SavingsAccount::SavingsAccount(int aN, char aT, double bal) :
		BankAccount(aN, aT, bal) {
	interestRate = 5; //Default interest rate of 10% taken for savings account
}

void SavingsAccount::addDeposit(double amount) {
	balance = balance + amount;
}

void SavingsAccount::subWdrawal(double amount) {
	balance = balance - amount;
}

void SavingsAccount::interestCalculation(float iRate) {
	interestRate = iRate;
	double interestAmount = (balance * interestRate) / 100;
	balance = balance + interestAmount;
	cout << "\nInterest Amount for savings account " << accNumber << " is "
			<< interestAmount << "%" << endl;
}

void SavingsAccount::displayFunction(float iRate) {
	interestCalculation(iRate);
}

// Cheque Account class
class ChequeAccount: public BankAccount {
private:
	float overDrawAmountLimit;
	bool isAccountOverDrawn;
public:
	ChequeAccount(int, char, double);
	void addDeposit(double);
	void subWdrawal(double amount);
	void displayFunction();

};

// Constructor function
ChequeAccount::ChequeAccount(int aN, char aT, double bal) :
		BankAccount(aN, aT, bal) {
	overDrawAmountLimit = 100;
}

void ChequeAccount::ChequeAccount::addDeposit(double amount) {
	balance = balance + amount;
}

void ChequeAccount::ChequeAccount::subWdrawal(double amount) {
	if (balance - amount < -100) {
		cout << "Withdrawal cannot be made because the account is over drawn\n";
	} else {
		balance = balance - amount;
		cout << "\n$" << amount << " deducted from cheque account " << accNumber
				<< endl;
	}
}

void ChequeAccount::displayFunction() {
	if (balance < -100) {
		cout << "\t The Account is over drawn by $" << (0 - balance) << "\n";
	}
}

// Credit Card Account class
class CreditCardAccount: public BankAccount {
private:
	float interestRate;
	float creditLimit;
public:
	float availableCredit;
	CreditCardAccount(int, char, double);
	void addDeposit(double);
	void subWdrawal(double);
	void isCreditLimitExceeded();
	void displayFunction();
	void displayFunction(float iRate);
};

// Constructor function
CreditCardAccount::CreditCardAccount(int aN, char aT, double bal) :
		BankAccount(aN, aT, bal) {
	interestRate = 18;
	creditLimit = 5000;
	availableCredit = creditLimit - balance;
}

void CreditCardAccount::addDeposit(double amount) {
	balance = balance - amount; //Since in credit card account balance represents the amount owing, so if you deposit amount, the balance that you owe reduces.
	availableCredit = creditLimit - balance;
}

void CreditCardAccount::subWdrawal(double amount) {
	if ((creditLimit - (balance + amount)) < 0) {
		cout << "Transaction cannot be made, the credit limit is exceeded.\n";
	} else {
		balance = balance + amount;
		availableCredit = creditLimit - balance;
		cout << "\n$" << amount
				<< " deducted from credit for credit card account " << accNumber
				<< endl;
	}
}

void CreditCardAccount::isCreditLimitExceeded() {
	if (availableCredit < 0) {
		cout << "\nThe credit Limit is Exceeded\n";
	} else {
		cout << "\nCredit Limit not Exceeded" << endl;
	}
}

void CreditCardAccount::displayFunction() {
	cout << "Available Credit: " << availableCredit << endl;
	cout << "Balance: " << balance;
	isCreditLimitExceeded();
}

void CreditCardAccount::displayFunction(float iRate) {
	double interestAmount = (balance * iRate) * 0.01;
	balance = balance + interestAmount;
	cout << "\n$" << interestAmount << " applied to credit card account "
			<< accNumber << "\nBalance: " << balance << endl;
}

//Customer class containing BankAccount object

class Customer {
public:
	string name;
	string address;
	BankAccount bAccount;
public:
	Customer(string = "", string = "", int = 0, char = 'X', double = 0.0);
};

//Constructor function calling BankAccount constructor

Customer::Customer(string nme, string addr, int an, char aT, double b) :
		bAccount(an, aT, b) {
	name = nme;
	address = addr;
}

//Process transactions class. Mainly performs the task of processing the transactions in the trans.dat file and displaying user initial and final balances.

class ProcessTrans {
private:
	ifstream infile;
	int numTrans;
	int findAcc(int);
	struct node {
		string data;
		node *link;
	}*p;
public:
	Customer cust[100];
	int numberOfCustomers;

	int countElementsInLinkedList();
	void displayLinkedList();
	void appendToLinkedList(string);
	void populateCustomerClass();
	void makeTransactions();
	void getAllCustomerDetails();
	void performTransaction(int, double, char);
};

// This method reads the customer details from the customer.dat file.
void ProcessTrans::getAllCustomerDetails() {
	ifstream infile;
	string content;

	p = NULL;
	infile.open("customers.dat");

	if (infile.fail())
		cout << "File not found";
	else {
		while (infile.peek() != EOF) {
			getline(infile, content);
			appendToLinkedList(content);
		}
	}
	populateCustomerClass();
}

//This method appends the customer details, name, address, account type, account number and account balance, into a linked list.
void ProcessTrans::appendToLinkedList(string details) {
	node *q, *t;
	if (p == NULL) {
		p = new node;
		p->data = details;
		p->link = NULL;
	} else {
		q = p;
		while (q->link != NULL)
			q = q->link;
		t = new node;
		t->data = details;
		t->link = NULL;
		q->link = t;
	}
}

//This is an additional method, just added to display the values in the linked list.
void ProcessTrans::displayLinkedList() {
	node *q;
	cout << endl;

	for (q = p; q != NULL; q = q->link)
		cout << endl << q->data;
}

// This method populates the values in the linked list to the customer class and places the customer objects in a customer object array.
void ProcessTrans::populateCustomerClass() {
	node *q;
	int count = 0;
	int i = 0;
	cout << endl;
	string custName;
	string custAddress;
	char accType;
	double accBal;
	int accNum;

	for (q = p; q != NULL; q = q->link) {
		string qdata = q->data;
		switch (count) {
		case 0:
			custName = qdata;
			break;

		case 1:
			custAddress = qdata;
			break;

		case 2:
			if (qdata.compare("S") == 0) {
				accType = 'S';
				break;
			} else if ((qdata).compare("C") == 0) {
				accType = 'C';
				break;
			} else if ((qdata).compare("K") == 0) {
				accType = 'K';
				break;
			}

		case 3:
			accNum = atoi(qdata.c_str());
			break;

		case 4:
			accBal = atof(qdata.c_str());
			break;

		default: {
			if ((qdata).compare("X") == 0) {
				count = -1;
				cust[i].name = custName;
				cust[i].address = custAddress;
				if (accType == 'S')
					cust[i].bAccount = SavingsAccount(accNum, accType, accBal);
				if (accType == 'C')
					cust[i].bAccount = ChequeAccount(accNum, accType, accBal);
				if (accType == 'K')
					cust[i].bAccount = CreditCardAccount(accNum, accType,
							accBal);
				i++;
			} else {
				count = 2;
				cust[i].name = custName;
				cust[i].address = custAddress;
				if (accType == 'S')
					cust[i].bAccount = SavingsAccount(accNum, accType, accBal);
				if (accType == 'C')
					cust[i].bAccount = ChequeAccount(accNum, accType, accBal);
				if (accType == 'K')
					cust[i].bAccount = CreditCardAccount(accNum, accType,
							accBal);
				accType = qdata[0];
				i++;
			}
			break;
		}
		}

		count++;
	}
	numberOfCustomers = i + 1;
}

// This method displays the customer balance after the transactions mentioned in the trans.dat file are applied to the customer data.
void ProcessTrans::makeTransactions() {
	ifstream infile;
	ofstream outfile;
	int accountNumber;
	double amountChange;
	char bankOperation;

	infile.open("trans.dat");
	if (infile.fail())
		cout << "File not found";
	else {
		while (infile.peek() != EOF) {
			infile >> accountNumber;
			infile >> amountChange;
			infile >> bankOperation;
			if (accountNumber == 0)
				break;
			performTransaction(accountNumber, amountChange, bankOperation);
			accountNumber = 0;
		}
		infile.close();
		cout << "\n\n----------Balance After Transactions----------\n";
		cout << "----------------------------------------------\n";
		cout << "        Name     Type    Acc. Number   Balance\n";
		cout << "----------------------------------------------\n";
		int j = 0;
		// Displaying the customer balances after the transaction from the trans.dat are made.
		while (j < numberOfCustomers - 1) {
			cout << fixed;
			cout << setw(15) << cust[j].name << setw(5)
					<< cust[j].bAccount.accountType << setw(15)
					<< cust[j].bAccount.accNumber << setw(10) << setprecision(2)
					<< cust[j].bAccount.balance << endl << endl;
			j++;
		}
		///Updating Customer Details into the customers.dat
		outfile.open("customers.dat");

		int m = 0;
		while (m < numberOfCustomers - 1) {
			if (m > 0 && (cust[m].name).compare(cust[m - 1].name) == 0) {
				outfile << cust[m].bAccount.accountType << endl;
				outfile << cust[m].bAccount.accNumber << endl;
				outfile << cust[m].bAccount.balance << endl;
			} else {
				if (m > 0)
					outfile << "X" << endl;
				outfile << cust[m].name << "\n";
				outfile << cust[m].address << "\n";
				outfile << cust[m].bAccount.accountType << endl;
				outfile << cust[m].bAccount.accNumber << endl;
				outfile << cust[m].bAccount.balance << endl;
			}
			m++;
		}
		outfile << "X";
		outfile.close();
	}
}

// The transactions in the trans.dat file are actually performed over here, in this method. Only the result is displayed in the makeTransactions() method.
void ProcessTrans::performTransaction(int accountNumber, double amountChange,
		char bankOperation) {
	int flag = 0;
	int k = 0;
	while (k < numberOfCustomers - 1) {
		if (cust[k].bAccount.accNumber == accountNumber) {
			flag = 1;
			BankAccount bA = cust[k].bAccount;
			char accountType = cust[k].bAccount.accountType;
			if (accountType == 'S') {
				SavingsAccount savAcc = SavingsAccount(bA.accNumber,
						bA.accountType, bA.balance);
				if (bankOperation == 'C') {
					savAcc.addDeposit(amountChange);
					cout << "\n$" << amountChange
							<< " deposited to savings account " << accountNumber
							<< endl;
					cust[k].bAccount = savAcc;
				} else if (bankOperation == 'D') {
					savAcc.subWdrawal(amountChange);
					if (savAcc.balance < 0) {
						cout << "\nINSUFFICIENT BALANCE: Unable to withdraw $"
								<< amountChange << " from account "
								<< savAcc.accNumber << endl;

					} else {
						cout << "\n$" << amountChange
								<< " withdrawn from savings account "
								<< accountNumber << endl;
						cust[k].bAccount = savAcc;
					}
				} else if (bankOperation == 'I') {
					savAcc.displayFunction(5);
					cust[k].bAccount = savAcc;
				}
			}

			if (accountType == 'C') {
				ChequeAccount chequeAccount = ChequeAccount(bA.accNumber,
						bA.accountType, bA.balance);
				if (bankOperation == 'C') {
					chequeAccount.addDeposit(amountChange);
					cout << "\n$" << amountChange
							<< " deposited to cheque account " << accountNumber
							<< endl;
					cust[k].bAccount = chequeAccount;
				} else if (bankOperation == 'D') {
					chequeAccount.subWdrawal(amountChange);
					chequeAccount.displayFunction();
					cust[k].bAccount = chequeAccount;
				} else if (bankOperation == 'I') {
					cout << "\nAccount Number " << accountNumber
							<< " : The cheque account does not accrue interest"
							<< endl;
					cust[k].bAccount = chequeAccount;
				}
			}

			if (accountType == 'K') {
				CreditCardAccount creAcc = CreditCardAccount(bA.accNumber,
						bA.accountType, bA.balance);
				if (bankOperation == 'C') {
					creAcc.addDeposit(amountChange);
					cout << "\n$" << amountChange
							<< " deposited to the credit available for credit card account "
							<< accountNumber << endl;
					cust[k].bAccount = creAcc;
				} else if (bankOperation == 'D') {
					creAcc.subWdrawal(amountChange);
					creAcc.displayFunction();
					cust[k].bAccount = creAcc;
				} else if (bankOperation == 'I') {
					creAcc.displayFunction(18);
					cust[k].bAccount = creAcc;
				}
			}
			break;
		} else
			flag = 0;
		k++;
	}
	if (flag == 0)
		cout << "\nAccount Number " << accountNumber
				<< " Does Not Exist In The Bank Database" << endl;
}

// ATM functionality class

class ATMSystem {
public:
	Customer custmr[100];
	int numOfCust;
	void displayOptions(int);
	int atmOperations(Customer, int);
	void updateBalances();
};

// The first method of the ATM operations. It gets the pin number from the user and validates it, and if the pin exists, atmOperations(Customer, int) is called.
void ATMSystem::displayOptions(int numOfCustomers) {
	numOfCust = numOfCustomers;
	ProcessTrans prt;
	Customer loggedInCustomer;
	int custpos;
	int pinNumber;
	int flag = 0;
	prt.getAllCustomerDetails();
	for (int i = 0; i < 100; i++) {
		custmr[i] = prt.cust[i];
	}
	pinentry:
	//PIN entry validation
	cout << "Enter Your PIN Number :" << endl;
	cin >> pinNumber;
	if (pinNumber == 9999) {
		cout << "Exited the ATM Application" << endl << endl;
		return;
	}
	if (pinNumber != 0) {
		for (int i = 0; i < 100; i++) {
			if (pinNumber == custmr[i].bAccount.accNumber) {
				loggedInCustomer = custmr[i];
				custpos = i;
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0) {
		cout << "Authentication Failed" << endl << endl;
		goto pinentry;
	} else {
		int returnValue = atmOperations(loggedInCustomer, custpos);
		if (returnValue == 1) {
			flag = 0;
			goto pinentry;
		}
	}
}

// This method performs the main ATM functionality of deposit, withdrawal, checking balance.
int ATMSystem::atmOperations(Customer lic, int custpos) {
	int enteredOption;
	ofstream outfile;
	mainmenu: cout << "\n1.Withdraw Cash" << endl << "2.Deposit" << endl
			<< "3.Show Balance" << endl << "4.Quit" << endl << endl;
	cout << "Enter your option : " << endl;
	cin >> enteredOption;

	char accountType = lic.bAccount.accountType;
	BankAccount bA = lic.bAccount;
	switch (enteredOption) {
	// withdrawal of specified amount of money from customer account.
	case 1:
		double amountToWithdraw;
		cout << "Enter the amount to withdraw : " << endl;
		cin >> amountToWithdraw;
		if (accountType == 'S') {
			SavingsAccount savAcc = SavingsAccount(bA.accNumber, bA.accountType,
					bA.balance);
			savAcc.subWdrawal(amountToWithdraw);
			if (savAcc.balance < 0) {
				cout << "Unable to withdraw the amount, insufficient balance."
						<< endl;
			} else {
				cout << "\n$" << amountToWithdraw
						<< " withdrawn from savings account "
						<< savAcc.accNumber << endl;
				custmr[custpos].bAccount = savAcc;
			}
		}
		if (accountType == 'C') {
			ChequeAccount chequeAccount = ChequeAccount(bA.accNumber,
					bA.accountType, bA.balance);

			chequeAccount.subWdrawal(amountToWithdraw);
			custmr[custpos].bAccount = chequeAccount;
		}
		if (accountType == 'K') {
			CreditCardAccount creAcc = CreditCardAccount(bA.accNumber,
					bA.accountType, bA.balance);
			creAcc.subWdrawal(amountToWithdraw);
			custmr[custpos].bAccount = creAcc;
		}
		// writing the transactions made by the ATM mode into a new transaction file, atmtrans.dat
		outfile.open("atmtrans.dat", ios::app);
		outfile << custmr[custpos].bAccount.accNumber << endl;
		outfile << amountToWithdraw << endl;
		outfile << "D" << endl;
		outfile.close();
		lic = custmr[custpos];
		cout << "\nNavigating back to the Main Menu....\n";
		goto mainmenu;

		// deposit of specified amount of money from customer account
	case 2:
		double amountToDeposit;
		cout << "Enter the amount to Deposit : " << endl;
		cin >> amountToDeposit;
		if (accountType == 'S') {
			SavingsAccount savAcc = SavingsAccount(bA.accNumber, bA.accountType,
					bA.balance);
			savAcc.addDeposit(amountToDeposit);
			custmr[custpos].bAccount = savAcc;
			cout << "\n$" << amountToDeposit
					<< " deposited to the savings account " << savAcc.accNumber
					<< endl;
		}
		if (accountType == 'C') {
			ChequeAccount chequeAccount = ChequeAccount(bA.accNumber,
					bA.accountType, bA.balance);
			chequeAccount.addDeposit(amountToDeposit);
			custmr[custpos].bAccount = chequeAccount;
			cout << "\n$" << amountToDeposit << " deposited to cheque account "
					<< chequeAccount.accNumber << endl;
		}
		if (accountType == 'K') {
			CreditCardAccount creAcc = CreditCardAccount(bA.accNumber,
					bA.accountType, bA.balance);
			creAcc.addDeposit(amountToDeposit);
			custmr[custpos].bAccount = creAcc;
			cout << "\n$" << amountToDeposit
					<< " deposited to credit card account " << creAcc.accNumber
					<< endl;
		}
		outfile.open("atmtrans.dat", ios::app);
		outfile << custmr[custpos].bAccount.accNumber << endl;
		outfile << amountToDeposit << endl;
		outfile << "C" << endl;

		outfile.close();
		lic = custmr[custpos];
		cout << "\nNavigating back to the Main Menu....\n";
		goto mainmenu;
		// Displaying the user balance.
	case 3:
		cout << "Your Account Balance is : " << custmr[custpos].bAccount.balance
				<< endl;
		if (accountType == 'K') {
			CreditCardAccount creAcc = CreditCardAccount(bA.accNumber,
					bA.accountType, bA.balance);
			cout << "Available credit in the account is "
					<< creAcc.availableCredit << endl;
		}
		cout << "\nNavigating back to the Main Menu....\n";
		goto mainmenu;
		// Returning back to the pin entry stage after a particular user exits the atm mode.
	case 4:
		cout << "Thank you for using our ATM" << endl << endl;
		return 1;
	};
	return 0;
}

void ATMSystem::updateBalances() {
	ofstream outfile;
	///Updating Customer Details, after atm mode transactions, into the customers.dat
	outfile.open("c://customers.dat");

	int m = 0;
	while (m < numOfCust - 1) {
		if (m > 0 && (custmr[m].name).compare(custmr[m - 1].name) == 0) {
			outfile << custmr[m].bAccount.accountType << endl;
			outfile << custmr[m].bAccount.accNumber << endl;
			outfile << custmr[m].bAccount.balance << endl;
		} else {
			if (m > 0)
				outfile << "X" << endl;
			outfile << custmr[m].name << "\n";
			outfile << custmr[m].address << "\n";
			outfile << custmr[m].bAccount.accountType << endl;
			outfile << custmr[m].bAccount.accNumber << endl;
			outfile << custmr[m].bAccount.balance << endl;
		}
		m++;
	}
	outfile << "X";
	outfile.close();
}

int main() {
	ProcessTrans pt;
	ATMSystem atm;
	Customer custmr[100];
	cout << "UWS Bank \n" << endl;
	cout << "Transaction Daily Report" << endl;
	cout << "=========================\n" << endl;
	cout << "\n---------Balance Before Transactions----------\n";
	cout << "----------------------------------------------\n";
	cout << "        Name     Type    Acc. Number   Balance\n";
	cout << "----------------------------------------------\n";
	pt.getAllCustomerDetails();
	for (int i = 0; i < 100; i++) {
		custmr[i] = pt.cust[i];
	}
	int k = 0;
	// Displaying the customer balance details after reading their data from the customers.dat
	while (k < pt.numberOfCustomers - 1) {
		cout << fixed;
		cout << setw(15) << custmr[k].name << setw(5)
				<< custmr[k].bAccount.accountType << setw(15)
				<< custmr[k].bAccount.accNumber << setw(10) << setprecision(2)
				<< custmr[k].bAccount.balance << endl << endl;
		k++;

	}
	cout << "\nTransactions Made" << endl;
	cout << "-----------------" << endl;
	pt.makeTransactions();
	cout << "\n\nEntering ATM Mode......\n" << endl;
	cout << "ATM Mode" << endl;
	cout << "--------" << endl;
	atm.displayOptions(pt.numberOfCustomers);
	cout << "\nBalances of all the Customers after ATM Transactions applied"
			<< endl;
	cout << "\n--------------Balance After ATM---------------\n";
	cout << "----------------------------------------------\n";
	cout << "        Name     Type    Acc. Number   Balance\n";
	cout << "----------------------------------------------\n";
	// Displaying the customer balance details after atm mode transactions are applied
	int l = 0;
	while (l < atm.numOfCust - 1) {
		cout << fixed;
		cout << setw(15) << atm.custmr[l].name << setw(5)
				<< atm.custmr[l].bAccount.accountType << setw(15)
				<< atm.custmr[l].bAccount.accNumber << setw(10)
				<< setprecision(2) << atm.custmr[l].bAccount.balance << endl
				<< endl;
		l++;
	}
	// Updating the customers.dat file with the atm mode transactions
	atm.updateBalances();
	system("pause");
	return 0;

}

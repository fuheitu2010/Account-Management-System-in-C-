#include<iostream>
#include<fstream>
#include<iomanip>
#include<time.h>
#include<string>
using namespace std;

#include"bank.h"

extern double balance;
extern double portfolio;

bank::bank()
{
}

void bank::view_balance()      //Function to view balance
{
	cout << "You have $" << balance<<" in your bank account."<<endl;
	cout << endl;
}

void bank::Deposit(double amount)      //Function to deposit money
{
	
	char tmpbuf[128];
	_strdate_s(tmpbuf, 128);           //get the system time
	
	ofstream file;
	file.open("balance.txt");
	balance = balance + amount;      //change the balance
	file << balance;
	file.close();

	file.open("history.txt",ios::app);
	file << endl << "Deposit "  << "$" << amount <<" "<<tmpbuf <<" $" << balance;  //Save to the history
	file.close();
}

void bank::withdraw(double amount)   //Function to deposit money
{
	ofstream file;
	if (amount > balance)
	{
		cout << "You have only $" << balance << " on your account, there is not enough balance to withdraw"<<endl;
	}
	else
	{
		char tmpbuf[128];
		_strdate_s(tmpbuf, 128);       //Get the system time
		file.open("balance.txt");
		balance = balance - amount;   //Change the balance
		file << balance;
		file.close();

		file.open("history.txt",ios::app);
		file << endl << "Withdraw "  << "$" << amount<< " " << tmpbuf  << " $" << balance;  //Save to the history
		file.close();
	}
}

void bank::print_history() //Function to print the history
{
	string a;
	string b;
	string c;
	string d;
	int ch;
	ifstream file;
	file.open("history.txt", ios::in);    //Open file
	ch = file.get();
	if (ch != EOF)
	{
		cout << setw(6) << "Event" << setw(13) << "Amount" << setw(8) << "Data" << setw(12) << "Balance" << endl;
		while (file.eof() == false)
		{
			file >> a;
			file >> b;
			file >> c;
			file >> d;      //Read information from file
			cout << setw(8) << a << setw(10) << b << setw(10) << c << setw(10) << d << endl; //Print
		}
		cout << endl;
	}
	else
	{
		cout << "There is not any transaction history!" << endl;
	}
		file.close();
}

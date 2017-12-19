#include<iostream>
#include"bank.h"
#include"stock.h"
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

int choice1,choice2,choice3;
double amount1;
string symbol;
double price1;
double balance;
double portfolio;        //Declare of main function variable

int share;
double wish_price;

int main()
{
	balance = 10000; //Innitial the balance
	ifstream file;
	file.open("balance.txt", ios::in | ios::out);
	if (file.eof() == false)
	{
		file >> balance;    //Read the balance if there is a balance in the txt file
	}
	file.close();
	

	bank bank1;
	stock stock1;

	menu1:
	cout << "Welcome to the Account Management System." << endl; //Print the menu
	cout << "Please select an account to access:" << endl;
	cout << "1. Stock Portfolio Account" << endl;
	cout << "2. Bank Account" << endl;
	cout << "3. Exit" << endl;

	cin >> choice1;    //Input choice
	switch (choice1)
	{
	case 1:
		while (1)
	{
		cout << "Stock Portfolio Account" << endl;      //Print the menu
		cout << "Please select an option:" << endl;
		cout << "1. Display the price for a stock symbol" << endl;
		cout << "2. Display the current portfolio" << endl;
		cout << "3. Buy shares" << endl;
		cout << "4. Sell shares" << endl;
		cout << "5. View a graph for the portfolio value" << endl;
		cout << "6. View transaction history" << endl;
		cout << "7. Return to previous menu" << endl;
		cout << "Option:";

		cin >> choice2;       //Input choice
		switch (choice2)
		{
		case 1:
			cout << "Please enter the stock symbol: ";
			cin >> symbol;
			price1=stock1.display_price(symbol);   //View stock price
			if (price1 == -100)
			{
				cout << "The symble can not found!" << endl;
			}
			else 
			{
				cout << "Company-Symbol" << setw(20) << "Price per share" << endl;  //Print the price
				cout << symbol << setw(25) << price1 << endl;
			}
			break;
		case 2:
			stock1.display_portfolio();      //View stocks
			break;
		case 3:
			cout << "Please enter the stock symbol you wish to purchase: ";
			cin >> symbol;
			cout << "Please enter the number of shares: ";
			cin >> share;
			cout << "Please enter the maximum amount you are willing to pay per share: ";
			cin >> wish_price;
			stock1.buy_shares(symbol, share, wish_price);          //Buy stocks
			break;
		case 4:
			cout << "Please enter the stock symbol you wish to sell: ";
			cin >> symbol;
			cout << "Please enter the number of shares: ";
			cin >> share;
			cout << "Please enter the minimum amount you are willing to sell per share: ";
			cin >> wish_price;
			stock1.sell_shares(symbol, share, wish_price);            //Sell stocks
			break;
		case 5:
			stock1.view_graphy();                  //Plot the graphy
			break;
		case 6:
			stock1.view_history();              //Print the transaction history
			break;
		case 7:
			stock1.save_total();   
			goto menu1;             //Goto previous menu
			break;
		}
	}
		break;
	case 2:
		while (1)
		{
			cout << "Bank Account" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. View account balance" << endl;
			cout << "2. Deposit money" << endl;
			cout << "3. Withdraw money" << endl;
			cout << "4. Print out history" << endl;
			cout << "5. Return to previous menu" << endl;    //Print the menu
			cout << "Option:";

			cin >> choice3;              //Input choice
			switch (choice3)
			{
			case 1:
				bank1.view_balance();        //View balance
				stock1.save_total();
				break;
			case 2:
				cout << "Please input the amount you wish to deposit:";
				cin >> amount1;
				bank1.Deposit(amount1);       //deposit money
				stock1.save_total();
				break;
			case 3:
				cout << "Please input the amount you wish to withdraw:";
				cin >> amount1;
				bank1.withdraw(amount1);   //Withdraw money
				stock1.save_total();
				break;
			case 4:
				bank1.print_history();     //print transaction history 
				stock1.save_total();
				break;
			case 5:
				stock1.save_total();
				goto menu1;             //Goto previous menu
				break;
			}
		}
		break;
	case 3:
		return 0;
		break;
	}
	return 0;
}
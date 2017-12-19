#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h" 

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

#include"stock.h"
#include<math.h>
#include<time.h>
#include<engine.h>

#pragma comment( lib, "libmx.lib")    
#pragma comment( lib, "libmex.lib" )     
#pragma comment( lib, "libeng.lib" )

extern double balance;
extern double portfolio;

stock::stock()         // Constructor of class stock
{
	mySize = 0;
	ifstream file;

	file.open("stock.txt", ios::in);
	string a;
	int b;
	int ch;

	portfolio = balance;
	myHead = 0;
	myTail = 0;            //Innitial the varibles
	ch = file.get();
	if (ch!=EOF)              //If the file is not empty, read the file
	{
		Node *xin;
		while (file.eof() == false)
		{
			file >> a;
			file >> b;
			xin = new Node(a, b);    //Recover the linked list
			addToEnd(xin);
			mySize++;
			save_total();
		}
	}
	file.close();
	
}

double stock::display_price(string sym)   //Function to check the price
{
	int a;
	string name;
	double pri;
	srand(time(NULL));
	a = rand() %10;                      //Generate a random number to choose a file
	ifstream file;
	if (a >4)
	{
		file.open("Results_1.txt", ios::in);
	}
	else
	{
		file.open("Results_2.txt", ios::in);
	}
	while ( file.eof()==false)      
	{
		file >> name;
		if(name == sym)
		{
			file >> pri;     //Read the file
			break;
		}
	}
	file.close();

	if(file.eof()==true)
	{
		return -100;         //If the stock is not existed, return -100
	}
	else
	{
		return pri;
	}
		
}

void stock::display_portfolio()       //Function to display the stocks
{
	double account_total=balance;
	cout << "Cash Balance: " << balance << endl;
	if (myHead == 0)
	{
		cout << "You do not have any stock" << endl;  //If the list is empty, print empty
		cout << endl;
		return;
	}

	sort();       //Sort the list

	Node *currentptr = myHead;     //Current pointer
	cout << "Company Symbol" <<setw(15)<<"Number"<<setw(20) <<"Price-per-share"<<setw(20)<<"Total Value"<<endl;
	while (currentptr != 0)
	{
		cout <<setw(6)<< currentptr->stock_symbol << setw(22)<< currentptr->stock_shares << setw(20)<<currentptr->per_price<<setw(20)<<currentptr->total1<<endl;  //Print the list
		account_total = account_total + currentptr->total1;    //Print the information
		currentptr = currentptr->next;     //point to the next node
	}

	cout << "Total portfolio value: " << account_total << endl;  //Print the total value
	cout << endl;
	save_total();
}

void stock::buy_shares(string s, int am, double p)   //  Function to buy stocks
{
	int share;
	ofstream outfile;
	double total;
	string name;
	double pri;
	int flag;

	share = am;
	pri = display_price(s);

	if (pri == -100)
	{
		cout << "The symble can not found!" << endl; //If cannot find the stock, print
		return;
	}
	total = pri*share;
	if (pri > p)            //Check the price
	{
		cout << "The cost per stock is higher than the price you are willing to pay" << endl;
	}
	else if (total > balance)      //Check whether the total price beyond the balance
	{
		cout << "The total price is " <<total<<", but you have only $ "<<balance<<" in your account, you do not have enough balance!"<<endl;
	}
	else
	{
		Node *current;         //current point
		Node *xin;
		if (myHead == 0)
		{
			xin = new Node(s, share);  //If the list is empty,build new node
			addToEnd(xin);
			mySize++;
		}
		else
		{
			current = myHead;
			while (current->stock_symbol != s)   // Check whether the Name is existed
			{
				if (current != myTail)
				{
					current = current->next;   //If not match, point to next node
				}
				else
				{
					xin = new Node(s,share);  //If the list is empty,build new node
					addToEnd(xin);       //Add to the list
					mySize++;
					flag = 1;
				}
			}
	
			if (flag!=1)
			{
				current->stock_shares = current->stock_shares + am;   //Already have this stock, plus shares
			}
			flag = 0;
		}
		
		// Save the information into text file
		save_linkedlist();
		balance = balance - total;
		char tmpbuf[128];
		_strtime_s(tmpbuf, 128);
		outfile.open("stock_transaction_history.txt",ios::app);
		outfile << endl << "Buy" << setw(10) << s << setw(10) << am << setw(10) << pri << setw(10) << total<<setw(10)<<tmpbuf;
		outfile.close();

		char tmpbuf1[128];
		_strdate_s(tmpbuf1, 128);
		outfile.open("history.txt", ios::app);
		outfile << endl << "Buy" << " $" << total<<" "<<tmpbuf1 << " $" << balance;
		outfile.close();

		outfile.open("balance.txt");
		outfile << balance;
		outfile.close();
		cout << "You have purchased " << am << " shares of " <<s << " at $" << pri << " each for a total of $" << total << endl;
		save_total();                   
	}
}

void stock::sell_shares(string s, int shares, double p) //Function to sell stocks
{
	double total;
	string name;
	double pri;
	ofstream outfile;
	pri = display_price(s);

	if (pri == -100)
	{
		cout << "The stock is not available!" << endl;     //If there is not the stock, print
		return;
	}

	total = pri*shares;
	if (pri < p)    //check the price
	{
		cout << "The cost per stock is lowwer than the price you are willing to sell" << endl;
	}
	else
	{
		Node *current;         //current point
		Node *last = 0;
		if (myHead == 0)
		{
			cout << "You do not have this stock, not be able to sell!";  //If do not have the stock,print
			return;
		}
		else
		{
			current = myHead;
			while (current->stock_symbol != s)   // Check whether the Name is existed
			{
				last = current;
				if (current != myTail)
				{
					current = current->next;   //If not match, point to next node
				}
				else
				{
					cout << "You do not have this stock, not be able to sell!"<<endl;  //If do not have the stock,print
					return;
				}
			}

			if (shares > current->stock_shares)
			{
				cout<< "You do not have enough shares to sell!"<<endl;  //If do not have the enough shares ,print
				return;
			}
			else if (shares == current->stock_shares)
			{
				if (current == myHead)
				{
					myHead = current->next;
					delete current;         //If sold all the stock, delete node
					mySize--;
				}
				else if(current==myTail)
				{
					myTail = last;
					delete current;      //If sold all the stock, delete node
					mySize--;
				}
				else
				{
					last->next = current->next;           //change the value of last pointer
					delete current;                  //Delete node
					mySize--;
				}
			}
			else
			{
				current->stock_shares = current->stock_shares - shares;    //Change the number of shares
			}
		}
		
		//Save to txt file
		save_linkedlist();
		balance = balance + total;
		char tmpbuf[128];
		_strtime_s(tmpbuf, 128);
		outfile.open("stock_transaction_history.txt", ios::app);
		outfile << endl << "Sell" << setw(10) <<s << setw(10) << shares << setw(10) << pri << setw(10) << total<<setw(10)<<tmpbuf;
		outfile.close();

		char tmpbuf1[128];
		_strdate_s(tmpbuf1, 128);
		outfile.open("history.txt", ios::app);
		outfile << endl << "Sell" << " $" << total <<" "<<tmpbuf1<<" $" << balance;
		outfile.close();

		outfile.open("balance.txt");
		outfile << balance;
		outfile.close();
		cout << "You have sold "<<shares<< " shares of "<<s<<" at $"<<pri<<" each for a total of $"<<total<< endl;
		save_total();
	}
}

void stock::view_history()              //Function to view history
{
	string a;
	string b;
	string c;
	string d;
	string e;
	string f;
	ifstream file;
	int ch;
	file.open("stock_transaction_history.txt", ios::in);
	ch = file.get();
	if (ch != EOF)    //Check whether the file is empty
	{
		cout << "Event" << setw(10) << "Symbol" << setw(10) << "Number" << setw(10) << "Per price" << setw(10) << "Total" << setw(10) << "Time" << endl;
		while (file.eof() == false)
		{
			file >> a;
			file >> b;
			file >> c;
			file >> d;
			file >> e;
			file >> f;      //Read the file
			cout << setw(4) << a << setw(10) << b << setw(8) << c << setw(12) << d << setw(13) << e << setw(10) << f << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "There is not any transaction!"<<endl;
	}
	file.close();
	save_total();
}

void stock::addToEnd(Node *a)   //Function to add nodes at end
{
	Node *newptr = a;          //Pointer to the new node
	if (myHead == 0)
	{
		myHead = myTail = newptr;   //If the list is empty, head pointer and tail pointer equal to new pointer
	}
	else
	{
		myTail->next = newptr; //Orinial last pointer's next point to the new node
		myTail = newptr;
	}
}

void stock::sort()
{
	double price;
	Node *currentptr = myHead;     //Current pointer
	
	while (currentptr != 0)
	{
		price = display_price(currentptr->stock_symbol);
		currentptr->per_price = price;
		currentptr->total1 = price*currentptr->stock_shares;
		currentptr = currentptr->next;     //point to the next node
	}

	Node* currentptr2 = myHead;
	Node* last11 = 0;
	Node* temp = 0;
	bool flag = false;

	for (int i = 0; i < mySize; i++)            // Code to sort the list, bubble sort
	{
		
			while (currentptr2->next != 0)
			{
				temp = currentptr2->next;

				if ((currentptr2->total1)< (temp->total1))
				{
					flag = true;
					currentptr2->next = temp->next;
					temp->next = currentptr2;
					if (last11 != 0)
						last11->next = temp;
					last11 = temp;
					if (myHead == currentptr2)
						myHead = temp;
					if (currentptr2->next == 0)
						myTail = currentptr2;
				}
				else
				{
					last11 = currentptr2;
					currentptr2 = currentptr2->next;
				}
			}
			if (flag == false)
				break;
			else
			{
				last11 = 0;
				currentptr2 = myHead;
				flag = false;
			}	
	}
}

void stock::view_graphy()   //Call matlab to plot
{
	save_total();
	Node *currentptr=myHead;
	
	double a[10] = { 0,1,2,3,4,5,6,7,8,9 }; //Array to pass value
	double b[10] = { 0 };

	ifstream file;
	file.open("portfolio.txt", ios::in);
	while (file.eof()!=true)
	{
		for (int i = 0; i < 10; i++)
		{
			file >> b[i];         //Read recent portfolios
		}
	}
	file.close();

	Engine *ep;
	ep = engOpen(NULL);      //Open the matlab engine
    if (ep == NULL)
	{
		cout << "Error: Not Found"<< endl;
		exit(1);
	}

	
	mxArray *A;         //Pointer A
	mxArray *B;        // Pointer B
	A = mxCreateDoubleMatrix(1, 10, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)a, sizeof(double)*10); //Pass the value
	engPutVariable(ep, "a", A);

	B = mxCreateDoubleMatrix(1, 10, mxREAL);
	memcpy((void *)mxGetPr(B), (void *)b, sizeof(double) * 10);   //Pass the value
	engPutVariable(ep, "b", B);

	engEvalString(ep, "plot(a, b); ");     //Use matlab to plot
}

void stock::save_linkedlist()  //Function to save the list, read after restart
{
	Node *currentptr = myHead;     //Current pointer
	ofstream file;
	file.open("stock.txt", ios::out);

	while (currentptr != 0)
	{
		file <<" "<< currentptr->stock_symbol << " " << currentptr->stock_shares;  //save to the file
		currentptr = currentptr->next;
	}
	file.close();
}

void stock::save_total()     //Function to save the total portfolio
{
	portfolio = 0;
	Node *currentptr = myHead;
	double price;
	while (currentptr != 0)
	{
		price = display_price(currentptr->stock_symbol);
		currentptr->total1 = price*currentptr->stock_shares;
		portfolio = portfolio + currentptr->total1;
		currentptr = currentptr->next;
	}
	portfolio = portfolio + balance;             //Calculate the total portfolio

	ofstream outfile;
	outfile.open("portfolio.txt", ios::app);   //Save to the txt file
	outfile << endl << portfolio;
	outfile.close();
}




#pragma once

#include<iostream>
#include<string>
using namespace std;

#include"account.h"

class Node {                     //Declare of class Node
	friend class stock;
public:
	Node(string& name, int num)         //Constructor
		:stock_symbol(name), stock_shares(num)
	{
		this->next = NULL;
	}
private:
	string stock_symbol;
	int stock_shares;
	double total1;
	Node *next;     //Declare of member data
	double per_price;

};


class stock :public account     //Declare of class stock
{
public:
	stock();
	double display_price(string);
	void display_portfolio();
	void buy_shares(string, int, double);
	void sell_shares(string, int, double);   //Declare of functions
	void view_history();
	void addToEnd(Node *);
	void sort();
	void view_graphy();
	void save_linkedlist();
	void save_total();
private:
	Node *myHead;
	Node *myTail;
	int mySize;     //Declare of variables

};

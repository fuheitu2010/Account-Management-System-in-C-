#pragma once

#include"account.h"
class bank:public account //Declare of class bank
{
public:
	bank();
	void view_balance();
	void Deposit(double);
	void withdraw(double); //Declare of functions
	void print_history();

};
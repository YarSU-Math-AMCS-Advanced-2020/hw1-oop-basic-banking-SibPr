#pragma once
#include "auxiliary_classes.h"


class Account {
private:
	int account_id;
	int client_id;
	Currency currency;
	double balance;
	double account_limit;

public:
	Account(int _account_id = -1, int _client_id = -1, Currency _currency = Currency::USD,
		double _balance = 0, double _limit = 15000);

	int get_account_id() { return account_id; }
	int get_client_id() { return client_id; }
	Currency get_currency() { return currency; }
	double get_balance() { return balance; }
	double get_account_limit() { return account_limit; }

	void set_balance(double _balance) { balance = _balance; }
	void set_limit(double _limit) { account_limit = _limit; }
};
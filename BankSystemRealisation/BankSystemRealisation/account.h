#pragma once
#include "auxiliary_classes.h"

class Account {
public:
	int account_id;
	int client_id;
	Currency currency;
	double balance;
	double limit;

	Account(int _account_id = -1, int _client_id = -1, Currency _currency = Currency::USD,
		double _balance = 0, double _limit = 15000) {
		account_id = _account_id;
		client_id = _client_id;
		currency = _currency;
		balance = _balance;
		limit = _limit;
	}

	int get_account_id() { return account_id; }
	int get_client_id() { return client_id; }
	Currency get_currency() { return currency; }
	double get_balance() { return balance; }
	double get_limit() { return limit; }

	void set_balance(double _balance) { balance = _balance; }
	void set_limit(double _limit) { limit = _limit; }
};
#pragma once
#include "auxiliary_classes.h"

class Account {
public:
	int account_id;
	Currency currency;
	double balance;
	double limit;

	Account(int _account_id, Currency _currency, double _balance = 0, double _limit = 15000) {
		account_id = _account_id;
		currency = _currency;
		balance = _balance;
		limit = _limit;
	}
};
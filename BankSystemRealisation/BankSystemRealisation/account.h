#pragma once
#include "bank.h"

enum Currency { RUB, USD, EUR };

class Account {
public:
	int account_id;
	Currency currency = USD;
	double balance;
};
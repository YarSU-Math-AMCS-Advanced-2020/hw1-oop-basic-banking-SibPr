#pragma once
#include "auxiliary_classes.h"

class Account {
public:
	int account_id;
	Currency currency = USD;
	double balance;
};
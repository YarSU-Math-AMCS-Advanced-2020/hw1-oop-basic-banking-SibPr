#pragma once
#include "account.h"
#include "auxiliary_classes.h"
#include <time.h>


class Transaction {
private:
	Account* sender_account;
	Account* receiver_account;
	double amount;
	time_t transaction_time;
	Currency currency;
	OperationStatus current_status;

public:
	Transaction(Account* _sender_account, Account* _receiver_account, double _amount);

	void commit_transaction();

	OperationStatus get_transaction_status() { return current_status; }
};
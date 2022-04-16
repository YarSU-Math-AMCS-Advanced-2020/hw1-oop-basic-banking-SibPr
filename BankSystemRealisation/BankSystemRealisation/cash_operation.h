#pragma once
#include "bank.h"

enum OperationStatus { InQueue, Processing, Complete, Rejected };
enum OperationType { Withdrawal, Replenishment };
enum OperationPlace { Bank, ATM };

class CashOperation {
public:
	Card& card;
	Account& account = card.get_account();
	OperationType type;
	int amount;
	Currency currency;
	time_t time;
	OperationStatus current_status;
	OperationPlace place;
	int bank_branch_id;
};
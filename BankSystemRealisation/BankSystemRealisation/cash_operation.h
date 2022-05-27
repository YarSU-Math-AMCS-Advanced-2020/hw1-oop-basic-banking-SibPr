#pragma once
#include "account.h"
#include "auxiliary_classes.h"


class CashOperation {
private:
	OperationType type;
	Account* account;
	double amount;
	Currency currency;
	time_t operation_time;
	OperationStatus current_status;
	OperationPlace place;
	int bank_branch_id;

public:
	CashOperation(OperationType _type, Account* _account, double _amount,
		OperationPlace _place, int _bank_branch_id);

	void commit_withdrawal_operation();
	void commit_replenishment_operation();

	OperationType get_type() { return type; }
	Account* get_account() { return account; }
	double get_amount() { return amount; }
	Currency get_currency() { return currency; }
	time_t get_operation_time() { return operation_time; }
	OperationStatus get_operation_status() { return current_status; }
	OperationPlace get_place() { return place; }
	int get_bank_branch_id() { return bank_branch_id; }
};
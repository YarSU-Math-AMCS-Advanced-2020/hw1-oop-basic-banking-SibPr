#pragma once
#include "auxiliary_classes.h"


class CashOperation {
public:
	OperationType type;
	Account* account;
	double amount;
	Currency currency;
	time_t operation_time;
	OperationStatus current_status;
	OperationPlace place;
	int bank_branch_id;

	CashOperation(OperationType _type, Account* _account, double _amount, 
		OperationPlace _place, int _bank_branch_id) {
		type = _type;
		this->account = _account;
		amount = _amount;
		currency = _account->get_currency();
		operation_time = time(NULL);
		current_status = OperationStatus::in_queue;
		place = _place;
		bank_branch_id = _bank_branch_id;
	}

	void commit_withdrawal_operation() {
		current_status = processing;

		if (type != OperationType::withdrawal || amount > account->get_balance() || amount > account->get_limit()) {
			// ошибка
			current_status = rejected;
			return;
		}

		account->set_balance(account->get_balance() - amount);
		// Client has received his $$$

		current_status = complete;
	}

	void commit_replenishment_operation() {
		current_status = processing;

		if (type != OperationType::replenishment || amount > account->get_limit()) {
			// ошибка
			current_status = rejected;
			return;
		}

		account->set_balance(account->get_balance() + amount);
		// Client has made a deposit

		current_status = complete;
	}

	OperationStatus get_operation_status() { return current_status; }
};
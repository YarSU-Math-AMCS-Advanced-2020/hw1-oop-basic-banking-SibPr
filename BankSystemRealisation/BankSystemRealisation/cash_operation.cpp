#include "cash_operation.h"

CashOperation::CashOperation(OperationType _type, Account* _account, 
	double _amount, OperationPlace _place, int _bank_branch_id) {
	type = _type;
	this->account = _account;
	amount = _amount;
	currency = _account->get_currency();
	operation_time = time(NULL);
	current_status = OperationStatus::in_queue;
	place = _place;
	bank_branch_id = _bank_branch_id;
}

void CashOperation::commit_withdrawal_operation() {
	current_status = processing;

	if (type != OperationType::withdrawal) {
		// ошибка Invalid operation type
		current_status = rejected;
		return;
	}
	else if (amount > account->get_balance()) {
		// ошибка Insufficient funds
		current_status = rejected;
		return;
	}
	else if (amount > account->get_account_limit()) {
		// ошибка The amount exceeds the limit
		current_status = rejected;
		return;
	}

	account->set_balance(account->get_balance() - amount);
	// Client has received his $$$

	current_status = complete;
}

void CashOperation::commit_replenishment_operation() {
	current_status = processing;

	if (type != OperationType::replenishment) {
		// ошибка Invalid operation type
		current_status = rejected;
		return;
	}
	else if (amount > account->get_account_limit()) {
		// ошибка The amount exceeds the limit
		current_status = rejected;
		return;
	}

	account->set_balance(account->get_balance() + amount);
	// Client has made a deposit

	current_status = complete;
}
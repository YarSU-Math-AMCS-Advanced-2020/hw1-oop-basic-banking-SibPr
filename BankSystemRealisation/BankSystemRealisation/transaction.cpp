#include "transaction.h"

Transaction::Transaction(Account* _sender_account, Account* _receiver_account, double _amount) {
	this->sender_account = _sender_account;
	this->receiver_account = _receiver_account;
	amount = _amount;
	transaction_time = time(NULL);
	currency = _sender_account->get_currency();
	current_status = OperationStatus::in_queue;
}

void Transaction::commit_transaction() {
	current_status = processing;

	if (currency != receiver_account->get_currency() ||
		amount > sender_account->get_balance() || amount > sender_account->get_limit()) {
		// ошибка
		current_status = rejected;
		return;
	}

	sender_account->set_balance(sender_account->get_balance() - amount);
	receiver_account->set_balance(receiver_account->get_balance() + amount);

	current_status = complete;
}
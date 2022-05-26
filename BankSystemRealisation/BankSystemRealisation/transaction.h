#pragma once
#include "auxiliary_classes.h"
#include <time.h>


class Transaction {
public:
	Account* sender_account;
	Account* receiver_account;
	int amount;
	time_t transaction_time;
	OperationStatus current_status;

	Transaction(Account* _sender_account, Account* _receiver_account, int _amount) {
		this->sender_account = _sender_account;
		this->receiver_account = _receiver_account;
		amount = _amount;
		transaction_time = time(NULL);
		current_status = in_queue;
	}

	void commit_transaction() {
		current_status = processing;

		if (sender_account->get_currency() != receiver_account->get_currency() ||
			amount > sender_account->get_balance() || amount > sender_account->get_limit()) {
			// ошибка
			current_status = rejected;
			return;
		}

		sender_account->set_balance(sender_account->balance - amount);
		receiver_account->set_balance(receiver_account->balance + amount);

		current_status = complete;
	}

	OperationStatus get_transaction_status() { return current_status; }
};
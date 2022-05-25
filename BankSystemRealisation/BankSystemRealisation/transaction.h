#pragma once
#include "auxiliary_classes.h"


class Transaction {
public:
	Card& sender_card;
	Card& receiver_card;
	Account& sender_account = sender_card.get_account();
	Account& receiver_account = receiver_card.get_account();
	int amount;
	Currency currency;
	time_t time;
	//TransactionStatus current_status;
};
#pragma once
#include "auxiliary_classes.h"


class Card {
public:
	Account* account;
	int card_id;
	bool is_debet = true;
	PaymentSystem payment_system;
	ShortDate expiration_date;

	Card() {
		account = new Account();
	}
	Account* get_account() { return account; }
};
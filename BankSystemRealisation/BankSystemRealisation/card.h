#pragma once
#include "auxiliary_classes.h"


class Card {
private:
	Account& account;
public:
	int card_id;
	bool is_debet = true;
	PaymentSystem payment_system;
	ShortDate expiration_date;

	Account& get_account() { return this->account; }
};
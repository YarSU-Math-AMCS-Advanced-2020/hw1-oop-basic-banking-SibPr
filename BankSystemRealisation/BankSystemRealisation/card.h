#pragma once
#include "bank.h"

enum PaymentSystem { Lisa, MasterBart, HoMiR };

struct ShortDate {
	int month;
	int year;

	ShortDate(int _month = 1, int _year = 1970) {
		month = _month;
		year = _year;
	}
};

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
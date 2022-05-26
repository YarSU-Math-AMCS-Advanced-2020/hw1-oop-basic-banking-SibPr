#pragma once
#pragma warning(disable : 4996)
#include "auxiliary_classes.h"


class Card {
public:
	int card_id;
	Account* account;
	CardType type = CardType::debet;
	PaymentSystem payment_system;
	ShortDate expiration_date;

	Card(int _card_id, Account* _account, PaymentSystem _payment_system) {
		card_id = _card_id;
		account = _account;
		payment_system = _payment_system;

		auto now = Clock::now();
		std::time_t now_c = Clock::to_time_t(now);
		struct tm* parts = std::localtime(&now_c);
		expiration_date = ShortDate(1 + parts->tm_mon, 1905 + parts->tm_year);
	}

	void set_account(Account* _account) { account = _account; }
};
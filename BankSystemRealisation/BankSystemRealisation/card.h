#pragma once
#pragma warning(disable : 4996)
#include "account.h"
#include "auxiliary_classes.h"


class Card {
private:
	int card_id;
	Account* account;
	CardType type = CardType::debet;
	PaymentSystem payment_system;
	ShortDate expiration_date;
	double card_limit;

public:
	Card(int _card_id, Account* _account, PaymentSystem _payment_system, double _card_limit = 10000);

	int get_card_id() { return card_id; }
	Account* get_account() { return account; }
	CardType get_type() { return type; }
	PaymentSystem get_payment_system() { return payment_system; }
	ShortDate get_expiration_date() { return expiration_date; }
	double get_card_limit() { return card_limit; }

	void set_account(Account* _account) { account = _account; }
	void set_limit(double _limit) { card_limit = _limit; }
};
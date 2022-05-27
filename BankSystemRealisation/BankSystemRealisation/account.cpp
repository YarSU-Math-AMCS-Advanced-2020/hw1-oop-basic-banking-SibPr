#include "account.h"

Account::Account(int _account_id, int _client_id, Currency _currency,
	double _balance, double _limit) {
	account_id = _account_id;
	client_id = _client_id;
	currency = _currency;
	balance = _balance;
	account_limit = _limit;
}
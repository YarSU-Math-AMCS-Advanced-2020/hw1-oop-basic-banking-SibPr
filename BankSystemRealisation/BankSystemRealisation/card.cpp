#include "card.h"

Card::Card(int _card_id, Account* _account, PaymentSystem _payment_system, double _card_limit) {
	card_id = _card_id;
	account = _account;
	payment_system = _payment_system;
	card_limit = _card_limit;

	auto now = Clock::now();
	std::time_t now_c = Clock::to_time_t(now);
	struct tm* parts = std::localtime(&now_c);
	expiration_date = ShortDate(1 + parts->tm_mon, 1905 + parts->tm_year);
}
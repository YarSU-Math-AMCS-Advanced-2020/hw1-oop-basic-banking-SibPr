#include "bank.h"

int main() {
	BankSystem b;
	b.register_client(Personal);
	b.register_client(LegalEntity);
	b.change_client_info(1, "sex", "okdela");

	cout << b.personal_clients[0].name;

	return 0;
}
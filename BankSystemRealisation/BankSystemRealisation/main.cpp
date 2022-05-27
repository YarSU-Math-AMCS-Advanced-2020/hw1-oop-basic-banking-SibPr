#include "bank.h"

int main() {
	BankSystem bank = BankSystem("DobroBank");

	// Client registry:
	bank.register_personal_client("Denis", "Ivanov", "Ivanovich", "M", FullDate(4, 7, 1978), "Yaroslavl, Pobedy str., 7", "+79201482329", "183243 7813");
	bank.register_personal_client("Ivan", "Petrov", "Ivanovich", "M", FullDate(5, 7, 1998), "Kostroma, Lenina str., 60", "+79151382329", "188173 7813");
	bank.register_personal_client("Georgy", "Korolev", "Petrovich", "M", FullDate(4, 9, 1948), "Yaroslavl, Pavlova str., 50", "+79201482543", "154373 7433");
	bank.register_personal_client("Vanya", "Novikov", "Ivanovich", "M", FullDate(13, 7, 1970), "Yaroslavl, Lenina str., 60", "+79541454329", "187673 7813");
	bank.register_personal_client("Zoya", "Smirnova", "Pavlovna", "W", FullDate(26, 12, 2000), "Moscow, Frunze str., 54", "+79201583139", "188143 7813");
	bank.register_legal_entity_client("OOO Technology", "58792134", "Moscow, Pervomayskaya str., 32");
	bank.register_legal_entity_client("OAO Ararat", "34252134", "Petropavlovsk Kamchatsky, Lenina str., 5");
	bank.register_legal_entity_client("ZAO Fact Channel", "58792655", "St. Petersburg, Pushkina str., 45");

	bank.print_bank_info();

	// Client info change:
	cout << endl << endl << endl;
	bank.print_client_info(3);

	bank.change_client_info(3, ClientInfoField::Address, "Orel, Lenina str., 5");

	bank.print_client_info(3);

	// Account creation:
	cout << endl << endl << endl;
	bank.print_client_info(8);

	bank.create_account(8, Currency::USD);
	bank.create_account(4, Currency::EUR);
	bank.create_account(8, Currency::USD);
	bank.create_account(3, Currency::EUR);
	bank.create_account(4, Currency::RUB);

	bank.print_client_info(8);

	// Account closure:
	cout << endl << endl << endl;
	bank.release_card(2, HoMiR);
	bank.commit_cash_operation(replenishment, 0, 14345, ATM, 214);

	bank.print_account_info(2, false);
	bank.close_account_with_transaction(2, 0);
	bank.print_account_info(2, false);

	bank.print_account_info(0, false);
	bank.close_account_with_withdrawal(0, ATM, 215);
	bank.print_account_info(0, false);

	// Set the operation limit for the account:
	cout << endl << endl << endl;
	bank.print_account_info(1, false);
	bank.set_account_limit(1, 5500);
	bank.print_account_info(1, false);

	// Release a card, replenish it, commit transaction and a withdrawal:
	cout << endl << endl << endl;
	bank.release_card(1, Lisa);
	bank.release_card(3, HoMiR);
	bank.commit_cash_operation(replenishment, 1, 4900, ATM, 214);
	bank.print_client_info(4);
	bank.commit_transaction(1, 2, 3459.67);
	bank.print_client_info(4);
	bank.print_client_info(3);
	bank.commit_cash_operation(withdrawal, 2, 500, ATM, 214);
	bank.print_client_info(3);

	// Rebind a card to another account:
	cout << endl << endl << endl;
	bank.print_card_info(1);
	bank.rebind_card(1, 4);
	bank.print_card_info(1);

	// Set card limit:
	cout << endl << endl << endl;
	bank.set_card_limit(1, 99996);
	bank.print_card_info(1);

	// Card closure:
	cout << endl << endl << endl;
	bank.close_card(1);
	bank.print_card_info(1);
	return 0;
}
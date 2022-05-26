#include "bank.h"

int main() {
	BankSystem bank;
	bank.register_personal_client("Denis", "Ivanov", "Ivanovich", "M", FullDate(4, 7, 1978), "Yaroslavl, Pobedy str., 7", "+79201482329", "183243 7813");
	bank.register_personal_client("Ivan", "Petrov", "Ivanovich", "M", FullDate(5, 7, 1998), "Kostroma, Lenina str., 60", "+79151382329", "188173 7813");
	bank.register_personal_client("Georgy", "Korolev", "Petrovich", "M", FullDate(4, 9, 1948), "Yaroslavl, Pavlova str., 50", "+79201482543", "154373 7433");
	bank.register_personal_client("Vanya", "Novikov", "Ivanovich", "M", FullDate(13, 7, 1970), "Yaroslavl, Lenina str., 60", "+79541454329", "187673 7813");
	bank.register_personal_client("Zoya", "Smirnova", "Pavlovna", "W", FullDate(26, 12, 2000), "Moscow, Frunze str., 54", "+79201583139", "188143 7813");
	bank.register_legal_entity_client("OOO Technology", "58792134", "Moscow, Pervomayskaya str., 32");
	bank.register_legal_entity_client("OAO Ararat", "34252134", "Petropavlovsk Kamchatsky, Lenina str., 5");
	bank.register_legal_entity_client("ZAO Fact Channel", "58792655", "St. Petersburg, Pushkina str., 45");

	bank.change_client_info(3, ClientInfoField::name, "OOO Everest");
	for (int i = 0; i < bank.legal_entity_clients.size(); i++) {
		cout << bank.legal_entity_clients[i].name << endl;
	}

	bank.create_account(8, Currency::USD);
	vector<Account> tmp = bank.personal_clients[4].get_accounts();
	for (int i = 0; i < tmp.size(); i++)
		cout << tmp[i].account_id << " " << tmp[i].currency << " " <<
		tmp[i].balance << " " << tmp[i].limit << " " << endl;
	return 0;
}
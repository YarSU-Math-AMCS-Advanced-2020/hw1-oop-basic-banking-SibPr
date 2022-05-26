#include "client.h"

PersonalClient::PersonalClient() {
	name = "IndefiniteName";
	surname = "IndefiniteSurname";
	patronymic = "IndefinitePatronymic";
	sex = "IndefiniteSex";
	birth_date = FullDate();
	address = "IndefiniteAddress";
	phone_number = "IndefiniteNumber";
	passport = "IndefinitePassportInfo";
}

PersonalClient::PersonalClient(string _name, string _surname, string _patronymic, string _sex,
	FullDate _birth_date, string _address, string _phone_number, string _passport) {
	name = _name;
	surname = _surname;
	patronymic = _patronymic;
	sex = _sex;
	birth_date = _birth_date;
	address = _address;
	phone_number = _phone_number;
	passport = _passport;
}

LegalEntityClient::LegalEntityClient() {
	name = "IndefiniteName";
	entity_registration_number = "IndefiniteRegistrationNumber";
	entity_address = "IndefiniteAddress";
}

LegalEntityClient::LegalEntityClient(string _name, string _entity_registration_number, string _entity_address) {
	name = _name;
	entity_registration_number = _entity_registration_number;
	entity_address = _entity_address;
}

void Client::create_account(Currency currency) {
	accounts.push_back(new Account(client_id, currency));
}

vector<Account> Client::get_accounts() {
	vector<Account> tmp;
	for (int i = 0; i < accounts.size(); i++)
		tmp.push_back(*accounts[i]);
	return tmp;
}
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "account.h"
#include "card.h"
#include "auxiliary_classes.h"
using namespace std;


class Client {
public:
	int client_id = 0;
	ClientType client_type;
	vector<Account*> accounts;
	vector<Card*> cards;

	void set_client_id(int _client_id) { client_id = _client_id; }
	void set_client_type(ClientType _client_type) { client_type = _client_type; }
	void create_account(Currency currency);
	vector<Account> get_accounts();
};


class PersonalClient : public Client {
public:
	string name;
	string surname;
	string patronymic;
	string sex;
	FullDate birth_date;
	string address;
	string phone_number;
	string passport;

	PersonalClient();
	PersonalClient(string _name, string _surname, string _patronymic, string _sex,
		FullDate _birth_date, string _address, string _phone_number, string _passport);
};


class LegalEntityClient : public Client {
public:
	string name;
	string entity_registration_number;
	string entity_address;

	LegalEntityClient();
	LegalEntityClient(string _name, string _entity_registration_number, string _entity_address);
};
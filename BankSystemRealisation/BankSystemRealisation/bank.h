#pragma once
#include <iostream>
#include "client.h"
#include "account.h"
#include "card.h"
#include "transaction.h"
#include "cash_operation.h"
#include <ctime>
#include <vector>
using namespace std;


class BankSystem {
public:
	vector<PersonalClient> personal_clients;
	vector<LegalEntityClient> legal_entity_clients;
	vector<Account> accounts;
	vector<Transaction> transactions;
	vector<CashOperation> cash_operations;

	int last_personal_client_id = 0;
	int last_legal_entity_client_id = 1;
	int transaction_limit = 5000;
	int band_operation_limit = 5000;

	bool is_valid_id(int client_id);
	ClientType get_client_type(int client_id);

	void register_personal_client(string name, string surname, string patronymic,
		string sex, FullDate birth_date, string address, string phone_number, string passport);
	void register_legal_entity_client(string name, string entity_registration_number, string entity_address);
	void change_client_info(int client_id, ClientInfoField property_to_change, string new_property);
	void create_account(int client_id, Currency currency);
};
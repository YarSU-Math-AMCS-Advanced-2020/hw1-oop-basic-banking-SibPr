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

	void register_client(ClientType client_type);
	void change_client_info(int client_id, string property_to_change, string new_property);
};
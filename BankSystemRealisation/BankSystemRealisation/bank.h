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
	vector<PersonalClient*> personal_clients;
	vector<LegalEntityClient*> legal_entity_clients;
	vector<Account*> accounts;
	vector<Card*> cards;
	vector<Transaction*> transactions;
	vector<CashOperation*> cash_operations;

	int last_personal_client_id = 0;
	int last_legal_entity_client_id = 1;
	int last_account_id = 0;
	int last_card_id = 0;

	bool is_valid_client_id(int client_id);
	bool is_valid_account_id(int account_id);
	bool is_valid_card_id(int card_id);
	ClientType get_client_type(int client_id);

	void register_personal_client(string name, string surname, string patronymic,
		string sex, FullDate birth_date, string address, string phone_number, string passport);
	void register_legal_entity_client(string name, string entity_registration_number, string entity_address);
	void change_client_info(int client_id, ClientInfoField property_to_change, string new_property);
	void create_account(int client_id, Currency currency);
	void close_account_with_transaction(int account_id, int receiver_account_id);
	void close_account_with_withdrawal(int account_id, OperationPlace place, int bank_branch_id);
	void release_card(int account_id, PaymentSystem payment_system);
	void rebind_card(int card_id, int account_id);
	void commit_transaction(int sender_card_id, int receiver_card_id, double amount);
	void commit_cash_operation(OperationType type, int card_id, double amount, OperationPlace place, int bank_branch_id);
};
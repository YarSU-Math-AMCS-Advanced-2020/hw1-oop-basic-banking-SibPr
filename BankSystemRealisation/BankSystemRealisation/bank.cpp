#include "bank.h"

bool BankSystem::is_valid_client_id(int client_id) {
	if (client_id < 0 || client_id % 2 == 0 && client_id > last_personal_client_id ||
		client_id % 2 == 1 && client_id > last_legal_entity_client_id) {
		//ошибка
		cout << "Incorrect client id, try again.\n";
		return false;
	}
	return true;
}

bool BankSystem::is_valid_account_id(int account_id) {
	if (account_id < 0 || account_id > last_account_id) {
		//ошибка
		cout << "Incorrect client id, try again.\n";
		return false;
	}
	return true;
}

ClientType BankSystem::get_client_type(int client_id) {
	if (client_id % 2 == 0) return Personal;
	else return LegalEntity;
}

void BankSystem::register_personal_client(string name, string surname, string patronymic,
	string sex, FullDate birth_date, string address, string phone_number, string passport) {
	PersonalClient new_client(name, surname, patronymic, sex,
		birth_date, address, phone_number, passport);
	new_client.set_client_id(last_personal_client_id);
	new_client.set_client_type(Personal);
	last_personal_client_id += 2;
	personal_clients.push_back(new_client);
}

void BankSystem::register_legal_entity_client(string name, 
	string entity_registration_number, string entity_address) {
	LegalEntityClient new_client(name, entity_registration_number, entity_address);
	new_client.set_client_id(last_legal_entity_client_id);
	new_client.set_client_type(LegalEntity);
	last_legal_entity_client_id += 2;
	legal_entity_clients.push_back(new_client);
}

void BankSystem::change_client_info(int client_id, ClientInfoField property_to_change, string new_property) {
	if (!is_valid_client_id(client_id)) {
		// ошибка
		return;
	}
	ClientType client_type = this->get_client_type(client_id);

	if (client_type == Personal) {
		switch (property_to_change) {
		case name: personal_clients[client_id / 2].name = new_property; break;
		case surname: personal_clients[client_id / 2].surname = new_property; break;
		case address: personal_clients[client_id / 2].address = new_property; break;
		case phone_number: personal_clients[client_id / 2].phone_number = new_property; break;
		case passport: personal_clients[client_id / 2].passport = new_property; break;
		default:
			//ошибка
			break;
		}
	}
	else {
		switch (property_to_change) {
		case name: legal_entity_clients[client_id / 2].name = new_property; break;
		case entity_registration_number: legal_entity_clients[client_id / 2].entity_registration_number = new_property; break;
		case entity_address: legal_entity_clients[client_id / 2].entity_address = new_property; break;
		default:
			// ошибка
			break;
		}
	}
}

void BankSystem::create_account(int client_id, Currency currency) {
	if (!is_valid_client_id(client_id)) {
		// ошибка
		return;
	}

	Account *new_account = new Account(last_account_id, client_id, currency);
	accounts.push_back(new_account);
	last_account_id++;
}

void BankSystem::close_account_with_transaction(int account_id, int receiver_account_id) {
	if (!is_valid_account_id(account_id) || !is_valid_account_id(receiver_account_id) || account_id == receiver_account_id) {
		// ошибка
		return;
	}

	Account* sender_account = accounts[account_id];
	Account* receiver_account = accounts[receiver_account_id];
	sender_account->set_limit(DBL_MAX);
	Transaction *transaction = new Transaction(sender_account, receiver_account, sender_account->get_balance());
	transactions.push_back(transaction);
	transaction->commit_transaction();

	if (transaction->get_transaction_status() == OperationStatus::complete) {
		delete accounts[account_id];
		accounts.erase(accounts.begin() + account_id);
	}
	else {
		// ошибка
		return;
	}
}

void BankSystem::close_account_with_withdrawal(int account_id, OperationPlace place, int bank_branch_id) {
	if (!is_valid_account_id(account_id)) {
		// ошибка
		return;
	}

	Account* account = accounts[account_id];
	account->set_limit(DBL_MAX);
	CashOperation* cash_operation = new CashOperation(OperationType::withdrawal, account,
		account->get_balance(), place, bank_branch_id);
	cash_operations.push_back(cash_operation);
	cash_operation->commit_withdrawal_operation();

	if (cash_operation->get_operation_status() == OperationStatus::complete) {
		delete accounts[account_id];
		accounts.erase(accounts.begin() + account_id);
	}
	else {
		// ошибка
		return;
	}
}
#include "bank.h"

bool BankSystem::is_valid_client_id(int client_id) {
	if (client_id < 0 || client_id % 2 == 0 && client_id > last_personal_client_id ||
		client_id % 2 == 1 && client_id > last_legal_entity_client_id) {
		return false;
	}
	return true;
}

bool BankSystem::is_valid_account_id(int account_id) {
	if (account_id < 0 || account_id > last_account_id) {
		return false;
	}
	return true;
}

bool BankSystem::is_valid_card_id(int card_id) {
	if (card_id < 0 || card_id > last_card_id) {
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
	PersonalClient* new_client = new PersonalClient(name, surname, patronymic, sex,
		birth_date, address, phone_number, passport);
	new_client->set_client_id(last_personal_client_id);
	new_client->set_client_type(Personal);
	last_personal_client_id += 2;
	personal_clients.push_back(new_client);
}

void BankSystem::register_legal_entity_client(string name, 
	string entity_registration_number, string entity_address) {
	LegalEntityClient* new_client = new LegalEntityClient(name, entity_registration_number, entity_address);
	new_client->set_client_id(last_legal_entity_client_id);
	new_client->set_client_type(LegalEntity);
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
		case name: personal_clients[client_id / 2]->set_name(new_property); break;
		case surname: personal_clients[client_id / 2]->set_surname(new_property); break;
		case address: personal_clients[client_id / 2]->set_address(new_property); break;
		case phone_number: personal_clients[client_id / 2]->set_phone_number(new_property); break;
		case passport: personal_clients[client_id / 2]->set_passport(new_property); break;
		default:
			//ошибка
			break;
		}
	}
	else {
		switch (property_to_change) {
		case name: legal_entity_clients[client_id / 2]->set_name(new_property); break;
		case entity_registration_number: legal_entity_clients[client_id / 2]->set_registration_number(new_property); break;
		case entity_address: legal_entity_clients[client_id / 2]->set_address(new_property); break;
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

void BankSystem::release_card(int account_id, PaymentSystem payment_system) {
	if (!is_valid_account_id(account_id)) {
		// ошибка
		return;
	}

	Card* new_card = new Card(last_card_id, accounts[account_id], payment_system);
	cards.push_back(new_card);
	last_card_id++;
}

void BankSystem::rebind_card(int card_id, int account_id) {
	if (!is_valid_card_id(card_id) || !is_valid_account_id(account_id)) {
		// ошибка
		return;
	}

	cards[card_id]->set_account(accounts[account_id]);
}

void BankSystem::commit_transaction(int sender_card_id, int receiver_card_id, double amount) {
	if (!is_valid_account_id(sender_card_id) || !is_valid_account_id(receiver_card_id) 
		|| sender_card_id == receiver_card_id) {
		// ошибка
		return;
	}

	Account* sender_account = cards[sender_card_id]->get_account();
	Account* receiver_account = cards[receiver_card_id]->get_account();

	Transaction* transaction = new Transaction(sender_account, receiver_account, amount);
	transactions.push_back(transaction);
	transaction->commit_transaction();
}

void BankSystem::commit_cash_operation(OperationType type, int card_id, double amount, OperationPlace place, int bank_branch_id) {
	if (!is_valid_card_id(card_id) || (type != OperationType::withdrawal && type != OperationType::replenishment)) {
		// ошибка
		return;
	}

	Account* account = cards[card_id]->get_account();

	CashOperation* operation = new CashOperation(type, account, amount, place, bank_branch_id);
	cash_operations.push_back(operation);
	if (type == OperationType::withdrawal) operation->commit_withdrawal_operation();
	else operation->commit_replenishment_operation();
}
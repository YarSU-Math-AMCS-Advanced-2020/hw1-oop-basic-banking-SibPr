#include "bank.h"


string return_currency_string(Currency currency) {
	if (currency == Currency::USD) return "USD";
	if (currency == Currency::RUB) return "RUB";
	if (currency == Currency::EUR) return "EUR";
}

bool BankSystem::is_valid_client_id(int client_id) {
	if (client_id < 0 || client_id % 2 == 0 && client_id >= last_personal_client_id ||
		client_id % 2 == 1 && client_id >= last_legal_entity_client_id) {
		return false;
	}
	return true;
}

bool BankSystem::is_valid_account_id(int account_id) {
	if (account_id < 0 || account_id >= last_account_id || 
		deleted_account_ids.find(account_id) != deleted_account_ids.end())
		return false;
	return true;
}

bool BankSystem::is_valid_card_id(int card_id) {
	if (card_id < 0 || card_id >= last_card_id ||
		deleted_card_ids.find(card_id) != deleted_card_ids.end()) {
		return false;
	}
	return true;
}

ClientType BankSystem::get_client_type(int client_id) {
	if (client_id % 2 == 0) return Personal;
	else return LegalEntity;
}

void BankSystem::print_bank_info() {
	cout << "--------------------------" << endl;
	cout << "Bank Name: " << name << endl << endl << "Personal clients:";
	for (int i = 0; i < personal_clients.size(); i++) {
		cout << endl << 2 * i << ") " << personal_clients[i]->get_name() << " " <<
			personal_clients[i]->get_surname() << " " <<
			personal_clients[i]->get_patronymic();
	}
	cout << endl << endl << "Legal Entity Clients:";
	for (int i = 0; i < legal_entity_clients.size(); i++)
		cout << endl << 2 * i + 1 << ") " << legal_entity_clients[i]->get_name();
	cout << endl;
}

void BankSystem::print_client_info(int client_id) {
	if (!is_valid_client_id(client_id)) {
		std::cout << std::endl << "Error: Invalid client id" << std::endl;
		return;
	}
	ClientType client_type = get_client_type(client_id);

	cout << "--------------------------" << endl;
	if (client_type == Personal) {
		cout << "Name: " << personal_clients[client_id / 2]->get_name() << endl;
		cout << "Surname: " << personal_clients[client_id / 2]->get_surname() << endl;
		cout << "Patronymic: " << personal_clients[client_id / 2]->get_patronymic() << endl;
		cout << "Sex: " << personal_clients[client_id / 2]->get_sex() << endl;
		cout << "Birth Date: " << personal_clients[client_id / 2]->get_birth_date().day << "." <<
			personal_clients[client_id / 2]->get_birth_date().month << "." <<
			personal_clients[client_id / 2]->get_birth_date().year << endl;
		cout << "Address: " << personal_clients[client_id / 2]->get_address() << endl;
		cout << "Phone Number: " << personal_clients[client_id / 2]->get_phone_number() << endl;
		cout << "Passport: " << personal_clients[client_id / 2]->get_passport() << endl;
	}
	else {
		cout << "Name: " << legal_entity_clients[client_id / 2]->get_name() << endl;
		cout << "Registration Number: " << legal_entity_clients[client_id / 2]->get_registration_number() << endl;
		cout << "Address: " << legal_entity_clients[client_id / 2]->get_address() << endl;
	}

	bool has_accounts = false;
	cout << endl << "Accounts:" << endl;
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts[i]->get_client_id() == client_id) {
			has_accounts = true;
			print_account_info(accounts[i]->get_account_id(), true);
			cout << endl;
		}
	}
	if (!has_accounts) cout << "Client does not have any accounts" << endl;
}

void BankSystem::print_account_info(int account_id, bool is_for_concrete_client) {
	if (!is_valid_account_id(account_id)) {
		std::cout << std::endl << "Error: Invalid account id" << std::endl;
		return;
	}

	if (!is_for_concrete_client) {
		ClientType client_type = get_client_type(accounts[account_id]->get_client_id());
		cout << "--------------------------" << endl;
		if (client_type == Personal) {
			PersonalClient client = *personal_clients[accounts[account_id]->get_client_id() / 2];
			cout << "This is an account of person " << client.get_name() << " " <<
				client.get_surname() << " " << client.get_patronymic();
		}
		else {
			LegalEntityClient client = *legal_entity_clients[accounts[account_id]->get_client_id() / 2];
			cout << "This is an account of legal entity " << client.get_name();
		}
		cout << " (client ID: " << accounts[account_id]->get_client_id() << ")" << endl;
	}

	cout << "Account ID: " << account_id << endl;
	cout << "Balance: " << accounts[account_id]->get_balance() << endl;
	cout << "Currency: " << return_currency_string(accounts[account_id]->get_currency()) << endl;
	cout << "Limit: " << accounts[account_id]->get_account_limit() << endl;
}

void BankSystem::print_card_info(int card_id) {
	if (!is_valid_card_id(card_id)) {
		std::cout << std::endl << "Error: Invalid card id" << std::endl;
		return;
	}
	
	cout << "--------------------------" << endl;
	cout << "Card ID: " << card_id << endl;
	cout << "Account ID: " << cards[card_id]->get_account()->get_account_id() << endl;
	cout << "Card Type: Debet" << endl;
	cout << "Limit: " << cards[card_id]->get_card_limit() << endl;
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
		std::cout << std::endl << "Error: Invalid client id" << std::endl;
		return;
	}
	ClientType client_type = get_client_type(client_id);

	if (client_type == Personal) {
		switch (property_to_change) {
		case 0: personal_clients[client_id / 2]->set_name(new_property); break;
		case 1: personal_clients[client_id / 2]->set_surname(new_property); break;
		case 5: personal_clients[client_id / 2]->set_address(new_property); break;
		case 6: personal_clients[client_id / 2]->set_phone_number(new_property); break;
		case 7: personal_clients[client_id / 2]->set_passport(new_property); break;
		default:
			std::cout << std::endl << "Error: Invalid property to change" << std::endl;
			break;
		}
	}
	else {
		switch (property_to_change) {
		case 0: legal_entity_clients[client_id / 2]->set_name(new_property); break;
		case 8: legal_entity_clients[client_id / 2]->set_registration_number(new_property); break;
		case 5: legal_entity_clients[client_id / 2]->set_address(new_property); break;
		default:
			std::cout << std::endl << "Error: Invalid property to change" << std::endl;
			break;
		}
	}
}

void BankSystem::create_account(int client_id, Currency currency) {
	if (!is_valid_client_id(client_id)) {
		std::cout << std::endl << "Error: Invalid client id" << std::endl;
		return;
	}

	Account *new_account = new Account(last_account_id, client_id, currency);
	accounts.push_back(new_account);
	last_account_id++;
}

void BankSystem::close_account_with_transaction(int account_id, int receiver_account_id) {
	if (!is_valid_account_id(account_id)) {
		std::cout << std::endl << "Error: Invalid account id" << std::endl;
		return;
	}
	else if (!is_valid_account_id(receiver_account_id)) {
		std::cout << std::endl << "Error: Invalid receiver account id" << std::endl;
		return;
	}
	else if (account_id == receiver_account_id){
		std::cout << std::endl << "Error: You have entered the same id as sender and receiver" << std::endl;
		return;
	}

	Account* sender_account = accounts[account_id];
	Account* receiver_account = accounts[receiver_account_id];

	double tmp = sender_account->get_account_limit();
	sender_account->set_limit(DBL_MAX);
	Transaction *transaction = new Transaction(sender_account, receiver_account, sender_account->get_balance());
	transactions.push_back(transaction);
	transaction->commit_transaction();

	if (transaction->get_transaction_status() == OperationStatus::complete) {
		delete accounts[account_id];
		deleted_account_ids.insert(account_id);
		// accounts.erase(accounts.begin() + account_id);
	}
	else {
		sender_account->set_limit(tmp);
		std::cout << std::endl << "Error: Transaction error. Your account has not been deleted" << std::endl;
		return;
	}
}

void BankSystem::close_account_with_withdrawal(int account_id, OperationPlace place, int bank_branch_id) {
	if (!is_valid_account_id(account_id)) {
		std::cout << std::endl << "Error: Invalid account id" << std::endl;
		return;
	}

	Account* account = accounts[account_id];

	double tmp = account->get_account_limit();
	account->set_limit(DBL_MAX);
	CashOperation* cash_operation = new CashOperation(OperationType::withdrawal, account,
		account->get_balance(), place, bank_branch_id);
	cash_operations.push_back(cash_operation);
	cash_operation->commit_withdrawal_operation();

	if (cash_operation->get_operation_status() == OperationStatus::complete) {
		delete accounts[account_id];
		deleted_account_ids.insert(account_id);
		//accounts.erase(accounts.begin() + account_id);
	}
	else {
		account->set_limit(tmp);
		std::cout << std::endl << "Error: Withdrawal error. Your account has not been deleted" << std::endl;
		return;
	}
}

void BankSystem::set_account_limit(int account_id, double limit) {
	accounts[account_id]->set_limit(limit);
}

void BankSystem::release_card(int account_id, PaymentSystem payment_system) {
	if (!is_valid_account_id(account_id)) {
		std::cout << std::endl << "Error: Invalid account id" << std::endl;
		return;
	}

	Card* new_card = new Card(last_card_id, accounts[account_id], payment_system);
	cards.push_back(new_card);
	last_card_id++;
}

void BankSystem::rebind_card(int card_id, int account_id) {
	if (!is_valid_card_id(card_id)) {
		std::cout << std::endl << "Error: Invalid card id" << std::endl;
		return;
	}
	else if (!is_valid_account_id(account_id)) {
		std::cout << std::endl << "Error: Invalid card id" << std::endl;
		return;
	}

	cards[card_id]->set_account(accounts[account_id]);
}

void BankSystem::close_card(int card_id) {
	if (!is_valid_card_id(card_id)) {
		std::cout << std::endl << "Error: Invalid card id" << std::endl;
		return;
	}

	delete cards[card_id];
	deleted_card_ids.insert(card_id);
}

void BankSystem::set_card_limit(int card_id, double limit) {
	cards[card_id]->set_limit(limit);
}

void BankSystem::commit_transaction(int sender_card_id, int receiver_card_id, double amount) {
	if (!is_valid_card_id(sender_card_id)) {
		std::cout << std::endl << "Error: Invalid sender card id" << std::endl;
		return;
	}
	else if (!is_valid_card_id(receiver_card_id)) {
		std::cout << std::endl << "Error: Invalid receiver card id" << std::endl;
		return;
	}
	else if (sender_card_id == receiver_card_id) {
		std::cout << std::endl << "Error: You have entered the same sender and receiver ids" << std::endl;
		return;
	}

	Account* sender_account = cards[sender_card_id]->get_account();
	Account* receiver_account = cards[receiver_card_id]->get_account();
	cout << sender_account->get_account_id() << " " << receiver_account->get_account_id() << endl;

	Transaction* transaction = new Transaction(sender_account, receiver_account, amount);
	transactions.push_back(transaction);
	transaction->commit_transaction();
}

void BankSystem::commit_cash_operation(OperationType type, int card_id, double amount, OperationPlace place, int bank_branch_id) {
	if (!is_valid_card_id(card_id)) {
		std::cout << std::endl << "Error: Invalid card id" << std::endl;
		return;
	}
	else if (type != OperationType::withdrawal && type != OperationType::replenishment) {
		std::cout << std::endl << "Error: Invalid operation type" << std::endl;
		return;
	}

	Account* account = cards[card_id]->get_account();

	CashOperation* operation = new CashOperation(type, account, amount, place, bank_branch_id);
	cash_operations.push_back(operation);
	if (type == OperationType::withdrawal) operation->commit_withdrawal_operation();
	else operation->commit_replenishment_operation();
}
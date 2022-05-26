#include "bank.h"

bool BankSystem::is_valid_id(int client_id) {
	if (client_id < 0 || client_id % 2 == 0 && client_id > 2 * personal_clients.size() - 2 ||
		client_id % 2 == 1 && client_id > 2 * legal_entity_clients.size() - 1) {
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
	if (!this->is_valid_id(client_id)) return;
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
	if (!this->is_valid_id(client_id)) return;
	personal_clients[client_id / 2].create_account(currency);
}
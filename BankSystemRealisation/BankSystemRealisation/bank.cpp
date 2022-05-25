#include "bank.h"

void BankSystem::register_client(ClientType client_type) {
	bool registration_complete = false;
	while (!registration_complete) {
		if (client_type == Personal) {
			string name;
			cout << "Enter your name: ";
			cin >> name;

			string surname;
			cout << "Enter your surname: ";
			cin >> surname;

			string patronymic;
			cout << "Enter your patronymic: ";
			cin >> patronymic;

			string sex;
			cout << "Enter your sex: ";
			cin >> sex;

			int birth_day, birth_month_, birth_year;
			cout << "Enter your birth date (Day Month Year): ";
			cin >> birth_day >> birth_month_ >> birth_year;
			FullDate birth_date(birth_day, birth_month_, birth_year);

			string address;
			cout << "Enter your address: ";
			cin >> address;

			string phone_number;
			cout << "Enter your phone number: ";
			cin >> phone_number;

			string passport;
			cout << "Enter your passport information: ";
			cin >> passport;

			PersonalClient new_client(name, surname, patronymic, sex,
				birth_date, address, phone_number, passport);
			new_client.set_client_id(last_personal_client_id);
			new_client.set_client_type(Personal);
			last_personal_client_id += 2;
			personal_clients.push_back(new_client);

			cout << "Registration completed successfully\n";
			registration_complete = true;
		}
		else if (client_type == LegalEntity) {
			string name;
			cout << "Enter your entity name: ";
			cin >> name;

			string entity_registration_number;
			cout << "Enter a registration number of your entity: ";
			cin >> entity_registration_number;

			string entity_address;
			cout << "Enter your entity address: ";
			cin >> entity_address;

			LegalEntityClient new_client(name, entity_registration_number, entity_address);
			new_client.set_client_id(last_legal_entity_client_id);
			new_client.set_client_type(LegalEntity);
			last_legal_entity_client_id += 2;
			legal_entity_clients.push_back(new_client);

			cout << "Registration completed successfully\n";
			registration_complete = true;
		}
		else cout << "Incorrect client type, try again.\n";
	}
}

void BankSystem::change_client_info(int client_id, string property_to_change, string new_property) {
	if (client_id < 0 || client_id % 2 == 0 && client_id > 2 * personal_clients.size() - 2 ||
		client_id % 2 == 1 && client_id > 2 * personal_clients.size() - 1) {
		cout << "Incorrect client id, try again.\n";
		return;
	}

	ClientType client_type;
	if (client_id % 2 == 0) client_type = Personal;
	else client_type = LegalEntity;

	if (client_type == Personal) {
		if (property_to_change == "name") personal_clients[client_id / 2].name = new_property;
		else if (property_to_change == "surname") personal_clients[client_id / 2].name = new_property;
		else if (property_to_change == "address") personal_clients[client_id / 2].name = new_property;
		else if (property_to_change == "phone_number") personal_clients[client_id / 2].name = new_property;
		else if (property_to_change == "passport") personal_clients[client_id / 2].name = new_property;
		else {
			cout << "Incorrect property for a personal client, try again.\n";
			return;
		}
	}
	else {
		if (property_to_change == "name") legal_entity_clients[client_id / 2].name = new_property;
		else if (property_to_change == "registration_number") legal_entity_clients[client_id / 2].name = new_property;
		else if (property_to_change == "address") legal_entity_clients[client_id / 2].name = new_property;
		else {
			cout << "Incorrect property for a legal entity client, try again.\n";
			return;
		}
	}
}
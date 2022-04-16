#pragma once
#include "client.h"
#include "account.h"
#include "card.h"
#include "transaction.h"
#include "cash_operation.h"
#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

vector<Client> clients;
vector<Account> accounts;
vector<Transaction> transactions;
vector<CashOperation> cash_operations;

int last_account_id = 0;
int transaction_limit = 5000;
int band_operation_limit = 5000;


void register_client() {
	string client_type;
	bool registration_complete = false;
	while (!registration_complete) {
		cout << "Enter the client type (Personal / LegalEntity): ";
		cin >> client_type;
		if (client_type == "Personal") {
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
			clients.push_back(new_client);
		}
		else if (client_type == "LegalEntity") {
			string name;
			cout << "Enter your entity name: ";
			cin >> name;

			int entity_registration_number;
			cout << "Enter a registration number of your entity: ";
			cin >> entity_registration_number;

			string entity_address;
			cout << "Enter your entity address: ";
			cin >> entity_address;

			LegalEntityClient new_client(name, entity_registration_number, entity_address);
			clients.push_back(new_client);
		}
		else cout << "Incorrect client type, try again.\n";

		cout << "Registration completed successfully\n";
	}
}
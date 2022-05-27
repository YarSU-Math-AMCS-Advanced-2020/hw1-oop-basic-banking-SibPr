#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "account.h"
#include "card.h"
#include "auxiliary_classes.h"
using namespace std;


class Client {
private:
	int client_id = 0;
	ClientType client_type;

public:
	void set_client_id(int _client_id) { client_id = _client_id; }
	void set_client_type(ClientType _client_type) { client_type = _client_type; }
};


class PersonalClient : public Client {
private:
	string name;
	string surname;
	string patronymic;
	string sex;
	FullDate birth_date;
	string address;
	string phone_number;
	string passport;

public:
	PersonalClient();
	PersonalClient(string _name, string _surname, string _patronymic, string _sex,
		FullDate _birth_date, string _address, string _phone_number, string _passport);

	string get_name() { return name; }
	string get_surname() { return surname; }
	string get_patronymic() { return patronymic; }
	string get_sex() { return sex; }
	FullDate get_birth_date() { return birth_date; }
	string get_address() { return address; }
	string get_phone_number() { return phone_number; }
	string get_passport() { return passport; }

	void set_name(string _name) { name = _name; }
	void set_surname(string _surname) { surname = _surname; }
	void set_patronymic(string _patronymic) { patronymic = _patronymic; }
	void set_sex(string _sex) { sex = _sex; }
	void set_birth_date(FullDate _birth_date) { birth_date = _birth_date; }
	void set_address(string _address) { address = _address; }
	void set_phone_number(string _phone_number) { phone_number = _phone_number; }
	void set_passport(string _passport) { passport = _passport; }
};


class LegalEntityClient : public Client {
private:
	string name;
	string registration_number;
	string address;

public:
	LegalEntityClient();
	LegalEntityClient(string _name, string _registration_number, string _address);

	string get_name() { return name; }
	string get_registration_number() { return registration_number; }
	string get_address() { return address; }

	void set_name(string _name) { name = _name; }
	void set_registration_number(string _registration_number) { 
		registration_number = _registration_number; 
	}
	void set_address(string _address) { address = _address; }
};
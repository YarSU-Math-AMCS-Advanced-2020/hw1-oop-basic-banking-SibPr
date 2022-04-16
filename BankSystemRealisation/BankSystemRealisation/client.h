#pragma once
#include "bank.h"


struct FullDate {
	int day;
	int month;
	int year;

	FullDate(int _day = 1, int _month = 1, int _year = 1970) {
		day = _day;
		month = _month;
		year = _year;
	}
};


class Client {
public:
	int client_id;
};


class PersonalClient : public Client {
public:
	string name;
	string surname;
	string patronymic;
	string sex;
	FullDate birth_date;
	string address;
	string phone_number;
	string passport;

	PersonalClient(string _name, string _surname, string _patronymic, string _sex,
		FullDate _birth_date, string _address, string _phone_number, string _passport);
};


class LegalEntityClient : public Client {
public:
	string name;
	int entity_registration_number;
	string entity_address;

	LegalEntityClient(string _name, int _entity_registration_number, string _entity_address) {
		name = _name;
		entity_registration_number = _entity_registration_number;
		entity_address = _entity_address;
	}
};
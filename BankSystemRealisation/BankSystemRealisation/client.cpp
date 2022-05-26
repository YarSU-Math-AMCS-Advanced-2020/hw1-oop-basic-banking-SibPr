#include "client.h"

PersonalClient::PersonalClient() {
	name = "IndefiniteName";
	surname = "IndefiniteSurname";
	patronymic = "IndefinitePatronymic";
	sex = "IndefiniteSex";
	birth_date = FullDate();
	address = "IndefiniteAddress";
	phone_number = "IndefiniteNumber";
	passport = "IndefinitePassportInfo";
}

PersonalClient::PersonalClient(string _name, string _surname, string _patronymic, string _sex,
	FullDate _birth_date, string _address, string _phone_number, string _passport) {
	name = _name;
	surname = _surname;
	patronymic = _patronymic;
	sex = _sex;
	birth_date = _birth_date;
	address = _address;
	phone_number = _phone_number;
	passport = _passport;
}

LegalEntityClient::LegalEntityClient() {
	name = "IndefiniteName";
	registration_number = "IndefiniteRegistrationNumber";
	address = "IndefiniteAddress";
}

LegalEntityClient::LegalEntityClient(string _name, string _registration_number, string _address) {
	name = _name;
	registration_number = _registration_number;
	address = _address;
}
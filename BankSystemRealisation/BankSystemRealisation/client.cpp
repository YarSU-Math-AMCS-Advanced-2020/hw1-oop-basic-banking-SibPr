#include "client.h"

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
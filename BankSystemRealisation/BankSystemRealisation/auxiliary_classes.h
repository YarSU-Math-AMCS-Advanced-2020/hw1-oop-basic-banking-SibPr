#pragma once
#include <chrono>
#include <ctime>

typedef std::chrono::system_clock Clock;

enum Currency { RUB, USD, EUR };
enum PaymentSystem { Lisa, MasterBart, HoMiR };
enum CardType { debet, credit };
enum OperationStatus { in_queue, processing, complete, rejected };
enum OperationType { transaction, withdrawal, replenishment };
enum OperationPlace { bank, ATM };
enum ClientType { Personal, LegalEntity };
enum ClientInfoField { name, surname, patronymic, sex, birth_date, address,
	phone_number, passport, entity_registration_number, entity_address };

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

struct ShortDate {
	int month;
	int year;

	ShortDate(int _month = 1, int _year = 1970) {
		month = _month;
		year = _year;
	}
};
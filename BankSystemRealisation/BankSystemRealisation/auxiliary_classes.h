#pragma once
enum Currency { RUB, USD, EUR };
enum PaymentSystem { Lisa, MasterBart, HoMiR };
enum OperationStatus { InQueue, Processing, Complete, Rejected };
enum OperationType { Withdrawal, Replenishment };
enum OperationPlace { Bank, ATM };
//enum TransactionStatus { InQueue, Processing, Complete, Rejected };
enum ClientType { Personal, LegalEntity };

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
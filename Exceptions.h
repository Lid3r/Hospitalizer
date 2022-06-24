#pragma once
#include <iostream>
#include <exception>

using namespace std;
namespace jb {
	class generalException : public exception{};

	class fileException : public exception {
	public:
		void say() {
			cout << "Couldn't open file! Please make sure the file has a correct name and is accesible (i.e. in the same folder)" << endl;
		}
	};

	class argumentAmountException : public generalException {
	public:
		void say() {
			cout << "Not enough or too much data or arguments given. Please try again" << endl;
		}
	};


	class personException : public exception {};

	class personNameException : public personException {
	public:
		void say() {
			cout << "Name cannot contain numbers!" << endl;
		}
	};

	class personPhoneException : public personException {
	public:
		void say() {
			cout << "Phone number must be 9 characters long and cannot contain letters and special characters" << endl;
		}
	};

	class personAgeException : public personException {
	public:
		void say() {
			cout << "The age cannot be negative" << endl;
		}
	};

	class patientException : public exception {};

	class patientAdressException : public patientException {
	public:
		void say() {
			cout << "An excpetion in adress field has occured!";
		}
	};

	class doctorSpecException : public exception {
	public:
		void say() {
			cout << "Doctor specialization may not be an empty string" << endl;
		}
	};


	class peselException : public exception {};

	class peselLengthException : public peselException {
	public:
		void say() {
			cout << "PESEL doesn't have the correct length" << endl;
		}
	};

	class peselLettersException : public peselException {
	public:
		void say() {
			cout << "Incorrect character in PESEL. PESEL cannot contain letters" << endl;
		}
	};

	class peselChecksumException : public peselException {
	public:
		void say() {
			cout << "PESEL checksum incorrect. Please make sure the PESEL is a correct one" << endl;
		}
	};

	class peselDuplicateException : public peselException {
		string pesel;
		string person;
	public:
		peselDuplicateException() : pesel(""), person(""){}
		peselDuplicateException(string pesel, string person) : pesel(pesel), person(person){}

		void say() {
			cout << "PESEL duplicate detected in database. Please try again" << endl;
			cout << "Duplicate pesel: " << pesel << endl;
			cout << "Assignet to patient: " << person << endl;
		}
	};

	class datetimeException : public exception {};

	class datetimeDateException : public datetimeException {
	public:
		void say() {
			cout << "The date is incorrect! " << endl;
		}
	};

	class appointmentException : public exception {};

	class appointmentFailbitException : public appointmentException {
	public:
		void say() {
			cout << "Incorrect input has been detected in scheduling an appointment. Please check your inputs" << endl;
		}
	};

	class appointmentConflictException : public appointmentException {
	public:
		void say() {
			cout << "There was a conflict between appointments. Patient or doctor may not be scheduled for two appointments in the same timeframe" << endl;
		}
	};
}
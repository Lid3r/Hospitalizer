#pragma once
#include <iostream>
#include <exception>

using namespace std;
namespace jb {
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


	class peselException : public exception {};

	class peselLengthException : peselException {
	public:
		void say() {
			cout << "PESEL doesn't have the correct length" << endl;
		}
	};

	class peselLettersException : peselException {
	public:
		void say() {
			cout << "Incorrect character in PESEL. PESEL cannot contain letters" << endl;
		}
	};

	class peselChecksumException : peselException {
	public:
		void say() {
			cout << "PESEL checksum incorrect. Please make sure the PESEL is a correct one" << endl;
		}
	};
}
#pragma once
#include <exception>

using namespace std;
namespace jb {
	class personException : public exception{};

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

	class patientException : public exception{};

	class 
}
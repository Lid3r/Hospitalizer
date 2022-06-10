#pragma once
#include <string>
#include "Exceptions.h"
using namespace std;

namespace jb {
	class Person {
	protected:
		string Name;
		string Phone_number;

		int Age;

	public:
		Person(const string& name, const string& phone, const int& age) : Name(name), Phone_number(phone), Age(age) {
			//Untested!
			if (name.find_first_of("0123456789") != string::npos) {
				throw personNameException();
			}
			
			if (phone.length() != 9) {
				throw personPhoneException();
			}

			if (age < 0) {
				throw personAgeException();
			}
		}
	};
}
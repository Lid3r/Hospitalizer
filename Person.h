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
		Person(const string& name, const string& phone, const string& age) : Name(name), Phone_number(phone), Age(stoi(age)) {
			if (name == "") {
				throw personNameException();
			}

			if (phone.length() != 9) {
				throw personPhoneException();
			}

			if (isNumeric(name)) {
				throw personNameException();
			}

			if (age == "") {
				throw personAgeException();
			}

			if (stoi(age) < 0) {
				throw personAgeException();
			}
		}

		string gName() {
			return Name;
		}

		string gPhone() {
			return Phone_number;
		}

		int gAge() {
			return Age;
		}


		//Check if string contains numbers
		bool isNumeric(string const& str)
		{
			return find_if(str.begin(), str.end(), ::isdigit) != str.end();
		}

		virtual void print() = 0;

		
	};

	

	
	inline ostream& operator << (ostream& out, Person& p) {
		out << p.gName() << ", " << p.gPhone() << ", " << p.gAge();
		return out;
	}
	
}
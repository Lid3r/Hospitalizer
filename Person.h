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
		Person(const string& name, const string& phone, const int age) : Name(name), Phone_number(phone), Age(age) {
			if (phone.length() != 9) {
				throw personPhoneException();
			}

			if (isNumeric(name)) {
				throw personNameException();
			}

			if (age < 0) {
				throw personAgeException();
			}
		}

		//Check if string contains numbers
		bool isNumeric(string const& str)
		{
			auto it = find_if(str.begin(), str.end(), [](char const& c) {
				return !isdigit(c);
			});

			return !str.empty() && it == str.end();
		}
	};
}
#pragma once
#include <string>

using namespace std;

namespace jb {
	class Person {
	protected:
		string Name;
		string Phone_number;

		int Age;

	public:
		Person(const string& name, const string& phone, const int& age) : Name(name), Phone_number(phone), Age(age) {
			if (phone.length() != 9) {
				throw invalid_argument("Phone number is too short or too long");
			}
		}
	};
}
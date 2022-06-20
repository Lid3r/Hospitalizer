#pragma once
#include "Person.h"

#include <vector>
#include <string>

namespace jb {
	class Doctor : public Person {
		string specialization;

	public:
		Doctor(const string& name, const string& phone, const int age, const string& spec) : Person(name, phone, age), specialization(spec) {}

		void print() {
			cout << Name << ", " << Phone_number << ", " << Age << ", " << specialization << endl;
		}

		//GETTERS
		string gName() {
			return Person::Name;
		}

		string gPhone() {
			return Person::Phone_number;
		}

		int gAge() {
			return Person::Age;
		}

		string gSpec() {
			return specialization;
		}
		//
	};

	inline ostream& operator << (ostream& out, Doctor& p) {
		out << p.gName() << ", " << p.gPhone() << ", " << p.gAge() << ", " << p.gSpec();
		return out;
	}
}
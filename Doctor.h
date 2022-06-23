#pragma once
#include "Person.h"

#include <vector>
#include <string>

namespace jb {
	class Doctor : public Person {
		string specialization;

	public:
		Doctor(const string& name, const string& phone, string& age, const string& spec) : Person(name, phone, age), specialization(spec) {
			if (spec == "") {
				throw jb::doctorSpecException();
			}
		}

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
		
		bool operator == (const Doctor& doc) noexcept {
			return ((Name == doc.Name) && (Phone_number == doc.Phone_number) && (Age == doc.Age) && (specialization == doc.specialization));
		}

	};

	inline ostream& operator << (ostream& out, Doctor& p) {
		out << p.gName() << ", " << p.gPhone() << ", " << p.gAge() << ", " << p.gSpec();
		return out;
	}
}
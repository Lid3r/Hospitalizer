#pragma once
#include "Person.h"
#include "Pesel.h"
#include "Exceptions.h"

#include <iostream>

using namespace std;

namespace jb {
	class Patient : public Person {
		string Adress;
		jb::Pesel PESEL;


	public:
		Patient(const string& name, const string& phone, string &age, const string& add, const jb::Pesel& pesel) : Person(name, phone, age), Adress(add), PESEL(pesel) {

		}


		//GETTERS
		string gAdd() {
			return Adress;
		}

		Pesel gPesel() {
			return PESEL;
		}
		//

		void print() {
			cout << Name << ", " << Phone_number << ", " << Age << ", " << Adress << ", " << PESEL.print() << endl;
		}


		bool operator == (const Patient& pat) noexcept {
			return ((Name == pat.Name) && (Phone_number == pat.Phone_number) && (Age == pat.Age) && (PESEL == pat.PESEL));
		}
		
	};



	inline ostream& operator << (ostream& out, Patient& p) {
		out << p.gName() << ", " << p.gPhone() << ", " << p.gAge() << ", " << p.gAdd() << ", " << p.gPesel().print();
		return out;
	}
	

}
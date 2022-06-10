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
		Patient(const string& name, const string& phone, const int age, const string& add, const jb::Pesel& pesel) : Person(name, phone, age), Adress(add), PESEL(pesel){
			
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
	};
}
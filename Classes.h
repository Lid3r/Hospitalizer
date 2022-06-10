#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace Cl{
	class Person {
	protected:
		string Name;
		string Phone_number;
		
		int Age;

	public:
		Person(const string name = "", const string phone = "", const int age=NULL) : Name(name), Phone_number(phone), Age(age) {}
	};

	class Patient : public Person {
		string Adress;
		long long int PESEL;

		string Appointment_time; //Set time at which the patient is to be admitted
		string Doctor;

	public:
		Patient(const string name="", const string phone = "", const int age = NULL, const string add = "", const long long int pesel = 0, const string app = "", const string doc = "") noexcept 
			: Person(name, phone, age), Adress(add), PESEL(pesel), Appointment_time(app), Doctor(doc) {}

		void print() {
			cout << Name << ", " << Phone_number << ", " << Age << ", " << Adress << ", " << PESEL << ", " << Appointment_time << ", " << Doctor << endl;
		}
		
	};

	class Doctor : Person {
		vector<string> Timetable = {"8:00", "8:30", "9:00", "9:30", "10:30", "11:00", "11:30", "12:30", "13:00", "13:30", "14:00", "14:30", "15:30"}; //Time that the doctor has to treat patients, assuming an appointment lasts 30 minutes
		
	public:
		Doctor(const string name = "", const string phone = "", const int age = NULL) : Person(name, phone, age) {}
	};

	
}
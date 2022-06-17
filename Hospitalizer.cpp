#include <iostream>
#include <map>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Functions.h"
#include "Exceptions.h"
using namespace std;



int main()
{
	try {
		bool breaker = true;
		while (breaker) {
			menu(breaker);
		}

		//Getting patients and doctors
		multimap<string, jb::Patient> patients;
		read_patient_data("patients.txt", patients);
		typedef multimap<string, jb::Patient>::iterator patientIterator;

		//Since multimap is alphabetically sorted, this returns the range from the first found key, to the last found key in the map
		pair<patientIterator, patientIterator> results = patients.equal_range("Krzychu Ziobro");

		for (patientIterator it = results.first; it != results.second; it++) {
			it->second.print();
		}
		
	}
	catch (jb::personNameException& e) {
		e.say();
	}
	catch (jb::personAgeException& e) {
		e.say();
	}
	catch (jb::personPhoneException& e) {
		e.say();
	}
	catch (jb::patientException& e) {
		cout << "Unknown exception with patient has occured" << endl;
	}
	catch (jb::peselLengthException& e) {
		e.say();
	}
	catch (jb::peselChecksumException& e) {
		e.say();
	}
	catch (jb::peselLettersException& e) {
		e.say();
	}

	return 0;
}
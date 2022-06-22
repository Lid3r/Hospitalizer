#include <iostream>
#include <map>
//#include "Patient.h"
//#include "Doctor.h"
#include "Appointment.h"
#include "Functions.h"
#include "Exceptions.h"
using namespace std;

int main()
{
	try {
		/*bool breaker = true;
		while (breaker) {
			menu(breaker);
		}
		*/
		multimap<string, jb::Appointment> appointments;
		read_appointment_data("Appointments.txt", appointments);
		for (auto itr = appointments.begin(); itr != appointments.end(); ++itr)
		{
			cout << itr->second << endl;
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
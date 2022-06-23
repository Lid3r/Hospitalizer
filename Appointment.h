#pragma once
#include "Patient.h"
#include "Doctor.h"
#include <string>
#include <iostream>
#include "Datetime.h"
using namespace std;

namespace jb {
	class Appointment {
		jb::Patient patient;
		jb::Doctor doctor;
		jb::Datetime dt;

	public:
		Appointment(const jb::Patient& pat, const jb::Datetime& date, const jb::Doctor& doc) : patient(pat), doctor(doc), dt(date) {
			
		}

		jb::Patient gPatient() {
			return patient;
		}

		jb::Datetime gDt() {
			return dt;
		}

		jb::Doctor gDoctor() {
			return doctor;
		}

		void print_nicely() {
			cout << "Patient:" << endl << patient << endl;
			cout << "Date and time:" << endl << dt << endl;
			cout << "Doctor:" << endl << doctor << endl << endl;
		}

		bool operator == (const Appointment& a) noexcept { //Check if patient has a collision between two times or if doctor is in two places at once
			bool docdate;
			bool patdate;
			docdate = ((dt == a.dt) && (doctor == a.doctor));
			patdate = (patient == a.patient) && (dt == a.dt);
			
			return docdate || patdate;
		}
	};

	inline ostream& operator << (ostream& out, Appointment& a) {
		out << a.gPatient().gName() << ", " << a.gPatient().gPhone() << ", " << a.gPatient().gAge() << ", " << a.gPatient().gAdd() << ", " << a.gPatient().gPesel().print() << ", " << a.gDt().print() << ", " << a.gDoctor().gName() << ", " << a.gDoctor().gPhone() << ", " << a.gDoctor().gAge() << ", " << a.gDoctor().gSpec();
		return out;
	}
}
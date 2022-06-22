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


	};

	inline ostream& operator << (ostream& out, Appointment& a) {
		out << a.gPatient().gName() << ", " << a.gPatient().gPhone() << ", " << a.gPatient().gAge() << ", " << a.gPatient().gAdd() << ", " << a.gPatient().gPesel().print() << ", " << a.gDt().print() << ", " << a.gDoctor().gName() << ", " << a.gDoctor().gPhone() << ", " << a.gDoctor().gAge() << ", " << a.gDoctor().gSpec();
		return out;
	}
}
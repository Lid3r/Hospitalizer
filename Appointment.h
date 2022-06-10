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
		Appointment(const jb::Patient& pat,const jb::Doctor& doc, const jb::Datetime& date) : patient(pat), doctor(doc), dt(date) {
			


		}
	};
}
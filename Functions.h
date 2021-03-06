#pragma once
#include <string>
#include <vector>
#include <map>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"

void read_patient_data(string name, multimap<string, jb::Patient>& patients);
void read_doctor_data(string name, multimap<string, jb::Doctor>& doctors);
jb::Patient return_patient_from_search();
jb::Doctor return_doctor_from_search();


void menu(bool& breaker);
void buffer_flush();
void data_dump();

/*-------------------------------------PATIENT ZONE----------------------------------*/
void p_records();

void print_patient_records(multimap<string, jb::Patient>& patients);

void patient_search(multimap<string, jb::Patient>& patients);

void manip_patients(multimap<string, jb::Patient>& patients);

void add_patient(multimap<string, jb::Patient>& patients);

void remove_patient(multimap<string, jb::Patient>& patients);

void add_many_patients(multimap<string, jb::Patient>& patients);

void write_to_file(string filename, jb::Patient& patient);

void override_file(string filename, multimap<string, jb::Patient>& patients);
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------STAFF ZONE-----------------------------------*/
void s_records();

void print_doctor_records(multimap<string, jb::Doctor>& doctors);

void doctor_search(multimap<string, jb::Doctor>& doctors);

void manip_doctors(multimap<string, jb::Doctor>& doctors);

void add_doctor(multimap<string, jb::Doctor>& doctors);

void remove_doctor(multimap<string, jb::Doctor>& doctors);

void add_many_doctors(multimap<string, jb::Doctor>& doctors);

void write_to_file(string filename, jb::Doctor& doctor);

void override_file(string filename, multimap<string, jb::Doctor>& doctors);
/*-----------------------------------------------------------------------------------*/


/*--------------------------------------APPOINTMENT ZONE-----------------------------*/

void read_appointment_data(string filename, multimap<string, jb::Appointment>& appointments);

void appointments();

void print_appointments(multimap<string, jb::Appointment>& appointments);

void appointment_search(multimap<string, jb::Appointment>& appointments);

void manip_appointments(multimap<string, jb::Appointment>& appointments);

void add_appointment(multimap<string, jb::Appointment>& appointments);

void remove_appointment(multimap<string, jb::Appointment>& appointments);

void add_many_appointments(multimap<string, jb::Appointment>& appointments);

void write_to_file(string filename, jb::Appointment& appointment);

void override_file(string filename, multimap<string, jb::Appointment>& appointments);
/*-----------------------------------------------------------------------------------*/
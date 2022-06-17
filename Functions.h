#pragma once
#include <string>
#include <vector>
#include <map>
#include "Patient.h"
#include "Doctor.h"

void read_patient_data(string name, multimap<string, jb::Patient>& patients);
void read_doctor_data(string name, multimap<string, jb::Doctor>& doctors);

void menu(bool& breaker);

void p_records();

void print_patient_records(multimap<string, jb::Patient>& patients);

void patient_search(multimap<string, jb::Patient>& patients);

void s_records();
void set_appointment();
void manip_data();
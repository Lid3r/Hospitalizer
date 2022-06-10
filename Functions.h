#pragma once
#include <string>
#include <vector>

void read_data(string name, vector<jb::Patient> &patients);

void menu(bool &breaker);

void p_records();
void s_records();
void set_appointment();
void manip_data();
#include "Functions.h"
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <fstream>
#include <map>

#include "Patient.h"
#include "Doctor.h"
using namespace std;

typedef pair<string, jb::Patient> spPair;
typedef pair<string, jb::Doctor> sdPair;
typedef multimap<string, jb::Patient>::iterator patientIterator;
typedef multimap<string, jb::Doctor>::iterator doctorIterator;

vector<string> split(string line) {
	vector<string> tokenized;
	size_t pos = 0;
	string delimiter = ", ";
	string token;
	while ((pos = line.find(delimiter)) != string::npos) {
		token = line.substr(0, pos);
		tokenized.push_back(token);
		line.erase(0, pos + delimiter.length());
	}

	tokenized.push_back(line);
	return tokenized;
}


//Legacy code, if something breaks
/*
//For patients
void read_patient_data(string name, vector<jb::Patient>& patients) {
	ifstream input;
	string line;
	input.open(name);
	if (!input) {
		cout << "Database file \"" << name << "\" could not be opened. Please check if the file has the correct name and if the program has the rights to open it." << endl;
		return;
	}
	else {

		vector<string> out;
		while (getline(input, line)) {
			out = split(line);

			patients.push_back(jb::Patient(out[0], out[1], stoi(out[2], nullptr), out[3], jb::Pesel(out[4])));
		}

	}
	input.close();
}
*/

//For doctors
void read_doctor_data(string name, multimap<string, jb::Doctor>& doctors) {
	ifstream input;
	string line;
	input.open(name);
	if (!input) {
		cout << "Database file \"" << name << "\" could not be opened. Please check if the file has the correct name and if the program has the rights to open it." << endl;
		return;
	}
	else {

		vector<string> out;
		while (getline(input, line)) {
			out = split(line);

			doctors.insert(sdPair(out[0], jb::Doctor(out[0], out[1], stoi(out[2], nullptr), out[3])));
		}

	}
	input.close();
}


/*--------------------------------PATIENT ZONE-------------------------------------*/

void read_patient_data(string name, multimap<string, jb::Patient>& patients) {
	ifstream input;
	string line;
	input.open(name);
	if (!input) {
		cout << "Database file \"" << name << "\" could not be opened. Please check if the file has the correct name and if the program has the rights to open it." << endl;
		return;
	}
	else {

		vector<string> out;
		while (getline(input, line)) {
			out = split(line);

			patients.insert(spPair(out[0], jb::Patient(out[0], out[1], stoi(out[2], nullptr), out[3], jb::Pesel(out[4]))));
		}

	}
	input.close();
}

void p_records() {
	multimap<string, jb::Patient> patients;
	read_patient_data("patients.txt", patients);

	bool stopper = true;
	while (stopper) {
		system("cls");
		cout << "What would you like to do:" << endl;
		cout << "1. See records" << endl;
		cout << "2. Search for a patient by name" << endl;
		cout << "3. Add a patient" << endl;
		cout << "4. Add multiple patients from file" << endl;
		cout << "5. Go back" << endl;
		
		int input = 0;
		cin >> input;

		switch (input) {
		case 1:
			print_patient_records(patients);
			break;
		case 2:
			patient_search(patients);
			break;
		case 3:

			break;
		case 4:

			break;
		case 5:
			stopper = false;
			break;
		default:
			cout << "Given input couldn't be resolved. Press any button to try again" << endl;
			cin.clear(); //Flush whole input buffer after a wrong input (in case a character got in or God forbid a string)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			break;
		}
	}

}

void patient_search(multimap<string, jb::Patient>& patients) {
	cout << "Please enter the name of the patient you wish to search for:" << endl;
	string name;

	cin.clear(); //Flush whole buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, name);

	//Since multimap is alphabetically sorted, this returns the range from the first found key, to the last found key in the map
	pair<patientIterator, patientIterator> results = patients.equal_range(name);

	for (patientIterator it = results.first; it != results.second; it++) {
		it->second.print();
	}
	system("pause");
}

void print_patient_records(multimap<string, jb::Patient>& patients) {

	for (auto itr = patients.begin(); itr != patients.end(); ++itr)
	{
		cout << itr->second;
	}
	system("pause");
}
/*---------------------------------------------------------------------------------*/
void s_records() {};
void set_appointment() {};
void manip_data() {};


void menu(bool& breaker) {

	int input = 0;
	system("cls");
	cout << "Welcome to Hospitalizer management program!" << endl << endl;
	cout << "Please select an operation:" << endl;
	cout << "1. See patient records" << endl;
	cout << "2. See staff records" << endl;
	cout << "3. See all records" << endl;
	cout << "4. See and schedule appointments" << endl;
	cout << "5. Exit" << endl;
	cin >> input;

	switch (input) {
	case 1:
		p_records();
		break;
	case 2:
		s_records();
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		breaker = false;
		break;
	default:
		cout << "Given input couldn't be resolved. Press any button to try again" << endl;
		cin.clear(); //Flush whole input buffer after a wrong input (in case a character got in or God forbid a string)
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("pause");
		break;
	}
}
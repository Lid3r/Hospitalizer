#include "Functions.h"
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <fstream>
#include <map>
//#include <ctype.h>

//#include "Patient.h"
//#include "Doctor.h"
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


/*--------------------------------PATIENT ZONE-------------------------------------*/		//Tried and tested, works

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
			if (line == "") {
				continue;
			}
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
		cout << "3. Add or remove a patient" << endl;
		cout << "4. Go back" << endl;
		
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
			manip_patients(patients);
			break;
		case 4:
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
	system("cls");
	cout << "Please enter the name of the patient you wish to search for:" << endl;
	string name;

	cin.clear(); //Flush whole buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, name);

	//Since multimap is alphabetically sorted, this returns the range from the first found key, to the last found key in the map
	pair<patientIterator, patientIterator> results = patients.equal_range(name);
	if (results.first == results.second) {
		cout << "No patient of a given name can be found in the database. Please check your input" << endl;
	}
	else {
		for (patientIterator it = results.first; it != results.second; it++) {
			cout << it->second;
		}
	}
	system("pause");
}

void print_patient_records(multimap<string, jb::Patient>& patients) {
	system("cls");
	for (auto itr = patients.begin(); itr != patients.end(); ++itr)
	{
		cout << itr->second;
	}
	system("pause");
}

void manip_patients(multimap<string, jb::Patient>& patients) {
	system("cls");
	bool stop = false;
	int choice = 0;
	while (!stop) {
		cout << "What would you like to do?" << endl;
		cout << "1. Add a patient" << endl;
		cout << "2. Remove a patient" << endl;
		cout << "3. Add multiple patients" << endl;
		cout << "4. Go back" << endl;
		

		cin.clear(); //Flush whole buffer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;

		switch (choice) {
		case 1:
			add_patient(patients);
			break;
		case 2:
			remove_patient(patients);
			break;
		case 3:
			//add_many_patients();
			break;
		case 4:
			stop = true;
			break;
		default:
			cout << "Given input couldn't be resolved. Press any button to try again" << endl;
			cin.clear(); //Flush whole input buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("pause");
			break;
		}

	}
}

void add_patient(multimap<string, jb::Patient>& patients) {
	system("cls");
	cout << "Please input the patient data in the following order:" << endl;
	cout << "Name Surname, Phone number, Age, Address, PESEL number" << endl;
	string line;
	vector<string> out;

	getline(cin, line);
	out = split(line);

	jb::Patient newPatient(out[0], out[1], stoi(out[2], nullptr), out[3], jb::Pesel(out[4]));
	patients.insert(spPair(out[0], newPatient));
	
	//Now save to database
	write_to_file("Patients.txt", newPatient);
}

void add_many_patients(multimap<string, jb::Patient>& patients) {
	system("cls");
	cout << "Please enter the filename from which you want to extract contents. To go back, please type exit" << endl;
	
	string filename;
	getline(cin, filename);

	if (filename != "exit") {
		ifstream input;
		string line;
		input.open(filename);

		if (!input) {
			cout << "Database file \"" << filename << "\" could not be opened. Please check if the file has the correct name and if the program has the rights to open it." << endl;
			return;
		}
		else {
			vector<string> out;

			while (getline(input, line)) {
				if (line == "") {
					continue;
				}
				out = split(line);
				jb::Patient newPatient(out[0], out[1], stoi(out[2], nullptr), out[3], jb::Pesel(out[4]));
				patients.insert(spPair(out[0], newPatient));
				write_to_file("Patients.txt", newPatient);
			}

		}
		input.close();
		}
	}

void remove_patient(multimap<string, jb::Patient>& patients){
	system("cls");
	cout << "Please enter the name of the patient you wish to delete:" << endl;
	string name;

	cin.clear(); //Flush whole buffer

	getline(cin, name);

	//Since multimap is alphabetically sorted, this returns the range from the first found key, to the last found key in the map
	pair<patientIterator, patientIterator> results = patients.equal_range(name);
	int i = 0;
	if (results.first == results.second) {
		cout << "No patient of a given name can be found in the database. Please check your input" << endl;
	}
	else {
		system("cls");
		cout << endl << "Please select which one you'd like to remove" << endl;
		for (patientIterator it = results.first; it != results.second; it++) {
			cout << i << ". " << it->second << endl;
			i++;
		}

		cin.clear(); //Flush whole buffer
		cin >> i;

		if (!isdigit(i)) {
			cout << "Input unrecognized" << endl;
		}
		else {
			cin.clear();
			cout << endl << "Are you sure you want to delete this patient? [Y/N]" << endl;
			string confirm;
			cin >> confirm;

			if (confirm == "Y" || confirm == "y") {
				int iter = 0;
				for (patientIterator it = results.first; it != results.second; it++) {
					if (iter == i) {
						patients.erase(it);
						break;
					}
					iter++;
				}
				override_file("Patients.txt", patients);
			}
			else {
				cout << "Cancelling deletion" << endl;
			}
		}
	}
}

void write_to_file(string filename, jb::Patient& patient){
	ofstream file;
	file.open(filename, std::ios::app);
	file << "\n" << patient;
	file.close();
}

void override_file(string filename, multimap<string, jb::Patient>& patients){
	ofstream file;
	file.open(filename);
	patientIterator it = patients.begin();
	file << it->second; //Write without newline
	it++;
	for (it; it != patients.end(); it++)
	{
		file << "\n" << it->second;
	}
	file.close();
}
/*---------------------------------------------------------------------------------*/


/*--------------------------------------STAFF ZONE-----------------------------------*/

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

void s_records() {
	multimap<string, jb::Doctor> doctors;
	read_doctor_data("patients.txt", doctors);

	bool stopper = true;
	while (stopper) {
		system("cls");
		cout << "What would you like to do:" << endl;
		cout << "1. See records" << endl;
		cout << "2. Search for a doctor by name" << endl;
		cout << "3. Add or remove a Doctor" << endl;
		cout << "4. Go back" << endl;

		int input = 0;
		cin >> input;

		switch (input) {
		case 1:
			//print_doctor_records(doctors);
			break;
		case 2:
			//doctor_search(doctors);
			break;
		case 3:
			//manip_doctors(doctors);
			break;
		case 4:
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
};
/*-----------------------------------------------------------------------------------*/

void set_appointment() {};



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
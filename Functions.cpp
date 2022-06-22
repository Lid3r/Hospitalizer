#include "Functions.h"
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <fstream>
#include <map>
#include <ctype.h>

//#include "Patient.h"
//#include "Doctor.h"
using namespace std;

typedef pair<string, jb::Patient> spPair;
typedef pair<string, jb::Doctor> sdPair;
typedef pair<string, jb::Appointment> saPair;
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
void buffer_flush() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
bool check_number(string str) {
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false;
		else {
			return true;
		}
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

			patients.insert(spPair(out[0], jb::Patient(out[0], out[1], out[2], out[3], jb::Pesel(out[4]))));
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
			buffer_flush(); //Flush whole input buffer after a wrong input (in case a character got in or God forbid a string)

			system("pause");
			break;
		}
	}

}

void patient_search(multimap<string, jb::Patient>& patients) {
	system("cls");
	cout << "Please enter the name of the patient you wish to search for:" << endl;
	string name;

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
	
		cin >> choice;

		switch (choice) {
		case 1:
			try {
				add_patient(patients);
			}
			catch (jb::argumentAmountException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personNameException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personAgeException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personPhoneException& e) {
				e.say();
				system("pause");
			}
			catch (invalid_argument& e) {
				cout << "Input incorrect!" << endl;
				cout << e.what() << endl;
				system("pause");
			}
			break;
		case 2:
			remove_patient(patients);
			break;
		case 3:
			add_many_patients(patients);
			break;
		case 4:
			stop = true;
			break;
		default:
			cout << "Given input couldn't be resolved. Press any button to try again" << endl;
			buffer_flush();
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
	if (line == "") {
		throw jb::argumentAmountException();
	}

	out = split(line);

	if (out.size() != 5) {
		throw jb::argumentAmountException();
	}

	for (auto itr = patients.begin(); itr != patients.end(); ++itr)
	{
		if (itr->second.gPesel() == jb::Pesel(out[4])) {
			throw jb::peselDuplicateException();
		}
	}

	jb::Patient newPatient(out[0], out[1], out[2], out[3], jb::Pesel(out[4]));
	patients.insert(spPair(out[0], newPatient));
	
	//Now save to database
	write_to_file("Patients.txt", newPatient);
	cout << newPatient << " has been created!" << endl;
	system("pause");
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
				if (out.size() != 5) {
					cout << "Not enough or too much information. The patient:" << endl;
					cout << line;
					cout << "Will be ommited" << endl;
					continue;
				}
				jb::Patient newPatient(out[0], out[1], out[2], out[3], jb::Pesel(out[4]));
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

			doctors.insert(sdPair(out[0], jb::Doctor(out[0], out[1], out[2], out[3])));
		}

	}
	input.close();
}

void s_records() {
	multimap<string, jb::Doctor> doctors;
	read_doctor_data("Doctors.txt", doctors);

	bool stopper = true;
	while (stopper) {
		system("cls");
		cout << "What would you like to do:" << endl;
		cout << "1. See records" << endl;
		cout << "2. Search for a Doctor by name" << endl;
		cout << "3. Add or remove a Doctor" << endl;
		cout << "4. Go back" << endl;

		int input = 0;
		cin >> input;

		switch (input) {
		case 1:
			print_doctor_records(doctors);
			break;
		case 2:
			doctor_search(doctors);
			break;
		case 3:
			manip_doctors(doctors);
			break;
		case 4:
			stopper = false;
			break;
		default:
			cout << "Given input couldn't be resolved. Press any button to try again" << endl;
			buffer_flush();
			system("pause");
			break;
		}
	}
};

void doctor_search(multimap<string, jb::Doctor>& doctors) {
	system("cls");
	cout << "Please enter the name of the doctor you wish to search for:" << endl;
	string name;

	buffer_flush();

	getline(cin, name);

	//Since multimap is alphabetically sorted, this returns the range from the first found key, to the last found key in the map
	pair<doctorIterator, doctorIterator> results = doctors.equal_range(name);
	if (results.first == results.second) {
		cout << "No patient of a given name can be found in the database. Please check your input" << endl;
	}
	else {
		for (doctorIterator it = results.first; it != results.second; it++) {
			cout << it->second << endl;
		}
	}
	system("pause");
}

void print_doctor_records(multimap<string, jb::Doctor>& doctors) {
	system("cls");
	for (auto itr = doctors.begin(); itr != doctors.end(); ++itr)
	{
		cout << itr->second << endl;
	}
	system("pause");
}

void manip_doctors(multimap<string, jb::Doctor>& doctors) {
	bool stop = false;
	int choice = 0;
	while (!stop) {
		system("cls");
		cout << "What would you like to do?" << endl;
		cout << "1. Add a doctor" << endl;
		cout << "2. Remove a doctor" << endl;
		cout << "3. Add multiple doctors" << endl;
		cout << "4. Go back" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			try {
				add_doctor(doctors);
			}
			catch(jb::argumentAmountException &e) {
				e.say();
				system("pause");
			}
			catch (jb::personNameException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personAgeException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personPhoneException& e) {
				e.say();
				system("pause");
			}
			catch (invalid_argument& e) {
				cout << "Input incorrect!" << endl;
				cout << e.what() << endl;
				system("pause");
			}
			break;
		case 2:
			try {
				remove_doctor(doctors);
			}
			catch (invalid_argument) {
				cout << "Given input is out of possible range" << endl;
				system("pause");
			}
			break;
		case 3:
			try {
				add_many_doctors(doctors);
			}
			catch (jb::argumentAmountException &e) {
				e.say();
				system("pause");
			}
			catch (jb::personNameException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personAgeException& e) {
				e.say();
				system("pause");
			}
			catch (jb::personPhoneException& e) {
				e.say();
				system("pause");
			}
			break;
		case 4:
			stop = true;
			break;
		default:
			cout << "Given input couldn't be resolved. Press any button to try again" << endl;
			buffer_flush();
			system("pause");
			break;
		}

	}
}

void add_doctor(multimap<string, jb::Doctor>& doctors) {
	system("cls");
	cout << "Please input the doctor data in the following order:" << endl;
	cout << "Name Surname, Phone number, Age, Specialization" << endl;
	string line;
	vector<string> out;

	buffer_flush();

	getline(cin, line);
	if (line == "") {
		throw jb::argumentAmountException();
	}
	else {
		out = split(line);
		
		if (out.size() != 4) {
			throw jb::argumentAmountException();
		}
			jb::Doctor newDoctor(out[0], out[1], out[2], out[3]);

			doctors.insert(sdPair(out[0], newDoctor));

			//Now save to database
			write_to_file("Doctors.txt", newDoctor);
	}
}

void add_many_doctors(multimap<string, jb::Doctor>& doctors) {
	system("cls");
	cout << "Please enter the filename from which you want to extract contents. To go back, please type exit" << endl;

	string filename;
	buffer_flush();
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
				if (out.size() != 4) {
					cout << "Not enough or too much information. The doctor:" << endl;
					cout << line << endl;
					cout << "Will be ommited" << endl;
					system("pause");
					continue;
				}
				
					jb::Doctor newDoctor(out[0], out[1], out[2], out[3]);

					doctors.insert(sdPair(out[0], newDoctor));

					write_to_file("Doctors.txt", newDoctor);
				
			}

		}
		input.close();
	}
}

void remove_doctor(multimap<string, jb::Doctor>& doctors) {
	system("cls");
	cout << "Please enter the name of the doctor you wish to delete:" << endl;
	string name;

	buffer_flush();

	getline(cin, name);

	//Since multimap is alphabetically sorted, this returns the range from the first found key, to the last found key in the map
	pair<doctorIterator, doctorIterator> results = doctors.equal_range(name);
	int i = 0;
	if (results.first == results.second) {
		cout << "No doctor of a given name can be found in the database. Please check your input" << endl;
	}
	else {
		system("cls");
		cout << endl << "Please select which one you'd like to remove" << endl;
		for (doctorIterator it = results.first; it != results.second; it++) {
			cout << i << ". " << it->second << endl;
			i++;
		}
		i--;
		cin.clear();
		string s;

		cin >> s;

		if (!check_number(s)) {
			cout << "Input unrecognized" << endl;
		}
		else {

			//check if the number can be found
			int inp = stoi(s, nullptr);
			if (inp < 0 || inp > i) {
				throw invalid_argument("");
			}

			cout << endl << "Are you sure you want to delete this doctor? [Y/N]" << endl;
			string confirm;
			cin >> confirm;

			if (confirm == "Y" || confirm == "y") {
				int iter = 0;
				for (doctorIterator it = results.first; it != results.second; it++) {
					if (iter == inp) {
						doctors.erase(it);
						break;
					}
					iter++;
				}
				override_file("Doctors.txt", doctors);
			}
			else {
				cout << "Cancelling deletion" << endl;
			}
		}
	}
}

void write_to_file(string filename, jb::Doctor& doctor) {
	ofstream file;
	file.open(filename, std::ios::app);
	file << "\n" << doctor;
	file.close();
}

void override_file(string filename, multimap<string, jb::Doctor>& doctors) {
	ofstream file;
	file.open(filename);
	doctorIterator it = doctors.begin();
	file << it->second; //Write without newline
	it++;
	for (it; it != doctors.end(); it++)
	{
		file << "\n" << it->second;
	}
	file.close();
}

/*-----------------------------------------------------------------------------------*/


/*--------------------------------------APPOINTMENT ZONE-----------------------------*/
void read_appointment_data(string filename, multimap<string, jb::Appointment>& appointments) {
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
			out = split(line);

			appointments.insert(saPair(out[0], jb::Appointment(jb::Patient(out[0], out[1], out[2], out[3], jb::Pesel(out[4])), jb::Datetime(out[5]), jb::Doctor(out[6], out[7], out[8], out[9]))));
		}

	}
	input.close();
}

void appointments() {
	multimap<string, jb::Appointment> appointments;
	bool stopper = true;
	while (stopper) {
		system("cls");
		cout << "What would you like to do:" << endl;
		cout << "1. See appointments" << endl;
		cout << "2. Search for an appointment by patient name" << endl;
		cout << "3. Schedule or remove an appointment" << endl;
		cout << "4. Go back" << endl;

		int input = 0;
		cin >> input;
	}
}

/*-----------------------------------------------------------------------------------*/


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
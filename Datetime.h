#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//This here works, don't touch


namespace jb {
	class Datetime {
		string original;
		string date;
		int hourStart;
		int minuteStart;
		int hourFinish;
		int minuteFinish;
		//Format of DD/MM/YYYY HH:MM or H:MM. Each appointment takes about 30 mins.
	public:

		Datetime(const string& dt) {
			//we assume the clinic is running from 8:00-20:00
			original = dt;
			vector<string> tokdt = tokenize(dt, ' ');
			//I'll think about wrong date logic

			string d = tokdt[0];
			string s = tokdt[1];

			int h, m;
			if (s.length() == 5) {
				h = stoi(s.substr(0, 2));
				m = stoi(s.substr(3, 2));
			}
			else if (s.length() == 4) {
				h = stoi(s.substr(0, 1));
				m = stoi(s.substr(2, 2));
			}
			else {
				throw invalid_argument("Appointment time not recognized");
			}

			if (h < 8 || h > 20) {
				throw invalid_argument("Appointment time invalid");
			}

			if (m < 0 || m > 60) {
				throw invalid_argument("Appointment time invalid");
			}

			if (m >= 30) {
				//If 30-minute appointment starts on XX:30 or more, increment hour and modulo the resulting minutes
				hourFinish = h + 1;
				minuteFinish = (m + 30) % 60;
			}
			else {
				hourFinish = h;
				minuteFinish = m + 30;
			}
			date = d;
			hourStart = h;
			minuteStart = m;
		}



		string print() {
			return original;
		}

		vector<string> tokenize(const string& str, const char delim)
		{
			vector<string> out;
			// construct a stream from the string
			stringstream ss(str);

			string s;
			while (getline(ss, s, delim)) {
				out.push_back(s);
			}
			return out;
		}

		bool checker(int h1, int h2, int m1, int m2) {
			//h1 ending of already set appointment, h2 start of the new one, m1 ending, m2 start
			int t1 = h1 * 60 + m1; //end time in minutes
			int t2 = h2 * 60 + m2; //start time in minutes

			//Absolute difference between the 2 times must be >= 30
			if (abs(t1 - t2) <= 30) {
				return true;
			}
			else {
				return false;
			}
		}

		bool operator == (const Datetime& app) noexcept {
			//Check if the appointment times don't overlap with another appointment (with the same doc for example);
			return date == app.date && checker(hourFinish, app.hourStart, minuteFinish, app.minuteStart);
		}
	};

	inline ostream& operator << (ostream& out, Datetime& d) {
		out << d.print();
		return out;
	}
}
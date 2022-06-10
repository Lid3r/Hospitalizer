#pragma once
#include <string>

using namespace std;

//This here works, don't touch


namespace jb {
	class Datetime {
		string date;
		int hs;
		int ms;
		int hf;
		int mf;
		//Format of DD/MM/YYYY HH:MM or H:MM. Each appointment takes about 30 mins.
	public:

		Datetime(const string& d, const string& s) {
			//we assume the clinic is running from 8:00-20:00

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
				hf = h + 1;
				mf = (m + 30) % 60;
			}
			else {
				hf = h;
				mf = m + 30;
			}
			date = d;
			hs = h;
			ms = m;
		}

		void print() {
			cout << "Starts: " << hs << ":" << ms << endl;
			cout << "Ends: " << hf << ":" << mf << endl;
		}

		bool checker(int h1, int h2, int m1, int m2) {
			//h1 ending of already set appointment, h2 start of the new one, m1 ending, m2 start
			int t1 = h1 * 60 + m1; //end time in minutes
			int t2 = h2 * 60 + m2; //start time in minutes

			if (abs(t1 - t2) < 30) {
				return true;
			}
			else {
				return false;
			}
		}

		bool operator == (const Datetime& app) noexcept {
			//Check if the appointment times don't overlap with another appointment with the same doc
			return date == app.date && checker(hf, app.hs, mf, app.ms);
		}
	};
}
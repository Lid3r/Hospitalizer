#pragma once
#include <string>
#include "Exceptions.h"
using namespace std;

namespace jb {

	class Pesel {
		string pesel;

		const uint8_t w[11] = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1 };

		//Checksum
	public:
		Pesel(const string& pesel) {

			//Correct length
			if (pesel.length() != 11) {
				throw peselLengthException();
			}

			//No letters
			for (const auto c : pesel) {
				if (c < '0' || c > '9') {
					throw peselLettersException();
				}
			}
			uint16_t sum = 0;
			//checksum checking
			for (size_t i = 0; i < pesel.size(); ++i) {
				sum += (pesel[i] - '0') * w[i];
			}

			if (sum % 10) {
				throw peselChecksumException();
			}

			Pesel::pesel = pesel;
		}

		string print() const {
			return pesel;
		}

		bool operator == (const Pesel& pes) noexcept {
			return pesel == pes.pesel;
		}
	};

	inline ostream& operator << (ostream& out, Pesel& pesel) {
		out << pesel.print();
		return out;
	}

	
}
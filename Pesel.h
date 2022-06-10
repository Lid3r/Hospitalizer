#pragma once
#include <string>
#include "Exceptions.h"
using namespace std;

namespace jb{

class Pesel {
	string pesel;

	const static uint8_t w[]; //Checksum
public:
	Pesel(const string& pesel) {

		//Correct length
		if (pesel.length() != 11) {
			throw invalid_argument("PESEL doesn't have the correct length");
		}

		//No letters
		for (const auto c : pesel) {
			if (c < '0' || c > '9') {
				throw invalid_argument("Incorrect character in PESEL");
			}
		}
		uint16_t sum = 0;
		//checksum checking
		for (size_t i = 0; i < pesel.size(); ++i) {
			sum += (pesel[i] - '0') * w[i];
		}

		if (sum % 10) {
			throw invalid_argument("PESEL checksum incorrect");
		}

		Pesel::pesel = pesel;
	}

	string print() const {
		return pesel;
	}
};

const uint8_t Pesel::w[] = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1 };
}
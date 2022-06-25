#include <iostream>
#include <map>
#include "Appointment.h"
#include "Functions.h"
#include "Exceptions.h"
#include <string>
using namespace std;

int main()
{
	try {
		bool breaker = true;
		while (breaker) {
			menu(breaker);
		}
	
		
	}
	catch (exception &e) {
		cout << "Unhandled exception has occured!" << endl;
	}

	return 0;
}
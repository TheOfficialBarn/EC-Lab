#include <iostream>
#include <cctype>
#include <iomanip> // For formatting the number
using namespace std;
double stringToDouble(const string& str) {
	double result = 0.0;
	int i = 0;
	bool negative = false;

	// Handle sign
	if (str[0] == '-') {negative = true; i++;}
	if (str[0] == '+') {i++;}

	// Process digits before the decimal
	while (i< str.length() && str[i] != '.') {
		result = result * 10.0 + (str[i] - '0');
		i++;
	}

	// Process digits after the decimal
	if (i < str.length() && str[i] == '.') {
		double fraction = 0.1;
		i++;
		while(i < str.length()) {
			result += (str[i] - '0') * fraction;
			fraction *= 0.1;
			i++;
		}
	}
	return negative ? -result : result;

}
double extractNumeric(string userString) {
	try {
		if (userString.length() == 0) {
		throw invalid_argument("User string is empty; there are no characters to validate");
		}
		if(userString.length() == 1 && !isdigit(userString[0])) {
			throw invalid_argument("The input invalid. (Ensure a digit is present in the string)");
		}

		bool decimalFlag = false; //  You can only have one decimal in a number

		for(int i=0; i<userString.length(); i++) {
			// If not first char AND char is + or -, throw error
			if(i != 0 && (userString[i] == '+' || userString[i] == '-')) throw invalid_argument("The input is invalid. (+/- in wrong location)");

			// If char is a decimal
			if(userString[i] == '.'){
				// It's okay if its the first (i.e. flag is fasle)
				if(decimalFlag == false) {
					decimalFlag = true;
					if(!isdigit(userString[i+1]) && !isdigit(userString[i-1])) {
						throw invalid_argument("The input is invalid. (no digits detected on either side of decimal)");
					}
				// Else, we throw an error bc there shouldn't be more than 1 decimal
				} else {
					throw invalid_argument("The input is invalid. (Too many decimal points)");
				}
			
			// If its not a decimal, we can check if its any other non-degit char
			} else {
				// We have to ensure that the if statement below only runs by a non +/- char.
				// This is because we already did a proper check for those symbols
				if(userString[i] != '+' && userString[i] != '-'){
					if(!isdigit(userString[i])) throw invalid_argument("The input is invalid. (A non-digit found)");
				}
			}
		}

		// By now, all tests have passed. We can now safely convert the string to double AND return it
		double num = stringToDouble(userString);
		return num;

	// If a test failed, we can let the user know what went wrong and return a "magic number"
	} catch (exception& e) {
		cerr << e.what() << endl; // Print the error that just occured
		double errorNum = -999999.99;
		return errorNum;
	}
}

int main() {
	while(true){
		string userString;
		do {
			cout << "—————————————————————————————————————" << endl << endl;
			userString = "";
			// Get a string from the user
			cout << "Enter a string below (or 'END' to quit): ";
			cin >> userString;
			// We want it to be less than 20 chars, otherwise we make user retry
			if(userString.length() > 20) {
				cout << "Enter a valid string of 20 or less characters!!" << endl << endl;
			}
		} while(userString.length() > 20);
		if(userString == "END") return 0;
		// If it's less than or equal to 20, we can extractNumeric
		double num = extractNumeric(userString);
		// It is possible that user entered a -0 equivalent value. To correct this value we run this simple check below.
		if(num==0) num=0;

		// Below we print the number to the formatting specifications
		cout << "The input is: " << fixed << setprecision(4) << num << endl << endl;
	}
}
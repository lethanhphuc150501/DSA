#include "main.h"

int MAXSIZE;

void LAPSE(string name) {
	cout << "LAPSE " << name << endl;
}

void KOKUSEN() {
	cout << "KOKUSEN" << endl;
}

void KEITEIKEN(int num) {
	cout << "KEITEIKEN " << num << endl;
}

void HAND() {
	cout << "HAND " << endl;
}

void LIMITLESS(int num) {
	cout << "LIMITLESS " << num << endl;
}

void CLEAVE(int num) {
	cout << "CLEAVE " << num << endl;
}

void simulate(string filename) {
	ifstream ss(filename);
	string str, maxsize, name, energy, num;
	while (ss >> str) {
		if (str == "MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		} else if (str == "LAPSE") {
			ss >> name;
			LAPSE(name);
		} else if (str == "KOKUSEN") {
			KOKUSEN();
		} else if (str == "KEITEIKEN") {
			ss >> num;
			KEITEIKEN(stoi(num));
		} else if (str == "HAND") {
			HAND();
		} else if (str == "LIMITLESS") {
			ss >> num;
			LIMITLESS(stoi(num));
		} else {
			ss >> num;
			CLEAVE(stoi(num));
		}
	}
	return;
}
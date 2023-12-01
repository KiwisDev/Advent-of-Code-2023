#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream fs("inputs/puzzle.txt");

	string line;
	int total = 0;
	while (getline(fs, line)) {
		string num = "";

		int i = 0;
		while (num.length() < 1 && i < line.length()) {
			//cout << line << endl;

			if (isdigit(line[i])) {
				num.push_back(line[i]);
			}
			else {
				int maxLenght = line.length() - i;

				if (line[i] == 'o') { // Check for "one"
					if (maxLenght >= 3) {
						if (line.substr(i, 3) == "one")
							num.push_back('1');
					}
				}

				if (line[i] == 't') {
					if (maxLenght >= 3) { // Check for "two"
						if (line.substr(i, 3) == "two")
							num.push_back('2');
					}

					if (maxLenght >= 5) { // Check for "three"
						if (line.substr(i, 5) == "three")
							num.push_back('3');
					}
				}

				if (line[i] == 'f') {
					if (maxLenght >= 4) { // Check for "four"
						if (line.substr(i, 4) == "four")
							num.push_back('4');
					}

					if (maxLenght >= 4) { // Check for "five"
						if (line.substr(i, 4) == "five")
							num.push_back('5');
					}
				}

				if (line[i] == 's') {
					if (maxLenght >= 3) { // Check for "six"
						if (line.substr(i, 3) == "six")
							num.push_back('6');
					}

					if (maxLenght >= 5) { // Check for "seven"
						if (line.substr(i, 5) == "seven")
							num.push_back('7');
					}
				}

				if (line[i] == 'e') { // Check for "eight"
					if (maxLenght >= 5) {
						if (line.substr(i, 5) == "eight")
							num.push_back('8');
					}
				}

				if (line[i] == 'n') { // Check for "nine"
					if (maxLenght >= 4) {
						if (line.substr(i, 4) == "nine")
							num.push_back('9');
					}
				}
			}
			i++;
		}

		i = line.length() - 1;
		while (num.length() < 2 && i >= 0) {
			if (isdigit(line[i])) {
				num.push_back(line[i]);
			}
			else {
				int maxLenght = i;

				if (line[i] == 'e') {
					if (maxLenght >= 3) { // Check for "one"
						if (line.substr(i - 2, 3) == "one")
							num.push_back('1');
					}

					if (maxLenght >= 5) { // Check for "three"
						if (line.substr(i - 4, 5) == "three")
							num.push_back('3');
					}

					if (maxLenght >= 4) { // Check for "five"
						if (line.substr(i - 3, 4) == "five")
							num.push_back('5');
					}

					if (maxLenght >= 4) { // Check for "nine"
						//cout << line.substr(i - 3, 4) << endl;
						if (line.substr(i - 3, 4) == "nine")
							num.push_back('9');
					}
				}

				if (line[i] == 'o') { // Check for "two"
					if (maxLenght >= 3) {
						if (line.substr(i - 2, 3) == "two")
							num.push_back('2');
					}
				}

				if (line[i] == 'r') { // Check for "four"
					if (maxLenght >= 4) {
						if (line.substr(i - 3, 4) == "four")
							num.push_back('4');
					}
				}

				if (line[i] == 'x') { // Check for "six"
					if (maxLenght >= 3) {
						if (line.substr(i - 2, 3) == "six")
							num.push_back('6');
					}
				}

				if (line[i] == 'n') { // Check for "seven"
					if (maxLenght >= 5) {
						if (line.substr(i - 4, 5) == "seven")
							num.push_back('7');
					}
				}

				if (line[i] == 't') { // Check for "eight"
					if (maxLenght >= 5) {
						if (line.substr(i - 4, 5) == "eight")
							num.push_back('8');
					}
				}
			}
			i--;
		}

		cout << line << " " << stoi(num) << endl;

		total += stoi(num);
	}

	cout << total;

	return 0;
}

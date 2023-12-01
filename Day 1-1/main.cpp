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
			if (isdigit(line[i]))
				num.push_back(line[i]);
			i++;
		}

		i = line.length()-1;
		while (num.length() < 2 && i >= 0) {
			if (isdigit(line[i]))
				num.push_back(line[i]);
			i--;
		}

		total += stoi(num);
	}

	cout << total;

	return 0;
}

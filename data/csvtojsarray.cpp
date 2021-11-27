#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv) {
	if (argc <= 1) {
		cerr << "Usage: " << argv[0] << " filename [array_name] [delimiter]" << endl;
		return 1;
	}
	
	string filename = argv[1];
	
	char del = ',';
	if (argc >= 4) {
		del = argv[3][0];
	}
	
	cerr << "Filename: " << filename << endl << "Delimiter character: " << del << endl;
	
	ifstream is(filename);
	if (!is) {
		cerr << "File error" << endl;
		return 2;
	}
	
	if (argc >= 3) {
		cout << "const " << argv[2] << " = ";
	}
	
	cout << "[\n";
	bool isstring = false;
	bool first = true;
	bool header = true;
	vector<string> vheader(1, "");
	char ch;
	while ((ch = is.get()) != -1) {
		if (ch == '\r') {
			continue;
		} else if (ch == '\n') {
			if (!header) cout << "\"],\n";
			first = true;
			header = false;
		} else if (ch == '\"') {
			isstring = !isstring;
		} else if (ch == del) {
			if (first && !header) {
				cout << "\t[\"";
				first = false;
			}

			if (header) {
				vheader.push_back("");
			} else {
				if (!isstring) {
					cout << "\", \"";
				} else {
					cout << ch;
				}
			}
		} else {
			
			if (header) {
				vheader.back() += ch;
			} else {
				if (first) {
					cout << "\t[\"";
					first = false;
				}
				cout << ch;
			}
		}
	}
	
	if (!first) {
		cout << '\n';
	}
	cout << "]";
	
	if (argc >= 3) {
		cout << ";";
	}
	
	cout << endl;

	// header data
	if (argc >= 3) {
		cout << "const " << argv[2] << "_header = {\n\t";
		for (int i = 0; i < vheader.size(); i++) {
			cout << "\"" << vheader[i] << "\": " << i << ", ";
		}
		cout << "\n};" << endl;
	}
}

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc <= 1) {
		cerr << "Usage: " << argv[0] << " filename [array_name] [delimiter]" << endl;
		return 1;
	}
	
	string filename = argv[1];
	
	if (argc >= 3) {
		cout << "const " << argv[2] << " = ";
	}
	
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
	
	cout << "[\n";
	bool isstring = false;
	bool first = true;
	char ch;
	while ((ch = is.get()) != -1) {
		if (ch == '\r') {
			continue;
		} else if (ch == '\n') {	
			cout << "\"],\n";
			first = true;
		} else if (ch == '\"') {
			isstring = !isstring;
		} else if (ch == del) {
			if (first) {
				cout << "\t[\"";
				first = false;
			}
			
			if (!isstring) {
				cout << "\", \"";
			} else {
				cout << ch;
			}
		} else {
			if (first) {
				cout << "\t[\"";
				first = false;
			}
			
			cout << ch;
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
}

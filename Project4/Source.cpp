#include <iostream>
#include <fstream>

#define MAS_SIZE 1024
const char sep[] = ". ,!?:;_\n";
const char vow[] = "aeiouyAEIOUY";

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

bool check(const char c, const char *sp);
void strcpy(char* s1, const char *s2, int size);

int main() {
	int i, j;
	int size;
	int count = 0;
	char c;
	char buf[MAS_SIZE];
	bool flagWord = false;
	bool flagVow = false;
	ifstream in("in.txt");
	if (!in.is_open()) {
		cout << "Error: file is not opened" << endl;
		in.close();
		return 0;
	}

	try {
		for (i = 0; (buf[i] = in.get()) != EOF && i < MAS_SIZE; ++i);
		if (buf[i] == EOF) {
			buf[i] = '\0';
			size = i;
			in.close();
		}
		else {
			throw "File > MAS_SIZE";
		}
	}
	catch (const char* str) {
		cout << "Error, " << str << endl;
		in.close();
		return 0;
	}


	cout << "Original text: " << buf << endl;


	for (i = 0; i < size; ++i) {
		if (!check(buf[i], sep)) {
			if (!flagWord) {
				flagWord = true;
				if (check(buf[i], vow)) {
					j = i;
					flagVow = true;
				}
			}
		}
		else if (flagWord) {
			if (flagVow && check(buf[i - 1], vow)) {
				c = buf[i];
				buf[i] = '\0';
				cout << "Word " << ++count << ": " << buf + j << endl;
				buf[i] = c;
			}
			flagWord = false;
			flagVow = false;
		}

	}

	if (!count)
		cout << "Choose another words";
	in.close();

	cin >> i;
	return 0;
}

bool check(const char c, const char *sp) {
	if (c == '\0') return false;
	for (int i = 0; sp[i] != '\0'; ++i)
		if (sp[i] == c) return true;
	return false;
}
void strcpy(char* s1, const char *s2, int size) {
	for (int i = 0; i < size; ++i)
		s1[i] = s2[i];
}

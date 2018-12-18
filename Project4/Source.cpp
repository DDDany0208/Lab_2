#include <iostream>
#include <fstream>

#define MAS_SIZE 1024
const char sep[] = ". ,!?:;_\n";
const char vow[] = "aeiouy";

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
	char *word;
	char buf[MAS_SIZE];
	ifstream in("in.txt");
	if (!in.is_open()) {
		cout << "Error: file is not opened" << endl;
		in.close();
		return 0;
	}
	for (i = 0; (buf[i] = in.get()) != EOF; ++i); in.close();
	buf[i] = '\0';
	size = i;
	cout << "Original text: " << buf << endl;
	for (i = 0; i < size; ++i) {
		
		if (!check(buf[i], sep)) {
			if (check(buf[i], vow)) {
				for (j = i + 1; j < size; ++j)
					if (check(buf[j], sep)) break;
				if (check(buf[j - 1], vow)) {
					word = new char[j - i + 1];
					strcpy(word, buf + i, j - i);
					word[j - i] = '\0';
					cout << "Word " << ++count << ": " << word << endl;
					delete[] word;
					i = j;
				}
			}
			else {
				for (; i < size; ++i)
					if (check(buf[i], sep)) break;
			}
		}
		
	}
	
	if (!count)
		cout << "Oops, another time :)";
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

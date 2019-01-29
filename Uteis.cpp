#include"Uteis.h"
#define _CRT_SECURE_NO_WARNINGS

void Uteis::split(std::string str, std::string sep) {
	arr.clear();
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
}

string Uteis::GetElement(int pos) {
	if (arr.size() >= pos)
		return arr[pos];
	return "";
}
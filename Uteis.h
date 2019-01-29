#include<iostream>
#include<string>
#include<time.h>
#include <fstream>
#include<list>
#include<map>
#include<vector>
using namespace std;

class Uteis {
private:
	vector<std::string> arr;
public:
	void split(std::string str, std::string sep);
	string GetElement(int pos);
};

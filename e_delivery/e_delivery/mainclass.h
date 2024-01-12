#pragma once
#include <string>
using namespace std;
class Main {
private:
	string category;
	string name;
public:
	Main(string _category, string _name);
	void set_category(string category);
	void set_name(string name);
	string get_category();
	string get_name();
	

};
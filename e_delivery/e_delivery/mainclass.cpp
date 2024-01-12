#include "mainclass.h"

Main::Main(string _category,string _name) {
	category = _category;    name = _name;  
}
void Main::set_category(string category) {
	this->category = category;
}
void Main::set_name(string name) {
	this->name = name;
}
string Main::get_category() {
	return category;
}
string Main::get_name(){
	return name;
}

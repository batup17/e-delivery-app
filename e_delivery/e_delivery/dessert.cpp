#include "dessert.h"
#include <iomanip>
#include <Windows.h>
#include <iostream>

using namespace std;
extern HANDLE hConsole;//We use the extern keyword to use this variable from other files.
//extern void send_to_dessert_menu();

Dessert::Dessert(string _category, string _name, int _price, string _type) :Main(_category, _name) {
	type = _type;
	price = _price;
}

void Dessert::set_type(string type) {
	this->type = type;
}

string Dessert::get_type() {
	return type;
}
int Dessert::get_price() {
	return price;
}


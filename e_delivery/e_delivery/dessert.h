#pragma once
#include "mainclass.h"

class Dessert :public Main{
private:
	string type;
	int price;
public:
	Dessert(string _category, string _name, int _price, string _type);
	void set_type(string type);
	string get_type();
	int get_price();
};

//void dessert_order_menu();
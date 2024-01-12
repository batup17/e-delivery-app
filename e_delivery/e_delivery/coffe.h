#pragma once
#include "mainclass.h"
#

class Coffe : public Main {
private:
	int price_big_size;
	int price_medium_size;
	int price_small_size;
public:
	Coffe(string _category, string _name, int _price_big_size,int _price_medium_size,int _price_small_size);
	int get_price_big_size();
	int get_price_medium_size();
	int get_price_small_size();
};

//void coffe_order_menu();
#include "coffe.h"
#include "mainclass.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>

using namespace std;
extern HANDLE hConsole;
//extern void send_to_coffe_menu();



Coffe::Coffe(string _category, string _name, int _price_big_size, int _price_medium_size, int _price_small_size) : Main(_category, _name) {
	price_big_size = _price_big_size;       price_medium_size = _price_medium_size;        price_small_size = _price_small_size;
}

int Coffe::get_price_big_size(){
	return price_big_size;
}

int Coffe::get_price_medium_size(){
	return price_medium_size;
}

int Coffe::get_price_small_size(){
	return price_small_size;
}


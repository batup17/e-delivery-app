#pragma once
#include <string>
using namespace std;

class Customers {
private:
	string first_name;
	string last_name;
	string email;
	string phone_number;
	string password;
	int balance;
public:
	Customers(string First_Name, string Last_Name, string Email, string Phone_Number, string Password , int Balance);//declaring the constructor.
	string get_first_name();//get methods for accessing private variables.
	string get_last_name();
	string get_email();
	string get_phone_number();
	string get_password();
	int get_balance();
};

void customer_register();
void customer_login();
void customer_menu();
void cin_check_bool(bool &try_again);
void cin_check_menu_choice(int& choice);
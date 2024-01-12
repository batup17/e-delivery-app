#include <iostream>
#include <list>
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include "coffe.h"
#include "dessert.h"
#include "customers.h"

using namespace std;

int EXIT = 4;
int dessert_choice_number;//global variable for copy and use product numbers of coffe menu.
int coffe_choice_number;//global variable for copy and use product numbers of dessert menu.
int product_number_coffe;
int product_number_dessert;
string email_check;//Gloabal variable for check customer email.

extern HANDLE hConsole; // We use the extern keyword to use this variable from other files.
extern void send_to_coffe_menu();
extern void send_to_dessert_menu();
extern vector<Coffe> read_text_file_coffe();//ý use this function here because ý have to storage coffe orders the vector and access coffe objects.
extern vector<Dessert> read_text_file_dessert();//ý use this function here because ý have to storage coffe orders the vector and access dessert objects.
extern void send_product_numbers_coffe();
extern void send_product_numbers_dessert();

Customers::Customers(string First_Name, string Last_Name, string Email, string Phone_Number, string Password , int Balance) { //Ýmplementing the constructor
	first_name = First_Name;        last_name = Last_Name;         email = Email;          phone_number = Phone_Number;        password = Password;   balance = Balance;
}

string Customers::get_first_name() { //get method for calling private variables.
	return first_name;
}
string Customers::get_last_name(){
	return last_name;
}
string Customers::get_email() {
	return email;
}
string Customers::get_phone_number() {
	return phone_number;
}
string Customers::get_password() {
	return password;
}
int Customers::get_balance() {
	return balance;
}

void cin_check_int(int &choice) {

	while (true) {

		cin >> choice;
		//cout << endl;

		if (cin.fail()) { //cin.fail() -> if user input string to int variable it gives error message.cin.fail() helps for avoid infinite loop
			cout << endl;
			cout << "  " << "Please only enter a number(dont try to input string or char) !!!" << endl << endl;
			cin.clear();// clearing users input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignores input other than integer.
			cout << "  " << "Input Again : ";
		}

		else {
			
			break;
		}
	}


}

void cin_check_bool(bool& try_again) { //Ýf user dont input integer,program goes infinite loop,so this is a input control function.Ýf user input string or char,it gives a warning then back to choose.
	
	SetConsoleTextAttribute(hConsole, 3);

	while (true)
	{
		
		cout << endl << "  " << "if you want to try again enter 1, you want to exit enter 0 : ";
		cin >> try_again;
		cout << endl;

		if (cin.fail() || (try_again != 0 && try_again != 1)) {
			cout << "  " << "Please enter only 1 or 0!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			try_again = true;
		}

		else
		{
			break;
		}
		
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void customer_register() {

	SetConsoleTextAttribute(hConsole, 3);
	bool tryagain = true;
	/*bool back_the_menu = 0;*/
	
	while(tryagain){
	string cin_name,cin_last_name,cin_email,cin_phone_number,cin_password;
	int balance = 0;
	cout << "               >> REGISTER AS CUSTOMER <<                     "<<endl;
	cout << "               -----------------------------------------------"<<endl;
	cout << "                   NAME : ";  cin.ignore(); getline(cin, cin_name);
	cout << "               -----------------------------------------------"<<endl;
	cout << "                   LAST NAME : ";           getline(cin, cin_last_name);
	cout << "               -----------------------------------------------"<<endl;
	cout << "                   EMAIL : ";               getline(cin,cin_email);   
	cout << "               -----------------------------------------------"<<endl;
	cout << "                   PHONE NUMBER : ";        getline(cin,cin_phone_number);  
	cout << "               -----------------------------------------------"<<endl;
	cout << "                   PASSWORD : ";            getline(cin, cin_password);
	cout << "               -----------------------------------------------"<<endl<<endl;

	ifstream checkcustomertxt("registercustomer.txt");
	string line;
	string customer_phone_number = cin_phone_number;
	string customer_email = cin_email;
	bool emailExists = false;
	bool phoneNumberExists = false;

	while (getline(checkcustomertxt, line)) {

		if (line.find("EMAIL : ") == 0) {

			string c_email = line.substr(8);

			if (customer_email == c_email) {

				emailExists = true;
			}
		}
		else if (line.find("PHONE NUMBER : ") == 0) {

			string c_phone_number = line.substr(15);

			if (customer_phone_number == c_phone_number) {

				phoneNumberExists = true;
			}
		}
	}

	checkcustomertxt.close();

	if (emailExists && phoneNumberExists) {
		
			cout << "  " << "You can not registered !!! This email address and phone number belong to another user. Please try different ones!" << endl << endl;
			cin_check_bool(tryagain);
	}
	else if (emailExists) {

		cout << "  " << "You can not registered !!! This email address belongs to another user. Please try a different email address!" << endl<<endl;
		cin_check_bool(tryagain);
	}
	else if (phoneNumberExists){

		cout << "  " << "You can not registered !!! This phone number belongs to another user. Please try a different phone number!" << endl<<endl;
		cin_check_bool(tryagain);
	}
	else {

		Customers customer(cin_name, cin_last_name, cin_email, cin_phone_number, cin_password ,balance);
		fstream registercustomertxt;
		registercustomertxt.open("registercustomer.txt", ios::out | ios::binary | ios::app);//this txt file created in this project folder.So it will work fine any computer. 

		if (!registercustomertxt.is_open()) {

			cout << "  " << "File can not open";
		}
		else
		{

			registercustomertxt << "NAME : " << customer.get_first_name() << endl << "LAST NAME : " << customer.get_last_name() << endl <<
			"EMAIL : " << customer.get_email() << endl << "PHONE NUMBER : " << customer.get_phone_number() << endl <<
			"PASSWORD : " << customer.get_password()<<endl<<"BALANCE : " <<customer.get_balance()<<endl << endl;//writing class objects into text file 
			registercustomertxt.close();//close text file.
		}
		cout << "  " << "You are registered succesfuly!!!"<<endl<<endl;
		tryagain = false;
	}

	}
	SetConsoleTextAttribute(hConsole, 7);
}


void customer_login() {
	
	bool tryagain = true;

	while(tryagain)
	{
	SetConsoleTextAttribute(hConsole, 3);	
	string cin_email, cin_password;

     cout <<endl<<"               >> LOGIN AS CUSTOMER <<                        " << endl;   
	      cout << "               -----------------------------------------------" << endl;
	      cout << "                   EMAIL    : ";        cin.ignore();    getline(cin, cin_email);
	      cout << "               -----------------------------------------------" << endl;
	      cout << "                   PASSWORD : ";                      getline(cin, cin_password);
	      cout << "               -----------------------------------------------" << endl << endl;

	ifstream checkcustomertxt("registercustomer.txt");
	string line;
	string customer_password = cin_password;
	string customer_email = cin_email;
	bool emailExists = false;
	bool passwordExists = false;

	while (getline(checkcustomertxt, line)) {
		if (line.find("EMAIL : ") == 0) {
			string c_email = line.substr(8);
			if (customer_email == c_email) {
				emailExists = true;
				email_check = customer_email;// I use email_check variable to access the email address of the person who is logged in.For use in add_balance_account and give order function.
				

			}
		}
		else if (line.find("PASSWORD : ") == 0) { // same thing as email
			string c_password = line.substr(11);
			if (c_password == customer_password) {
				passwordExists = true;
			}
		}
	}

	checkcustomertxt.close();

	if (!passwordExists && !emailExists) {   //controls email and password. 

		cout <<"  "<<"Password or email adress is wrong !!!" << endl << endl;
		cin_check_bool(tryagain);
	}
	else if (!passwordExists) {

		cout << "  " << "Password or email adress is wrong !!!"<< endl << endl;
		cin_check_bool(tryagain);
	}
	else if (!emailExists) {

		cout << "  " << "Password or email adress is wrong !!!" << endl << endl;
		cin_check_bool(tryagain);
	}
	else {

		cout << "  " << "You are login succesfuly !!!" << endl << endl;
		SetConsoleTextAttribute(hConsole, 7);
		customer_menu();
		tryagain = false;
	}
	} 
	
}


void cin_check_menu_choice(int& choice) {

	while (true) {

		cout << endl << "  " << "Enter a number between 1 and 3 (To exit, enter 4) : ";
		cin >> choice;
		cout << endl;

		if (cin.fail() || (choice < 1 || choice > 4)) { //cin.fail() -> if user input string to int variable it gives error message.cin.fail() helps for avoid infinite loop
			cout << "  " << "Please only enter a number between 1 and 3 (dont try to input string or char) , To exit, enter 4 !!!" << endl;
			cin.clear();// clearing users input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignores input other than integer.
		}

		else {
			break;
		}
	}
}

void balance_update(int &choice,int &order_cost) {
	int current_balance;
	int add_balance;

	if(choice == 1){

	cout << "  " << "How many dollars do you want to add to your account ? : ";
	cin_check_int(add_balance);
	}

	ifstream inputFile("registercustomer.txt"); 
	ofstream tempFile("temp.txt"); 

	if (!inputFile.is_open()) {
		cout << "  " << "File can not open";
		return;
	}

	bool found = false;
	string line;

	while (getline(inputFile, line)) { //Read text file line by line and transfer informations in line variable.

		if (line.find("EMAIL : ") == 0) { // if EMAÝL line found in text file

			string email = line.substr(8); // Copy characters beyond 8 characters and transfer in email variable

			if (email == email_check) { // if the entered email is equal to the email variable enter the condition 

				found = true;
				tempFile << line << endl; // write email line in temporary text file.
				getline(inputFile, line); // go to next line well phone number line
				tempFile << line << endl; // write phone number line in temporary text file.
				getline(inputFile, line); // go to next line well Password line.
				tempFile << line << endl; // write password line in temporary text file.
				getline(inputFile, line); // go to next line well balance line;
				if(choice==1){//if choice == 1 add balance account
					current_balance = stoi(line.substr(10)) + add_balance;//in balance line copy other chars without "BALANCE : " and plus current balance.
				}
				else{//else,pay the order.
					current_balance = stoi(line.substr(10)) - order_cost;
                    
				}
				tempFile << "BALANCE : " << current_balance << endl<<endl;//update balance and write temporary file.						
			}
			else {
				tempFile << line << endl; //Copy unmatched lines directly well name and last name line
			}
		}
		else {
			tempFile << line << endl; //if email line not found directly copy.
		}
	}

	inputFile.close(); // close the file.
	tempFile.close();

	if (found) { // if matches , replace temp file with original file.

		remove("registercustomer.txt");

		if (rename("temp.txt", "registercustomer.txt") != 0) { //Rename control.

			perror("File rename error: ");
		}
		else if(choice == 1){
			cout << "  " << "Balance updated successfully!" << endl<<endl;
			cout << "  " << "Your new balance is " << current_balance;
		}
	}
	else {
		remove("temp.txt"); // if not matches delete temporary file.
		cout << "  " << "Email not found in the records." << endl;
	}
}

void animation() {

	for (int i = 0; i <= 2; i++) {
		cout << "  " << "Your ";
		Sleep(500);
		cout << "Order ";
		Sleep(500);
		cout << "is ";
		Sleep(500);
		cout << "Preparing";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		std::cout << "\r                            \r";
	}
	cout << "  " << "DONE !!!";

}
void display_completed_orders_dessert(vector<Dessert>& previous_dessert_orders) {

	for (Dessert& completed_dessert_orders : previous_dessert_orders)
	{
		cout << "\t\t" << left << setw(20) << completed_dessert_orders.get_category()
			<< left << setw(20) << completed_dessert_orders.get_name()
			<< left << setw(20) << completed_dessert_orders.get_price() << left << setw(20) << completed_dessert_orders.get_type()
			<< endl;
		cout << "\t\t" << "---------------------------------------------------------------------------" << endl;
	}
}

void display_completed_orders_coffe(vector<Coffe>& previous_coffe_orders) {
	
	for (Coffe& completed_coffe_orders : previous_coffe_orders)
	{
		cout << "\t\t" << left << setw(20) << completed_coffe_orders.get_category()
			<< left << setw(20) << completed_coffe_orders.get_name()
			<< left << setw(20) << completed_coffe_orders.get_price_big_size()
			<< endl;
		cout << "\t\t" << "---------------------------------------------------------------------------" << endl;
	}
}
void read_completed_orders_dessert() {

	ifstream read_dessert_orders("dessertorders.txt");
	string line;
	vector<Dessert> previous_dessert_orders;

	while (getline(read_dessert_orders, line)) {

		if (line.find("EMAIL : ") == 0) {

			string email = line.substr(8);

			if (email == email_check) {

				string category, name, price, type;

				getline(read_dessert_orders, category);
				getline(read_dessert_orders, name);
				getline(read_dessert_orders, price);
				getline(read_dessert_orders, type);
				int price_int = stoi(price);

				Dessert completed_dessert_orders(category, name, price_int,type);
				previous_dessert_orders.push_back(completed_dessert_orders);
				getline(read_dessert_orders, line);
			}

		}

	}
	read_dessert_orders.close();
	display_completed_orders_dessert(previous_dessert_orders);
	
	
}


void read_completed_orders_coffe() {

	ifstream read_coffe_orders("coffeorders.txt");
	string line;
	vector<Coffe> previous_coffe_orders;

	while (getline(read_coffe_orders, line)) {

		if (line.find("EMAIL : ") == 0) {

			string email = line.substr(8);

			if (email == email_check) {

				string category, name, price;

				getline(read_coffe_orders, category);
				getline(read_coffe_orders, name);
				getline(read_coffe_orders, price);

				int price_int = stoi(price);

				Coffe completed_coffe_orders(category, name, price_int, 0, 0);		
				previous_coffe_orders.push_back(completed_coffe_orders);
				getline(read_coffe_orders, line);
			}

		}

	}
	read_coffe_orders.close();
	display_completed_orders_coffe(previous_coffe_orders);
}

void give_order() {

	int choice_pay = 2;
	int coffe_choice;
	int dessert_choice;
	int choice;
	int size = 0;
	int order_cost_coffe = 0;
	int order_cost_dessert = 0;
	int customer_balance = 0;
	
	vector<Coffe> coffe_order;
	vector<Coffe> storage_coffe_order;
	vector<Dessert> dessert_order;
	vector<Dessert> storage_dessert_order;

	ifstream checkcustomertxt("registercustomer.txt");
	string line;

	while (getline(checkcustomertxt, line)) {//email check

		if (line.find("EMAIL : ") == 0) {

			string email = line.substr(8);

			if (email == email_check) {

				getline(checkcustomertxt, line);
				getline(checkcustomertxt, line);
				getline(checkcustomertxt, line);
				customer_balance = stoi(line.substr(10));
			}

		}

	}

	checkcustomertxt.close();
	send_to_coffe_menu(); // show coffe menu to customer
	cout << endl;
	send_to_dessert_menu(); // show dessert menu to customer
	cout << endl;

	SetConsoleTextAttribute(hConsole, 2);//Changing texts color(2 is green)

	cout << "\t" << "~~ Order Coffe Enter 1 ~~"<<"\t";      cout << "~~ Order Dessert Enter 2 ~~"<<"\t";      cout << "~~ Order Coffe and Dessert Enter 3 ~~"<<endl<<endl;
	cout << endl;
	cin_check_menu_choice(choice);

	if (choice==1){

		cout << "  " << "Please enter a number which coffe you want order : ";
		cin_check_int(coffe_choice);
		cout << endl;
		cout << "  " << "Which size you want order ?(Big : 1 / Medium : 2 / Small : 3) : ";

		while (true) //input control for avoid endless loop.
		{
			cin >> size;
			cout << endl;

			if (cin.fail() || (size < 1 || size > 3)) { 

				cout << "  " << "Please only enter 1,2 or 3 (dont try to input string or char)" << endl<<endl;
				cin.clear();// clears users input
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "  " << "Input Again : ";
			}

			else {

				break;
			}
		}
		
	      coffe_choice_number = coffe_choice;
		  send_product_numbers_coffe();

		if (coffe_choice == product_number_coffe) {

			 coffe_order = read_text_file_coffe(); //Transfering class objects to another vector.
			

			if (size == 1) {

			order_cost_coffe = coffe_order[coffe_choice].get_price_big_size();// if users choose big size coffe, transfer price of big size coffe into variable.
			}

			else if (size == 2){

			order_cost_coffe = coffe_order[coffe_choice].get_price_medium_size();// if users choose medium size coffe, transfer price of medium size coffe into variable.
			}

			else {

			order_cost_coffe = coffe_order[coffe_choice].get_price_small_size();// if users choose small size coffe, transfer price of small size coffe into variable.
			}			

			if (customer_balance >= order_cost_coffe) {// Checking balance of customer.

				storage_coffe_order.push_back(coffe_order[coffe_choice]);
				balance_update(choice_pay,order_cost_coffe);//reducing the user's balance.

					ofstream write_coffe_orders;
					write_coffe_orders.open("coffeorders.txt", ios::out | ios::binary | ios::app);

					if (!write_coffe_orders.is_open()) { //Checks the text file is opened.

						cout << "File cant open !!! ";
					}
					else
					{

						write_coffe_orders << "EMAIL : " << email_check << endl << storage_coffe_order[0].get_category() << endl << storage_coffe_order[0].get_name() << endl << order_cost_coffe << endl<< endl;//add coffe order text file.
						write_coffe_orders.close();
					}
				
				cout << "  " << "Your order has been received !!!"<<endl<<endl;
				animation();

			}

			else{

				cout << "  " << "You dont have enough balance to order this coffe !!! Please add balance your account !!! ";
			}

	    }

		else {
			cout << "  " << "There is no coffee for the number you entered in the coffee order list !!!";
			return;
		}
	
	}

	else if(choice ==2){// same thing as choice==1 condition.

		cout << "  " << "Please enter a number which dessert you want order : ";
		cin_check_int(dessert_choice);
		dessert_choice_number = dessert_choice;
	    send_product_numbers_dessert();

		if (dessert_choice == product_number_dessert) {

			dessert_order = read_text_file_dessert();	
			order_cost_dessert = dessert_order[dessert_choice].get_price();

			if (customer_balance >= order_cost_dessert) {

				storage_dessert_order.push_back(dessert_order[dessert_choice]);
				balance_update(choice_pay, order_cost_dessert);

				ofstream write_dessert_orders;
				write_dessert_orders.open("dessertorders.txt", ios::out | ios::binary | ios::app);

				if (!write_dessert_orders.is_open()) { //Checks the text file is opened.

					cout << "File cant open !!! ";
				}
				else
				{

					write_dessert_orders << "EMAIL : " << email_check << endl << storage_dessert_order[0].get_category() << endl << storage_dessert_order[0].get_name() << endl << storage_dessert_order[0].get_price() << endl << storage_dessert_order[0].get_type() << endl << endl;//add dessert order text file.
					write_dessert_orders.close();
				}
				cout << "  " << "Your order has been received !!!"<<endl<<endl;
				animation();

			}

			else{

				cout << "  " << "You dont have enough balance to order this dessert !!! Please add balance your account !!! ";
			}
		}

		else{

			cout << "  " << "There is no dessert for the number you entered in the dessert order list !!!";
			return;
		}

	}

	else if (choice == EXIT){

		return;
	}

	else if(choice ==3){//same thing as choice == 1 condition

		cout << "  " << "Please enter a number which coffe and dessert you want order : "<<endl<<endl;
		cout << "  " << "Coffe Choice   : ";    cin_check_int(coffe_choice);
		cout << "  " << "Which size you want order ?(Big : 1 / Medium : 2 / Small : 3) : ";
		while (true)
		{
			cin >> size;
			cout << endl;
			if (cin.fail() || (size < 1 || size > 3)) {

				cout << "  " << "Please only enter 1,2 or 3 !!! (dont try to input string or char)" << endl<<endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "  " << "Input Again : ";
			}
			else {
				break;
			}
		}
		cout << "  " << "Dessert Choice : ";    cin_check_int(dessert_choice);

		dessert_choice_number = dessert_choice;     send_product_numbers_dessert();
		coffe_choice_number = coffe_choice;         send_product_numbers_coffe();

		if (coffe_choice == product_number_coffe && dessert_choice == product_number_dessert) {

			coffe_order = read_text_file_coffe();
			dessert_order = read_text_file_dessert();
			order_cost_dessert = dessert_order[dessert_choice].get_price();

			if (size == 1) {

				order_cost_coffe = coffe_order[coffe_choice].get_price_big_size();
			}

			else if (size == 2) {

				order_cost_coffe = coffe_order[coffe_choice].get_price_medium_size();
			}

			else {

				order_cost_coffe = coffe_order[coffe_choice].get_price_small_size();
			}

			if (customer_balance >= order_cost_dessert + order_cost_coffe) {

				;
				storage_coffe_order.push_back(coffe_order[coffe_choice]);
				storage_dessert_order.push_back(dessert_order[dessert_choice]);
				balance_update(choice_pay, order_cost_coffe);
				balance_update(choice_pay, order_cost_dessert);

				ofstream write_coffe_orders;
				write_coffe_orders.open("coffeorders.txt", ios::out | ios::binary | ios::app);

				if (!write_coffe_orders.is_open()) { //Checks the text file is opened.

					cout << "File cant open !!! ";
				}

				else
				{

					write_coffe_orders << "EMAIL : " << email_check << endl << storage_coffe_order[0].get_category() << endl << storage_coffe_order[0].get_name() << endl << order_cost_coffe << endl << endl;//add coffe order text file.
					write_coffe_orders.close();
				}

				ofstream write_dessert_orders;
				write_dessert_orders.open("dessertorders.txt", ios::out | ios::binary | ios::app);

				if (!write_dessert_orders.is_open()) { //Checks the text file is opened.

					cout << "File cant open !!! ";
				}

				else
				{

					write_dessert_orders << "EMAIL : " << email_check << endl << storage_dessert_order[0].get_category() << endl << storage_dessert_order[0].get_name() << endl << storage_dessert_order[0].get_price() << endl << storage_dessert_order[0].get_type() << endl << endl;//add dessert order text file.
					write_dessert_orders.close();
				}

				cout << "  " << "Your order has been received !!!"<<endl<<endl;
				animation();
			}

			else {

				cout << "  " << "You dont have enough balance to order this dessert and coffe !!! Please add balance your account !!! ";
			}

		}
		else {

			cout << "  " << "There is no dessert and coffe for the number you entered in the dessert order list !!!";
			return;
		}
	}
	
	SetConsoleTextAttribute(hConsole, 7); //Back to normal color
}

void see_your_previous_orders() {
  	
	cout << "                                    ~~  YOUR PREVIOUS ORDERS  ~~                      " << endl;
	cout << "\t\t" << "---------------------------------------------------------------------------" << endl;
	cout << "\t\t" << left << setw(20) << "Category" << left << setw(20) << "Name" << left << setw(20) << "Order Cost($)" << left << setw(20)<<"Type"<< endl;
	cout << "\t\t" << "---------------------------------------------------------------------------" << endl;

	read_completed_orders_coffe();	                                 
	read_completed_orders_dessert();

}

void customer_menu() {

	do
	{
		cout << endl << endl;
		int choice;

		SetConsoleTextAttribute(hConsole, 2);//Changing texts color(2 is green)
		cout << "               --------------------------------------------------------------------------------------" << endl;
		cout << "                                               ~~ CUSTOMER  MENU  ~~                                 " << endl;
		cout << "               --------------------------------------------------------------------------------------" << endl;
		cout << "                | 1.Give Order | ~~ | 2.Add Balance Your Account | ~~ | 3.See Your Previous Orders |" << endl;

		cin_check_menu_choice(choice);

		if (choice == 1) {

			give_order();
		}

		else if (choice == 2) {
			int choice_add = 1;
			int temp = 1;
			balance_update(choice_add, temp);
		}

		else if (choice == EXIT) {

			return;
		}

		else {
			see_your_previous_orders();
		}

		SetConsoleTextAttribute(hConsole, 7); //Back to normal color
	} while (true);
	
	

}

#include <iostream>//input output lib
#define NOMINMAX //fix for some windows.h problems.if ı dont use this, program cant running.İf ı delete windows.h everything is good.But i need to use windows.h so ı use this method.
#include <Windows.h>//Needs for change color
#include <vector>//for store orders
#include <string>//use some methods like atoi(),substr(),find() vs.
#include <fstream>//needs for file process.
#include <iomanip>//Used to align text.(setw and left)
#include "coffe.h"
#include "dessert.h"
#include "mainclass.h"
#include "customers.h"
// FOR ADMINISTOR LOGİN = email:admin / password:admin
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//HANDLE a kind of pointer ım not sure exactly , ı use for change color the texts :D.GetStdHandle is interested input and output.
const int EXIT = 4; // global variable

extern void cin_check_int(int &choice);
extern int dessert_choice_number;
extern int coffe_choice_number;
extern int product_number_coffe;
extern int product_number_dessert;


void access_dessert_product_numbers(vector<Dessert>& product_list) {

	int product_number = 1;

	for (Dessert& newdessert : product_list) {
		
		if (dessert_choice_number == product_number) {

			product_number_dessert = product_number;
			break;
			
		}
		product_number++;
	}
}

void access_coffe_product_numbers(vector<Coffe>& product_list) {
	
	int product_number = 1;
	
	for (Coffe& newcoffe : product_list) {

		if (coffe_choice_number == product_number) {

			product_number_coffe = product_number;
			break;
			
		}
		product_number++;
	}	
}

void display_product_list_dessert(vector<Dessert>& product_list) { // display dessert menu.  

	SetConsoleTextAttribute(hConsole, 6);
	int product_number = 1;// ı create a counter for numbering.

	cout << "                                        ~~  DESSERT  ORDER   MENU  ~~                     " << endl;
	cout << "\t\t" << "--------------------------------------------------------------------------------" << endl;
	cout << "\t\t" << left << setw(20) << "Category" <<"  " << left << setw(20) << "Name" << left << setw(20) << "Price($)" << left << setw(20) << "Type" << endl;
	cout << "\t\t" << "--------------------------------------------------------------------------------" << endl;
	for (Dessert& newdessert : product_list) {

     cout << "\t\t" << product_number << "." << left << setw(20) << newdessert.get_category()
		    <<left << setw(20) << newdessert.get_name()
			<<left<< setw(20) << newdessert.get_price()
			<<left<< setw(20) << newdessert.get_type() << endl;
	 cout << "\t\t" << "--------------------------------------------------------------------------------" << endl;

	 product_number++;
	 
	}
	SetConsoleTextAttribute(hConsole, 7);
}


void display_product_list_coffe(vector<Coffe>& product_list) {//display coffe menu

	SetConsoleTextAttribute(hConsole, 6);
	int product_number = 1;// ı create a counter for numbering.

	cout << "                                               ~~  COFFE  ORDER   MENU  ~~                                 " << endl;
		cout << "\t\t" << "-------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t" << left << setw(20) << "Category" <<"  "<< left << setw(20) << "Name" << left << setw(20) << "Price(Big)$" << left << setw(20) << "Price(Medium)$" << left << setw(20) << "Price(Small)$" << endl;
		cout << "\t\t" << "-------------------------------------------------------------------------------------------------" << endl;
		for (Coffe& newcoffe : product_list) {//Copies or references product_list vector's class objects into newcoffe class object 

	           cout <<"\t\t"<<product_number<<"."<< left << setw(20) << newcoffe.get_category()
				<< left << setw(20) << newcoffe.get_name()
				<<left<< setw(20) << newcoffe.get_price_big_size()
				<<left<< setw(20) << newcoffe.get_price_medium_size()
				<<left<< setw(20) << newcoffe.get_price_small_size() << endl;
             cout << "\t\t" << "-------------------------------------------------------------------------------------------------" << endl;
		   product_number++;// Counter is increasing every loop.
		}
		SetConsoleTextAttribute(hConsole, 7);
}

vector<Dessert> read_text_file_dessert() {

	vector<Dessert>product_list;
	ifstream new_products_read("newproductsdessert.txt");
	string line;

	while (getline(new_products_read, line)) {
		
		string category = line;
		string name, price, type;

		getline(new_products_read, name);
		getline(new_products_read, price);
		getline(new_products_read, type);

		int price_int = stoi(price);

		Dessert product(category, name, price_int, type);
		product_list.push_back(product);

		getline(new_products_read, line);
	}
	
	return product_list;
}

vector<Coffe> read_text_file_coffe() { // this function returns a vector formed from the coffee class 

	vector<Coffe>product_list;
	ifstream new_products_read("newproductscoffe.txt");
	string line;

	while (getline(new_products_read, line)) { // Reading text file line by line and transfering string variable.
		
		string category = line;//first line transfering category variable
		string name, price_big, price_medium, price_small;

		getline(new_products_read, name);//second line transfering name variable
		getline(new_products_read, price_big);//thirth line transfering price_big variable
		getline(new_products_read, price_medium);//fourth line transfering price_medium variable 
		getline(new_products_read, price_small);//fifth line transfering price_small variable

		int price_big_int = stoi(price_big); // transforming string price_big variable to float variable.
		int price_medium_int = stoi(price_medium);// transforming string price_medium variable to float variable.
		int price_small_int = stoi(price_small);// transforming string price_small variable to float variable.

		Coffe product(category, name, price_big_int, price_medium_int, price_small_int);
		product_list.push_back(product);//Adding coffe class objects(product) into vector.

		getline(new_products_read, line);//Every 5 lines read one more line to launch a new product
	}

	return product_list;//returns product_list vector for use this vector another places.
}
void send_product_numbers_dessert() {

	vector<Dessert> product_list = read_text_file_dessert();
	access_dessert_product_numbers(product_list);
	
}
void send_product_numbers_coffe() {

	vector<Coffe> product_list = read_text_file_coffe();
	access_coffe_product_numbers(product_list);
	
}

void send_to_dessert_menu() {

	vector<Dessert> product_list = read_text_file_dessert();
	display_product_list_dessert(product_list);
}


void send_to_coffe_menu() {//i create this function because other functions taking parametres. 

	vector<Coffe> product_list = read_text_file_coffe(); // The read_text file function transfers the return value to a vector.
	display_product_list_coffe(product_list);


}

void write_to_text_file_dessert(string &category, string &name,int &price,string &type) {
	
	ofstream new_products_write;
	new_products_write.open("newproductsdessert.txt", ios::out | ios::binary | ios::app);

	if (!new_products_write.is_open()) { 

		cout << "File cant open !!! ";
	}
	else
	{
		
		new_products_write << category << endl << name << endl << price << endl << type << endl << endl;//add new dessert product the text file.
		
	}
}

void write_to_text_file_coffe(string &category,string &name,int &price_big,int &price_medium,int &price_small) {

	ofstream new_products_write;
	new_products_write.open("newproductscoffe.txt", ios::out | ios::binary | ios::app);

	if (!new_products_write.is_open()) { //Checks the text file is opened.

		cout << "File cant open !!! ";
	}
	else
	{
		
		new_products_write << category << endl << name << endl << price_big << endl << price_medium << endl << price_small << endl << endl;//add new coffe product the text file.
		
	}
}

void add_new_product() {

	string category, name, type;
	int price, price_big, price_medium, price_small;
	bool choice;

	cout << "  " << "You want add coffe or dessert to order menu ?"<<endl<<endl;
	cout << "  " << "0.Coffe" << "\t\t" << "1.Dessert" << endl<<endl;

	while (true) {

		cout << "  " << "Your choice : ";
		cin >> choice;
		cout << endl;

		if (cin.fail()) {

			cout << "  " << "Please only enter 0 or 1!!!(not string or char)" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		else {

			break;
		}
	}
	if (choice == 0) {

		cout <<"  "<< ">> Available coffe order menu <<" << endl<<endl;
		send_to_coffe_menu();
	}
	else{

		cout << "  " << ">> Available dessert order menu <<" << endl<<endl;
		send_to_dessert_menu();
	}
	
	SetConsoleTextAttribute(hConsole, 4);
	cout << endl;
	cout <<"\t\t"<< ">> ADD PRODUCT <<"<<endl;
	cout <<"\t\t"<< "------------------------------------"<<endl;
	cout <<"\t\t"<< "Category : ";  cin.ignore();  getline(cin, category);
	cout <<"\t\t"<< "------------------------------------" << endl;
	cout <<"\t\t"<< "Name : ";      getline(cin, name);
	cout <<"\t\t"<< "------------------------------------" << endl;

	if(choice == 0){

		cout << "\t\t" << "Price For Big Size    : ";     cin_check_int(price_big);//cin_check_int -> input control for integer.
		cout << "\t\t" << "------------------------------------"<<endl;
		cout << "\t\t" << "Price For Medium Size : ";     cin_check_int(price_medium);
		cout << "\t\t" << "------------------------------------"<<endl;
		cout << "\t\t" << "Price For Small Size  : ";     cin_check_int(price_small);
		cout << "\t\t" << "------------------------------------" << endl << endl;
		
		ifstream check_coffe_menu_list("newproductscoffe.txt");//
		string line;
		bool check_coffe = true;

	    while(getline(check_coffe_menu_list,line)) {//check if administor add same product to coffe menu

			if (name == line){

				cout <<"  "<< "The coffe product you try to added already exist in coffe order menu !!! Please try to add another coffe product !!!";
				check_coffe = false;
				
			}
		}

		if (check_coffe == true){

			cout << "  " << "Your product is added menu succesfly !!!" << endl;
			write_to_text_file_coffe(category, name, price_big, price_medium, price_small);
			check_coffe_menu_list.close();
		}
		
	}

	else{

		cout << "\t\t" << "Price : ";     cin_check_int(price);
		cout << "\t\t" << "------------------------------------"<<endl;
		cout << "\t\t" << "Type : ";     cin.ignore();    getline(cin, type);
		cout << "\t\t" << "------------------------------------" << endl<<endl;

		ifstream check_dessert_menu_list("newproductsdessert.txt");
		string line;
		bool check_dessert = true;
		
		while (getline(check_dessert_menu_list, line)) {//check if administor add same product to dessert menu
			
			if (name == line){

				cout <<"  "<< "The dessert product you try to added already exist in dessert order menu !!! Please try to add another dessert product !!!";
				check_dessert = false;
			}
		}

		if (check_dessert == true)
		{
			cout << "  " << "Your product is added menu succesfly !!!" << endl << endl;
			write_to_text_file_dessert(category, name, price, type);
			check_dessert_menu_list.close();
		}
	}
	
	SetConsoleTextAttribute(hConsole, 7);
}

void see_customers() {

	string c_name, c_last_name, c_email, c_phone_number, c_password;
	int c_balance;
	ifstream customers_accs("registercustomer.txt");//open text file for read 
	string accs;

	cout << "\t\t" << ">> CUSTOMERS <<" << endl;
	cout << "\t\t" << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t"<<left <<setw(30) << "NAME" << left << setw(30) << "LAST NAME" << left << setw(30) << "EMAIL" << left << setw(30) << "PHONE NUMBER" << left << setw(30) << "PASSWORD" << left << setw(30) << "BALANCE"<< endl;
	cout << "\t\t" << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	while (getline(customers_accs, accs)) {//reading the text file line by line and storing it in a string variable named accs
		
		if (accs.find("NAME : ") == 0) {  //Searching for the written characters in the text file(find method) and, 
			
			c_name = accs.substr(7);      //if found, saving the characters after those characters(substr method)into a variable.
		}
		else if (accs.find("LAST NAME : ") == 0) { 
			
			c_last_name = accs.substr(12);
		}
		else if (accs.find("EMAIL : ") == 0){
			
			c_email = accs.substr(8);
		}
		else if (accs.find("PHONE NUMBER : ") == 0) {

			c_phone_number = accs.substr(15);
		}
		else if (accs.find("PASSWORD : ") == 0)
		{
			c_password = accs.substr(11);
		}
		else if (accs.find("BALANCE : ") == 0){
			
			c_balance = atoi(accs.substr(10).c_str());//Balance variable is a int so I transformed  string to int with atoi() method.
			cout << "\t\t" << left << setw(30) << c_name << left << setw(30) << c_last_name << left << setw(30) << c_email << left << setw(30) << c_phone_number << left << setw(30) << c_password<<left << setw(30) << c_balance << endl;
			cout << "\t\t" << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		}		
	}
}

void see_all_orders(){


	cout << "                                                               ~~  ALL ORDERS  ~~                                            " << endl;
	cout << "\t\t" << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t" << left << setw(20) <<"Account(EMAIL)"<<left<<setw(20)<< "Category" << left << setw(20) << "Name" << left << setw(20) << "Order Cost($)" << left << setw(20) << "Type" <<left<<setw(20)<<"Situation"<<endl;
	cout << "\t\t" << "-------------------------------------------------------------------------------------------------------------" << endl;

	ifstream read_coffe_orders("coffeorders.txt");
	string line;
	int total_coffe_order = 0;

	while (getline(read_coffe_orders, line)) {
		total_coffe_order++;
		if (line.find("EMAIL : ") == 0) {

			string email = line.substr(8);
			string category, name, price;

			getline(read_coffe_orders, category);
			getline(read_coffe_orders, name);
			getline(read_coffe_orders, price);
			getline(read_coffe_orders, line);

			cout << "\t\t" << left << setw(20) << email << left << setw(20) << category << left << setw(20) << name << left << setw(20) << price << left << setw(20) << "XXXX" << left << setw(20) << "Completed" << endl;
			cout << "\t\t" << "-------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	read_coffe_orders.close();

	ifstream read_dessert_orders("dessertorders.txt");
	int total_dessert_order = 0;
	
	while (getline(read_dessert_orders, line)) {
		total_dessert_order++;
		if (line.find("EMAIL : ") == 0) {

			string email = line.substr(8);
			string category, name, price, type;

			getline(read_dessert_orders, category);
			getline(read_dessert_orders, name);
			getline(read_dessert_orders, price);
			getline(read_dessert_orders, type);

			getline(read_dessert_orders, line);
			
			cout << "\t\t" << left << setw(20) << email << left << setw(20) << category << left << setw(20) << name << left << setw(20) << price << left << setw(20) << type << left << setw(20) << "Completed" << endl;
			cout << "\t\t" << "-------------------------------------------------------------------------------------------------------------" << endl;
		}

	}
	read_dessert_orders.close();

	cout << endl;	
	cout << "\t\t" << ">> Total Coffe Order = " << total_coffe_order<<" <<" << endl << endl;
	cout << "\t\t" << ">> Total Dessert Order = " << total_dessert_order<<" <<" << endl << endl;
	cout << "\t\t" << ">> Total Orders = " << total_coffe_order + total_dessert_order<<" <<"<< endl;
	
}

void administor_menu() {
	do
	{
		cout << endl << endl;
		int choice;

		SetConsoleTextAttribute(hConsole, 4);//Changing texts color(4 is red)
		cout << endl;
		cout << "                                               ~~ ADMINISTOR   MENU  ~~                              " << endl;
		cout << "               --------------------------------------------------------------------------------------" << endl;
		cout << "                | 1.See All Orders |  ~~  | 2.Add New Product |  ~~  | 3.See All Customers Accounts |" << endl;
		cout << endl << endl;

		cin_check_menu_choice(choice);

		if (choice == 1) {
			see_all_orders();
		}

		else if (choice == 2) {

			add_new_product();
		}

		else if (choice == EXIT) {

			return;
		}

		else {

			see_customers();
		}

		SetConsoleTextAttribute(hConsole, 7);//Back to normal color
		
	} while (true);
	
		
}

void administor_login() {

	string admin_email = "admin";//İf you want login as administor use this email and password.
	string admin_password = "admin";
	string a_email,a_password;
	bool choice = true;

	while(choice){

	SetConsoleTextAttribute(hConsole, 3);
	cout << endl<<endl;
	cout << "               >> LOGIN AS ADMINISTOR <<                      " << endl;
	cout << "               -----------------------------------------------" << endl;
	cout << "                   EMAIL    : ";       cin.ignore();  getline(cin, a_email);
	cout << "               -----------------------------------------------" << endl;
	cout << "                   PASSWORD : ";                   getline(cin, a_password);
	cout << "               -----------------------------------------------" << endl << endl;

	if (a_email != admin_email || a_password != admin_password)
	{
		cout << "  " << "You cant login !!! Email or password incorrect !!!" << endl;
		cin_check_bool(choice);//customer.h input control function
	}

	else if(a_email != admin_email && a_password != admin_password)
	{
		cout << "  " << "You cant login !!! Email or password incorrect !!!" << endl;
		cin_check_bool(choice);
	}

	else
	{
		cout << "  " << "You are login succesfuly!!!"<<endl;
		administor_menu();
		choice = false; // changing choice to false for ending while loop.
		SetConsoleTextAttribute(hConsole, 7);
	}
	
	}	
}

void login_menu() {
     	
	cout << endl<<endl;
	cout << "                                               ~~  LOGIN   MENU  ~~                                  " << endl;
	cout << "               --------------------------------------------------------------------------------------" << endl;
	cout << "               | 1.Login As CUSTOMER |  ~~  | 2.Login As ADMINISTOR |  ~~  | 3.Register As CUSTOMER |" << endl << endl;
		
}

int main()
{	
	do
	{
		SetConsoleTextAttribute(hConsole, 3);

		login_menu();
		int choice;
		cin_check_menu_choice(choice);
		SetConsoleTextAttribute(hConsole, 7);//Back to normal color

		if (choice == 1) {
			customer_login();
		}
		else if (choice == 2) {
			administor_login();
		}
		else if (choice == EXIT) {
			return 0;
		}
		else {
			customer_register();
		}
		
	} while (true);

}



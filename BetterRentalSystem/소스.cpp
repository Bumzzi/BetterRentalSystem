#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <time.h>
using namespace std;

void customerData();
int carCount();
int custCount();
int rate(int, int);
void newCustData();
/*void carData();
void admin();
void user();*/
void menu();/*
void newCarData();
void delCar();*/
void displayCar();
void existingCust();
int countUser();
void readUserPass();
void availCar();
int countAvail();
void dispAvailCar();
/*void resetAvail();
void showCarData();*/

class car {
public:
	char plate_num[10];
	char brand[20];
	char model[20];
	float capacity;
	char color[20];
	float rate_per_hour;
	float rate_per_half;
	float rate_per_day;
	char transmission[6];

};

class customer {
public:
	int id;
	char name[100];
	char phone[12];
	char ic[15];
	char address[1500];
};

class pass {
public:
	int ID;
	char passWord[20];

};

pass userPass[1000];
car rent[1000];
customer cust[1000];
car avail[1000];

/*const string currentDateTime() {
	time_t;
	now = time(0);
}*/
void readUserPass() {
	ifstream ifs;
	ifs.open("UserPass.txt");
	int i;
	while (!ifs.eof()) {
		ifs >> userPass[i].ID;
		ifs.ignore();
		ifs.getline(userPass[i].passWord, 20);
		i++;
	}
	ifs.close();
}

int rate(int hour, int j) {
	int hour_24, hour_12, hour_1;
	int total, total_24, total_12, total_1;
	hour_24 = hour / 24;
	hour_12 = (hour - hour_24 * 24) / 12;
	hour_1 = (hour - hour_24 * 24 - hour_12 * 12) / 1;
	total_24 = hour_24 * rent[j].rate_per_day;
	total_12 = hour_12 * rent[j].rate_per_half;
	total_1 = hour_1 * rent[j].rate_per_hour;
	total = total_24 + total_12 + total_1;
	return total;
}

void customerData() {
	ifstream ifs;
	ifs.open("Customer.txt");
	int custNum = 0;
	
	while (!ifs.eof()) {
		ifs >> cust[custNum].id;
		ifs.ignore();
		ifs.getline(cust[custNum].name, 100, ';');
		ifs.getline(cust[custNum].phone, 15, ';');
		ifs.getline(cust[custNum].ic, 15, ';');
		ifs.getline(cust[custNum].address, 1500);
		custNum++;
	}
	ifs.close();
}

int carCount() {
	int numOfCar = 0;
	ifstream ifs("car rental.txt");
	string word;
	while (getline(ifs, word)) {
		if (!word.empty())
			numOfCar++;
	}
	ifs.close();
	return numOfCar;
}

int custCount() {
	int numOfCust = 0;
	ifstream ifs("Customer.txt");

	string word;
	while (getline(ifs, word)) {
		if (!word.empty())
			numOfCust++;
	}
	ifs.close();
	return numOfCust;
}

int countUser() {
	int numOfCust = 0;
	ifstream ifs("UserPass.txt");
	string word;
	while (getline(ifs, word)) {
		if (!word.empty())
			numOfCust++;
	}
	ifs.close();
	return numOfCust;
}

int countAvail() {
	int numOfCust = 0;
	ifstream ifs("available.txt");
	string word;
	while (getline(ifs, word)) {
		if (!word.empty())
			numOfCust++;
	}
	ifs.close();
	return numOfCust;
}

void displayCar() {
	cout << "\t  |  Plate Number\tBrand\t Model\tCapacity    Color   Rate Per Hour   Rate Per 12 Hour   Rate Per 24 Hour   Transmission" << endl;
	cout << "\t  |  =======================================================================================================================" << endl;
	for (int i = 0; i < carCount(); i++)
	{
		cout << "\t  |   " << rent[i].plate_num << "\t\t" << rent[i].brand << "\t " << rent[i].model << "\t   " << rent[i].capacity << "\t     "
			<< rent[i].color << "\t  " << rent[i].rate_per_hour << "\t\t    " << rent[i].rate_per_half << "\t\t    " << rent[i].rate_per_day
			<< "\t\t       " << rent[i].transmission << endl;
	}
}

void dispAvailCar() {
	cout << "\t  |  Plate Number\tBrand\t Model\tCapacity    Color   Rate Per Hour   Rate Per 12 Hour   Rate Per 24 Hour   Transmission" << endl;
	cout << "\t  |  =======================================================================================================================" << endl;
	for (int i = 0; i < countAvail(); i++)
	{
		cout << "\t  |   " << avail[i].plate_num << "\t\t" << avail[i].brand << "\t " << avail[i].model << "\t   " << avail[i].capacity << "\t     "
			<< avail[i].color << "\t  " << avail[i].rate_per_hour << "\t\t    " << avail[i].rate_per_half << "\t\t    " << avail[i].rate_per_day
			<< "\t\t       " << avail[i].transmission << endl;
	}
}

void existingCust() {
	int tempCust, hour, userID;
	char carSelect[10];
	tempCust = custCount() - 1;
	ofstream log;
	log.open("Log.txt", fstream::app);
	ofstream ofs;
	ofs.open("temp.txt");
	cout << "Please enter user ID : ";
	cin >> userID;

	for (int i = 0; i < custCount(); i++) {
		if (userID == cust[i].id) {
			cout << "\n\t  |\t\t\t\t\tWELCOME ";
			cout << cust[i].name;
			log << "\nNAME: " << cust[i].name;
			cout << "\t  |\tID ";
			cout << cust[i].id;
			cout << "\n\n";
			log << "\nPHONE: " << cust[i].phone;
			log << "\nIC: " << cust[i].ic;
		}
	}

	dispAvailCar();
	cout << "Please select car";
	cout << "\nPlate Number : ";
	cin >> ws;
	cin.getline(carSelect, 10);
	int x = countAvail();
	for (int i = 0; i < countAvail(); i++) {
		if (strcmp(carSelect, avail[i].plate_num) != 0) {
			ofs << avail[i].plate_num;
			ofs << " ";
			ofs << avail[i].brand;
			ofs << " ";
			ofs << avail[i].model;
			ofs << " ";
			ofs << avail[i].capacity;
			ofs << " ";
			ofs << avail[i].color;
			ofs << " ";
			ofs << avail[i].rate_per_hour;
			ofs << " ";
			ofs << avail[i].rate_per_half;
			ofs << " ";
			ofs << avail[i].rate_per_day;
			ofs << " ";
			ofs << avail[i].transmission;
			if (i != countAvail()) {
				ofs << endl;
			}
		}
	}
	ofs.close();

	remove("available.txt");
	rename("temp.txt", "available.txt");
	cout << "Hours of rent : ";
	cin >> hour;
	int j;
	for (int i = 0; i < carCount(); i++) {
		if (strcmp(carSelect, rent[i].plate_num) == 0) {
			j = i;
			log << "\nCAR: " << rent[i].plate_num;
			log << "\nBRAND: " << rent[i].brand;
			log << "\nMODEL: " << rent[i].model;
			log << "\nHOUR: " << hour;
			log << "\nPAYMENT: " << rate(hour, j);
		}
	}
	cout << "Price for " << hour << "hours of rent: RM";
	cout << rate(hour, j);
	log.close();

	system("CLS");
	menu();
}

void newCustData() {
	availCar();
	ofstream ofs, log;
	ofs.open("Customer.txt", fstream::app);
	log.open("Log.txt", fstream::app);
	ofs << endl;
	ofstream avialTemp;
	avialTemp.open("availtemp.txt");
	cout << "\n\n\n\n";
	cout << endl;

	cust[custCount()].id = custCount() + 1001;
	ofs << cust[custCount()].id;
	ofs << ";";

	cout << "Please enter the Data below : " << endl;
	cout << "Name : ";
	cin >> ws;
	cin.getline(cust[custCount()].name, 100);
	ofs << cust[custCount()].name << ";";
	log << "\nName: " << cust[custCount()].name;

	cout << "\t  |\t\t\t\t\t  Phone Number : ";
	cin.getline(cust[custCount()].phone, 15);
	ofs << cust[custCount()].phone;
	ofs << ";";
	log << "\nPHONE: " << cust[custCount()].phone;

	cout << "\t  |\t\t\t\t\t  IC : ";
	cin.getline(cust[custCount()].ic, 15);
	ofs << cust[custCount()].ic;
	ofs << ";";
	log << "\nIC: " << cust[custCount()].ic;

	cout << "\t  |\t\t\t\t\t  Address : ";
	cin.getline(cust[custCount()].address, 1500);
	ofs << cust[custCount()].address;

	ofs.close();

	system("CLS");

	int tempCust, hour;
	char carSelect[10];
	tempCust = custCount() - 1;

	cout << "\n\t  |\t\t\tWELCOME ";
	cout << cust[tempCust].name;
	cout << "\t  |\tID ";
	cout << cust[tempCust].id;
	cout << "\n\n";

	dispAvailCar();

	cout << "\n\n\t  |\tPlease select car";
	cout << "\n\t  |\tPlate Number : ";
	cin >> ws;
	cin.getline(carSelect, 10);

	int x = countAvail();

	for (int i = 0; i < countAvail(); i++) {
		if (strcmp(carSelect, avail[i].plate_num) != 0) {
			availTemp << avail[i].plate_num;
			availTemp << " ";
			availTemp << avail[i].brand;
			availTemp << " ";
			availTemp << avail[i].model;
			availTemp << " ";
			availTemp << avail[i].capacity;
			availTemp << " ";
			availTemp << avail[i].color;
			availTemp << " ";
			availTemp << avail[i].rate_per_hour;
			availTemp << " ";
			availTemp << avail[i].rate_per_half;
			availTemp << " ";
			availTemp << avail[i].rate_per_day;
			availTemp << " ";
			availTemp << avail[i].transmission;
			if (i != countAvail()) {
				availTemp << endl;
			}
		}
	}
}
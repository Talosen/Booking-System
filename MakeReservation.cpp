// MakeReservation.cpp
// AvailSeats-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h"

extern int inputAnInteger( int begin, int end );

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
   AvailSeatsDatabase &theSeatsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availSeatsDatabase( theSeatsDatabase )
{
}

void MakeReservation::execute()
{
   cout << "\nEnter the party size (1~6): ";

   int partySize;
   do cout << "? ";
   while( ( partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   Date date;
   inputDate( date, currentDate, partySize );

   int timeCode;
   inputTimeCode( timeCode, date, partySize );

   string name;
   cout << "\nEnter name: ";
   cin >> name;

   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   cout << "\nChoose a menu:\n";
   cout << "1. NT$ 1080\n";
   cout << "2. NT$ 1680\n";
   cout << "3. NT$ 2280\n";

   int menuCode;
   do cout << "? ";
   while( ( menuCode = inputAnInteger( 1, 3 ) ) == -1 );

   Reservation newReservation( phoneNumber, name, date, timeCode, partySize, menuCode );

   cout << endl;
   newReservation.displayReservationInfo();

   cout << "\nReservation Completed\n";

   reservationDatabase.pushBack( newReservation );

   availSeatsDatabase.decreaseAvailSeats( date, timeCode, partySize );
}

void MakeReservation::inputDate( Date &date, Date currentDate, int partySize )
{
	cout << "\nChoose a date\n";
	bool check[31] = {};
	for (int i = 1; i <= 30; i++) {
		if (availSeatsDatabase.availableTimes((currentDate + i), partySize)) {
			check[i] = 1;
			cout << i << ". " << (currentDate + i).getYear() << "/" << (currentDate + i).getMonth() << "/" << (currentDate + i).getDay();
			if (i % 4 != 0 && i != 30)
				cout << setw(10);
		}
		if (i % 4 == 0)
			cout << endl;
	}

	int choice;
	cout << endl;
	do cout << "? ";
	while (((choice = inputAnInteger(1, 30)) == -1)|| check[choice]==0);
	date= currentDate.operator+(choice);//設置預訂天數
	/*int newy = currentDate.getYear()+ choice, newm = currentDate.getMonth() + choice, mewd = currentDate.getDay() + choice;//錯誤用法
	date.setYear(newy);
	date.setMonth(newm);
	date.setDay(mewd);*/
	//date.setDate((currentDate.getYear() + choice), (currentDate.getMonth() + choice), (currentDate.getDay() + choice));//設置預訂天數

}

void MakeReservation::inputTimeCode( int &timeCode, Date date, int partySize )
{
	string time[5] = { "","11:30","13:30","17:45","19:45" };
	cout << "\nChoose a time:\n";
	bool check[5] = {};
	for (int i = 1; i <= 4; i++) {
		if (availSeatsDatabase.availableTimes(date, i, partySize)) {
			check[i] = 1;
			cout << i << ". " << time[i] << endl;
		}
	}
	int choice;
	do cout << "? ";
	while (((choice = inputAnInteger(1,4)) == -1) || check[choice]==0);
	timeCode = choice;
}
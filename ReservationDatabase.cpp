#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string phoneNumber )
{
	
	for (int i = 0; i < reservations.size(); i++) {
		if (reservations[i].getPhoneNumber() == phoneNumber)
			return true;
	}
	return false;
}

void ReservationDatabase::displayReservationInfo( string phoneNumber )
{
	vector< Reservation >::iterator it = reservations.begin();
	int i = 1;
	for (; it !=reservations.end(); it++) {
		if (it->getPhoneNumber() == phoneNumber) {
			cout << i << ". ";
			it->displayReservationInfo();
		}
		i++;
	}
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{
	fstream inFile("Reservations.dat", ios::in|ios::binary);
	if (!inFile) {
		cout << "file could not open!" << endl;
	}
	else {
		inFile.seekg(0, ios::end);
		int numLine = inFile.tellg() / sizeof(Reservation);
		inFile.seekg(0, ios::beg);
		reservations.resize(numLine);//­n°O±oresize
		for (int i = 0; i < numLine; i++) {
			inFile.read(reinterpret_cast<char*>(&reservations[i]), sizeof(reservations[i]));
		}
	}
}

void ReservationDatabase::storeReservations()
{
	fstream inFile("Reservations.dat", ios::out | ios::binary);
	if (!inFile) {
		cout << "file could not open!" << endl;
	}
	else {
		for (int i = 0; i < reservations.size(); i++) {
			inFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(reservations[i]));
		}
	}
}
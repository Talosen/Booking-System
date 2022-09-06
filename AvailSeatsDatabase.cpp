#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailSeatsDatabase.h"

AvailSeatsDatabase::AvailSeatsDatabase()
{
	loadAvailSeats();
	Date currentDate;
	computeCurrentDate(currentDate);
	int pos = 0;
	vector< AvailSeats >temp;
	for (int i = 0; i < availSeats.size(); i++) {//對的日期存起來，不要的日期忽略
		if (currentDate < availSeats[i].getDate()) {
			temp.push_back(availSeats[i]);
		}
	}
	for (int i = 0; i < temp.size(); i++) {//放對的日期從0開始
		availSeats[i] = temp[i];
	}
	int numAvailSeats[5] = { 0,20,20,20,20 };//設availablenum=20

	for (int i = temp.size() + 1; i <= 30; i++) {//加1是為了日期，相對的i<=30
		AvailSeats temp2(currentDate + i, numAvailSeats);
		availSeats.push_back(temp2);
	}

}

AvailSeatsDatabase::~AvailSeatsDatabase()
{
	storeAvailSeats();
}

void AvailSeatsDatabase::decreaseAvailSeats(Date date, int timeCode, int requiredSeats)
{
	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	it->setNumAvailSeats(timeCode, (it->getNumAvailSeats(timeCode) - requiredSeats));
}

bool AvailSeatsDatabase::availableTimes(Date date, int requiredSeats)
{
	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	for (int i = 1; i <= 4; i++) {
		if (it->getNumAvailSeats(i) >= requiredSeats)
			return true;
	}
	return false;
}

bool AvailSeatsDatabase::availableTimes(Date date, int timeCode, int requiredSeats)
{

	vector< AvailSeats >::iterator it = searchAvailSeats(date);
	if (it->getNumAvailSeats(timeCode) >= requiredSeats)
		return true;
	else
		return false;
}

vector< AvailSeats >::iterator AvailSeatsDatabase::searchAvailSeats(Date date)
{

	vector< AvailSeats >::iterator it = availSeats.begin();
	for (; it != availSeats.end(); it++) {
		if (it->getDate() == date)
			return it;
	}
	return availSeats.end();
	
}

void AvailSeatsDatabase::loadAvailSeats()
{
	fstream inFile("AvailSeats.dat", ios::in | ios::binary);
	if (!inFile) {
		cout << "file could not open!" << endl;
	}
	else {
		inFile.seekg(0, ios::end);
		int numLine = inFile.tellg() / sizeof(AvailSeats);
		inFile.seekg(0, ios::beg);
		availSeats.resize(numLine);////要記得resize
		for (int i = 0; i < numLine; i++) {
			inFile.read(reinterpret_cast<char*>(&availSeats[i]), sizeof(availSeats[i]));
		}
	}
}

void AvailSeatsDatabase::storeAvailSeats()
{
	fstream oFile("AvailSeats.dat", ios::out | ios::binary);
	if (!oFile) {
		cout << "file could not open!" << endl;
	}
	else {
		for (int i = 0; i < availSeats.size(); i++) {
			oFile.write(reinterpret_cast<const char*>(&availSeats[i]), sizeof(availSeats[i]));
		}
	}
}
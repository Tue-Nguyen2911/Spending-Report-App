#include <iostream>
#include <cstring>
#include "Report.h"
using namespace std;
using namespace TueNg;
int main()
{
	int option;
	char filename[10]{};
	cout << "Which month do you want to report your spendings? (1-12): ";
	bool out = false;
	while (!out)
	{
		cin >> option;
		cin.clear();
		cin.ignore(100, '\n');
		switch (option)
		{
		case 1:
			strcpy(filename, "Jan.csv");
			out = true;
			break;
		case 2:
			strcpy(filename, "Feb.csv");
			out = true;
			break;
		case 3:
			strcpy(filename, "March.csv");
			out = true;
			break;
		case 4:
			strcpy(filename, "April.csv");
			out = true;
			break;
		case 5:
			strcpy(filename, "May.csv");
			out = true;
			break;
		case 6:
			strcpy(filename, "June.csv");
			out = true;
			break;
		case 7:
			strcpy(filename, "July.csv");
			out = true;
			break;
		case 8:
			strcpy(filename, "August.csv");
			out = true;
			break;
		case 9:
			strcpy(filename, "Sep.csv");
			out = true;
			break;
		case 10:
			strcpy(filename, "Oct.csv");
			out = true;
			break;
		case 11:
			strcpy(filename, "Nov.csv");
			out = true;
			break;
		case 12:
			strcpy(filename, "Dec.csv");
			out = true;
			break;
		default:
			cout << "Invalid integer! Try again: ";
			out = false;
			break;
		}
	}
	Report aReport(filename, option);
	aReport.run();
	return 0;
}
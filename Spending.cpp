#include <iostream>
#include <cstring>
#include <iomanip>
#include "Spending.h"
using namespace std;
namespace TueNg
{
	Spending::Spending()
	{
		m_day = 0;
		m_desctiption = nullptr;
		m_expense = 0;
		m_month = 0;
		m_year = THE_YEAR;
	}
	Spending::Spending(int month)
	{
		m_day = 0;
		m_desctiption = nullptr;
		m_expense = 0;
		m_month = month;
		m_year = THE_YEAR;
	}
	Spending::Spending(const char* description, const double expense, int month, int day, int year)
	{
		if (strlen(description) < 2 || strlen(description) > MAX_DESC || description == nullptr)
			setDesc(description);
		else
			description = nullptr;
		if (DateValid(month, day))
		{
			m_month = month;
			m_year = year;
		}
		else
		{
			m_month = 0;
			m_year = 0;
		}
		if (expense > 0)
			m_expense = expense;
		else m_expense = 0;	
	}
	Spending::Spending(const Spending* aExp)
	{
		if (this != aExp)
		{
			m_day = aExp->m_day;
			m_month = aExp->m_month;
			m_year = aExp->m_year;
			m_expense = aExp->m_expense;
			m_desctiption = nullptr;
			setDesc(aExp->m_desctiption);
		}
		else
		{
			m_day = 0;
			m_desctiption = nullptr;
			m_expense = 0;
			m_month = 0;
			m_year = 0;
		}
	}
	Spending::~Spending()
	{
		delete[] m_desctiption;
		m_desctiption = nullptr;
	}
	istream& Spending::read(istream& is)
	{
		if (isCsv())
		{
			char temp[MAX_DESC];
			if (m_day == 0)
			{
				is >> m_day;
				is.ignore(2, ',');
			}
			is >> m_month;
			is.ignore(2, ',');
			is >> m_year;
			is.ignore(4, ',');
			is.getline(temp, MAX_DESC, ',');
			setDesc(temp);
			is >> m_expense;
			is.ignore(9, ',');
		}
		else
		{
			char temp[MAX_DESC]{'\0'};
			if (m_month == 0)
			{
				cout << "Enter month: ";
				is >> m_month;
				is.clear();
				is.ignore(100, '\n');
				while (!DateValid(m_month) || is.fail())
				{
					cout << "Wrong month, please enter again: ";
					is >> m_month;
					is.clear();
					is.ignore(100, '\n');
				}
			}
			cout << "Enter day: "; 
			is >> m_day; 
			is.clear();
			is.ignore(100,'\n');
			while (!DateValid(m_month, m_day) || is.fail())
			{
				cout << "Wrong day, please enter again: ";
				is >> m_day;
				is.clear();
				is.ignore(100, '\n');
			}
			cout << "What did you spend on: "; 
			is.getline(temp, MAX_DESC);
			setDesc(temp);

			cout << "How much did you spend: ";
			is >> m_expense;
			is.clear();
			is.ignore(100, '\n');
			while (m_expense == 0 || is.fail())
			{
				cout << "Invalid amount! Please enter again: ";
				is >> m_expense;
				is.clear();
				is.ignore(100, '\n');
			}

		}
		return is;
	}
	ostream& Spending::write(ostream& os) const
	{
		if (isCsv())
		{
			os << m_day << "," << m_month << "," << m_year << "," << m_desctiption << "," << m_expense << "," << endl;
		}
		else
		{
			os << setw(2) << right << m_day << "/" << setw(2) << right << m_month << "/" << m_year << " | " 
				<< setw(20) << left << m_desctiption << " | " 
				<< "$" << m_expense << endl;
		}
		return os;
	}
	/*void Spending::Copy(const Spending& aExp)
	{
		if (this != &aExp)
		{
			m_day = aExp.m_day;
			m_month = aExp.m_month;
			m_year = aExp.m_year;
			m_expense = aExp.m_expense;
			delete[] m_desctiption;
			setDesc(aExp.m_desctiption);
		}
	}*/
	
	bool Spending::DateValid(int month, int day) const
	{
		if (month < 1 || month > 12)
			return false;
		if (month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day > 0 && day <= 31)
				return true;
			else
				return false;
		}
		else if (month == 2)
		{
			if (day > 0 && day <= 29)
				return true;
			else
				return false;
		}
		else
		{
			if (day > 0 && day <= 30)
				return true;
			else
				return false;
		}
		return false;
	}
	void Spending::setDesc(const char* description)
	{
		if (description != nullptr && strlen(description) > 0)
		{
			delete[] m_desctiption;
			m_desctiption = new char[strlen(description) + 1];
			strcpy(m_desctiption, description);
		}
		else
			m_desctiption = nullptr;
	}
}
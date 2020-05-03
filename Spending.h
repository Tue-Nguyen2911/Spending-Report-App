#ifndef TUENG_SPENDING_H
#define TUENG_SPENDING_H
#include <iostream>
#include "ReadWritable.h"
namespace TueNg
{
	const int THE_YEAR = 2020;
	const int MAX_DESC = 40;
	class Spending : public ReadWritable
	{
		double m_expense; 
		int m_year;
		int m_month;
		int m_day;
		char* m_desctiption;
		bool DateValid(int month, int day = 1) const;
	public: 
		Spending();
		Spending(int month);
		Spending(const char* description, const double expense, int month, int day, int year = THE_YEAR);
		Spending(const Spending*) ;
		~Spending();
		Spending& operator=(const Spending&) = delete;
		void Copy(const Spending& aExp);
		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout) const;
	//	bool isEmpty() const;
		void setDesc(const char* description);
		void setDay(int day) { m_day = day; }
		double getExpense() const { return m_expense; }
	};
}
#endif 
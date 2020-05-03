#ifndef TUENG_REPORT_H
#define TUENG_REPORT_H
#include <iostream>
#include "Menu.h"
#include "ReadWritable.h"
#include "Spending.h"
namespace TueNg
{
	const int MAX_LIST = 10;
	class Report
	{
		int m_month;
		char* m_filename;
		Spending* m_spending_list[MAX_LIST];
		Menu* m_mainMenu;
		int m_num_of_spendings;
		bool isEmpty() const;
		void Add();
		void Total();
		void Delete();
		void List_Spending() const;
		bool Exit() const;
		bool LoadData();
		void SaveData() const;

		void seperator() const;
		void Title_display(const char* title) const;
		bool YesNo() const;
	public:
		Report();
		Report(const char* file_name, int month);
		~Report();
		int run(); 
	};
}

#endif // !TUENG_REPORT_H

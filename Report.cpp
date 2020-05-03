#include <iostream>
#include <cstring>
#include <Windows.h>
#include <fstream>
#include "Report.h"
using namespace std;
namespace TueNg
{
	Report::Report()
	{
		m_filename = nullptr;
		m_mainMenu = nullptr;
		m_num_of_spendings = 0;
		for (int i = 0; i < MAX_LIST; i++)
		{
			m_spending_list[i] = nullptr;
		}
	}
	Report::Report(const char* filename, int month)
	{
		m_num_of_spendings = 0;
		m_month = month;
		for (int i = 0; i < MAX_LIST; i++)
			m_spending_list[i] = nullptr;

		if (filename != nullptr || strlen(filename) > 0)
		{
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		}
		else
			m_filename = nullptr;
		if (LoadData())
		{
			m_mainMenu = new Menu("====== Spending Report App ======");
			m_mainMenu->add("List all expenditures");
			m_mainMenu->add("Total spending");
			m_mainMenu->add("Add an expenditure");
			m_mainMenu->add("Delete an expenditure");
			m_mainMenu->add("Exit");
		}
		else
		{
			cout << "Error in data" << endl;
			m_mainMenu = nullptr;
		}
	}
	Report::~Report()
	{
		SaveData();
		delete[] m_filename;
		m_filename = nullptr;
		delete m_mainMenu;
		m_mainMenu = nullptr;
		for (int i = 0; i < MAX_LIST; i++)
		{
			delete m_spending_list[i];
			m_spending_list[i] = nullptr;
		}
	}
	bool Report::isEmpty() const
	{
		return m_filename == nullptr;
	}
	void Report::Add()
	{
		seperator();
		Title_display("Adding an expenditure");
		if (m_num_of_spendings == MAX_LIST)
		{
			cout << "Max" << endl;
		}
		else
		{
			Spending* temp = new Spending(m_month);
			temp->setCsv(false);
			temp->read();
			for (int i = 0; i < MAX_LIST; i++)
			{
				if (m_spending_list[i] == nullptr)
				{
					m_spending_list[i] = temp;
					m_num_of_spendings++;
					cout << endl;
					cout << "Your spending: ";
					m_spending_list[i]->write();
					break;
				}
			}
		}
		seperator();
	}
	void Report::Delete()
	{
		if (m_num_of_spendings == 0)
		{
			seperator();
			Title_display("Deleting an expenditure");
			cout << "You have no expenditure to delete" << endl;
		}
		else
		{
			int index;
			List_Spending();
			Title_display("Deleting an expenditure");
			cout << "Which task do you want to delete(number according to the list): ";
			cin >> index;
			while (index > m_num_of_spendings || cin.fail() || index == 0)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid number, try again: ";
				cin >> index;
			}

			cout << endl << "Deleting an expenditure: ";
			m_spending_list[index - 1]->write();
			delete m_spending_list[index - 1];
			m_spending_list[index - 1] = nullptr;
			m_num_of_spendings--;
			for (int j = index - 1; j < m_num_of_spendings; j++)
			{
				if (j == m_num_of_spendings - 1)
				{
					Spending* temp = new Spending(m_spending_list[m_num_of_spendings]);
					m_spending_list[j] = temp;
					delete m_spending_list[m_num_of_spendings];
					m_spending_list[m_num_of_spendings] = nullptr;
				}
				else
					m_spending_list[j] = m_spending_list[j+1];
			}
		}
		seperator();
	}
	void Report::List_Spending() const
	{
		seperator();
		Title_display("Listing All Expenditures");
		if (m_num_of_spendings == 0)
			cout << "You have no expenditure" << endl;
		else
		{
			for (int i = 0; i < m_num_of_spendings; i++)
			{
				if (m_spending_list[i] != nullptr)
				{
					cout << i + 1 << ". ";
					m_spending_list[i]->setCsv(false);
					m_spending_list[i]->write();
				}
			}
		}
		seperator();
	}
	void Report::Total()
	{
		double sum = 0;
		for (int i = 0; i < m_num_of_spendings; i++)
		{
			if (m_spending_list[i] != nullptr)
			{
				sum += m_spending_list[i]->getExpense();
			}
		}
		seperator();
		Title_display("Total spending");
		cout << "Total spending is: $" << sum << endl;
		seperator();
	}
	bool Report::Exit() const
	{
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		if (YesNo())
		{
			cout << "Exiting program!" << endl;
			return true;
		}
		else
		{
			cout << "Aborted!" << endl;
			return false;
		}
	}
	bool Report::LoadData()
	{
		if (!isEmpty())
		{
			ifstream ifs(m_filename);
			Spending* aExp = nullptr;
			while (ifs)
			{
				int day = 0;
				ifs >> day;
				ifs.ignore(2, ',');
				if (day >= 1 || !ifs.fail())
				{
					aExp = new Spending(m_month);
					aExp->setCsv(true);
					aExp->setDay(day);
					aExp->read(ifs);
					if (!ifs.fail())
					{
						for (int i = 0; i < MAX_LIST; i++)
						{
							if (m_spending_list[i] == nullptr)
							{
								m_spending_list[i] = aExp;
								m_num_of_spendings++;
								break;
							}
						}
					}
					else
						return false;
					if (m_num_of_spendings == MAX_LIST) break;
				}
				else
					return true;
			}
		}
		return true;
	}
	void Report::SaveData() const
	{
		if (!isEmpty())
		{
			ofstream ofs(m_filename);
			if (ofs)
			{
				for (int i = 0; i < m_num_of_spendings; i++)
				{
					if (m_spending_list[i] != nullptr)
					{
						m_spending_list[i]->setCsv(true);
						m_spending_list[i]->write(ofs);
					}
				}
			}
		}
	}
	int Report::run()
	{
		int empty;
		if (!isEmpty())
		{
			empty = 0;

			bool out = false;
			while (!out)
			{
				int option = m_mainMenu->run();
				switch (option)
				{
				case 1:
					List_Spending();
					out = false;
					break;
				case 2:
					Total();
					out = false;
					break;
				case 3:
					Add();
					out = false;
					break;
				case 4:
					Delete();
					out = false;
					break;
				case 5:
					if (Exit())
					{
						out = true;
						break;
					}
					else
						out = false;
					break;
				default:
					break;
				}
				system("pause");
				system("CLS");
			}
		}
		else
			empty = 1;
		return empty;
	}

	void Report::seperator() const
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetConsoleTextAttribute(h, 2);
		cout << endl;
		cout << "-------------------------------------------" << endl << endl;
		SetConsoleTextAttribute(h, 15);
	}
	void Report::Title_display(const char* title) const
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetConsoleTextAttribute(h, 14);
		cout << title << endl;
		cout << "``````````````````" << endl;
		SetConsoleTextAttribute(h, 15);
	}
	bool Report::YesNo() const
	{
		{
			char option[10];
			bool response;
			bool correct = false;
			while (!correct)
			{
				cin >> option;
				cin.clear();
				cin.ignore(100, '\n');
				if (option[1] != '\0' || (option[0] != 'Y' && option[0] != 'y' && option[0] != 'N' && option[0] != 'n'))
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					correct = false;
				}
				else
					correct = true;
			}
			if (option[0] == 'Y' || option[0] == 'y')
			{
				response = true;
			}
			else
			{
				response = false;
			}
			return response;
		}
	}
}
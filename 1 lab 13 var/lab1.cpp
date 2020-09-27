#include <iostream>
#include "13.h"


Line* input(int& rm, int& bm) 
{
	int bar;
	int row;
	Line* lines = nullptr;	// ������������ ������ ����� �������
	const char* pr = "";
	do 
	{
		std::cout << pr << std::endl;
		pr = "Repeat pls";
		std::cout << "������ ���������� ����� --> ";
		if (getNum(row) < 0)	
		{
			return nullptr;
		}
	} 
	while (row < 1);
	const char* pr1 = "";
	do {
		std::cout << pr1 << std::endl;
		pr1 = "Repeat pls";
		std::cout << "������� ���������� �������� --> ";
		if (getNum(bar) < 0)
		{
			return nullptr;
		}
	} 
	while (bar < 1);
	// �������� ������ ��� ������ �������� �������� �����
	try 
	{
		lines = new Line[row];
	}
	catch (std::bad_alloc& ba) 
	{
		std::cout << "------- too many rows in matrix: " << ba.what() << std::endl;
		return nullptr;
	}
	for (int i = 0; i < row; ++i)
	{
		lines[i].root = nullptr;
		lines[i].num = 0;	// ����� ��������� �����
	}
	int k = 1, p = 1;
	while (k > 0)
	{
		std::cout << "� ����� ������ �� ������ �������� ��������� �������?(������� ������������� ���� ������ �����) --> ";
		if (getNum(k) < 0)
		{
			erase(lines, row);
			return nullptr;
		}
		else if (k == 0)
		{
			std::cout << "����� ������ ���������� � 1..." << std::endl;
		}
		else if (k > row)
		{
			std::cout << "��� ����� ������ ���� ������ ���� ����� " << row << std::endl;
		}
		else if (k > 0)
		{
			while (true) {
				std::cout << "������� ����� ������� ��� ����������(������� ������������� ���� ������ �����) --> ";
				if (getNum(p) < 0)
				{
					erase(lines, row);
					return nullptr;
				}
				if (p < 0)
				{
					break;
				}
				else if (p == 0)
				{
					std::cout << "����� ������ ���������� � 1..." << std::endl;
				}
				else if (p > bar)
				{
					std::cout << "��� ����� ������ ���� ������ ���� ����� " << bar << std::endl;
				}
				else if (p > 0)
				{
					std::cout << "������� ��������� ������� ��� " << k << " ������, " << p << " �������" << std::endl;
					int num;
					if (getNum(num) < 0)
					{
						erase(lines, row);
						return nullptr;
					}
					Item* tmp = new Item[1];	// ������� ������ �������� � ���� ��������� ��������
					tmp->j = p - 1;		// ���������� ������ ��������
					tmp->n = num;		// � ��� ��������
					tmp->next = nullptr;
					Item* last = nullptr;
					if (lines[k - 1].root == nullptr)
					{
						lines[k - 1].root = tmp;
					}
					else
					{
						last = getLast(lines[k - 1].root);
						last->next = tmp;
					}
				}
			}
		}
	}
	rm = row;
	bm = bar;
	return lines;
}


// ���������� ��������� �� ����� ��������� ���� � ������
Item* getLast(Item* last)
{
	if (last == nullptr)
	{
		return nullptr;
	}
	while (last->next) 
	{
		last = last->next;
	}
	return last;
}


void output(const char* msgs, Line* lines, int row, int bar) 
{
	std::cout << msgs << ":\n";
	for (int i = 0; i < row; ++i)
	{
		Item* tmp = lines[i].root;
		for (int j = 0; j < bar; ++j)
		{
			if (tmp && tmp->j == j)
			{
				std::cout << tmp->n << " ";
				if (tmp->next)
				{
					tmp = tmp->next;
				}
		}
			else
			{
				std::cout << "0" << " ";
			}
		}
		std::cout << std::endl;
	}
}


Line* erase(Line*& lines, int row) 
{
	for (int i = 0; i < row; ++i) 
	{
		Item* tmp = getLast(lines[i].root);
		delete[] tmp;
	}
	delete[] lines;
	return nullptr;
}


void solve(const char* msgs, Line* lines, int row, int bar)
{
	std::cout << msgs << std::endl;
	std::vector <int> vc(row);
	for (int i = 0; i < row; ++i)
	{
		int count = 0;
		Item* tmp = lines[i].root;
		if (tmp)
		{
			for (int j = 0; j < bar; ++j)
			{
				if (tmp->j == j)
				{
					++count;
					if (tmp->next)
					{
						tmp = tmp->next;
					}
				}
			}
		}
		vc[i] = count;
		std::cout << vc[i] << std::endl;
	}
}
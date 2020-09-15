#include <iostream>
#include "header.h"


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
		std::cout << "Enter number of rows: --> ";
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
		std::cout << "Enter number of bars: --> ";
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
		std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
		for (int j = 0; j < bar; ++j) 
		{
			int k;
			if (getNum(k) < 0) 
			{
				erase(lines, i + 1);
				return nullptr;
			}
			else if (k > 0) 
			{
				lines->num += 1;
				Item* tmp = new Item[1];	// ������� ������ �������� � ���� ��������� ��������
				tmp->j = j;		// ���������� ������ ��������
				tmp->n = k;		// � ��� ��������
				tmp->next = nullptr;
				Item* last = nullptr;
				if (lines[i].root == nullptr) 
				{
					lines[i].root = tmp;
				}
				else
				{
					last = getLast(lines[i].root);
					last->next = tmp;
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
			if (tmp)
			{
				if (tmp->j == j) 
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
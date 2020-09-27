#include <iostream>
#include "13.h"


Line* input(int& rm, int& bm) 
{
	int bar;
	int row;
	Line* lines = nullptr;	// Динамический массив строк матрицы
	const char* pr = "";
	do 
	{
		std::cout << pr << std::endl;
		pr = "Repeat pls";
		std::cout << "Ведите количество строк --> ";
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
		std::cout << "Введите количество столбцов --> ";
		if (getNum(bar) < 0)
		{
			return nullptr;
		}
	} 
	while (bar < 1);
	// Выделяем память под массив структур размером строк
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
		lines[i].num = 0;	// Число ненулевых ячеек
	}
	int k = 1, p = 1;
	while (k > 0)
	{
		std::cout << "В какую строку вы хотите добавить ненулевой элемент?(введите отрицательный если хотите выйти) --> ";
		if (getNum(k) < 0)
		{
			erase(lines, row);
			return nullptr;
		}
		else if (k == 0)
		{
			std::cout << "Номер строки начинается с 1..." << std::endl;
		}
		else if (k > row)
		{
			std::cout << "Ваш номер должен быть меньше либо равен " << row << std::endl;
		}
		else if (k > 0)
		{
			while (true) {
				std::cout << "Введите номер столбца для добваления(введите отрицательный если хотите выйти) --> ";
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
					std::cout << "Номер должен начинаться с 1..." << std::endl;
				}
				else if (p > bar)
				{
					std::cout << "Ваш номер должен быть меньше либо равен " << bar << std::endl;
				}
				else if (p > 0)
				{
					std::cout << "Введите ненулевой элемент для " << k << " строки, " << p << " столбца" << std::endl;
					int num;
					if (getNum(num) < 0)
					{
						erase(lines, row);
						return nullptr;
					}
					Item* tmp = new Item[1];	// Создаем список хранящий в себе ненулевые элементы
					tmp->j = p - 1;		// Запоминаем индекс такового
					tmp->n = num;		// И его значение
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


// Нахождение указателя на самый последний узел в списке
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
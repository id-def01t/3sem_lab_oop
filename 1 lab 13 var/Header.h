#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>


struct Item {	// Список хранящий в себе ненулевые элементы матрицы
	int n;		// Ненулевое число в ячейке
	int j;		// Номер столбца (с учетом элементов равных нулю)
	struct Item* next;	// Указатель на следующий элемент
};

struct Line {	// Структура для задания строки матрицы
	int num;	// Число ненулевых элементов в строке
	Item* root;	// Указатель на начало списка 
};

template <class T>
int getNum(T& a) {
	std::cin >> a;
	if (!std::cin.good())	
		return -1;
	return 1;
}


Line* input(int&, int&);								
void output(const char*, Line*, int, int);	
Line* erase(Line*&, int);									
Item* getLast(Item*);
void solve(const char*, Line*, int, int);

#endif 
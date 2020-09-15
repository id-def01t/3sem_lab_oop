#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>


struct Item {	// ������ �������� � ���� ��������� �������� �������
	int n;		// ��������� ����� � ������
	int j;		// ����� ������� (� ������ ��������� ������ ����)
	struct Item* next;	// ��������� �� ��������� �������
};

struct Line {	// ��������� ��� ������� ������ �������
	int num;	// ����� ��������� ��������� � ������
	Item* root;	// ��������� �� ������ ������ 
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
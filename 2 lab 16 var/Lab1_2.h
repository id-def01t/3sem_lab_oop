#pragma once
#ifndef _LAB1_2_
#define _LAB1_2_

#include <iostream>
#include "Catenary.h"

extern const int NMsgs;


namespace Lab1_2 
{

	// ������ ������� ����� ����� (1 � ������ �������, � 0 ��� ������)
	template <class T>
	int getNum(T& a)
	{
		int rc = 0;
		std::cin >> a;
		if (!std::cin.good())
			rc = 1;				// ���������� ������ �����
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return rc;
	};


	// ��������� ��������� �������
	Class::Catenary Input();					// ������ ������������� ��������� ������ "������ �����"
	int dialog(const char* msgs[], int N);		// ����������� �������
	int D_GetStatus(const Class::Catenary&);	// ��������� ���������� � ��������� ������ "������ �����": ����-�� ������� � ������
	// ���������� ������� ������ � ������� "������ �����"
	int D_SetVertex(Class::Catenary&);			// "1. ������ ����� ���������� �������"
	int D_SetBorders(Class::Catenary&);			// "2. ������ ����� ������� ����"
	int D_GetOrdinate(Class::Catenary&);		// "3. ������� �������� ������ ����� �� �������� ��������"
	int D_GetLength(Class::Catenary&);			// "4. ������� ����� ���� ������ ����� �� �� �������� �� ��� �������"
	int D_GetRadius(Class::Catenary&);			// "5. ������� ������ �������� ������ ����� ������������ ���������� �� ��� �������"
	int D_GetCenter(Class::Catenary&);			// "6. ������� ���������� ������ �������� ������ ����� � ���������� ������� ��������� ������������ ���������� �� ��� �������"
	int D_GetArea(Class::Catenary&);			// "7. ������� ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� ������� (����� �������� = �������� ������� ������)"

}

#endif




#include "Lab1_2.h"
#include <iomanip>


const char* msgs[] = { "0. �����",
"1. ������ ����� ���������� �������",
"2. ������ ����� ������� ����",
"3. ������� �������� ������ ����� �� �������� ��������",
"4. ������� ����� ���� ������ ����� �� �� �������� �� ��� �������",
"5. ������� ������ �������� ������ ����� ������������ ���������� �� ��� �������",
"6. ������� ���������� ������ �������� ������ ����� � ���������� ������� ��������� ������������ ���������� �� ��� �������",
"7. ������� ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� ������� (����� �������� = �������� ������� ������)" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


namespace Lab1_2 
{
	void input_Type(Type& p)
	{
		while (Lab1_2::getNum(p))
		{
			std::cout << "����������, ������� ���������� �����: --> ";
		}
	}

	// ������ ������������� �������� ������
	Class::Catenary Input() 
	{
		Class::Point p;
		std::cout << "������� �������� ������� ����: --> ";
		input_Type(p.x);
		while (1) 
		{
			std::cout << "������� �������� ������� ���� (������ ������������): --> ";
			input_Type(p.y);
			try 
			{
				Class::Catenary line(p, 0, 0);
				Type x1, x2;
				std::cout << "������� �������� ������ ������� ����: --> ";
				input_Type(x1);
				std::cout << "������� �������� ������ ������� ����: --> ";
				input_Type(x2);
				line.setL(x1, x2);
				return line;
			}
			catch (const std::exception& ex) 
			{
				std::cout << ex.what() << std::endl;
			}
		}
	}


	// ����� ������ ������������
	int dialog(const char* msgs[], int N) 
	{
		const char* errmsgs = "";
		int rc, i;
		do
		{
			puts(errmsgs);
			errmsgs = "������! ��������� ����!";
			for (i = 0; i < N; ++i)					// ����� ������ �����������
			{
				puts(msgs[i]);
			}
			printf("��������: --> ");
		} while (getNum(rc) < 0 || rc >= N);
		return rc;
	}


	// ��������� ���������� � ��������� ������
	int D_GetStatus(const Class::Catenary& line) 
	{
		std::cout << "-----------------------------------------------\n������� ��������� ������: \n";
		std::cout << "���������� �������: " << std::fixed << std::setprecision(2) << line.getP().x << "\/" << std::fixed << std::setprecision(2) << line.getP().y << ";\n";
		std::cout << "���������� ����� ��������� �����: " << std::fixed << std::setprecision(2) << line.getL_limit().x << "\/" << std::fixed << std::setprecision(2) << line.getL_limit().y << ";\n";
		std::cout << "���������� ������ ��������� �����: " << std::fixed << std::setprecision(2) << line.getR_limit().x << "\/" << std::fixed << std::setprecision(2) << line.getR_limit().y << ";\n-----------------------------------------------";
		return 1;
	}

	// 1. ������ ����� ���������� �������
	int D_SetVertex(Class::Catenary& line) 
	{
		Class::Point p;
		std::cout << "������� �������� ������� ����: --> ";
		input_Type(p.x);
		while (1) 
		{
			std::cout << "������� �������� ������� ���� (������ ������������): --> ";
			input_Type(p.y);
			try 
			{
				line.setP(p);
				std::cout << "������� ���� ������� ��������\n";
				return 1;
			}
			catch (const std::exception& ex) 
			{
				std::cout << ex.what() << std::endl;
			}
		}
	}

	// 2. ������ ����� ������� ����
	int D_SetBorders(Class::Catenary& line) 
	{
		Type x1, x2;
		std::cout << "������� �������� ������ ������� ����: --> ";
		input_Type(x1);
		std::cout << "������� �������� ������ ������� ����: --> ";
		input_Type(x2);
		line.setL(x1, x2);
		return 1;
	}

	// 3. ������� �������� ������ ����� �� �������� ��������
	int D_GetOrdinate(Class::Catenary& line) 
	{
		Type x, y;
		std::cout << "������� �������� ��������: --> ";
		input_Type(x);
		std::cout << "���������� �����, ������������� ���� � ��������� ���������: " << std::fixed << std::setprecision(2) << x << "\/" << std::fixed << std::setprecision(2) << line.ordinate(x) << ";\n";
		return 1;
	}

	// 4. ������� ����� ���� ������ ����� �� �� �������� �� ��� �������
	int D_GetLength(Class::Catenary& line) 
	{
		std::cout << "����� ���� ������ ����� �� �� �������� �� ��� ������� ����� ���������� �������: " << line.length() << "\n";
		return 1;
	}

	// 5. ������� ������ �������� ������ ����� ������������ ���������� �� ��� �������
	int D_GetRadius(Class::Catenary& line) 
	{
		Type x;
		std::cout << "������� �������� ��������: --> ";
		input_Type(x);
		std::cout << "������ �������� ������ ����� ������������ ���������� �� ��� �������: " << std::fixed << std::setprecision(2) << line.radius(x) << ";\n";
		return 1;
	}

	// 6. ������� ���������� ������ �������� ������ ����� � ���������� ������� ��������� ������������ ���������� �� ��� �������
	int D_GetCenter(Class::Catenary& line) 
	{
		Type x;
		std::cout << "������� �������� ��������: --> ";
		input_Type(x);
		Class::Point center = line.center(x);
		std::cout << "���������� ������ �������� ������ ����� � ���������� ������� ��������� ������������ ���������� �� ��� �������: " << std::fixed << std::setprecision(2) << center.x << "\/" << std::fixed << std::setprecision(2) << center.y << ";\n";
		return 1;
	}

	// 7. ������� ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� ������� (����� �������� = �������� ������� ������)
	int D_GetArea(Class::Catenary& line) 
	{
		std::cout << "������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� ������� (����� �������� = �������� ������� ������): " << std::fixed << std::setprecision(2) << line.area() << ";\n";
		return 1;
	}

}


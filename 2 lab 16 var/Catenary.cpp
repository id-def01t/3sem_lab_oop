
#include<stdio.h>
#include<exception>
#include "Catenary.h"


namespace Class 
{ 

	// ������� �������� ������������ ��������� �������
	// �����, ��� ��� � ��������� �� ������� ���� ������� �� ����� ������������ ����� � ������������� ��������� 
	bool Point::check() const 
	{
		if (y <= 0)
		{
			return false; 
		}	
		else
		{
			return true;
		}	
	}

	// ���������������� ����������� ��� �������� �� ���������
	Catenary::Catenary(const Point& p0, Type x1, Type x2)
	{
		if (!p0.check())
		{
			throw std::exception("������� �� : �������� ������ ������������. ���������� ��� ���.");
		}
		p = p0;
		Catenary::setL(x1, x2);
	}


	// ������ ��� ��������� ������
	Catenary& Catenary::setL(Type x1, Type x2) 
	{
		Type y1 = ordinate(x1);
		Type y2 = ordinate(x2);
		if (x1 <= x2) 
		{
			// ����� ����� ��������� this
			this->l_limit.x = x1;
			this->l_limit.y = y1;
			this->r_limit.x = x2;
			this->r_limit.y = y2;
		}
		else 
		{
			// � ����� ����� ���������� ���������
			Catenary::l_limit.x = x2;
			Catenary::l_limit.y = y2;
			Catenary::r_limit.x = x1;
			Catenary::r_limit.y = y1;
		}
		return *this;
	}


	// ������ ��� ��������� ������� 
	Catenary& Catenary::setP(const Point& p0)
	{
		if (!p0.check())
		{		
			throw std::exception("������� �� : �������� ������ ������������. ���������� ��� ���.");
		}
		p = p0;
		Catenary::setL(l_limit.x, r_limit.x);
		return *this;
	}


	// ���������� �������� �������� �� �������� ��������
	Type Catenary::ordinate(Type x) const 
	{
		return (p.y * (cosh((x - p.x) / p.y)));
	}


	// �.4: ����� ���� ������ ����� �� �� �������� �� ��� �������
	Type Catenary::length() const 
	{
		Type l1 = sqrt(pow(l_limit.y, 2) - pow(p.y, 2));
		Type l2 = sqrt(pow(r_limit.y, 2) - pow(p.y, 2));
		return (l1 + l2);
	}

	// �.5: ������ �������� ������ ����� ������������ ���������� �� ��� �������
	Type Catenary::radius(Type x) const 
	{
		return (pow(ordinate(x), 2) / p.y);
	}

	// �.6: ���������� ������ �������� ������ ����� � ��� ������������ ���������� �� ��� �������
	Point Catenary::center(Type x) const 
	{
		Type ch = cosh(x / Catenary::p.y);
		Type sh = sinh(x / Catenary::p.y);
		Point res;
		res.x = Catenary::p.y * (ch * sh + log(ch - sh));
		res.y = 2 * Catenary::p.y * ch;
		return res;
	}

	// �.7: ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� �������
	Type Catenary::area() const 
	{
		return (p.y * (sqrt(pow(l_limit.y, 2) - pow(p.y, 2)) - (sqrt(pow(r_limit.y, 2) - pow(p.y, 2)))));
	}

}
#include "13.h"


int main() 
{
	setlocale(LC_ALL, "Russian");
	Line* arr = nullptr;
	int row;				// ����� �����
	int bar;				// ����� ��������
	arr = input(row, bar);	
	if (!arr) 
	{
		std::cout << "�������� ������" << std::endl;
		return 1;
	}
	output("�������� �������", arr, row, bar);	// ����� �������� �������
	solve("�������������� ������: ", arr, row, bar);
	erase(arr, row);							// ������������ ������
	return 0;
}
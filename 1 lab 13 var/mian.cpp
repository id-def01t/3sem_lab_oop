#include "header.h"


int main() 
{
	Line* arr = nullptr;
	int row;				// ����� �����
	int bar;				// ����� ��������
	arr = input(row, bar);	
	if (!arr) 
	{
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output("Sourced matrix", arr, row, bar);	// ����� �������� �������
	solve("This is the vector: ", arr, row, bar);
	erase(arr, row);							// ������������ ������
	return 0;
}
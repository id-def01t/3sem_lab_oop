#include "header.h"


int main() 
{
	Line* arr = nullptr;
	int row;				// Число строк
	int bar;				// Число столбцов
	arr = input(row, bar);	
	if (!arr) 
	{
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output("Sourced matrix", arr, row, bar);	// Вывод исходной матрицы
	solve("This is the vector: ", arr, row, bar);
	erase(arr, row);							// Освобождение памяти
	return 0;
}
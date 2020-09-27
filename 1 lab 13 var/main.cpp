#include "13.h"


int main() 
{
	setlocale(LC_ALL, "Russian");
	Line* arr = nullptr;
	int row;				// Число строк
	int bar;				// Число столбцов
	arr = input(row, bar);	
	if (!arr) 
	{
		std::cout << "Неверные данные" << std::endl;
		return 1;
	}
	output("Исходная матрица", arr, row, bar);	// Вывод исходной матрицы
	solve("Результирующий вектор: ", arr, row, bar);
	erase(arr, row);							// Освобождение памяти
	return 0;
}
#include <iostream>
#include "header.hpp"


int main() {
	Lab3::Number number1("-f90da"), number2, number3;
	int fl = 1, p;
	long long int k;
	while (fl) {
		std::cout << "First number is: " << number1 << std::endl;
		// 2
		std::cout << "Please, enter the number to count sum and merge (int)" << std::endl;
		std::cout << "Second number is: ";
		std::cin >> k;
		Lab3::Number number2(k);
		// 4-5
		number3 = number1 + number2;
		std::cout << number1 << " + " << number2 << " = " << number3 << std::endl;
		number3 = number1 - number2;
		std::cout << number1 << " - " << number2 << " = " << number3 << std::endl;
		// 8
		//ответ на рецензию if (number1 == number2) ...
		if (number1 == number2)
		std::cout << number1 << " = " << number2 << std::endl;
		else if (number1 > number2)
			std::cout << number1 << " > " << number2 << std::endl;
		else
			std::cout << number1 << " < " << number2 << std::endl;
		// 9
		bool m = number1.isEven();
		if (m)
			std::cout << number1 << " is Even." << std::endl;
		else
			std::cout << number1 << " is not Even " << std::endl;
		// 6-7
		std::cout << "Enter the number to slide: ";
		std::cin >> p;
		number1 <<=(p); // 6
		number2 >>=(p); // 7
		std::cout << "First number: " << number1 << ", Second number: " << number2 <<std::endl;
		// 3
		std::cout << "Enter new array of symbols to continue, or press ^C to quit (char):" << std::endl;
		std::cin >> number1;
	}
	return 0;
}

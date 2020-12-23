#ifndef header_hpp
#define header_hpp

#include <iostream>
#include <math.h>

namespace Lab3 {
	class Number {
	private:
		static const int SZ = 31;	// Максимальный размер массива
		int len;	// Число цифр в числе
		char a[SZ + 2];	// Массив длинной 31 символ и + знак
	public:
		// Конструкторы
		Number();	// Инициализирует число нулем	(Пункт 1)
		Number(long long int k);	// Инициализирует число константой (Тобишь инициализация интом)	(Пункт 2) 
		Number(const char *c);	// Инициализирует число массивом символов char	(Пункт 3)

		// Геттеры
		char getFullArray() const { return *a; }	// Возвращает указатель на массив элементов
		int getLength() const { return len; }
		char *getArray() const;

		// Сеттеры
		Number &setArray(char *a0) { strcpy(a, a0); return *this; }
		Number &setLength(int l) { len = l; return *this; }
		Number &setSign() { a[0] = (a[0] == '1') ? '0' : '1'; return *this; }	// Изменяет знак у числа на противоположный 

		Number sum(const Number &r) const; 		// Сложение двух чисел (Пункт 5)
		Number sub(const Number &r) const;	// Разность двух чисел (Пункт 5)

		// Перегруженные операторы
		friend std::istream & operator >>(std::istream &, Number &r);	// Ввод экземпляров класса из входного потока (Пункт 4)
		friend std::ostream & operator <<(std::ostream &, const Number &r);	// Вывод экземпляров класса во входной потока (Пункт 4)
		friend Number operator +(const Number &c, const Number &r);
		friend Number operator -(const Number &c, const Number &r);

		// Number operator +(const Number &r) const;	// Перегруженный оператор сложения чисел
		// Number operator -(const Number &r) const;	// Перегруженный оператор разности чисел
		
		Number &operator <<=(int n);	// Сдвиг числа на n цифр влево (583->58300 при n = 2) (Пункт 6)
		Number &operator >>=(int n);	// Сдвиг числа на n цифр вправо (583->5 при n = 2) (Пункт 7)

		int isAbsMore(const Number &r) const;	// Сравнение двух чисел по модулю (Нужно для сложения)
		bool isMore(const Number &r) const;		// Сравнение двух чисел (Пункт 8)
		bool isEqual(const Number &r) const;	// Сравнение двух чисел (Пункт 8)
		bool isEven() const;	// Проверка четности (true если четно)	(Пункт 9)

		friend bool operator >(const Number &first, const Number &second); // Перегруженный оператор сравнения
		friend bool operator <(const Number &first, const Number &second);
		friend bool operator <=(const Number &first, const Number &second);
		friend bool operator >=(const Number &first, const Number &second);
		friend bool operator ==(const Number &first, const Number &second);

		void reduction();	// Изменение числа из вида 10000053 в 153 и тд
	};
}

#endif
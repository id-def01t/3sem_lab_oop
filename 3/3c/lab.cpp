#define _CRT_SECURE_NO_WARNINGS


#include <strstream>
#include <stdio.h>
#include <iostream>
#include <string>

#include "header.hpp"

namespace Lab3 {
	// Конструкторы
	// Пустой конструктор
	Number::Number() : len(1) {
		a = new char[2];
		a[0] = '0';
		a[1] = '0';
	}

	// Инициализация интом (Пункт 2)
	Number::Number(long long int k) {
		int l = 0, r, p = k, i = 0;
		while (p) {		// Узнаем количество цифр в числе
			l += 1;
			p /= 16;
		}
		len = l;
		a = new char[len + 1];
		if (k < 0) { 	// Узнаем знак числа
			a[0] = '1';
			k = -k;
		}
		else
			a[0] = '0';
		do {			// Преобразовываем dec to hex
			r = k % 16;
			k = k / 16;
			if (r > 9) 
				r += (int)'a' - 10;
			else
				r += (int)'0';
			a[len - i] = (char)r;
			++i;
		} while (k);
	}

	// Инициализация массивом символов
	Number::Number(const char *c) {	// Пункт 3
		len = strlen(c);
		int k = len;
		a = new char[len + 1];
		if (c[0] == '-') {
			a[0] = '1';
			len -= 1;
		}
		else
			a[0] = '0';
		for (int i = 1; i <= len; ++i) {
			a[i] = c[k - len - 1 + i];
		}
	}

	// Копирующий конструктор
	Number::Number(const Number &r) : len(r.len) {
		a = new char[len + 1];
		//printf("Copy\n");
		strcpy(a, r.a);
	}

	// Перемещающий конструктор
	Number::Number(Number &&r) : len(r.len), a(r.a) /* Копируем адрес памяти */ {
		//printf("Move\n");
		r.a = nullptr; // Далее вызовется деструктор 
	}

	// Перегруженный oператор присваивания копированием
	Number &Number::operator =(const Number &r) {
		if (this == &r)		// Проверка на самоприсванивание
			return *this;
		delete[] a;			// Очистка предыдущего значения a, что б утечек не было
		len = r.len;
		a = new char[len + 1];
		strcpy(a, r.a);
		return *this;
	}

	// Перегруженный оператор присваивания перемещением
	Number &Number::operator =(Number &&r) {
		//printf("_MOVE_\n");
		if (&r == this)
			return *this;
		delete a;
		a = r.a;
		len = r.len;
		r.len = 0;
		r.a = nullptr;
		return *this;
	}	

	// Сеттер
	Number &Number::setArray(char *a0) {
		delete[] a;
		len = strlen(a0) - 1;
		a = new char[len + 1];
		for (int i = 0; i <= len; ++i)
			a[i] = a0[i];
		return *this;
	}

	// Операции сложения и вычитания
	Number Number::sum(const Number &r) const {		
		int maxLen = (len > r.len) ? len : r.len;	// Узнаем в каком числе больше символов
		char *b = new char [maxLen + 2];		// +2 тк один символ под знак, один символ на случай перехода порядка
		int m = 0;	// Определяет действие (0 - сложение, 1 - вычетание из 1го 2е, 2 - выч. из 2-го 1-е)
		int k = Number::isAbsMore(r);	// Нашли большее по модулю число

		if (a[0] != r.a[0] && k == 0) {	// Числа разных знаков и по модулю равны (будет ноль)
			Number l;
			return l;
		}
		if (a[0] == '0' && k == 1) {	// Первое число больше по модулю и оно положительное
			if (r.a[0] == '1') { b[0] = '0'; m = 1; }		// 1 > 0, 2 < 0, 1 > 2
			else { b[0] = '0'; m = 0; }						// 1 > 0, 2 > 0, 1 > 2
		}
		else if (a[0] == '1' && k == 1) {	// Первое больше по модулю и оно отрицательное
			if (r.a[0] == '1') { b[0] = '1'; m = 0;}		// 1 < 0, 2 < 0, 1 > 2
			else { b[0] = '1'; m = 1; }						// 1 < 0, 2 > 0, 1 > 2
		}
		else if (r.a[0] == '0' && k == -1) {	// Второе число больше по модулю и оно положительное
			if (a[0] == '1') { b[0] = '0'; m = 2; }			// 1 < 0, 2 > 0, 1 < 2
			else { b[0] = '0'; m = 0; }						// 1 > 0, 2 > 0, 1 < 2
		}
		else if (r.a[0] == '1' && k == -1) {	// Второе больше по модулю и оно отрицательное
			if (a[0] == '1') { b[0] = '1'; m = 0; }		// 1 < 0, 2 < 0, 1 < 2
			else { b[0] = '1'; m = 2; }						// 1 > 0, 2 < 0, 1 < 2
		}
		else if (a[0] == '0' && k == 0) {	// Оба числа положительные, равные по модулю
			b[0] = '0'; m = 0;							// 1 > 0, 2 > 0, 1 == 2
		}
		else if (a[0] == '1' && k == 0) {	// Оба числа отрицательные равные по модулю
			b[0] = '1'; m = 0;							// 1 < 0, 2 < 0, 1 == 2
		}

		int s, t = 0, l = 0, n = 1, p, q;	// t - переход порядка, l - длинна
		for (int i = 0; i < maxLen; ++i) {
			if (len - i > 0)
				p = (int)a[len - i];
			else
				p = (int)'0';
			if (r.len - i > 0)
				q = (int)r.a[r.len - i];
			else
				q = (int)'0';

			if (p > 90)
				p -= 39;
			if (q > 90)
				q -= 39;
			if (m == 0) {	// Суммирование
				s = p + q;
				if (s > 96) {
					if (!n) {	// Для критического случая, когда после нуля идут цифры
						n = 1;
						++l;
					}
					++l;	// Изменяем длинну 
				}
				else if (s == 96)
					n = 0;
				if (t)
					++s;
				if (s > 111) {
					t = 1;
					s -= 64;
				}
				else {
					t = 0;
					s -= 48;
				}
				if (s > 57)
					s += 39;
			}
			else {		// Разность
				if (m == 1)	// Из первого вычитаем второе
					q = -q;
				else
					p = -p;	// Из второго первое
				s = p + q + t;
				if (s < 0) {
					t = -1;
					s += 16;
				}
				else
					t = 0;
				if (s != 0) {	// Изменяем длинну
					if (!n) {	// Для критического случая, когда после нуля идут цифры
						n = 1;
						++l;
					}
					++l;
				}
				else if (s == 0)
					n = 0;
				s += 48;
				if (s > 57)
					s += 39;
			}
			b[maxLen - i] = (char)s;
		}
		if (t == 1) {
			++l;
		}
		Number f;
		f.setArray(b);
		f.reduction();
		delete[] b;
		return f;
	}

	Number Number::sub(const Number &r) const {	// Разность
		Number l1(r);	// Копируем число r в l1
		l1.setSign();	// Меняем знак у l1
		Number l = Number::sum(l1);
		return l;
	}

	Number operator +(const Number &c, const Number &r) {
		Number m;
		m = c.sum(r);
		return m;
	}

	Number operator -(const Number &c, const Number &r) {
		Number m;
		m = c.sub(r);
		return m;
	}

	// Перегруженные операторы ввода вывода
	std::istream &operator >>(std::istream &c, Number &r) {
		int i = 0;
		delete[] r.a;
		std::string s; 
		c >> s;
		if (s[0] == '-') {
			std::string s1  = "1";
			s.replace(0, 1, s1);
		}
		else {
			std::string s1 = "0";
			s.insert(0, s1);
		}
		r.len = s.length() - 1;
		r.a = new char[r.len];
		strcpy(r.a, s.c_str());
		return c;
	}

	std::ostream &operator <<(std::ostream &c, const Number &r) {
		if (r.a[0] == '1')
			c << '-';
		for (int i = 1; i <= r.len; ++i)
			c << r.a[i];
		return c;
	}

	// Сдвиг числа на n цифр влево (583->58300 при n = 2) (Пункт 6)
	Number &Number::operator <<=(int n) {
		char *b = new char[len + n + 1];
		for (int i = 0; i <= len; ++i)
			b[i] = a[i];
		for (int i = 0; i < n; ++i)
			b[len + n - i] = '0';
		this->setArray(b);
		return *this;
	}

	// Сдвиг числа на n цифр вправо (583->5 при n = 2) (Пункт 7)
	Number &Number::operator >>=(int n) {
		char *b;
		if (len - n > 0) {
			b = new char[len + 1 - n];
			for (int i = 0; i <= len - n; ++i)
				b[i] = a[i];
		}
		else {
			b = new char[2];
			b[0] = '0';
			b[1] = '0';
		}
		this->setArray(b);
		return *this;
	}

	// Сравнение двух чисел по модулю (1 если передаваемое больше, 0 если равны, -1 если меньше) (Пункт 8)
	int Number::isAbsMore(const Number &r) const {	
		int m = 0;
		if (len > r.len)
			return (m == 0) ? 1 : -1;
		else if (len < r.len)
			return (m == 0) ? -1 : 1;
		else {
			for (int i = 1; i < (len + 1); ++i) {
				if ((int)a[i] > (int)r.a[i]) 
					return (m == 0) ? 1 : -1;
				else if ((int)a[i] < (int)r.a[i])
					return (m == 0) ? -1 : 1;
			}
		}
		return 0;
	}

	// Если первое больше второго - true, иначе false
	bool Number::isMore(const Number &r) const {
		if ((int)a[0] < (int)r.a[0])	// a[0] > 0, r.a[0] < 0
			return true;
		else if ((int)a[0] > (int)r.a[0])	// a[0] < 0, r.a[0] > 0
			return false;
		int m = (a[0] == '0') ? 0 : 1;	// 0 - оба положительные, 1 оба отрицательные
		if (len > r.len)
			return (m == 0) ? true : false;
		else if (len < r.len)
			return (m == 0) ? false : true;
		else {
			for (int i = 1; i < (len + 1); ++i) {
				if ((int)a[i] > (int)r.a[i]) 
					return (m == 0) ? true : false;
				else if ((int)a[i] < (int)r.a[i])
					return (m == 0) ? false : true;
			}
		}
		return false;
	}

	// true если равны, иначе false
	bool Number::isEqual(const Number &r) const {
		if (len == r.len) {
			if (a[0] == r.a[0]) {
				for (int i = 1; i < (len + 1); ++i) {
					if ((int)a[i] != (int)r.a[i]) 
						return false;
				}
				return true;
			}
		}
		return false;
	}

	// Проверка на четность (true - четное)
	bool Number::isEven() const {
		if ((int)a[len] <= (int)'9') {
			if ((int)a[len] % 2 == 0)
				return true;
			else
				return false;
		}
		else {
			if ((int)a[len] % 2 == 1)
				return true;
			else
				return false;
		}
	}

	// Изменение числа из вида 10000053 в 153 и тд
	void Number::reduction() {
		int i;
		for (i = 1; i <= len; ++i)
			if (a[i] != '0')	// Теперь у нас i - 1 незначащих нулей
				break;
		if (i - 1 > 0) {
			len -= (i - 1);
			char *b = new char[len - i + 2];
			b[0] = a[0];
			for (int j = 1; j <= len; ++j) {
				b[j] = a[j + i - 1];
			}
			this->setArray(b);
		}
	}

	// Возвращает строку, предварительно сократив (нужно только для проверки в Gtest)
	char *Number::getArray() const {
		char *b = new char[len + 1];
		for (int i = 0; i <= len; ++i)
			b[i] = a[i];
		return b;
	}

	// Перегруженные операторы сравнения
	bool operator >(const Number &first, const Number &second) {
		if (first.isMore(second))
			return true;
		return false;
	}

	bool operator <(const Number &first, const Number &second) {
		if (second.isMore(first))
			return true;
		return false;
	}

	bool operator <=(const Number &first, const Number &second) {
		if (second.isMore(first) || first.isEqual(second))
			return true;
		return false;
	}

	bool operator >=(const Number &first, const Number &second) {
		if (first.isMore(second) || first.isEqual(second))
			return true;
		return false;
	}

	bool operator ==(const Number &first, const Number &second) {
		if (first.isEqual(second))
			return true;
		return false;
	}
}
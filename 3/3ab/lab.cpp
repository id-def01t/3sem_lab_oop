#include <strstream>
#include <stdio.h>
#include <iostream>
#include <cstring>

#include "header.hpp"

namespace Lab3 {
	// Конструкторы
	// Пустой конструктор
	Number::Number() {
		len = 0;
		for (int i = 0; i < SZ + 1; ++i)	// Заполнение нулями
			a[i] = '0';
		a[SZ + 1] = '\0';
	}

	// Инициализация интом (Пункт 2)
	Number::Number(long long int k) {
		int i = 0, r;
		if (k < 0) { 
			a[0] = '1';
			k = -k;
		}
		else
			a[0] = '0';
		do {
			r = k % 16;
			k = k / 16;
			if (r > 9) 
				r += (int)'a' - 10;
			else
				r += (int)'0';
			a[SZ - i] = (char)r;
			++i;
		} while (k);
		len = i;
		for (int j = 0; j < SZ - len; ++j) {		// Заполнение нулями
				a[j + 1] = '0';
		}
		a[SZ + 1] = '\0';
	}

	// Инициализация массивом символов
	Number::Number(const char *c) {	// Пункт 3
		len = strlen(c);
		int k = len;
		if (c[0] == '-') {
			a[0] = '1';
			len -= 1;
		}
		else
			a[0] = '0';
		if (len > SZ + 2)
			throw std::length_error("This number is too big.");
		for (int i = 1; i < SZ - len + 1; ++i)
			a[i] = '0';
		for (int i = 0; i <= len; ++i) {
			a[SZ + 1 - i] = c[k - i];
		}
	}

	// Операции сложения и вычитания
	Number Number::sum(const Number &r) const {	// Сумма
		char b[SZ + 2];
		int m = 0;	// Определяет действие (0 - сложение, 1 - вычетание из 1го 2е, 2 - выч. из 2-го 1-е)
		int k = Number::isAbsMore(r);	// Нашли большее по модулю число

		if (a[0] != r.a[0] && k == 0) {	// Числа разных знаков и по модулю равны (будет ноль)
			Number l;
			l.setLength(0);
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

		int s, t = 0, l = 0, n = 1;	// t - переход порядка, l - длинна
		for (int i = 0; i < SZ; ++i) {
			int p = (int)a[SZ - i];
			int q = (int)r.a[SZ - i];
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
			b[SZ - i] = (char)s;
		}
		if (t == 1)
			++l;
		b[SZ + 1] = '\0';
		Number f(b);
		f.setLength(l);
		return f;
	}

	Number Number::sub(const Number &r) const {	// Разность
		Number l1 = r;	// Копируем число r в l1
		l1.setSign();	// Меняем знак у l1
		Number l = Number::sum(l1);
		return l;
	}

	// Number Number::operator +(const Number &r) const {
	// 	Number l;
	// 	l = Number::sum(r);
	// 	return l;
	// }

	// Number Number::operator -(const Number &r) const {
	// 	Number l;
	// 	l = Number::sub(r);
	// 	return l;
	// }

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
		c >> r.a;
		r.len = strlen(r.a);
		for (int i = 0; i <= r.len; ++i) {
			if (r.a[r.len - i] == '-') {
				r.a[r.len - i] = '1';
				--r.len;
			}
			else {
				r.a[Number::SZ + 1 - i] = r.a[r.len - i];
				r.a[r.len - i] = '0';
			}
		}
		for (int i = 1; i < Number::SZ - r.len + 1; ++i)
			r.a[i] = '0';
		return c;
	}

	std::ostream &operator <<(std::ostream &c, const Number &r) {
		Number b = r;
		if (r.a[0] == '1')
			c << '-';
		b.reduction();
		c << b.a;
		return c;
	}

	// Сдвиг числа на n цифр влево (583->58300 при n = 2) (Пункт 6)
	Number &Number::operator <<=(int n) {
		for (int i = len - 1; i >= 0; --i) {
			if (n + i < 31) {
				a[SZ - i - n] = a[SZ - i] ;
				a[SZ - i] = '0';
			}
			//printf("i = %d, a[] = %c\n", i, a[SZ - i]);
		}
		len += n;
		if (len > 31)
			len = 31;
		return *this;
	}

	// Сдвиг числа на n цифр вправо (583->5 при n = 2) (Пункт 7)
	Number &Number::operator >>=(int n) {
		for (int i = 1; i < len; ++i) {
			if (n - i <= 0) {
				a[SZ - i + n] = a[SZ - i];
				a[SZ - i] = '0';
			}
		}
		len -= n;
		if (len < 0)
			len = 0;
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
		if ((int)a[SZ] <= (int)'9') {
			if ((int)a[SZ] % 2 == 0)
				return true;
			else
				return false;
		}
		else {
			if ((int)a[SZ] % 2 == 1)
				return true;
			else
				return false;
		}
	}

	// Изменение числа из вида 10000053 в 53 и тд
	void Number::reduction() {
		if (this->len) {
			char *b = new char[len + 1];
			for (int i = 0; i <= len; ++i)
				b[len - i] = a[SZ + 1 - i];
			Number::setArray(b);
			delete[] b;
		}
		else {
			char b[2];
			b[0] = '0';
			b[1] = '\0';
			Number::setArray(b);
			delete[] b;
		}
	}

	// Возвращает строку, предварительно сократив (нужно только для проверки в Gtest)
	char *Number::getArray() const {
		char *b = new char[len + 1];
		for (int i = 0; i < len; ++i)
			b[len - i] = a[SZ - i];
		b[0] = a[0];
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
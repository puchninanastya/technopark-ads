#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;

/*	
 *	Модуль 1. Задание 1. Вариант 1 (Нули факториала).
 *	Найти, на   сколько   нулей   оканчивается   n!= 1 * 2 * 3 * ...   *   n.
 *	n   ≤   1000.
 *	in:	25	out: 6
 */ 

int findFactNZero (int n) {
	int nPowerOfFive = 1;
	// Количество нулей будем определять по формуле деления числа n на степень 5.
	// (n / 5) + (n / 25) + ... .
	while (n / pow(5, nPowerOfFive) >= 1) {
		nPowerOfFive++;
	}
	// Считаем количество нулей
	int nZero = 0;
	for (int i = 1; i < nPowerOfFive; i++) {
		nZero += (int) (n / pow(5, i));
	}
	
	return nZero;
}
 
int main() {
	int n = 0;
	cin >> n;
	assert(n <= 1000);

	int nZero = findFactNZero(n);

	cout << nZero;
	return 0;
}
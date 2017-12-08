#include <iostream>
#include <assert.h>

using namespace std;

/* 
 * Модуль 1. Задача 2. Вариант 1. Максимальная сумма. 
 * Даны   два   массива   целых   чисел   одинаковой   длины   A[0..n-1]   и   B[0..n-1].   
 * Необходимо   найти  п   ервую пару   индексов   i0   и   j0,    i0   ≤   j0 ,   такую  
 * что   A[i0]   +   B[j0]   =   max   {A[i]   +   B[j],   где   0   <=   i   <   n,   0   
 * <=   j   <   n,    i   <=   j }.   Время работы   -   O(n).
 * n   ≤   100000.
 */

class Indexes {
public:
	int i;
	int j;

	Indexes() : i(0), j(0) {};
};

Indexes findMaxSum(int* A, int* B, int n) {
	Indexes resIndexes;
	int prevMaxA = 0;
	int maxSum = A[0] + B[0];

	for (int i = 0; i < n; i++) {
		if (A[i] > A[prevMaxA]) {
			prevMaxA = i;
		}
		if (B[i] + A[prevMaxA] > maxSum) {
			resIndexes.i = prevMaxA;
			resIndexes.j = i;
			maxSum = B[i] + A[prevMaxA];
		}
	}

	return resIndexes;
}

int main() {
	int n = 0;
	cin >> n;

	assert(n != 0);

	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	int* B = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> B[i];
	}

	Indexes maxSumIndexes = findMaxSum(A, B, n);

	cout << maxSumIndexes.i << ' ' << maxSumIndexes.j;
	getchar();
	getchar();

	delete[] A;
	delete[] B;

	return 0;
}
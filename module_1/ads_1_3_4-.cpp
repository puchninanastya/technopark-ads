#include <iostream>
#include <math.h>

using namespace std;

/* 
 * Модуль 1. Задача 3. Вариант 4 (Поиск близнеца).
 * Дан   отсортированный   массив   различных   целых   чисел   A[0..n-1]   
 * и   массив   целых   чисел   B[0..m-1].   Для каждого   элемента   массива   B[i]
 * найдите   минимальный   индекс   элемента   массива   A[k],   ближайшего
 * по значению   к   B[i].   Время   работы   поиска   для   каждого   элемента
 * B[i]:   O(log(k)).
 * n   ≤   110000,   m   ≤   1000.
*/

// Attention!!! Not for contest. 

void findSearchBoundaries(int* arr, int n, int elem, int& first, int& last) {
	int nearElementIndex = 0;
	int nearElementDiffB = abs(elem - arr[nearElementIndex]);

	int currentDiff = 0;
	for (int i = 1; i < n; i *= 2) {
		currentDiff = abs(elem - arr[i]);
		if (currentDiff < nearElementDiffB) {
			nearElementIndex = i;
			nearElementDiffB = currentDiff;
		}
		else if (currentDiff > nearElementDiffB) {
			first = nearElementIndex;
			last = i;
			break;
		}
	}
}
int binarySearch(int* arr, int elem, int start, int finish)
{
	int left = start, right = finish;

	while (left < right - 1)
	{
		int middle = left + (right - left) / 2;
		if (arr[middle] > arr[middle + 1])
			if (arr[middle - 1] < arr[middle])
				left = middle;
			else
				right = middle;
		else
			if (arr[middle - 1] < arr[middle])
				left = middle;
			else
				right = middle;
	}
	return left;

}

int main() {
	// input A array
	int n;
	cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	// input B array
	int m;
	cin >> m;
	int* B = new int[m];
	for (int i = 0; i < m; i++) {
		cin >> B[i];
	}

	// find twins for B array elements in A array
	int first = 0, last = 0;
	for (int i = 0; i < m; i++) {
		findSearchBoundaries(A, n, B[i], first, last);
		cout << binarySearch(A, B[i], first, last);

	}

	// output result
	getchar();
	getchar();

	return 0;
}
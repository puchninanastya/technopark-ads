#include <iostream>

using namespace std;

/*
 * Модуль 1. Задача 6. Вариант 1 (Высокая пирамида).
 * Дано N кубиков.
 * Требуется определить, каким количеством способов можно 
 * выстроить из этих кубиков пирамиду.
 * Формат входных данных:
 * На вход подается количество кубиков N.
 * Формат выходных данных:
 * Вывести число различных пирамид из N кубиков.
 *
 */

// Attention!!! Not for contenst.

int countPyramids(int base, int freeCubes) {
	int counterPyramids = 0;
	int currentNCubes = 0;		// current number of cubes on this layer
	bool isFullPyramid = true;	// no free cubes

	// count cubes on this layer
	while (currentNCubes < base && currentNCubes < freeCubes)
		++currentNCubes;

	// there are free cubes but base is full
	if (currentNCubes < freeCubes && currentNCubes == base) {
		counterPyramids += countPyramids(base, freeCubes - currentNCubes);
		isFullPyramid = false;
	}

	// no free cubes, count pyramids for new base decreasing by 1
	if (currentNCubes == freeCubes || !isFullPyramid)
	{
		if (isFullPyramid)
			counterPyramids++;
		int newFreeCubes = freeCubes - currentNCubes;

		// free 1 cube and count for new base decreased by 1
		while (currentNCubes > 1)
			counterPyramids += countPyramids(--currentNCubes, ++newFreeCubes);
	}

	return counterPyramids;
}

int main() {
	int cube_count = 0;
	cin >> cube_count;
	cout << countPyramids(cube_count, cube_count);

	return 0;
}
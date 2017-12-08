#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Модуль 1. Задача 7. Вариант 2 (Заявки на переговоры).
 * В   большой   IT-фирме   есть   только   одна   переговорная   комната.   
 * Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
 * Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
 * Число заявок ≤ 100000.
 * Формат входных данных:
 * Вход содержит только пары целых чисел — начала и концы заявок.
 * Формат выходных данных:
 * Выход должен содержать натуральное число — максимальное число заявок.
 */

void inputRequests(vector<pair<int, int>>& requests) {
	pair<int, int> newRequest;
	// read pairs until EOF
	while (cin >> newRequest.first >> newRequest.second) {
		requests.push_back(newRequest);
	}
}

bool myPairSecondComparison(const pair<int, int> &a, const pair<int, int> &b) {
	return a.second < b.second;
}

int selectRequests(vector<pair<int, int>>& requests) {
	// number of selected requests
	int result = 1;

	// select first request
	pair<int, int> lastSelectedReq;
	if (!requests.empty())
		lastSelectedReq = requests[0];

	for (int i = 1; i < requests.size(); i++) {
		// compare start time of new request with end time of last selected request
		if (requests[i].first >= lastSelectedReq.second) {
			lastSelectedReq = requests[i];
			result++;
		}
	}

	return result;
}

int main() {
	// request: <start time, end time> 
	vector<pair<int, int>> requests;
	inputRequests(requests);
	
	// sort requests by end time 
	sort(requests.begin(), requests.end(), myPairSecondComparison);

	// output number of selected requests
	cout << selectRequests(requests);

	getchar();
	getchar();

	return 0;
}
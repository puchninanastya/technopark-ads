#include <iostream>
#include <assert.h>

using namespace std;

/*
 * Модуль 1. Задача 4. Вариант 1 (Очередь с динамическим буфером).
 * 
 * Написать   структуру   данных,   обрабатывающую   команды
 * push*   и   pop*.
 * Формат   входных   данных.
 * В   первой   строке   количество   команд   n.   n   ≤   1000000.
 * Каждая   команда   задаётся   как   2   целых   числа:   a   b.
 * a   =   1   -   push   front
 * a   =   2   -   pop   front
 * a   =   3   -   push   back
 * a   =   4   -   pop   back
 * Команды   добавления   элемента   1   и   3   заданы   с   неотрицательным   параметром   b.
 * Для   очереди   используются   команды   2   и   3.   
 * Если   дана   команда   pop*,   то   число   b   -   ожидаемое   значение.   
 * Если   команда   pop   вызвана   для   пустой структуры   данных,   то   ожидается   “-1”.
 * Формат   выходных   данных.
 * Требуется   напечатать   YES   -   если   все   ожидаемые   значения   совпали.   
 * Иначе,   если   хотя   бы   одно   ожидание не   оправдалось,   то   напечатать   NO.
 */

// Available commands:
#define PUSH_BACK 3
#define POP_FRONT 2

#define BUFFER_SIZE 4

class Queue {
public: 
	explicit Queue(int size);
	~Queue();

	void push_back(int a);
	int pop_front();

	bool isEmpty();
	int size();

private:
	bool resize(int newSize);

	int* buffer;
	int bufferSize;
	int head; // first queue element index
	int tail; // index after last queue element
};

Queue::Queue(int size) :
	bufferSize(size), 
	head(0), 
	tail(0) {
	buffer = new int[bufferSize];
}

Queue::~Queue() {
	delete[] buffer;
}

void Queue::push_back(int a) {
	if ((tail + 1) % bufferSize == head)
		resize(bufferSize * 2);
	buffer[tail] = a;
	tail = (tail + 1) % bufferSize;
}

int Queue::pop_front() {
	if (size() < bufferSize / 2)
		resize(bufferSize / 2);
	int result = buffer[head];
	head = (head + 1) % bufferSize;
	return result;
}

bool Queue::isEmpty() {
	return (head == tail);
}

bool Queue::resize(int newSize) {
	int* newBuffer = new int[newSize];
	int newTail = 0;
	while (!isEmpty()) {
		newBuffer[newTail] = buffer[head];
		head = (head + 1) % bufferSize;
		newTail++;
	}
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newSize;
	head = 0;
	tail = newTail;
	return true;
}

int Queue::size() {
	if (tail >= head)
		return tail - head;
	else
		return tail + (bufferSize - head);
}

int main() {
	int n = 0;
	cin >> n;
	int command = 0;
	int value = 0;
	int resultValue = 0;
	Queue queue(BUFFER_SIZE);
	bool isNoResult = false;
	for (int i = 0; i < n; i++) {
		cin >> command;
		cin >> value;
		if (command == PUSH_BACK) {
			queue.push_back(value);
		}
		else if (command == POP_FRONT) {
			if (queue.isEmpty()) {
				if (value != -1) {
					isNoResult = true;
					break;
				}
			}
			else {
				resultValue = queue.pop_front();
				if (resultValue != value) {
					isNoResult = true;
					break;
				}
			}
		}
		// don't available command
		else {
			isNoResult = true;
			break;
		}
	}
	if (isNoResult)
		cout << "NO";
	else
		cout << "YES";

	getchar();
	getchar();

	return 0;
}
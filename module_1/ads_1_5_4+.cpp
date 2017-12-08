#include <iostream>
#include <string>

/*
 * Модуль 1. Задача 5. Вариант 4  (Вычисление выражения).
 * Дано   выражение   в   инфиксной   записи.
 * Вычислить   его,   используя   перевод   выражения   в   постфиксную запись. 
 * Выражение   не   содержит   отрицительных   чисел.
 * Количество   операций   ≤   100.
 * Формат   входных   данных:
 * Строка,   состоящая   их   символов   “0123456789-+*\/()”
 * Гарантируется, что   входное   выражение   корректно, 
 * нет   деления   на   0, вычислимо   в   целых   числах. 
 * Деление   целочисленное.
 * Формат   выходных   данных:
 * Значение   выражения.
*/

template<typename T>
class Stack {
public:
	Stack() : topElement(nullptr), stackSize(0) {}
	~Stack() {
		while (stackSize) {
			pop();
		}
	}

	void push(const T& t) {
		if (Node* newNode = new Node(t, topElement)) {
			stackSize++;
			topElement = newNode;
		}
	}
		
	void pop() {
		if (topElement) {
			stackSize--;
			Node* nodeToPop = topElement;
			topElement = topElement->next;
			delete nodeToPop;
		}
	}

	T top() const {
		if (topElement) {
			return topElement->data;
		}
		return NULL;
	}

	unsigned int size() const {
		return stackSize;
	}

	bool isEmpty() const {
		return (stackSize ? 0 : 1);
	}

private:
	// stack is based on linked list (nodes)
	struct Node {
		Node() : next(nullptr) {}
		Node(const T& newData) : data(newData), next(nullptr) {}
		Node(const T& newData, Node* newNext) : data(newData), next(newNext) {}

		T data;
		Node* next;
	};

	unsigned int stackSize;
	Node* topElement;
};

// operations
#define OPER_PLUS	'+'
#define OPER_MINUS	'-'
#define OPER_MULT	'*'
#define OPER_DIV	'/'

// operations priorities
#define OPER_PRIORITY_PM	1
#define OPER_PRIORITY_MD	2

// is symbol end of string
bool isEnd(std::string str, int curPos) {
	return (curPos >= static_cast<int>(str.size()));
}

// functions to check symbols for numbers, operations or brackets
bool checkNumber(char c) {
	return (c >= '0' && c <= '9');
}
bool checkMathOper(char c) {
	return (c == OPER_PLUS || c == OPER_MINUS || c == OPER_MULT || c == OPER_DIV);
}
bool checkOpenBracket(char c) {
	return (c == '(');
}
bool checkCloseBracket(char c) {
	return (c == ')');
}

int getMathOperPriority(char c) {
	if (c == OPER_PLUS || c == OPER_MINUS)	return OPER_PRIORITY_PM;
	if (c == OPER_MULT || c == OPER_DIV)	return OPER_PRIORITY_MD;
	return NULL;
}

int calcNumbers(int a, int b, char op) {
	switch (op) {
	case OPER_PLUS:		return a + b;
	case OPER_MINUS:	return a - b;
	case OPER_MULT:		return a * b;
	case OPER_DIV:		return a / b;
	default:			return NULL;
	}
}

// read full number in string from current position
int readNumber(std::string str, int& curPos) {
	int res = 0;
	while (!isEnd(str, curPos) && checkNumber(str[curPos])) {
		// multiply by ten for right number orders
		// (minus 48) to get int number from char
		res = res*10 + (static_cast<int>(str[curPos]) - 48);
		curPos++;
	}
	curPos--;
	return res;
}

int calcExpression(std::string inputExpression) {
	Stack<int> numbersStack;	// stack for current numbers and result
	Stack<char> operStack;		// stack for math operations and brackets

	int curPos = 0; // current position in expression string
	int a = 0;
	int b = 0;
	int res = 0;

	// until the end of expression string 
	while (!isEnd(inputExpression, curPos)) {
		char curSymb = inputExpression[curPos];
		if (checkCloseBracket(curSymb)) {
			// calc everything until meet open bracket on stack
			while (!checkOpenBracket(operStack.top())) {
				a = numbersStack.top();
				numbersStack.pop();
				b = numbersStack.top();
				numbersStack.pop();
				numbersStack.push(calcNumbers(b, a, operStack.top()));
				operStack.pop();
			}
			operStack.pop(); // pop open bracket
		}
		else if (checkOpenBracket(curSymb)) {
			operStack.push(curSymb);
		}
		else if (checkMathOper(curSymb)) {
			int curOperPriority = getMathOperPriority(curSymb);
			// calc while there are math operations with bigger or equal priority in stack
			while (!operStack.isEmpty() 
				&& checkMathOper(operStack.top())
				&& (getMathOperPriority(operStack.top()) >= curOperPriority)) {
				a = numbersStack.top();
				numbersStack.pop();
				b = numbersStack.top();
				numbersStack.pop();
				res = calcNumbers(b, a, operStack.top());
				operStack.pop();
				numbersStack.push(res);
			}
			operStack.push(curSymb); // add new operator to stack
		}
		else if (checkNumber(curSymb)) {
			numbersStack.push(readNumber(inputExpression, curPos));
		}

		curPos++;
	}

	// calc remaining operation in stack
	while (!operStack.isEmpty()) {
		a = numbersStack.top();
		numbersStack.pop();
		b = numbersStack.top();
		numbersStack.pop();
		numbersStack.push(calcNumbers(b, a, operStack.top()));
		operStack.pop();
	}

	// numbers stack contain one number - expression result
	return numbersStack.top();
}

int main() {
	std::string inputExpression;
	std::cin >> inputExpression;

	int result = calcExpression(inputExpression);

	std::cout << result;

	getchar();
	getchar();

	return 0;
}
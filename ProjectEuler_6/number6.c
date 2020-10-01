#include <stdio.h>

int sumOfSquares(int n) {
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += i * i;
	}
	return sum;
}

int squareOfSum(int n) {
	int sum = 0;
	for (int i = 1; i <= n; i++) { 
		sum += i;
	}
	return sum * sum;
}

int difference(int a, int b) {
	return a - b;
}

int main() {
	int x = difference(squareOfSum(100), sumOfSquares(100));
	printf("%d\n", x);
	return 0;
}
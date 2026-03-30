#include <stdio.h>

int add(int x, int y);

int main(void) {
	int a = 10;
	int b = 20;

	printf("Sum = %d\n", add(a, b));
	return 0;
}

int add(int x, int y) {
	return x + y;
}

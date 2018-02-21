#include<stdio.h>

int func(int a);

int main() {
	printf("Before calling func.\n");
	
	func(10);

	printf("After calling func.\n");
	return 0;
}

int func(int a) {

	printf("Value passed as argument is %d\n" , a);
	return a+1;
}

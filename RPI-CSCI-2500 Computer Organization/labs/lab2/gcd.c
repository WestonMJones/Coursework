#include <stdio.h>



int gcd(int a, int b) {

	int t;

	while (b!=0) {
		t = b;
		b = a % b;
		a = t;
	}

	return a;
}


int main()
{
  
  int x, y;
  printf("Enter a number: ");
  scanf("%d",&x);
  printf("Enter another a number: ");
  scanf("%d",&y);

  printf("The greatest common divisor is: %d\n", gcd(x,y) );

  return 0;
}
#include<stdio.h>
int sum(int);
int fib(int);
int dec(int);

int main()
{
	int n,a,b,c,choice;
	printf("Enter Choice\t1.n numbers sum\t2.n numbers fibonacci\t3.convert to binary\n");
	scanf ("%d",&choice);
	printf("enter the value of n\n");
	scanf("%d",&n);
	switch(choice)
	{
		case 1:
		a=sum(n);
		printf("sum of %d numbers is %d\n",n,a);
		break;
		case 2:
		b=fib(n);
		printf("fibonacci of %d numbers is %d\n",n,b);
		break;
		case 3:
		c=dec(n);
		printf("binary of %d numbers is %d\n",n,c);
		break;
	}
	return 0;
}
int sum (int n)
{
	if (n==0)
	return 0;
	else
	return (n+sum(n-1));
}
int fib (int n)
{
	if (n==0||n==1)
	return n;
	else 
	return (fib(n-1)+fib(n-2));
}
int dec (int n)
{
	if (n==0)
	return 0;
	else 
	return (n%2)+10*(dec(n/2));
}

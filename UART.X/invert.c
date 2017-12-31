#include<stdio.h>

int* invert(int );
void main()
{
	char a=0x55,*b;
	
	b=invert(a);
	printf("%d\n",*b);
	if(a==~*b)
	printf("pass");
	else
	printf("fail");
}

int* invert (int in)
{
/*	static*/ int out;
	out=~in;
	return &out;
}

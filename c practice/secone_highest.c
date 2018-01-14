#include <stdio.h>
void main()
{
	
	char x[10]={22,1,2,4,21,2,6,3,7,23};
	int temp=x[0],temp1=x[1],i;
	
	if(temp<temp1)
	{
		temp=temp1;
		temp1=x[0];
	}
	
	
	for(i=2;i<sizeof(x);i++)
	{	
		if(temp<x[i])
		{
			temp1 = temp;
			temp = x[i];
		}
		else
		{
			if(temp1<x[i])
			{
				temp1=x[i];
			}
		}
	}
	printf("%d",temp1);
	
	
}

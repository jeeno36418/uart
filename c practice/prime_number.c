#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
int* get_prime_number(int *num_arry,int size);

void main ()
{
	int number_list[]={3,1299827,1009,54,89,47,28,39,4,56,88,167,95,38,188,1001,99,91,97,87,73,167};
	int *arry_ptr,i;
	arry_ptr = get_prime_number(number_list ,sizeof(number_list)/sizeof(int));
	
	for(i=0;*(arry_ptr+i)!=0; i++)
	{
		printf(" %d  \n",*(arry_ptr+i) );
	}
	
}
typedef struct
{
	int prime;
}pr;
int* get_prime_number(int *num_arry,int size)
{
	static int *prime_list;
	int i,j,count=0,not_prime=FALSE;
	prime_list =  (int *)malloc(size * sizeof(int));
	for(j=0; j<size; j++)
	{
		if(*(num_arry + j) == 2 || *(num_arry + j) == 1)
		{
			 
			prime_list[count++] = *num_arry;
			continue;
		}
		if(*(num_arry + j) % 2 == 0)
		{
			continue;
		}
		for(i=3;i*i<=*(num_arry+j);i+=2)
		{
			if(*(num_arry+j) % i == 0)
			{
				not_prime = TRUE;
				break;
			}
		}
		if(not_prime == FALSE)
		 prime_list[count++] = *(num_arry+j);
		 else
		not_prime=FALSE;
	}
	prime_list[count]=0;
	printf(" size of prime number %d  \n",sizeof(prime_list)/sizeof(int) );

	return prime_list;
}

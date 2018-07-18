#include<stdio.h>

void main()
{
	int i,j,row;
	
	printf("Give number of row to print\n");
	scanf("%d",&row);
	
	for(i=0; i<row;i++)
	{
		for(j=0; j<row; j++)
		{
			//printf("i=%d j=%d\n",i,j);
			/*Calculate number of space to filled in currently printing row*/
			if(j >= (row-1-i))
			{	
				printf("%d",i+1);
			}
			if(j==row-1)
			{
				
				printf("\n"); 
				break;
				
			}
			printf(" ");
			
			
				
			
			
		}
	}
	return ;	
}

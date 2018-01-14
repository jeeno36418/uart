#include<stdio.h>
#include<string.h>
#define row 70
#define coloumn 70
#define buff_size row*coloumn
int draw_Box(int x,int y,int height,int width,int pixel_width,char *);

typedef struct
{
	char r;
	char g;
	char b;
	char a;
}rgba_t;

typedef struct
{
	int x;
	int y;
	int height;
	int width;
	int pixel_width;
	
	char * base_ptr;
}box_t;

rgba_t *rgba_ptr;
unsigned char data[buff_size]={1};
void main()
{
	    
	long unsigned int status,i,j=0;
	memset(data,0,sizeof(data));
   if(status = draw_Box(8,8,15 ,20,2,data))
   {
     printf("out of boundary");
   	return ;
   }
	
	for(i=0;i<buff_size;i++)
	{
	
		if(i%coloumn==0)
		{
		
			if(i==0)
			{
				
			}
			else
			{
				printf("%3d\n",(j++));
			}
		}
		printf("%2d ",data[i]);
	
	
	}
	printf("%3d\n\n",j-1);
	
		for(i=0;i<coloumn;i++)
	{
	
		
	
		printf("%2d ",i);
	
	
	}
	return ;


}


int draw_Box(int x,int y,int height,int width,int thick,char *base_ptr)
{
	int x1,y1,i,j;
	x1 = x + height-1;
	y1 = y + width-1;
//	char *box_base_ptr = (base_ptr+((x*10)+y));
	if((x1)>row || (y1) >coloumn)
	{
	
		return 1;
	}
#if 1
for(j=0;j<thick;j++)
{	
	for(i=x+j;i<=x1-j;i++)
	{
		
		  *(base_ptr+(i*coloumn)+y+j)=1+j;	
		  *(base_ptr+(i*coloumn)+y1-j)=1+j;
	}
}
#endif	
#if 1
for(j=0;j<thick;j++)
{
	for(i=y+1+j;i<y1-j;i++)
	{
		
		  *(base_ptr+((x+j)*coloumn)+i)=1+j;	
		  *(base_ptr+((x1-j)*coloumn)+i)=1+j;	
	}
}
#endif	
	return 0;
//	for(i=x;)
	
}

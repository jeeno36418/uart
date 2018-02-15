#include<stdio.h>

typedef  unsigned char int_u8;
int_u8 hour[2]={1,9},min[2]={4,0},sec[2]={5,9},day[1]={1},date[2]={2,6},month[2]={1,1},year[2]={1,8};
int_u8 *timer_ptr[7]={hour,min,sec,day,date,month,year };
//int_u8 year[2]={9,2};
int char2int(int_u8 *in);
void main()
{
	int result;
	
	result=char2int(timer_ptr[5]);
	printf("%x",result);
//	return 0;
}

int char2int(int_u8 *in)
{
    return (*(in)<<4 | *(in+1)) ;


}

#include<stdio.h>

typedef  unsigned char int_u8;
int_u8 year[2]={9,2};
int char2int(int_u8 *in);
void main()
{
	int result;
	
	result=char2int(year);
	printf("%x",result);
//	return 0;
}

int char2int(int_u8 *in)
{
    return (*(in)<<4 | *(in+1)) ;


}

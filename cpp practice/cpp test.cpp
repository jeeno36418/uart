#include <iostream>
#include <cstdlib>
using namespace std;


int main ()
{
	char *a= new char[2] ,i ;
	float b=12;
for(i=0;i<2;i++ )
{	
  
  cin>>*(a+i);
	
}
for(i=0;i<2;i++ )
{	
  
  cout<<*(a+i)<<endl;
	
}
cout<<sizeof(a)<<endl;
	return 0;
}
	




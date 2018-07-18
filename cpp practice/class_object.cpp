#include<iostream>

using namespace std;

class Box{
	public:
		double length; //length of the box
		double height; // height of the box	
		double breadth;// breadth of the box
		
};


int main()
{
	Box box1;
	Box box2;
	
	double volume = 0;
	
	//box 1 specification
	
	box1.breadth = 5.0;
	box1.height = 6.0;
	box1.length = 7.0;
	
	volume = box1.breadth * box1.height * box1.length;
	
	cout <<"volume of box1 is "<<volume<<endl;
	return 0;
}



#include<iostream>

using namespace std;

// Bass class

class Shape{
	public:	
		int height;
		int width;
		
	public:
		void set_height(int h){
			height = h;
		}
		
		void set_width(int w){
			width = w;
		}
	

};


// Derived class

class Rectangle: public Shape {
	public:
		int getArea() {
			return (width * height);
		}
	
};

int main()
{
	Rectangle rect;
	Shape rect_dim;
	int area;
	
	rect.set_height(5);
	rect.set_width(7);
	rect_dim.height=9;
	area =  rect.getArea();
	
	cout << " Area of Rectangel is "<<area<<endl;
	cout << " Area of dim is "<<rect_dim.height<<endl;	
	
}


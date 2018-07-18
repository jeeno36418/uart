#include<iostream>

using namespace std;

class box{
	public:
		void set_length(double len){
			length = len;
		}
		void set_breadth(double bre){
			breadth = bre;
		}
		void set_height(double hei){
			height = hei;
		}
		public:
			double get_volume()
			{
				return height * breadth * length;
			}
		box operator + (const box& b){
			box Box;
			Box.breadth = this->breadth + b.breadth;
			Box.height = this->height + b.height;
			Box.length = this->length + b.length;
			
			return Box;
		}
			
			
		public:
			double length;
			double breadth;
			double height;
};


int main(void)
{
	
	box box1,box2,box3;
	
	
	box1.set_breadth(10);
	box1.set_height(5);
	box1.set_length(10);
	 
	box2.set_breadth(5);
	box2.set_height(2);
	box2.set_length(3);
	
	box3 = box1 + box2;
	 
	cout <<"volume : "<< box1.get_volume()<<endl; 
	cout <<"volume : "<< box2.get_volume()<<endl; 
	cout <<"volume : "<< box3.get_volume()<<endl;  
	return 0;
}

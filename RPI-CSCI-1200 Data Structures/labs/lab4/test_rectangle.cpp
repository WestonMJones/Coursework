#include "Rectangle.h"
#include "Point2D.h"
#include <iostream>


int main() {

	std::cout << "Initial Rectangle given 0,0 and 5,5" << std::endl;
	Point2D p1(0,0);
	Point2D p2(5,5);
	Rectangle r1(p1,p2);

	print_rectangle(r1);

	std::cout << std::endl << "Testing addition of points" << std::endl;


	Point2D p3(10,10);
	Point2D p4(3,3);

	std::cout << r1.add_point(p3) << std::endl;
	std::cout << r1.add_point(p3) << std::endl;
	std::cout << r1.add_point(p4) << std::endl;

	print_rectangle(r1);

	std::cout << std::endl << "Creating second rectangle with points 2,2 and 7,7" << std::endl;
	std::cout << "Testing is point within" << std::endl;



	Point2D p5(2,2);
	Point2D p6(7,7);
	Point2D p7(4,4);
	Point2D p8(6,6);

	Rectangle r2(p5,p6);

	print_rectangle(r2);

	std::cout << r2.is_point_within(p7) << std::endl;
	std::cout << r2.is_point_within(p8) << std::endl;

	return 0;
}
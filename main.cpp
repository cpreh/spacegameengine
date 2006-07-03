#include "./scheduler.hpp"

#include <iostream>

void fun1()
{
	std::cout << ":):):):)\n";
}

void fun2()
{
	std::cout << ":/:/:/:/\n";
}

int main()
{
	qfbot::scheduler s;
	s.add_task( qfbot::priority_handler( fun1, 0));
	s.add_task( qfbot::priority_handler( fun2, 1));
	s.run();
}

/* Write your test code for the ULListStr in this file */

#include <iostream>
#include "ulliststr.h"


int main(int argc, char* argv[])
{
	ULListStr one; //tests push and pop
	std::cout << "Test one:" << std::endl;

	one.push_front("4");
	std::cout << one.size() << std::endl; //should be 1

	one.push_back("3");
	std::cout << one.size() << std::endl; //should be 2

	std::cout << one.get(0) << "   " << one.get(1) << std::endl; //should be 4 3

	one.pop_front();
	one.push_front("9");
	std::cout << one.get(0) << "   " << one.get(1) << std::endl; //should be 9 3

	one.pop_back();
	one.push_back("9");
	std::cout << one.get(0) << "   " << one.get(1) << std::endl; //should be 9 9
	one.clear();



	ULListStr two; //if no room, create node
	std::cout << "Test two:" << std::endl;
	two.push_front("1");
	two.push_front("2");
	two.push_front("3");
	two.push_front("4");
	two.push_front("5");
	two.push_front("6");
	two.push_front("7");
	two.push_front("8");
	two.push_front("9");
	two.push_front("10");
	two.push_front("11");
	
	std::cout << two.get(0) << "   " << two.get(1) << std::endl; //should be 11 10
	two.clear();



	ULListStr three; //making sure pop and size work
	std::cout << "Test three:" << std::endl;
	three.push_back("10");
	three.push_back("9");
	three.push_back("8");
	three.push_back("7");
	three.push_back("6");
	three.push_back("5");
	three.push_back("4");
	three.push_back("3");
	three.push_back("2");
	three.push_back("1");
	std::cout << "Size is: " << three.size() << std::endl; //should be 10
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	three.pop_back();
	std::cout << "Size is: " << three.size() << std::endl; //should be 0
	three.clear();

  return 0;
}

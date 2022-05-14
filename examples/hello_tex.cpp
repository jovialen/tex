#include <iostream>

#include <tex.hpp>

int main(int argc, char *argv[])
{
	tex::init();
	std::cout << "Hello, Tex!" << std::endl;
	tex::quit();
}

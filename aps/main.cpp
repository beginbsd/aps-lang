#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
	if (argv[1]) {
		std::ifstream maincc(argv[1]);
	}else {
		std::cout<<"ERROR|:  NO FILE SPECIFIED"<<std::endl;
	}
}
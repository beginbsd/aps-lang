#include <iostream>
#include <string>
#include "maincc.h"
int main(int argc, char* argv[])
{
	if (argv[1]) {
		if (argv[1] == "-version") { std::cout << "ASP lang: version 0.1 " << std::endl; return 0; }
		std::string ts = argv[1];
		if (ts.ends_with(".asp")) {
			readFile(ts);
		}
		else {
			std::cerr << "ERROR|:  INVALID FILE TYPE" << std::endl;
		}
	}
	else {
		std::cerr << "ERROR|:  NO FILE SPECIFIED" << std::endl;
	}
}
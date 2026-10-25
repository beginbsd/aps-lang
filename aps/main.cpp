#include <iostream>
#include <string>
#include "maincc.h"
int main(int argc, char* argv[])
{
	if (argv[1]!=0) {
		std::string ts = argv[1];
		if (ts == "-version") { std::cout << "ASP lang: version 0.1 " << std::endl; return 0; }
		if (ts.ends_with(".aps"));
	}else {
		std::cout << "ERROR|:  NO FILE SPECIFIED" << std::endl;
	}
}
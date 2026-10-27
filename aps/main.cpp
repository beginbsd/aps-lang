#include <iostream>
#include <string>
#include "maincc.h"
int main(int argc, char* argv[])
{
	if (argv[1]!=0) {
		std::string ts = argv[1];
		if (ts == "-version") { 
			std::cout << "ASP lang: version 0.1 " << std::endl; 
			std::cout << "ASP lang from WYY " << std::endl;
			std::cout << "ASP lang is a simple programming language that can be used to create simple programs." << std::endl;
			return 0; 
		}
		if (ts == "-help") {
			std::cout << "ADD SUB MUL DIV MOD EQ:"<<std::endl;
			std::cout << "(variable) (number1) (number2) ADD/SUB/MUL/DIV/MOD/EQ" << std::endl;
			std::cout << "Like:" << std::endl;
			std::cout << "$a 1 5 ADD" <<std::endl;
			std::cout << "input/print" << std::endl;
			std::cout << "inout: (variable) input" << std::endl;
		}
		if (ts.ends_with(".aps")) {
			readFile(ts);
		}
		else {
			std::cerr << "ERROR|:  FILE TYPE NOT SUPPORTED" << std::endl;
		}
	}else {
		std::cout << "ERROR|:  NO FILE SPECIFIED" << std::endl;
	}
}
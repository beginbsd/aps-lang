#include "maincc.h"
#include <iostream>
#include <string>

int readFile(std::string fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "ERROR|:  COULD NOT OPEN FILE" << std::endl;
		return -1;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl; 
	}
	file.close();
	return 0;
}
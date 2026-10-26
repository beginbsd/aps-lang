#include "maincc.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include<map>

double sum = 0;

std::vector<std::string> keywords = {  //关键字
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"MOD",
	"EQ",
	"print",
	"input"
};
std::stack <std::string> aps_stack;//程序TOKEN
std::map<std::string,std::string> asp_stack;//主栈


void var_push(std::string ss, std::string sv) {
	for (const auto& [key, value] : asp_stack) {
		if (key == ss) {
			asp_stack[key] = sv;
			break;
		}
	}
}
int readFile(std::string fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "ERROR|:  COULD NOT OPEN FILE" << std::endl;
		return -1;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::vector<std::string> tokens;
		std::string token;
		while (iss >> token) {
			aps_stack.push(token);
		}
		for (size_t i = 0;i < keywords.size();i++) {
			if (aps_stack.top() == keywords[i]) {
				if (keywords[i] == "ADD") {
					aps_stack.pop();
					try {
						double a = std::stoi(aps_stack.top());
						aps_stack.pop();
						sum += a;
						a = std::stoi(aps_stack.top());
						sum += a;
						aps_stack.pop();
						std::string n = aps_stack.top();
						aps_stack.pop();
						var_push(n, std::to_string(sum));
					}
					catch (std::exception& e) {
						std::cerr << "ERROR|: ADD only need 2 number!" << std::endl;
						return -1;
					}
				}
				else if (keywords[i] == "SUB") {
					aps_stack.pop();
					try {
						double a = std::stoi(aps_stack.top());
						aps_stack.pop();

						double b = std::stoi(aps_stack.top());
						sum = a - b;
						aps_stack.pop();
						std::string n = aps_stack.top();
						aps_stack.pop();
						var_push(n, std::to_string(sum));
					}
					catch (std::exception& e) {
						std::cerr << "ERROR|: SUB only need 2 number!" << std::endl;
						return -1;
					}
				}
				else if (keywords[i] == "MUL") {
					aps_stack.pop();
					try {
						double a = std::stoi(aps_stack.top());
						aps_stack.pop();
						double b = std::stoi(aps_stack.top());
						sum = a * b;
						aps_stack.pop();
						std::string n = aps_stack.top();
						aps_stack.pop();
						var_push(n, std::to_string(sum));
					}
					catch (std::exception& e) {
						std::cerr << "ERROR|: MUL only need 2 number!" << std::endl;
						return -1;
					}
				}
				else if (keywords[i] == "DIV") {
					aps_stack.pop();
					try {
						double a = std::stoi(aps_stack.top());
						aps_stack.pop();

						double b = std::stoi(aps_stack.top());
						sum = a / b;
						aps_stack.pop();
						std::string n = aps_stack.top();
						aps_stack.pop();
						var_push(n, std::to_string(sum));
					}
					catch (std::exception& e) {
						std::cerr << "ERROR|: DIV only need 2 number!" << std::endl;
						return -1;
					}
				}
				else if (keywords[i] == "MOD") {
					aps_stack.pop();
					try {
						int a = std::stoi(aps_stack.top());
						aps_stack.pop();

						int b = std::stoi(aps_stack.top());
						sum = a % b;
						aps_stack.pop();
						std::string n = aps_stack.top();
						aps_stack.pop();
						var_push(n, std::to_string(sum));
					}
					catch (std::exception& e) {
						std::cerr << "ERROR|: MOD only need 2 number!" << std::endl;
						return -1;
					}
				}
				else if (keywords[i] == "EQ") {
					aps_stack.pop();
					try {
						double a = std::stoi(aps_stack.top());
						aps_stack.pop();
						double b = std::stoi(aps_stack.top());
						aps_stack.pop();
						if (a == b) {
							sum = 1;
						}
						else {
							sum = 0;
						}
						std::string n = aps_stack.top();
						aps_stack.pop();
						var_push(n, std::to_string(sum));
					}
					catch (std::exception& e) {
						std::cerr << "ERROR|: EQ only need 2 number!" << std::endl;
						return -1;
					}

				}
				else if (keywords[i] == "print") {
					aps_stack.pop();
					if (aps_stack.empty()) {
						std::cerr << "print can`t appear alone at line" << std::endl;
						return -1;
					}
					else {
						std::string ss = aps_stack.top();
						aps_stack.pop();
						if (ss[0] == '@') { ss.erase(0, 1); }
						else { std::cout << ss; }
					}
				}
				else if (keywords[i] == "input") {
					aps_stack.pop();
					std::string ss = aps_stack.top();
					aps_stack.pop();
					if (ss[0] != '$') {
						std::cerr << "Your var` first char need to use '$'";
						return -1;
					}
					std::string sv;
					std::cin >> sv; //用户输入
					var_push(ss, sv);
				}
				else if (keywords[i] == "var") {
					aps_stack.pop();
					std::string var_value = aps_stack.top();
					aps_stack.pop();
					std::string var_name = aps_stack.top();
					var_push(var_name, var_value);//定义变量
				}
			}
		}
	}
	file.close();
	return 0;
}
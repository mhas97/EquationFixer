#pragma once
#include "LinkedList.h"
#include <string>
#include <iostream>

class Fixer
{
protected:
	bool isOperator(const char& c);
	int getPrecedence(const char& c);
	void digitsHandler(std::string& digits, std::string& postfixed);
	void fixCleaner(std::string& digits, LinkedList<char>* ll, std::string& postfixed);

public:
	std::string insertValues(std::string expression);
	virtual std::string fix(std::string expression) = 0;
	virtual int evaluate(std::string expression) = 0;
};
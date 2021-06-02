#include "Fixer.h"
#include <map>

//Checks a given character to see if it is an operator.
bool Fixer::isOperator(const char& c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
	{
		return true;
	}
	return false;
}

//Checks a given operator and returns its precedence.
//The cases it will drop out of the switch statement
//are when given NULL (empty stack) or an open bracket, 
//in which case returning 0 handles this safely.
int Fixer::getPrecedence(const char& c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	}
	return 0;
}

//Allows the user to assign integer values to variables
//within an expression. Loops for each variable in the expression 
//until a valid number is assgined to it. This is finally
//converted to a string for evaluation purposes
std::string Fixer::insertValues(std::string expression)
{
	//Map a character (variable) to a value
	std::map<char, std::string> seen;
	std::string toEvaluate = "";
	for (int i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];
		//---HANDLE VARIABLES---//
		//If an alphabet character (variable) is found, ask the user to assign
		//a number to it. If an invalid number is added, clear the flag, ignore
		//any trailing characters and ask the user to try again.
		if (std::isalpha(c) && seen.count(c) ==0)
		{
			std::string val;
			std::cout << "What value is '" << expression[i] << "' equal to?: ";
			std::cin >> val;
			while (val.find(".") != std::string::npos)
			{
				std::cout << "Please do not enter decimal values: ";
				std::cin >> val;
			}
			toEvaluate += val;
			//Insert unseen variables to the map with its associated value
			seen.insert(std::pair<char, std::string>(c, val));
		}
		else if (seen.count(c) > 0)
		{
			//If we have seen the variable before, retrieve its value
			toEvaluate += seen[c];
		}
		//Spaces, digits, decimals and operands are all appended to the evaluation string.
		else
		{
			toEvaluate += c;
		}
	}
	return toEvaluate;
}

//Upon termination of a string of digits, this function
//handles appending to the postfixed string.
void Fixer::digitsHandler(std::string& digits, std::string& postfixed)
{
	if (digits != "")
	{
		digits += ' ';
		postfixed += digits;
		digits = "";
	}
}

//Handle remaining digits and stack operators
void Fixer::fixCleaner(std::string& digits, LinkedList<char>* ll, std::string& postfixed)
{
	//handle any remaining digits in digits substring
	digitsHandler(digits, postfixed);
	//append remaining stack operators
	while (!ll->isEmpty())
	{
		postfixed += ll->pop();
		postfixed += ' ';
	}
	//delete final unnecessary space
	postfixed.pop_back();
}

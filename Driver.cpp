#include "Postfixer.h"
#include "Prefixer.h"
#include <iostream>

//Count the number of integers in an expression.
int getNumberOfIntegers(std::string infix)
{
	int count = 0;
	for (int i = 0; i < infix.length(); ++i)
	{
		//If a digit is found, inner loop to the end of its digits.
		if (std::isdigit(infix[i]))
		{
			++count;
			for (int j = i + 1; j < infix.length(); ++j)
			{
				if (!std::isdigit(infix[i]))
				{
					//Break once the last digit is found.
					break;
				}
				//Continue from the end of the last integer.
				i = j;
			}
		}
	}
	return count;
}

//Take a yes/no decision.
std::string getUserChoice()
{
	std::string choice;
	std::cin >> choice;
	while (choice != "y" && choice != "n")
	{
		std::cout << "Please enter either y or n: ";
		std::cin >> choice;
	}
	return choice;
}

//Display help info.
void showHelp()
{
	std::cout << "\n***---HELP---***\n";
	std::cout << "- An infix expression is one where the operators are in between their operands, ex. a * b + c\n";
	std::cout << "- This calculator only accepts up to a maximum of 4 integer values\n";
	std::cout << "- If the infix contains variables, ex. a + 2, the program will ask for substitution before evaluation\n";
	std::cout << "- This calculator requires bracket multiplication to include a '*' operator, ex. a * (b + c)\n";
	std::cout << "- Space formatting does not matter, ex. a + b * c == a+b*c\n";
	std::cout << "Please enter a valid infix expression, or alternatively enter 'h for help: ";
}

int main()
{
	std::cout << "Welcome!\n\n";
	std::cout << "This program converts an infix expression to its postfix/prefix equivalent.\n";
	std::cout << "It can also evaluate expressions from both prefix and postfix notation.\n\n";
	bool playing = true;
	//---PROGRAM LOOP---//
	do
	{
		//---TAKE INFIX---//
		//Ask the user for an infix expression or request help.
		std::cout << "Please enter a valid infix expression, or alternatively enter 'h' for help: ";
		std::string infix;
		std::getline(std::cin, infix);
		//Show help, or reject empty expressions, decimal values and expressions with too many integers.
		while (infix == "h" || infix == "" || infix.find(".") != std::string::npos || getNumberOfIntegers(infix) > 4)
		{
			if (infix[0] == 'h') {
				showHelp();
			}
			else if (infix == "") {
				std::cout << "Please do not enter an empty expression: ";
			}
			else if (infix.find(".") != std::string::npos) {
				std::cout << "Please do not enter decimal values: ";
			}
			else {
				std::cout << "Please enter an expression with no more than 4 integer values: ";
			}
			std::getline(std::cin, infix);
		}

		//---FIX THE EXPRESSION---//
		//Take the users choice of postfix/prefix, create fixer object and post/prefix the expression.
		std::cout << "You have entered the infix expression: " << infix << "\n\n";
		std::cout << "Please enter which notation you wish to convert to (postfix/prefix): ";
		Fixer* f;
		std::string fixChoice;
		std::string p;
		std::cin >> fixChoice;
		while (fixChoice != "postfix" && fixChoice != "prefix") {
			std::cout << "Sorry I do not recognise this notation, please enter either prefix or postfix: ";
			std::cin >> fixChoice;
		}
		if (fixChoice == "postfix") 
		{
			f = new Postfixer();	//Allocate memory for postfixer.
			p = "post";
		}
		else 
		{
			f = new Prefixer();	//Allocate memory for prefixer.
			p = "pre";
		}
		std::string fixed = f->fix(infix);
		std::cout << "Your " << p << "fixed expression is: " << fixed << "\n\n";

		//---EVALUATION---//
		//Ask if the user wants to evaluate the expression.
		std::cout << "Do you wish to evaluate this expression? y/n: ";
		if (getUserChoice() == "y")
		{
			std::string toEval = f->insertValues(fixed);	//Check if variables need substituting
			int eval = f->evaluate(toEval);
			std::cout << "Your fixed expression [" << toEval << "], evaluates to: " << eval << "\n";
		}
		delete f;	//Deallocate memory.

		//---END OF CALCULATOR---//
		std::cout << "Do you wish to have another go? y/n: ";
		if (getUserChoice() == "n")
		{
			playing = false;
		}
		std::cout << "\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (playing == true);
}
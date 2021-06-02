#include "Prefixer.h"
#include "LinkedList.h"
#include <string>

//Reverses a given expression using a stack, used
//for prefixing. Note brackets are not swapped here, 
//this is instead handled while fixing the expression.
std::string Prefixer::reverseExpression(std::string expression)
{
	std::string reversed = "";
	LinkedList<char>* stringReverser = new LinkedList<char>(expression.length());
	for (int i = 0; i < expression.length(); ++i)
	{
		stringReverser->push(expression[i]);
	}
	for (int i = 0; i < expression.length(); ++i)
	{
		reversed += stringReverser->pop();
	}
	return reversed;
}

//This function is a modified version of a postfixer. It
//Handles left to right operator associativity as well as 
//brackets and formatting.
std::string Prefixer::modifiedPostfixer(std::string expression)
{
	std::string postfixed = "";
	std::string digits = "";
	LinkedList<char>* postfixer = new LinkedList<char>(expression.length());	//stack could never be larger than expression length
	for (int i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];

		//---HANDLE DIGITS & ALPHABET CHARACTERS---//
		//digits are appended to the digits substring and variable appended to the postfix string.
		if (std::isdigit(c))
		{
			digits += c;
		}
		else if (std::isalpha(c))
		{
			postfixed += c;
			postfixed += ' ';
		}

		//---HANDLE OPERATORS---//
		//An operator signals that any string of digits has ended, digitsHandler deals with this.
		else if (isOperator(c))
		{
			digitsHandler(digits, postfixed);

			//---HANDLE BRACKETS---//
			//Brackets are handled by pushing open brackets and upon finding a close bracket,
			//popping until a matching open bracket is found. Brackets are not included in the
			//final postfix string. In this function brackets are switched due to string reversal.
			if (c == ')')
			{
				postfixer->push(c);
			}
			else if (c == '(')
			{
				while (postfixer->peek() != ')')
				{
					postfixed += postfixer->pop();
					postfixed += ' ';
				}
				postfixer->pop();
			}
			else
			{
				//---HANDLE OPERATORS---//
				//Stack operators of greater than or equal precedence to the current operator
				//are popped. When this is no longer true or the stack is empty, the current operator
				//is pushed.
				while (getPrecedence(c) < getPrecedence(postfixer->peek()) && postfixer->peek() != '(')
				{
					postfixed += postfixer->pop();
					postfixed += ' ';
				}
				postfixer->push(c);
			}
		}
	}
	//---CLEAN UP---//
	//Any remaining digits digits and stack operators are appended to the postfix string,
	//the stack memory is deallocated and postfix string returned.
	fixCleaner(digits, postfixer, postfixed);
	delete postfixer;
	return postfixed;
}

//This prefixer function operates by an initial call to the
//reverse function, this resulting expression is then
//postfixed via the modified postfixer. Another call to 
//reverse on this postfixed expression results in a completed 
//prefix representation. 
std::string Prefixer::fix(std::string expression)
{
	std::string reversedExpression = reverseExpression(expression);
	std::string postfixed = modifiedPostfixer(reversedExpression);;
	std::string prefixed = reverseExpression(postfixed);
	return prefixed;
}

//For each character, uses stack methods (pop, push and peek) 
//to evaluate a given prefix expression
int Prefixer::evaluate(std::string expression)
{
	std::string digits = "";
	LinkedList<int>* evaluator = new LinkedList<int>(expression.length());	//create linked list of floats
	for (int i = expression.length() - 1; i >= 0; --i)
	{
		char c = expression[i];

		//---HANDLE OPERATORS---//
		//Pop 2 operands and perform the operation on them. Push answer to stack.
		if (isOperator(c))
		{
			int x = evaluator->pop();
			int y = evaluator->pop();
			switch (expression[i])
			{
			case '+':
				evaluator->push(x + y);
				break;
			case '-':
				evaluator->push(x - y);
				break;
			case '*':
				evaluator->push(x * y);
				break;
			case '/':
				evaluator->push(x / y);
				break;
			case '^':
				evaluator->push(pow(x, y));
			}
		}
		//---HANDLE DIGITS---//
		//Append digits to the digit string. When a space is found, any potential 
		//string if digits is terminated. To handle this, convert the digits string 
		//to an int (if populated) and push it to the stack.
		else if (std::isdigit(c))
		{
			digits += c;
		}
		else
		{
			if (digits != "")
			{
				reverse(digits.begin(), digits.end());
				evaluator->push(std::stoi(digits));
				digits = "";
			}
		}
	}
	//Answer is at the the remaining node on the stack. Deallocate stack memory.
	int eval = evaluator->pop();
	return eval;
	delete evaluator;
}
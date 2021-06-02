#include "Postfixer.h"
#include "LinkedList.h"

//Takes an expression in string format and for each character
//uses stack methods (pop, push and peek) to produce a postfix 
//representation. This function handles formatting by at first 
//removing spaces and then inserting them when the postfix string
//is appended. This allows for future evaluation of multi-digit integers
//and format control of any given expression.
std::string Postfixer::fix(std::string expression)
{
	std::string postfixed = "";	//postfixed string to return
	std::string digits = "";	//digits substring
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
			//final postfix string.
			if (c == '(')
			{
				postfixer->push(c);
			}
			else if (c == ')')
			{
				while (postfixer->peek() != '(')
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
				while (getPrecedence(c) <= getPrecedence(postfixer->peek()) && postfixer->peek() != '(')
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

//For each character, uses stack methods (pop, push and peek) 
//to evaluate a given postfix expression
int Postfixer::evaluate(std::string expression)
{
	std::string digits = "";
	LinkedList<int>* evaluator = new LinkedList<int>(expression.length());	//create linked list of floats
	for (int i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];

		//---HANDLE OPERATORS---//
		//Pop 2 operands and perform the operation on them. Push answer to stack.
		if (isOperator(expression[i]))
		{
			int x = evaluator->pop();
			int y = evaluator->pop();
			switch (expression[i])
			{
			case '+':
				evaluator->push(y + x);
				break;
			case '-':
				evaluator->push(y - x);
				break;
			case '*':
				evaluator->push(y * x);
				break;
			case '/':
				evaluator->push(y / x);
				break;
			case '^':
				evaluator->push(pow(y, x));
			}
		}
		//---HANDLE DIGITS---//
		//Append digits to the digit string. When a space is found, any potential 
		//string of digits is terminated. To handle this, convertthe digits string 
		//to an int (if populated) and push it to the stack.
		else if (std::isdigit(c) || c == '.')
		{
			digits += c;
		}
		else
		{
			if (digits != "")
			{
				evaluator->push(std::stoi(digits));
				digits = "";
			}
		}
	}
	//Answer is at the the remaining node on the stack. Deallocate stack memory.
	int eval = evaluator->pop();
	delete evaluator;
	return eval;
}
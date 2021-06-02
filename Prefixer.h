#pragma once
#include "Fixer.h"

class Prefixer : public Fixer
{
private:
	std::string reverseExpression(std::string expression);
	virtual std::string modifiedPostfixer(std::string expression);
	std::string fix(std::string expression) override;
	virtual int evaluate(std::string expression) override;
};

#pragma once
#include "Fixer.h"

class Postfixer : public Fixer
{
private:
	virtual std::string fix(std::string expression) override;
	virtual int evaluate(std::string expression) override;
};


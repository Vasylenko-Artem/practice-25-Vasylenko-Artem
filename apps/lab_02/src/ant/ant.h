#pragma once

class Ant
{
public:
	double x = 0;
	double y = 0;
	double V = 0;

	virtual void update() = 0;
	virtual void print() = 0;

	virtual ~Ant() {}
};

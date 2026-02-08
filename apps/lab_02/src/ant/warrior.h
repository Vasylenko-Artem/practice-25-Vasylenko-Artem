#pragma once

#include "ant.h"

class WarriorAnt : public Ant
{
private:
	double R;
	double angle = 0;

public:
	WarriorAnt(double r, double v);
	void update() override;
	void print() override;
};

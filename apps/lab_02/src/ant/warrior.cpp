#include "warrior.h"

#include <iostream>
#include <mutex>

#include "common.h"

WarriorAnt::WarriorAnt(double r, double v)
{
	R = r;
	V = v;
}

void WarriorAnt::update()
{
	angle += V;
	x = R * cos(angle);
	y = R * sin(angle);
}

using namespace std;

void WarriorAnt::print()
{
	safePrint("[Warrior] x=" + to_string(x) + " y=" + to_string(y));
}

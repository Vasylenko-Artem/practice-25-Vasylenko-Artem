#pragma once

#include "ant.h"

class WorkerAnt : public Ant
{
private:
	double startX, startY;
	bool toHome = true;

public:
	WorkerAnt(double sx, double sy, double v);
	void update() override;
	void print() override;
};

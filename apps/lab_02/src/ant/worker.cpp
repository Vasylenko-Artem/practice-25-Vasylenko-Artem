#include "ant.h"
#include "worker.h"
#include "common.h"
#include <cmath>

WorkerAnt::WorkerAnt(double sx, double sy, double v)
{
	x = sx;
	y = sy;
	startX = sx;
	startY = sy;
	V = v;
}

void WorkerAnt::update()
{
	double dx = toHome ? -x : (startX - x);
	double dy = toHome ? -y : (startY - y);

	double len = sqrt(dx * dx + dy * dy);

	if (len < 0.05)
		toHome = !toHome;

	if (len > 0)
	{
		x += (dx / len) * V;
		y += (dy / len) * V;
	}
}

using namespace std;

void WorkerAnt::print()
{
	safePrint("[Worker] x=" + to_string(x) + " y=" + to_string(y));
}

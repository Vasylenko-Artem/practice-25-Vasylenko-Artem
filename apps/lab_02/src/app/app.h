#pragma once

#include <thread>
#include "ant/ant.h"
#include "ant/worker.h"
#include "ant/warrior.h"

class App
{
public:
	void run();

private:
	void simulate(Ant *ant);

	WorkerAnt worker{5.0, 5.0, 0.1};
	WarriorAnt warrior{1.0, 1.0};
};

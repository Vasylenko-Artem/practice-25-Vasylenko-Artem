#include <thread>
#include <chrono>

#include "ant/ant.h"
#include "ant/worker.h"
#include "ant/warrior.h"

using namespace std;

void simulate(Ant *ant)
{
	while (true)
	{
		ant->update();
		ant->print();

		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

int main()
{
	WorkerAnt worker(5.0, 5.0, 0.1);
	WarriorAnt warrior(1.0, 1.0);

	thread t1(simulate, &worker);
	thread t2(simulate, &warrior);

	t1.join();
	t2.join();

	return 0;
}

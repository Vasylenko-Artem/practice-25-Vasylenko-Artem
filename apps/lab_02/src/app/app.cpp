#include "app.h"
#include <chrono>

void App::simulate(Ant *ant)
{
	while (true)
	{
		ant->update();
		ant->print();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void App::run()
{
	std::thread t1(&App::simulate, this, &worker);
	std::thread t2(&App::simulate, this, &warrior);

	t1.join();
	t2.join();
}

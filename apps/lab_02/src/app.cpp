#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <chrono>

using namespace std;

mutex mtx;

class Ant
{
public:
	double x = 0;
	double y = 0;
	double V = 0;

	virtual void update() = 0; // чисто віртуальна
	virtual void print() = 0;  // різний print

	virtual ~Ant() {}
};

class WorkerAnt : public Ant
{
private:
	double startX, startY;
	bool toHome = true;

public:
	WorkerAnt(double sx, double sy, double v)
	{
		x = sx;
		y = sy;
		startX = sx;
		startY = sy;
		V = v;
	}

	void update() override
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

	void print() override
	{
		lock_guard<mutex> lock(mtx);
		cout << "[Worker] x=" << x << " y=" << y << endl;
	}
};

class WarriorAnt : public Ant
{
private:
	double R;
	double angle = 0;

public:
	WarriorAnt(double r, double v)
	{
		R = r;
		V = v;
	}

	void update() override
	{
		angle += V;
		x = R * cos(angle);
		y = R * sin(angle);
	}

	void print() override
	{
		lock_guard<mutex> lock(mtx);
		cout << "[Warrior] x=" << x << " y=" << y << endl;
	}
};

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
	WorkerAnt worker(5.0, 3.0, 0.1);
	WarriorAnt warrior(4.0, 0.1);

	thread t1(simulate, &worker);
	thread t2(simulate, &warrior);

	t1.join();
	t2.join();

	return 0;
}

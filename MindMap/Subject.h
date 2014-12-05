#pragma once
#include "IObserver.h"
#include <list>

using namespace std;

class Subject
{
private:
	list<IObserver *> _observers;

public:
	Subject();
	~Subject();
	void attach(IObserver *observer);
	void detach(IObserver *observer);
	void notify();
};

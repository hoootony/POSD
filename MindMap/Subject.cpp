#include "Subject.h"


Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::attach(IObserver *observer) 
{
	_observers.push_back(observer);
}

void Subject::detach(IObserver *observer)
{
	_observers.remove(observer);
}

void Subject::notify()
{
	for (list<IObserver *>::iterator it = _observers.begin(); it != _observers.end(); ++it)
	{
		if (*it != 0)
		{
			(*it)->refreshUI();
		}
	}
}
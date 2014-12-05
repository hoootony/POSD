#pragma once

class IObserver
{
public:
	IObserver();
	virtual ~IObserver();
	virtual void refreshUI() = 0;
};
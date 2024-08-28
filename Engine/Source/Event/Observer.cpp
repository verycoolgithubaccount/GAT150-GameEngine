#include "Observer.h"
#include "EventManager.h"

Observer::~Observer()
{
	REMOVE_OBSERVER;
}

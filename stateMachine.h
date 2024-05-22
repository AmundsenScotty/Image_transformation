#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "states.h"

class StateMachine
{
	State* currentState;
	State* prevState;

public:
	StateMachine();

	void run();
};

#endif

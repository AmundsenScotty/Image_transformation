#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "states.h"

/// Class representing a state machine.
class StateMachine
{
	State* currentState; ///< Pointer to the current state.
	State* prevState; ///< Pointer to the previous state.

public:
	/// Constructor for StateMachine class.
	StateMachine();

	/// Executes the state machine until the current state is nullptr.
	void run();
};

#endif

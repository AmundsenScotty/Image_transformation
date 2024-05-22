#include "stateMachine.h"

/// Constructor for StateMachine class.
StateMachine::StateMachine()
{
	currentState = new Start(); ///< Initializes currentState with the Start state.
	prevState = nullptr; ///< Initializes prevState to nullptr.
}

/// Executes the state machine until the current state is nullptr.
void StateMachine::run()
{
	while (currentState != nullptr)
	{
		bool error = false; ///< Flag to track if an error occurred during state execution.

		try
		{
			currentState->run(); ///< Executes the current state's run function.
		}
		catch (std::exception const& err)
		{
			std::cout << "Hiba: " << err.what() << std::endl; ///< Prints error message.
			std::cout << "Kérem próbálja újra!" << std::endl; ///< Prints a message prompting the user to try again.
			error = true; ///< Sets the error flag to true.

			prompt_next(); ///< Prompts the user to continue by pressing a key.
		}

		if (!error)
		{
			prevState = currentState; ///< Stores the current state in prevState.
			currentState = currentState->next_state(); ///< Updates currentState to the next state.
			delete prevState; ///< Deletes the previous state to prevent memory leaks.
		}
	}
}

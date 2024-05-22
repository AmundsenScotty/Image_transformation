#include "stateMachine.h"

StateMachine::StateMachine()
{
	currentState = new Start();
	prevState = nullptr;
}

void StateMachine::run()
{
	while (currentState != nullptr)
	{
		bool error = false;

		try
		{
			currentState->run();
		}
		catch (std::exception const& err)
		{
			std::cout << "Hiba: " << err.what() << std::endl;
			std::cout << "Kérem próbálja újra!" << std::endl;
			error = true;

			prompt_next();
		}

		if (!error)
		{
			prevState = currentState;
			currentState = currentState->next_state();
			delete prevState;
		}
	}
}
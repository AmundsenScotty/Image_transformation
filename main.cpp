//// Image transformation project

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "states.h"
#include "image.h"
#include "point.h"

#include "gtest_lite.h"
#include "memtrace.h"

template <class T>
void try_fun()
{
    T type_name;

    try
    {
        type_name.run();
    }
	catch (std::exception const& err)
	{
		std::cout << "Hiba: " << err.what() << std::endl;
		std::cout << "Kérem próbálja újra!" << std::endl;
		type_name.restart();
	}
	type_name.next_state();
}

int main()
{
    /// Setting the format fot the output
    #ifdef _WIN32
        SetConsoleOutputCP(1250);
    #endif

    /// Loop for the running through the states
    while(State::getState() != Finish_state)
    {
        switch (State::getState())
        {
        case Start_state:
			try_fun<Start>();
			break;
        case Read_file_state:
            try_fun<Read_file>();
            break;

        case Example_state:
            try_fun<Example>();
			break;

        case Select_corners_state:
			try_fun<Select_corners>();
            break;
        
        case Transform_state:
			try_fun<Transform>();
			break;

        case End_state:
			try_fun<End>();
			break;
        }
    }

    return 0;
}
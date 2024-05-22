//// Image transformation project

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "stateMachine.h"

int main()
{
    /// Setting the format fot the output
    #ifdef _WIN32
        SetConsoleOutputCP(1250);
    #endif

    StateMachine sm;

    sm.run();

    return 0;
}
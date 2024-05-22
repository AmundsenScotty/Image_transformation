#ifndef STATES_H
#define STATES_H

#include "image.h"


//// State class

    /// @brief The base class for all states in the program.
class State
{
    static Image* base; ///< Pointer to the base image.
    static Image* in_progress; ///< Pointer to the in-progress image.
public:
    virtual ~State(); ///< Destructor.
    virtual void run() const = 0; ///< Pure virtual function to execute the state's functionality.
    virtual State* next_state() const = 0; ///< Pure virtual function to determine the next state.

    static Image* getBase(); ///< Getter for the base image pointer.
    static void setBase(Image* ip); ///< Setter for the base image pointer.
    static Image* getInProgress(); ///< Getter for the in-progress image pointer.
    static void setInProgress(Image* ip); ///< Setter for the in-progress image pointer.
};

////


//// Start class

    /// @brief Represents the start state of the program.
class Start : public State
{
    static unsigned choice; ///< Static member variable to store the user's choice.
public:
    Start(); ///< Constructor.

    void run() const override; ///< Overrides the base class's run function.
    State* next_state() const override; ///< Overrides the base class's next_state function.
};

////


//// Read_file class

    /// @brief Represents the state for reading a file.
class Read_file : public State
{
public:
    void run() const override; ///< Overrides the base class's run function.
    State* next_state() const override; ///< Overrides the base class's next_state function.
};

////


/// Example class

    /// @brief Represents the example state.
class Example : public State
{
public:
    void run() const override; ///< Overrides the base class's run function.
    State* next_state() const override; ///< Overrides the base class's next_state function.
};

////


//// Select_corners class

    /// @brief Represents the state for selecting corners.
class Select_corners : public State
{
public:
    void run() const override; ///< Overrides the base class's run function.
    State* next_state() const override; ///< Overrides the base class's next_state function.
};

////


//// Transform class

    /// @brief Represents the transformation state.
class Transform : public State
{
public:
    void run() const override; ///< Overrides the base class's run function.
    State* next_state() const override; ///< Overrides the base class's next_state function.
};

////


//// End class

    /// @brief Represents the end state of the program.
class End : public State
{
public:
    ~End(); ///< Destructor.

    void run() const override; ///< Overrides the base class's run function.
    State* next_state() const override; ///< Overrides the base class's next_state function.
};

////


//// Prompt next

    /// @brief Prompts the user to continue by pressing a key.
void prompt_next();

////

#endif

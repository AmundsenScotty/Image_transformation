#ifndef STATES_H
#define STATES_H

#include "image.h"

#include "gtest_lite.h"
#include "memtrace.h"

//// State names

    enum States
    {
        Start_state,
        Read_file_state,
        Example_state,
        Select_corners_state,
        Transform_state,
        End_state,
        Finish_state
    };

////


//// State class

    class State
    {
        static enum States currentState;
        static Image* base;
        static Image* in_progress;
    public:
        virtual ~State();
        virtual void run() const = 0;
        virtual void restart() const;
        virtual void next_state() const = 0;

        static Image* getBase();
        static void setBase(Image* ip);
        static Image* getInProgress();
        static void setInProgress(Image* ip);

        static unsigned getState();
        static void setState(enum States s);
    };

////


//// Start class

    class Start : public State
    {
        static unsigned choice;
    public:
        Start();

        void run() const override;
        void restart() const override;
        void next_state() const override;
    };

////


//// Read_file class

    class Read_file : public State
    {
    public:
        void run() const override;
        void restart() const override;
        void next_state() const override;
    };

////


/// Example class

    class Example : public State
    {
    public:
	    void run() const override;
	    void restart() const override;
	    void next_state() const override;
    };

////


//// Select_corners class

    class Select_corners : public State
    {
    public:
	    void run() const override;
	    void restart() const override;
	    void next_state() const override;
    };

////


//// Transform class

    class Transform : public State
    {
    public:
	    void run() const override;
	    void restart() const override;
	    void next_state() const override;
    };

////


//// End class

    class End : public State
    {
    public:
        ~End();

	    void run() const override;
	    void restart() const override;
	    void next_state() const override;
    };

////

#endif

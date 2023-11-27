#pragma once
#include "processState.h"

using namespace std;

class Process
{
private:
    processState state;
    int PID;
    int AT;
    int RT;
    int CT;
    int TT;
    int remainingTime;

public:

    Process(int PID, int arrivalTime, int cpuTime) 
    {
        this -> PID = PID;
        this -> AT = arrivalTime;
        this -> CT = cpuTime;
        this -> state = processState::NEW;
        this -> remainingTime = cpuTime;
    }

    void setProcessState(processState s)
    {
        this -> state = s;
    }

    processState getProcessState() const
    {
        return this -> state;
    }


    int getPID() const
    {
        return this -> PID;
    }

    int getArrivalTime() const
    {
        return this -> AT;
    }

    void setArrivalTime(int AT)
    {
        this -> AT = AT;
    }

    int getCpuTime() const
    {
        return this -> CT;
    }

    void setCpuTime(int CT)
    {
        this -> CT = CT;
    }

    int getRemainingTime() const
    {
        return this -> remainingTime;
    }

    void setRemainingTime(int RT)
    {
        this -> remainingTime = RT;
    }
};


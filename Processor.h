#pragma once
#include "linkedListADT.h"
#include "Process.h"
#include "processorState.h"
#include <string>
using namespace std;

class Processor
{
    string type; //processor type: FCFS - SJF - RR
    processorState state; //processor state: IDLE - BUSY
    Process* process; //current process
    int sliceConstant; //slice constant time
    linkedListADT<Process*> listofProcesses; //processes' list

public:

    virtual Process* ScheduleAlgo() = 0; //Schedule Algorithm

    virtual void setProcessorType(string t) 
        // A virtual function is a member function in the base class that we 
        //expect to redefine in derived classes. Basically, a virtual function is 
        //used in the base class in order to ensure that the function is overridden. 
        //This especially applies to cases where a pointer of base class points to an 
        //object of a derived class.
    {
        this -> type = t;
    }

    virtual string getProcessorType()
    {
        return this -> type;
    }

    virtual void setProcessorState(processorState state)
    {
        this -> state = state;
    }

    virtual processorState getProcessorState()
    {
        return this -> state;
    }

    virtual void setCurrentProcess(Process* p)
    {
        if (p != nullptr)
            this -> state = processorState::BUSY;
        else
            this -> state = processorState::IDLE;
        this -> process = p;
    }

    virtual Process* getCurrentProcess()
    {
        return this -> process;
    }

    virtual void RUN()
    {
        Process* currentProcess = getCurrentProcess();
        if (currentProcess == NULL) {
            return;
        }
        setProcessorState(processorState::BUSY);

        //generates a random number from 1 to 100
        int num = rand() % 100 + 1;
        if (num >= 1 && num <= 15)
        {
            setCurrentProcess(nullptr);
            currentProcess -> setProcessState(processState::BLK);
        }

        if (num >= 20 && num <= 30)
        {
            setCurrentProcess(NULL);
            listofProcesses.addNode(currentProcess);
            currentProcess -> setProcessState(processState::RDY);
        }

        if (num >= 50 && num <= 60)
        {
            setCurrentProcess(nullptr);
            currentProcess -> setProcessState(processState::TRM);
        }
    }

    virtual void setSliceConstant(int sliceTimeRR)
    {
        this -> sliceConstant = sliceTimeRR;
    }

    virtual void addProcess2List(Process* p)
    {
        listofProcesses.addNode(p);
    }

    virtual linkedListADT<Process*>* getProcessesList()
    {
        return &listofProcesses;
    }
};
#pragma once
#include <iostream>
#include "Processor.h"

class ProcessorFCFS : public Processor
{
public:

	ProcessorFCFS() //constructor for the FCFS processor
	{
		this -> setProcessorType("FCFS");
	}

	Process* ScheduleAlgo() override
	{
		if (this -> getProcessesList() -> isEmpty())
			return NULL;
		Process* process = this -> getProcessesList() -> getItem(0);
		this -> getProcessesList() -> removeNode(process);
		return process;
	}

	~ProcessorFCFS() //destructor for the FCFS processor
	{
	}
};
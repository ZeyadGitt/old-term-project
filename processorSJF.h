#pragma once
#include <iostream>
#include "Processor.h"

class ProcessorSJF : public Processor
{
public:

	ProcessorSJF() //constructor for the SJF processor
	{
		this -> setProcessorType("SJF");
	}
	Process* ScheduleAlgo() override
	{
		if (this -> getProcessesList() -> isEmpty())
			return NULL;
		Process* process = this -> getProcessesList() -> getItem(0);
		this -> getProcessesList() -> removeNode(process);
		return process;
	}

	~ProcessorSJF() //destructor for the SJF processor
	{
	}
};
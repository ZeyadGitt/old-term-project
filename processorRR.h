#pragma once
#include "Processor.h"

class ProcessorRR : public Processor
{
public:

	ProcessorRR(int sliceTimeRR) //constructor for the RR processor
	{
		this -> setProcessorType("RR");
		this -> setSliceConstant(sliceTimeRR);
	}

	Process* ScheduleAlgo() override
	{
		if (this -> getProcessesList() -> isEmpty())
			return nullptr;
		Process* process = this -> getProcessesList() -> getItem(0);
		this -> getProcessesList() -> removeNode(process);
		return process;
	}

	~ProcessorRR() //destructor for the RR processor
	{
	}
};
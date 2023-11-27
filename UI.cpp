//SYS
#include <fstream>
#include <iostream>
#include <sstream>
//A stringstream associates a string object with a stream 
//allowing you to read from the string as if it were a stream (like cin).
#include <string>

//PROCESS
#include "Process.h"

//PROCESSORS
#include "Processor.h"
#include "ProcessorFCFS.h"
#include "ProcessorSJF.h"
#include "ProcessorRR.h"

//DS
#include "linkedListADT.h"

using namespace std;

class UI
{
public:

	void interactiveMode(int currentTime, linkedListADT<Process*>* listofProcesses, linkedListADT<Processor*>* processorsList)
	{
		cout << "Current Timestep: " << currentTime << endl; //prints current timestep
		cout << "------------- RDY Processes -------------" << endl; // prints ready processes
		for (int k = 0; k < processorsList -> getSize(); k++)
		{
			cout << "Processor " << k + 1 << "[" << processorsList -> getItem(k) -> getProcessorType().c_str() << "]: " << processorsList -> getItem(k) -> getProcessesList() -> getSize() << " RDY: ";
			for (int i = 0; i < processorsList -> getItem(k) -> getProcessesList() -> getSize(); i++)
				cout << processorsList -> getItem(k) -> getProcessesList() -> getItem(i) -> getPID();
			cout << '\n';
		}

		cout << "------------- BLK Processes -------------" << endl; //prints BLK processes
		int numberOfBlockedProcesses = 0; string result = "";
		for (int n = 0; n < listofProcesses -> getSize(); n++)
		{
			if (listofProcesses -> getItem(n) -> getProcessState() == processState::BLK)
			{
				numberOfBlockedProcesses++;
				result = result + to_string(listofProcesses -> getItem(n) -> getPID()) + " ";
			}
		}
		cout << numberOfBlockedProcesses << " BLK: " << result << endl;


		cout << "------------- RUN Processes -------------" << endl; //prints RUN processes
		int numberOfRunningProcesses = 0;
		result = "";
		for (int i = 0; i < processorsList -> getSize(); i++)
		{
			if (processorsList -> getItem(i) -> getProcessorState() == processorState::BUSY) // %n RUN: 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
			{
				numberOfRunningProcesses++;
				result  += to_string(processorsList -> getItem(i) -> getCurrentProcess() -> getPID())
					+ "(P" + to_string(i + 1) + ") ";
			}
		}
		cout << numberOfRunningProcesses << " RUN: " << result << endl;

		cout << "------------- TRM Processes -------------" << '\n'; //prints TRM processes
		int numberOfTerminatedProcesses = 0; result = "";
		for (int f = 0; f < listofProcesses -> getSize(); f++)
		{
			if (listofProcesses -> getItem(f) -> getProcessState() == processState::TRM)
			{
				numberOfTerminatedProcesses++;
				result += to_string(listofProcesses -> getItem(f) -> getPID()) + " ";
			}
		}
		cout << numberOfTerminatedProcesses << " TRM: " << result << endl;

		cout << "Press Any Key for Next Timestep..." << endl; //prints user prompt for next timestep
		getchar();
		system("cls");
	};











};
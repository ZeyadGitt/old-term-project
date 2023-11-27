//SYS
#include <fstream>
//The fstream term stands for File Stream. 
//Stream refers to a sequence of characters moving from the disk 
//to the C++ program or from the C+ program to the disk. 
//Moving characters from a file in disk to the program is inputting. 
//Moving characters from the program to a file in the disk is outputting.
#include <random>
#include <string>

//ENUMS
#include "processorState.h"
#include "processState.h"

//DS
#include "linkedListADT.h"

//Process
#include "Process.h"

//Processors
#include "Processor.h"
#include "ProcessorFCFS.h"
#include "ProcessorSJF.h"
#include "ProcessorRR.h"

//UI
#include "UI.cpp"

using namespace std;

void dataLoading(string fileName, linkedListADT<Process*> &listofProcesses, linkedListADT<Processor*> &processors) //loads data from the file and initializes processors and processes
{
	int numofFCFSprocessors = 0; //# of FCFS processors
	int numofSJFprocessors = 0; //# of SJF processors
	int numofRRprocessors = 0; //# of RR processors
	int sliceTimeRR = 0; //Slice Time for RR
	int numofProcesses = 0; //# of processes
	float rtf = 0; // RTF
	float maxw = 0; //max. waiting time
	float stl = 0; //stealing limit > 0.4
	float fp = 0; //fork probability

	ifstream file(fileName); //open file stream
	if (!file.is_open()) {
		throw exception("File not found!");
		return;
	}

	file >> numofFCFSprocessors >> numofSJFprocessors >> numofRRprocessors; //#FCFS Processors, #SJF Processors, #RR Processors 
	file >> sliceTimeRR; //slice time for RR
	file >> rtf >> maxw >> stl >> fp; //RTF, MaxW, STL, FP
	file >> numofProcesses; //number of processes 
	
	int process_PID = 0;
	int process_ArrivalTime = 0;
	int process_CPUTime = 0;
	int process_IORequests = 0;

	for (int i = 0; i < numofProcesses; i++) //loops through the processes then adds them to the processes list
	{
		file >> process_ArrivalTime >> process_PID >> process_CPUTime >> process_IORequests;
		listofProcesses.addNode(new Process(process_PID, process_ArrivalTime, process_CPUTime));
	}
	file.close();

	for (int i = 0; i < numofFCFSprocessors; i++) //initialization of FCFS processors 
		processors.addNode(new ProcessorFCFS());

	for (int j = 0; j < numofSJFprocessors; j++) //initialization of SJF processors
		processors.addNode(new ProcessorSJF());

	for (int k = 0; k < numofRRprocessors; k++) //initialization of RR processors
		processors.addNode(new ProcessorRR(sliceTimeRR));
}

void startSimulation(int currentTime, linkedListADT<Process*> &listofProcesses, linkedListADT<Processor*> &processors, UI &ui)
{
	while (1) 
	{
		for (int i = 0; i < listofProcesses.getSize(); i++) //adds processes to the RDY list (if they arrive at the current time)
		{
			if (listofProcesses.getItem(i) -> getArrivalTime() == currentTime) 
				processors.getItem(i % processors.getSize()) -> addProcess2List(listofProcesses.getItem(i));
		}

		for (int i = 0; i < processors.getSize(); i++) //if idle: move one process from each RDY list to RUN state
		{
			if (processors.getItem(i) -> getProcessorState() == processorState::IDLE) //if idle: move one process from each RDY list to RUN state
			{
				Process* process = processors.getItem(i) -> ScheduleAlgo(); 
				if (process != nullptr) 
				{
					process -> setProcessState(processState::RUN);
					processors.getItem(i) -> setCurrentProcess(process);
					processors.getItem(i) -> RUN();
				}
			}
			else 
				processors.getItem(i) -> RUN();
		}

		for (int i = 0; i < listofProcesses.getSize(); i++) //(0 <= num < 100 and num < 10) : move the process from BLK to RDY
		{
			if (listofProcesses.getItem(i) -> getProcessState() == processState::BLK) 
			{
				if (rand() % 100 < 10) 
				{
					listofProcesses.getItem(i) -> setProcessState(processState::RDY);
					processors.getItem(rand() % processors.getSize()) -> addProcess2List(listofProcesses.getItem(i)); //adds the process to the RDY list of a random processor 
				}
				break;
			}
		}

		for (int i = 0; i < processors.getSize(); i++) //terminates a random process if found from the FCFS processor 
		{
			if (processors.getItem(i) -> getProcessorType()._Equal("FCFS")) 
			{
				if (processors.getItem(i) -> getProcessesList() -> getSize() == 0) 
					continue;
				int random = rand() % processors.getItem(i) -> getProcessesList() -> getSize();
				processors.getItem(i) -> getProcessesList() -> getItem(random) -> setProcessState(processState::TRM);
				processors.getItem(i) -> getProcessesList() -> removeNode(listofProcesses.getItem(random));
				break;
			}
		}

		ui.interactiveMode(currentTime, &listofProcesses, &processors); //passing by reference - displays the current state of the simulation
		currentTime += 1; //increments the current time
		bool allprocessesTerminated = true; //checks if all processes are halted
		for (int i = 0; i < listofProcesses.getSize(); i++) 
		{
			if (listofProcesses.getItem(i) -> getProcessState() != processState::TRM) 
			{
				allprocessesTerminated = false;
				break;
			}
		}

		if (allprocessesTerminated)  //if successful termination for all processes : end simulation
			exit(0);
	}
}

int main()



{
	int currentTime = 0;
	linkedListADT<Process*> listofProcesses = linkedListADT<Process*>();
	linkedListADT<Processor*> processors = linkedListADT<Processor*>();
	UI ui = UI();
	dataLoading("IP.txt", listofProcesses, processors);
	startSimulation(currentTime, listofProcesses, processors, ui);
}
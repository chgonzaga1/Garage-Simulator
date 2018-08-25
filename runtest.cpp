//Christian Gonzaga
//CSC 326 Lab 4


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "simulator.h"


using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers,
	int& transTime,
	int& tBetweenCArrival);

bool isCustomerArrived(double arvTimeDiff);

void generateStatistics(serverList& server,
	waitingCustomerQueueType& CQueue,//sets up CQueue
	int numOfCustArrived,
	int waitTimeServedCustomers);
void runSimulation();

int main()
{
	runSimulation();

	return 0;
}

void setSimulationParameters(int& sTime, int& numOfServers,
	int& transTime,
	int& tBetweenCArrival)
{
	cout << "Enter the test run time: " << flush;
	cin >> sTime;
	cout << endl;

	cout << "Enter the number of servers: " << flush;
	cin >> numOfServers;
	cout << endl;

	cout << "Enter the transaction time: " << flush;
	cin >> transTime;
	cout << endl;

	cout << "Enter the time between customers arrival: " << flush;
	cin >> tBetweenCArrival;
	cout << endl;
}

bool isCustomerArrived(double arvTimeDiff)
{
	double value;

	value = static_cast<double> (rand()) / static_cast<double>(RAND_MAX);

	return (value > exp(-1.0 / arvTimeDiff));
}

void runSimulation()
{
	int simulationTime;
	int numberOfServers;
	int transactionTime;
	int timeBetweenCustomerArrival;

	waitingCustomerQueueType customerQueue;

	customer customerPPL;

	int custNumber = 0;

	int totalWaitTimeServedCustomers = 0;
	int totalWaitTime = 0;
	int numberOfCustomersServed = 0;
	int customersLeftInServers = 0;
	int clock = 0;
	int serverID;

	setSimulationParameters(simulationTime, numberOfServers,
		transactionTime, timeBetweenCustomerArrival);

	serverList serverListPPL(numberOfServers);

	for (clock = 1; clock <= simulationTime; clock++)
	{
		serverListPPL.updateServers(cout);

		if (!customerQueue.IsEmpty())
			customerQueue.updateWaitingQueue();

		if (isCustomerArrived(timeBetweenCustomerArrival))
		{
			custNumber++;
			customerPPL.setCustomerInfo(custNumber, clock, 0,
				transactionTime);
			customerQueue.enqueue(customerPPL);
			cout << "Customer number " << custNumber
				<< " arrived at time unit " << clock << endl;
		}

		serverID = serverListPPL.getFreeServerID();
		if (serverID != -1 && !customerQueue.IsEmpty())
		{
			customerPPL = customerQueue.Front();
			customerQueue.dequeue();
			totalWaitTimeServedCustomers = totalWaitTimeServedCustomers
				+ customerPPL.getWaitingTime();
			serverListPPL.setServerBusy(serverID, customerPPL);
		}
	}

	cout << endl;

	cout << "The simulation ran for " << simulationTime
		<< " time units" << endl;
	cout << "Number of servers: " << numberOfServers << endl;
	cout << "Average transaction time: "
		<< transactionTime << endl;
	cout << "Average arrival time difference between customers: "
		<< timeBetweenCustomerArrival << endl;

	generateStatistics(serverListPPL, customerQueue,
		custNumber, totalWaitTimeServedCustomers);
}

void generateStatistics(serverList& server,
	waitingCustomerQueueType& CQueue,
	int numOfCustArrived,
	int waitTimeServedCustomers)
{
	int customersLeftInQueue = 0;

	int totalWaitTime = waitTimeServedCustomers;

	customer customerPPL;

	while (!CQueue.IsEmpty())
	{
		customerPPL = CQueue.Front();
		CQueue.dequeue();
		totalWaitTime = totalWaitTime + customerPPL.getWaitingTime();
		customersLeftInQueue++;
	}

	//Find number of customers left in servers
	int numberOfServers;
	serverList serverListPPL(numberOfServers);
	int customersLeftInServers = serverListPPL.getNumberOfBusyServers();
	//Find number of customers completely served
	int numberOfCustomersServed = numOfCustArrived - customersLeftInServers -
		customersLeftInQueue;

	double averageWaitTime = 0;

	cout << "Total waiting time: " << totalWaitTime << endl;
	cout << "Number of customers that completed a transaction: "
		<< numberOfCustomersServed << endl;
	cout << "Number of customers left in the servers: "
		<< customersLeftInServers << endl;
	cout << "The number of customers left in queue: " << customersLeftInQueue
		<< endl;

	if (numOfCustArrived > 0)  // If number of customers arrived is > 0
		averageWaitTime = (static_cast<double>(totalWaitTime)) / numOfCustArrived;

	cout << fixed << showpoint;
	cout << setprecision(2);
	cout << "Average waiting time: " << averageWaitTime << endl;
	cout << "Simlution done" << endl;
}
//Christian Gonzaga
//CSC 326 Lab 4


#include <iostream>
#include <string>
#include <cstdlib>
#include "Simulator.h"


using namespace std;

//Implementation of Customer


customer::customer(int customerT, int arrivTime, int wTime, int transTime)
{
	setCustomerInfo(customerT, arrivTime, wTime, transTime);


}

void customer::setCustomerInfo(int customerT, int arrvTime,
	int wTime, int tTime)
{
	customerTally = customerT;
	arrivingTime = arrvTime;
	waitingTime = wTime;
	transactionTime = tTime;
}

void customer::incrementWaitingTime()
{
	waitingTime++;
}

void customer::setWaitingTime(int time)
{
	waitingTime = time;
}

int customer::getWaitingTime() const
{
	return waitingTime;
}

int customer::getArrivalTime() const
{
	return arrivingTime;
}

int customer::getTransactionTime() const
{
	return transactionTime;
}

int customer::getCustomerTally() const
{
	return customerTally;
}

//IMPLEMENTATION OF SERVER CLASS

server::server() // CONSTRUCTOR
{
	status = "currently available";
	transactionTime = 0;
}

bool server::isAvailable() const
{
	return (status == "SERVER IS CURRENTLY AVAILABLE");
}

void server::setBusy()
{
	status = "sorry, the server is busy";
}

void server::setAvailablity()
{
	status = "Server is now available";
}

void server::setTransactionTime(int t)
{
	transactionTime = t;
}

void server::setTransactionTime()
{
	int time;

	time = currentCustomer.getTransactionTime();

	transactionTime = time;
}

void server::decreaseTransactionTime()
{
	transactionTime--;
}

int server::getRemainingTransactionTime() const
{
	return transactionTime;
}

void server::setCurrentCustomer(customer cCustomer)
{
	currentCustomer = cCustomer;
}

int server::getCurrentCustomerTally() const
{
	return currentCustomer.getCustomerTally();
}

int server::getCurrentCustomerArrivalTime() const
{
	return currentCustomer.getArrivalTime();
}

int server::getCurrentCustomerWaitingTime() const
{
	return currentCustomer.getWaitingTime();
}

int server::getCurrentCustomerTransactionTime() const
{
	return currentCustomer.getTransactionTime();
}


serverList::~serverList()
{
	delete[] servers;
}

int serverList::getFreeServerID() const
{
	int serverID = -1;

	int i;

	for (i = 0; i < numOfServers; i++)
	if (servers[i].isAvailable())
	{
		serverID = i;
		break;
	}
	return serverID;
}

int serverList::getNumberOfBusyServers() const
{
	int busyServers = 0;

	int i;

	for (i = 0; i < numOfServers; i++)
	if (!servers[i].isAvailable())
		busyServers++;
	return busyServers;
}

void serverList::setServerBusy(int serverID,
	customer cCustomer,
	int tTime)
{
	servers[serverID].setBusy();
	servers[serverID].setTransactionTime(tTime);
	servers[serverID].setCurrentCustomer(cCustomer);
}

void serverList::setServerBusy(int serverID,
	customer cCustomer)
{
	int time;

	time = cCustomer.getTransactionTime();

	servers[serverID].setBusy();
	servers[serverID].setTransactionTime(time);
	servers[serverID].setCurrentCustomer(cCustomer);
}


void serverList::updateServers(ostream& outFile)
{
	int i;

	for (i = 0; i < numOfServers; i++)
	if (!servers[i].isAvailable())
	{
		servers[i].decreaseTransactionTime();
		if (servers[i].getRemainingTransactionTime() == 0)
		{
			outFile << "Server No: " << (i + 1) << " Customer number "
				<< servers[i].getCurrentCustomerTally()
				<< " departed at " << endl
				<< "             clock unit "
				<< servers[i].getCurrentCustomerArrivalTime()
				+ servers[i].getCurrentCustomerWaitingTime()
				+ servers[i].getCurrentCustomerTransactionTime()
				<< endl;
			servers[i].setAvailablity();
		}
	}
}

//waitQueue 


waitingCustomerQueueType::waitingCustomerQueueType(int size)
:Queue<customer>(size)
{
}

void waitingCustomerQueueType::updateWaitingQueue()
{
	customer cust;

	cust.setWaitingTime(-1);
	int wTime = 0;

	enqueue(cust);//push the customer into the queue

	while (wTime != -1)
	{
		cust = Front();//sets customer back to the front
		dequeue();

		wTime = cust.getWaitingTime();
		if (wTime == -1)
			break;
		cust.incrementWaitingTime();
		enqueue(cust);
	}
}

//Christian Gonzaga
//CSC 326 Lab 4


#include <fstream>
#include <string>
#include "queuea.h"

using namespace std;
//CUSTOMER CLASS

class customer
{
public:
	customer(int cusTally = 0, int arriTime = 0, int waiTime = 0,
		int transTime = 0); //constructor
	void setCustomerInfo(int customerT = 0, int inTime = 0,
		int wTime = 0, int tTime = 0); //setting up the variables
	int getWaitingTime() const;//returns customer's waiting time
	void setWaitingTime(int time);
	void incrementWaitingTime();
	int getArrivalTime() const;
	int getTransactionTime() const;
	int getCustomerTally() const;
private:
	int customerTally;
	int arrivingTime;
	int waitingTime;
	int transactionTime;
};


//SERVER CLASS
class server
{
public:
	server();
	bool isAvailable() const;
	void setBusy();
	void setAvailablity();
	void setTransactionTime(int t);
	void setTransactionTime();
	int getRemainingTransactionTime() const;
	void decreaseTransactionTime();
	void setCurrentCustomer(customer curCustomer);
	//Function to set the info of the current customer 

	int getCurrentCustomerTally() const;
	// return current customer's tally
	int getCurrentCustomerArrivalTime() const;
	int getCurrentCustomerWaitingTime() const;
	int getCurrentCustomerTransactionTime() const;

private:
	customer currentCustomer;
	string status;
	int transactionTime;
};


//SERVER LIST
class serverList
{
public:
	serverList(int num = 1);
	//constructor to initialize a list of servers, which is already done

	~serverList();
	//destructor
	
	int getFreeServerID() const;
	//Function to search the list of servers. 

	int getNumberOfBusyServers() const;
	//Function to return the number of busy servers.
	void setServerBusy(int serverID, customer cCustomer,
		int tTime);

	void setServerBusy(int serverID, customer cCustomer);
	
	void updateServers(ostream& outFile);
	//The transaction time of each busy server is decremented
	//by one unit.


private:
	int numOfServers;
	server *servers;
};


//wait QUEUE

class waitingCustomerQueueType : public Queue<customer>
{
public:
	waitingCustomerQueueType(int size = 100);
	//The queue is initialized according to the

	void updateWaitingQueue();
	//Function to increment the waiting time of each 
	//customer in the queue by one time unit.
};


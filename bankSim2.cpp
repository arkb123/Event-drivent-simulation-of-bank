#include <iostream>
#include "Event.h"
#include <queue>
#include <iomanip>
#include <vector>
#include "Event.h"
#include "Teller.h"
using namespace std;


// void testFunc(const Event &currentEvent, priority_queue<Event, vector<Event>, greater<Event>> &pQ, bool tracker){
//    Event newEv = currentEvent;
//    newEv = pQ.top();
//    cout <<"old:" << newEv.getTime() << endl;
//    cout << newEv.setTime() << endl;
//    cout <<"new:" << newEv.getTime() << endl;
//    pQ.pop();
//    cout << "size:" << pQ.size() << endl;
// }

// bool needSpace = true;

//golbel vars used to reduce the amount of parameters sent to the two functions 
double waitTime = 0; 
//used for Average wait line length
double avgLineSize = 0;
//used for Maximum wait line length
unsigned mWaitLine = 0;
//keep track of the number of transaction
double transaction = 0;
//used for Average transaction time
double avgTrans = 0;


//function used to get the correct teller number
unsigned newT(vector<Teller> myVec)
{

    unsigned tellerNum = 0;
    //using a big number to make sure it is hadded to the end of the Queue
    unsigned departureTime = 99999;
    //bool tarcker = true;
    unsigned temp = myVec.size();

    for (unsigned i = 0; i < temp; i++)
    {
        if (myVec[i].getDepartureTime() < departureTime && myVec[i].getDepartureTime() != 0)
        {
            tellerNum = i;
            departureTime = myVec[i].getDepartureTime();
        }
    }
    return tellerNum;
}
// processArriva function similar to prog 4 with a few changes
// now takes in a vector of tellers
void processArrival(const Event &currentEvent, priority_queue<Event, vector<Event>, greater<Event > > &pQ,vector<Teller> &myVecc, queue<Event> &bankQ)
{ 
    Event customer = currentEvent;
    // poping the priority queue here insted of while loop in the main
    pQ.pop();
    // cout <<"size:" <<  pQ.size() << endl;
    unsigned tempp = myVecc.size();
    for (unsigned i = 0; i < tempp; i++)
    {
       //myVec stores all the Tellers
       //if statement checks if the teller at index i is avaliable
        if (!myVecc[i].isavaliable())
        { 
            // create new Var to store the departure time
            unsigned departureTime = customer.getTime() + customer.getDuration();
            //creating new event of type departure
            Event newDepartureEvent(Event::departure, departureTime, customer.getDuration());
            //sets what teller is helping this customer
            // i is the current teller
            newDepartureEvent.settellerNum(i);
            //push the event into the priority queue
            pQ.push(newDepartureEvent);
            //change the avaliablity of this teller after they have departured their customer
            myVecc[i].setavaliable(true);
            //TT = trans time
            myVecc[i].addTT(newDepartureEvent.getDuration());
            //add client function just keeps track of the amount of ppl this teller has helped
            myVecc[i].addClient();
            //DT = dep time
            myVecc[i].setDT(newDepartureEvent.getTime());
            myVecc[i].setCurrentEvent(newDepartureEvent);
            //i + 1 becuause i starts at index 0 insted of 1
            cout << "Teller  " << i + 1 << " processing   arrival event at time:" << setw(5) << customer.getTime() << setw(5) << customer.getDuration() << endl;
            //breaks used to terminate the for loop
            break;
        }
        else if (i == myVecc.size() - 1)
        {
            bankQ.push(customer);
            //breaks used to terminate the for loop
            break;
        }
    }
}

void processDeparture(const Event &currentEvent, priority_queue<Event, vector<Event>, greater<Event > > &pQ,vector<Teller> &myVecc, queue<Event> &bankQ, 
                      unsigned currentTime)
{
    pQ.pop();
    //bool tempp = true;
    //uses the newT function implemented above to get the teller Number
    unsigned tellerNum = newT(myVecc);
    if (!bankQ.empty())
    {
       //set new customer to what evers on top
        Event customer = bankQ.front();
        bankQ.pop();
        //cout <<"front:" << bankQ.front() << endl;
        // cout << "size:" << bankQ.size() << endl;
        //makes sure mWaitLine is always greater
        if (bankQ.size() > mWaitLine){
            mWaitLine = bankQ.size();
        }
        //used to keep track of line size
        avgLineSize += bankQ.size();
        // create new Var to store the departure time
        unsigned departureTime = currentTime + customer.getDuration();
        Event newDepartureEvent(Event::departure, departureTime, customer.getDuration());
        pQ.push(newDepartureEvent);
        cout << "Teller  " << tellerNum + 1 << " processing departure event at time:" << setw(5) << currentTime << endl;
        //stores avg waittime
        waitTime += (currentTime - customer.getTime());
        cout << "Teller  " << tellerNum + 1 << " processing   arrival event at time:" << setw(5) << currentTime << setw(5) << customer.getDuration() << endl;
        //update the all Tellers information here
        myVecc[tellerNum].addClient();
        //adds the transaction time
        myVecc[tellerNum].addTT(newDepartureEvent.getDuration());
        //sets the departure time
        //cout << myVecc[tellerNum].getTime() << endl;
        myVecc[tellerNum].setDT(newDepartureEvent.getTime());
        myVecc[tellerNum].setCurrentEvent(newDepartureEvent);
    }
    else
    { 
       //teller is busy so they cant procces until they have helped everyone
        myVecc[tellerNum].setavaliable(false);
        //big number to make sure its at end of the queue
        myVecc[tellerNum].setDT((unsigned)9999999999);
        //cout << myVecc[tellerNum].getDepartureTime << endl;
        cout << "Teller  " << tellerNum + 1 << " processing departure event at time:" << setw(5) << currentTime << endl;
    }
}

int main()
{

    priority_queue<Event, vector<Event>, greater<Event > > pQ;
    //  priority_queue<Event,vector<Event>,greater<Event>> dQ;
    queue<Event> bankQ;
    vector<Teller> myVec;

    // bool myVecc = true;
    unsigned firstData, secondData;
    unsigned currentTime = 0;
    unsigned numTellers = 0;
    unsigned transaction = 0;

   //cin the number of teller avaliable 
    cin >> numTellers;
    for (unsigned i = 0; i < numTellers; i++)
    {
        Teller temp(i);
        myVec.push_back(temp);
    }

    cout << "<<< BEGIN SIMULATION (" << numTellers << " tellers) >>>" << endl;

   //cin from standard input
    while (cin >> firstData >> secondData)
    {
        Event newArrivalEvent(Event::arrival, firstData, secondData);
        pQ.push(newArrivalEvent);
    }
    
    while (!pQ.empty())
    {
       //pQ gets poped in the function call
        Event newEvent = pQ.top();
        //used to keep track of time
        currentTime = newEvent.getTime();
         //if the event type is an arival, it processes the arival
        if (newEvent.getType() == Event::arrival) {
            processArrival(newEvent, pQ, myVec, bankQ);
            transaction++;
        }
        //if the type is not arival, we assume its an departure event
        else {
            processDeparture(newEvent, pQ, myVec, bankQ, currentTime);
        }
    }
    

    cout << "<<< END SIMULATION >>>\n\n";
    cout << ">>> SIMULATION STATISTICS\n\n";
    cout << "           Teller number:";
    

   //size of vec store in a var to reduce function calls
   // all the forloops used to format the output of the code correctly
    unsigned tempSize = myVec.size();

    for (unsigned i = 0; i < tempSize; i++)
    {
        cout << setw(8) << i + 1;
    }
    cout << setw(10) << "OVERALL" << endl;
    cout << "  Transactions processed:";
    for (unsigned i = 0; i < tempSize; i++)
    {
        cout << setw(8) << myVec[i].getProcessedClients();
    }
    cout << setw(10) << transaction << endl;

    cout << "Average transaction time:";
    for (unsigned i = 0; i < tempSize; i++)
    {
        cout << fixed << setw(8) << setprecision(2) << myVec[i].getTransactionTime() / myVec[i].getProcessedClients();
        avgTrans += myVec[i].getTransactionTime();
    }
    cout << fixed << setw(10) << setprecision(2) << avgTrans / transaction << endl << endl;

    for (unsigned i = 0; i < tempSize; i++)
    {
        cout << setw(8) << " ";
    }
    cout << "Maximum wait line length:" << setw(10) << mWaitLine << endl;

    for (unsigned i = 0; i < tempSize; i++)
    {
        cout << setw(8) << " ";
    }

    cout << "Average wait line length:" << fixed << setw(10) << setprecision(2) << avgLineSize / transaction << endl;

    for (unsigned i = 0; i < tempSize; i++)
    {
        cout << setw(8) << " ";
    }

    cout << "       Average wait time:" << fixed << setw(10) << setprecision(2) << waitTime / transaction << endl << endl;
    //  cout << "Simulation Ends\n\n";
    //  cout << "Simulation Statistics\n";
    //  cout <<"  Number of transactions processed:" <<setw(5)<<  numTrans << endl;
    //  cout << "          Average transaction time:" <<fixed<<setw(8)<<setprecision(2)<< avgTime/numTrans<<endl;
    //  cout << "                 Average wait time:" << setw(8)<<avgWait/numTrans << endl;

    //  cout << endl;

    return 0;
}
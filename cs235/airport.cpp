/*****************************************************************************
* Program:
*    Assignment 04, Airport Simulation
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This program simulates an airport that has planes coming either to take
*    off or land. It uses queues with up to 5 planes lined up for each, and 
*    allows them to land or take off, one at a time, giving landing precedence.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <cstdlib>
#include <time.h>
using namespace std;

const int DEFAULT_QUEUE = 5;
const int RANDOM_SEED = 2500;

const int GENERAL = 0;
const int TAKEOFF = 1;
const int LANDING = 2;

/*****************************************************************************
* Random objects can be used to generate random numbers. Uses poissonRandom
* function to return a random integer.
******************************************************************************/
class Random
{
   public:
      Random(void);
      int poissonRandom(double expected);
};

/*****************************************************************************
* Simple Queue allows for first in, first out ordering. 
******************************************************************************/
template <class T>
class Queue
{
   public:
      Queue(void);
      Queue(int size);
      Queue(const Queue& original);
      ~Queue(void);

      void insert(T item); // Inserts an item at the back
      void remove(void);   // Removes front item

      T front(void); // Returns front item
      T next (void); // Returns front item and removes it

      bool full(void);
      bool empty(void);
      int  size(void);

      Queue<T>& operator = (const Queue<T>& rtSide);
   
   private:
      T*  line;
      int theFront;
      int back;
      int maxSize;
      int currentSize;
};

/*****************************************************************************
* Airplane contains the amount of time it's been waiting in a queue, whether
* or not it is airborn, and if needed has the capacity for a location.
******************************************************************************/
struct Airplane
{
   int    waitTime;
   bool   airborn;
   string location;
};


/*****************************************************************************
* Airport accepts requests for an airplane to take off or land. It has one
* queue each for planes wishing to take off or land, and only allows for 5
* planes on each. Airports also keep statistical data of planes coming,
* leaving, or rejected.
******************************************************************************/
class Airport
{
   public:
      Airport();

      void runSim();
      void run();
   
      void requestTakeoff(Airplane newPlane);
      void requestLanding(Airplane newPlane);
      double avgWaitTime(int type = GENERAL); // 0 is avg for both
                                 // TAKEOFF  or  1 is takeoff avg
                                 // LANDING  or  2 is landing avg
      int numPlanes(int type = GENERAL); // same as above
      int time(void); // Returns run time
      void printReport();
   
   private:
      int             runTime;
      int             numLPlanes;  // Number of Landing Planes
      int             totLWTime;   // Total wait time for landing planes
      int             numTPlanes;  // Number of planes taking off
      int             totTWTime;   // Total wait time to take off
      int             idleTime;  
      int             numRefused;
      Queue<Airplane> takeoff;
      Queue<Airplane> landing;
};

double getDouble(string prompt);

/*****************************************************************************
* Main creates an airport, and starts its simulation.
******************************************************************************/
int main()
{
   Airport myAirport;
   myAirport.runSim();
   return 0;
}

/*****************************************************************************
* This function safely prompts the user for a double. The input is a string
* to prompt the user, and it returns the double the user types in.
******************************************************************************/
double getDouble(string prompt)
{
   double response;
   bool valid = false;
   cout << prompt;
   while (!valid)
   {
      cin >> response;
      if (cin.fail())
      {
         cin.clear();
         cin.ignore();
         cout << "Error: Invalid Entry! Please try again\n\n> ";
      }
      else
         valid = true;
   }
   return response;
}

/*****************************************************************************
* Constructor sets the seed for the random number generator.
******************************************************************************/
Random::Random()
{
   srand(RANDOM_SEED);
}

/*****************************************************************************
* This function takes in a double which is the expected/average number, and
* returns a random integer value.
******************************************************************************/
int Random::poissonRandom(double expected)
{
   int n = 0;
   double limit = exp(-expected);
   double x = rand() / ((double)RAND_MAX + 1);

   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   
   return n;
}

/*****************************************************************************
* Constructor for an airport, initializes all values to zero.
******************************************************************************/
Airport::Airport()
{
   runTime    = 0;
   numLPlanes = 0;
   totLWTime  = 0;
   numTPlanes = 0;
   totTWTime  = 0;
   idleTime   = 0;
   numRefused = 0;
}

/*****************************************************************************
* Runs a simulation for the airport.  Asks the user for the amount of time the
* simulation will run, and the expected number of planes coming each unit of
* time. Runs the simulation, and prints the results. No parameters. No return.
******************************************************************************/
void Airport::runSim()
{
   int      totalTime;
   double   expectedPlanesT;
   double   expectedPlanesL;
   Random   myRand;
   int      randomNum;
   Airplane newplane;
   
   totalTime       = getDouble("Units of time the simulation will run: ");
   expectedPlanesL = getDouble("Expected number of arrivals per time unit: ");
   expectedPlanesT = getDouble("Expected number of take offs per time unit: ");
   
   for (int i = 0; i < totalTime; i++)
   {
      // Add landing planes
      randomNum = myRand.poissonRandom(expectedPlanesL);
      for (int i = 0; i < randomNum; i++)
      {
         requestLanding(newplane);
      }
      // Add planes taking off
      randomNum = myRand.poissonRandom(expectedPlanesT);
      for (int i = 0; i < randomNum; i++)
      {
         requestTakeoff(newplane);
      }
      // Run single unit of time
      run();
   }

   // Display report
   cout << endl;
   printReport();
   
   return;
}

/*****************************************************************************
* Runs a single unit of time. Determines what planes can take off or land.
* A plane trying to land has priority over a plane attempting to take off.
* if no planes are waiting, the time is idle. No parameters, no return.
******************************************************************************/
void Airport::run()
{
   if(!landing.empty()) // Landing planes have priority
   {
      totLWTime += runTime - landing.next().waitTime;
   }
   else if (!takeoff.empty())
   {
      totTWTime += runTime - takeoff.next().waitTime;
   }
   else
      idleTime++;

   runTime++;
   return;
}

/*****************************************************************************
* A plane requests permission from the airport to take off. If the queue is not
* full, the plane is added to the queue. Otherwise it is refused. Input is the
* plane requesting to take off. No return.
******************************************************************************/
void Airport::requestTakeoff(Airplane newPlane)
{
   newPlane.airborn = false;
   newPlane.waitTime = runTime;
   if (takeoff.full())
      numRefused++;
   else
   {
      numTPlanes++;
      takeoff.insert(newPlane);
   }
   return;
}

/*****************************************************************************
* A plane requests permission from the airport to land. If the queue is not
* full, the plane is added to the queue. Otherwise it is refused. Input is the
* plane requesting to land. No return.
******************************************************************************/
void Airport::requestLanding(Airplane newPlane)
{
   newPlane.airborn = true;
   newPlane.waitTime = runTime;
   if (landing.full())
      numRefused++;
   else
   {
      numLPlanes++;
      landing.insert(newPlane);
   }
   return;
}

/*****************************************************************************
* Returns the avg wait time for planes. Input is an int. 1, or TAKEOFF will
* give the average wait time of planes wishing to takeoff. 2 or LANDING will
* give the average wait time of planes wishing to land. Default or any other
* integer will return the average wait time of both put together.
******************************************************************************/
double Airport::avgWaitTime(int type)
{
   double avg = 0;
   try
   {
      if ((numTPlanes < 1) && (numLPlanes < 1))
         throw 0;
      switch (type)
      {
         case TAKEOFF:
         {
            if (numTPlanes < 1)
               throw 0;
            avg = ((double)totTWTime / (double)numTPlanes);
            break;
         }
         case LANDING:
         {
            if (numLPlanes < 1)
               throw 0;
            avg = ((double)totLWTime / (double)numLPlanes);
            break;
         }
         default:
         {
            avg = (((double)totLWTime  + (double)totTWTime) /
                   ((double)numLPlanes + (double)numTPlanes));
            break;
         }
      }
   }
   catch (int e)
   {
      avg = 0;
   }
   return avg;
}

/*****************************************************************************
* Returns the number of planes allowed to take off or land. input is an int:
* 1 or TAKEOFF for planes wishing to take off, 2 or LANDING for planes wishing
* to land, or by default and any other integer, will return the number of both.
******************************************************************************/
int Airport::numPlanes(int type)
{
   int number = 0;
   switch (type)
   {
      case TAKEOFF:
      {
         number = numTPlanes;
         break;
      }
      case LANDING:
      {
         number = numLPlanes;
         break;
      }
      default:
      {
         number = (numTPlanes + numLPlanes);
         break;
      }
   }
   return number;
}

/*****************************************************************************
* Returns the current run time of the airport. No input.
******************************************************************************/
int Airport::time(void)
{
   return runTime;
}

/*****************************************************************************
* Prints a statistical report of the airport. No inputs, no return.
******************************************************************************/
void Airport::printReport(void)
{
   int totalPlanes      = numPlanes() + numRefused;
   int planesLanded     = numLPlanes - landing.size();
   int planesTakenOff   = numTPlanes - takeoff.size();
   double idlePercent   = 0;
   if (runTime != 0)
      idlePercent = ((double)idleTime / (double)runTime) * 100.0;
   
   cout << "Total number of planes processed: " << totalPlanes        << endl
        << "Number of planes landed: "        << planesLanded         << endl
        << "Number of planes taken off: "     << planesTakenOff       << endl
        << "Number left ready to land: "      << landing.size()       << endl
        << "Number left ready to take off: "  << takeoff.size()       << endl
        << "Number of planes refused use: "   << numRefused           << endl
        << setprecision(2) << fixed << showpoint
        << "Percentage of time runway idle: " << idlePercent << "%"   << endl
        << "Average wait time to land: "      << avgWaitTime(LANDING) << endl
        << "Average wait time to take off: "  << avgWaitTime(TAKEOFF) << endl;
   
   return;
}

/*****************************************************************************
* Constructor for Queue, allocates max size to default const. sets all other
* values to zero
******************************************************************************/
template <class T>
Queue<T>::Queue(void)
{
   maxSize = DEFAULT_QUEUE;
   line = new T[maxSize];
   currentSize = 0;
   theFront = 0;
   back = 0;
}

/*****************************************************************************
* Constructor for Queue, allocates max size to given input int. Sets all other
* values to zero.
******************************************************************************/
template <class T>
Queue<T>::Queue(int size)
{
   maxSize = size;
   line = new T[maxSize];
   currentSize = 0;
   theFront = 0;
   back = 0;
}

/*****************************************************************************
* Copy constructor makes exact copy of queue.
******************************************************************************/
template <class T>
Queue<T>::Queue(const Queue& original)
{
   maxSize = original.maxSize;
   line = new T[maxSize];
   theFront = 0;
   back = 0;
   for (int i = 0; i < original.currentSize; i++)
   {
      insert(original.line[i]);
   }
}

/*****************************************************************************
* Destructor, deletes the dynamically allocated data.
******************************************************************************/
template <class T>
Queue<T>::~Queue(void)
{
   delete [] line;
}

/*****************************************************************************
* Inserts an item at the back of the line. Input is the item to insert. No
* return.
******************************************************************************/
template <class T>
void Queue<T>::insert(T item)
{
   if (currentSize < maxSize) 
   {
      if (back == maxSize)  // Make use of all allocated space.
         back = 0;
      line[back] = item;
      back++;
      currentSize++;
   }
   else
   {
      T* newLine = new T[(maxSize * 2)]; // Doubles amount of space each time 
      int newBack = theFront;            // It has to allocate more space.
      for (int i = 0; i < maxSize; i++)
      {
         newLine[i] = line[newBack];
         newBack++;
         if (newBack == maxSize)
            newBack = 0;
      }
      delete [] line;
      maxSize *= 2;
      line = newLine;
      line[back] = item;
      back++;
      currentSize++;
   }
      
   return;
}

/*****************************************************************************
* Removes an item from the front of the line. No inputs. No return.
******************************************************************************/
template <class T>
void Queue<T>::remove(void)
{
   if (currentSize > 0)
   {
      theFront++;
      currentSize--;
      if (theFront == maxSize)
         theFront = 0;
   }
   return;
}

/*****************************************************************************
* Returns the item at the front of the line. No inputs.
******************************************************************************/
template <class T>
T Queue<T>::front(void)
{
   return line[theFront];
}

/*****************************************************************************
* Returns the item at the front of the line and removes it. No inputs.
******************************************************************************/
template <class T>
T Queue<T>::next(void)
{
   T item = line[theFront];
   remove();
   return item;
}

/*****************************************************************************
* Returns true if queue is full, false otherwise. No Inputs.
******************************************************************************/
template <class T>
bool Queue<T>::full(void)
{
   bool isFull = false;
   if (currentSize == maxSize)
      isFull = true;
   return isFull;
}

/*****************************************************************************
* Returns true if queue is empty, false otherwise. No Inputs.
******************************************************************************/
template <class T>
bool Queue<T>::empty(void)
{
   bool isEmpty = false;
   if (currentSize == 0)
      isEmpty = true;
   return isEmpty;
}

/*****************************************************************************
* Returns the current size of the queue. No inputs.
******************************************************************************/
template <class T>
int Queue<T>::size(void)
{
   return currentSize;
}

/*****************************************************************************
* Assignment operator makes an exact replica of right side parameter, and
* returns it by reference.
******************************************************************************/
template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& rtSide)
{
   delete [] line;
   maxSize = rtSide.maxSize;
   line = new T[maxSize];
   currentSize = rtSide.currentSize;
   for (int i = 0; i < currentSize; i++)
      line[i] = rtSide.line[i];
   theFront = rtSide.theFront;
   back = rtSide.back;
   
   return *this;
}

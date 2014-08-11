/*****************************************************************************
* Program:
*    Assignment 05, Stock Market
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This program reads in a list of transactions to buy or sell stocks.  It
*    keeps track of the profit gained, and records the transactions and their
*    results to the screen.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <deque>
using namespace std;

/*****************************************************************************
* Contains the value of each share when it was bought, as well as the quantity
* of shares bought at that price.
******************************************************************************/
struct Share
{
   double buyVal;
   int    quantity;
};

/*****************************************************************************
* An investor is one that buys and sells shares.  It can return the total
* profit gained, or can clear itself (go bankrupt), or drop stocks.
******************************************************************************/
class Investor
{
   public:
      Investor(void);

      void   clear(void);
   
      void   buy (Share buyShare );
      double sell(Share sellShare);

      double profit(void);      // Returns total profit
      Share  drop  (void);      // Drops and returns top share

      int    investments(void); // Returns current number of investments
   
   private:
      deque<Share> shares;
      double  totalProfit;
};


/*****************************************************************************
* Main opens up files from the command line, reads in transactions, and
* displays their results to the console.
******************************************************************************/
int main(int argc, char* argv[])
{
   ifstream read;
   Investor newInvestor;
   Share    newShare;
   string   transType;
   double   profit;
   
   for (int i = 1; i < argc; i++)
   {
      try
      {
         read.open(argv[i]);
         if (read.fail())
            throw argv[i];

         cout << setprecision(2) << fixed << showpoint;

         while (read >> transType)
         {
            read >> newShare.quantity;
            read >> newShare.buyVal;
            if (transType == "BUY")
            {
               newInvestor.buy(newShare);
               cout << "Bought " << newShare.quantity
                    << " shares at $" << newShare.buyVal << endl;
            }
            else
            {
               profit = newInvestor.sell(newShare);
               cout << "Sold " << newShare.quantity
                    << " shares at $" << newShare.buyVal
                    << " for a profit of $";
               if (profit < 0)
                  cout << "(" << -profit << ")" << endl;
               else
                  cout << profit << endl;
            }
         }

         cout << "\nTotal Profit: $" << newInvestor.profit() << endl;
         cout << "\nUnsold Shares\n";
         while (newInvestor.investments() != 0)
         {
            newShare = newInvestor.drop();
            cout << "   " << newShare.quantity
                 << " shares bought for $" << newShare.buyVal << endl;
         }
         
         read.close();
         newInvestor.clear();
      }
      catch (char* e)
      {
         cout << "Error: Could not open " << e << endl;
      }
   }
   return 0;
}

/*****************************************************************************
* Constructor initializes current profit to zero.
******************************************************************************/
Investor::Investor(void)
{
   totalProfit = 0;
}

/*****************************************************************************
* Clears the investor of his stocks and profits and gives him a clean slate.
* No parameters. No return.
******************************************************************************/
void Investor::clear(void)
{
   totalProfit = 0;
   shares.clear();
   return;
}

/*****************************************************************************
* Adds a share to the investors deque of shares. Input is the share to add.
******************************************************************************/
void Investor::buy(Share buyShare)
{
   shares.push_back(buyShare);  
   return;
}

/*****************************************************************************
* Sells a number of the investors shares. Input is a Share of what to sell.
* In essence, the quantity will be the quantity to sell, and the buyVal will
* actually be the selling value. Returns the profit from the transaction.
******************************************************************************/
double Investor::sell(Share sellShare)
{
   Share  trans;
   double profit = 0;
   
   while (sellShare.quantity > 0)
   {
      trans = shares.front();           
      shares.pop_front();
      
      if (sellShare.quantity < trans.quantity)
      {
         trans.quantity -= sellShare.quantity;
         shares.push_front(trans);
         trans.quantity = sellShare.quantity;
      }
      profit += (trans.quantity * (sellShare.buyVal - trans.buyVal));
      sellShare.quantity -= trans.quantity;
   }
   
   totalProfit += profit;
   return profit;
}

/*****************************************************************************
* Returns the total profit.
******************************************************************************/
double Investor::profit(void)
{
   return totalProfit;
}

/*****************************************************************************
* Drops the top share, and returns it.
******************************************************************************/
Share Investor::drop(void)
{
   Share temp;
   if (shares.size() > 0)
   {
      temp = shares.front();
      shares.pop_front();
   }
   else
   {
      temp.quantity = 0;
      temp.buyVal = 0.0;
   }
   return temp;
}

/*****************************************************************************
* Returns the number of the investor's active investments.
******************************************************************************/
int Investor::investments(void)
{
   return shares.size();
}

/***********************************************************************
* Program:
*    Assignment 14, Matthew 18:21-22  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program displays scripture of how many times one should
*    forgive their neighbor.
*    
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     1.2 hrs
*      It was difficult to find out what to return for each function.
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Display Peter's question.
***********************************************************************/
int questionPeter()
{
   cout << "Lord, how oft shall my brother sin against me, and I"
        << " forgive him?\nTill seven times?\n";      
   return 0;
}

/**********************************************************************
* Display Lord's answer.
***********************************************************************/
int responseLord()
{
   int forgive = (7 * 70);
   return forgive;
}

/**********************************************************************
* Will display peter's question, and then the Lord's answer.
***********************************************************************/
int main()
{
   questionPeter();
   cout << "Jesus saith unto him, I say not unto thee, Until seven\n";
   cout << "times: but, Until " << responseLord() << ".\n";
   return 0;
}


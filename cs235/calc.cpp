/************************************************************
* Program:
*    Assignment 03, Stack Application
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This program reads in a file of equations, and displays
*    the machine code for each problem.
************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

/************************************************************
* Structure for an operator. Has a priority, and a visible
* postfix symbol. i.e. parentheses are invisible.
************************************************************/
struct Operat
{
   int    priority;
   string symbol;
};

/************************************************************
* Stack class. Allows for first in, last out, last in first
* out structure.
************************************************************/
template <class T>
class Stack
{
   public:
      Stack(int size);
      Stack(const Stack &aStack);

      T    top  (void);
      bool empty(void);
      bool full (void);

      void push(T item);
      void pop (void);

      Stack<T>& operator = (const Stack<T>& rtSide);

      ~Stack();
   
   private:
      int  maxSize;
      int  myTop;
      T*   stackItems;
};

/************************************************************
* Equation has an infix expression and an automatically
* created postfix expression. Can display machine code to
* express the solution for an equation.
************************************************************/
class Equation
{
   public:
      Equation(void);
      Equation(string theEquation);

      string in  (void);
      string post(void);
      void   code(void);

      void set(string theEquation);
   
   private:
      string infix;
      string postfix;
      void   convert(void);
      Operat decipher(char theOperator);
};

string int2String(int num);

/************************************************************
* Reads a file of equations, evaluates them into post-fix
* notation, and prints them in machine code.
************************************************************/
int main(int argc, char* argv[])
{
   ifstream read;
   string inEQ;
   Equation EQ;
   for (int i = 1; i < argc; i++)
   {
      read.open(argv[i]);
      while (getline(read, inEQ))
      {
         EQ.set(inEQ);
         EQ.code();
         cout << endl;
      }
      read.close();
   }
   return 0;
}

/************************************************************
* Uses a stack to transform an integer into a string.
* Input: integer. Output: string.
************************************************************/
string int2String(int num)
{
   string newString = "";
   int mod;
   Stack<int> pile(32);
   
   while (num != 0)
   {
      mod = num % 10;
      num = num / 10;
      pile.push(mod);
   }
   
   while (!pile.empty())
   {
      newString += (char)(pile.top() + 48);
      pile.pop();
   }
   
   return newString;
}

/************************************************************
* Constructor for equation. sets the expressions to empty.
************************************************************/
Equation::Equation(void)
{
   infix   = "";
   postfix = "";
}

/************************************************************
* Constructor sets the expressions to the given parameter
* equation.
************************************************************/
Equation::Equation(string theEquation)
{
   infix = theEquation;
   convert();
}

/************************************************************
* Getter - Returns string as infix expression.
************************************************************/
string Equation::in(void)
{
   return infix;
}

/************************************************************
* Getter - Returns string as postfix expression.
************************************************************/
string Equation::post(void)
{
   return postfix;
}

/************************************************************
* Displays machine code for expressing equation.
* No parameters. No return.
************************************************************/
void Equation::code(void)
{

   int  size = postfix.size();
   Stack<string> ram(size);
   int count = 1;
   string op1;
   string op2;
   string op3;
   string operand;

   // Loop through postfix expression
   for (int i = 0; i < size; i++) 
   {
      if (isalpha(postfix[i]))   // Add operands to a stack
      {
         operand = postfix[i];
         ram.push(operand);
      }
      else     // Do operation on top two operands on stack
      {
         op2 = ram.top();
         ram.pop();
         op1 = ram.top();
         ram.pop();

         cout << "LD  " << op1 << endl;

         switch (postfix[i])      // Decide operation to do
         {
            case '+':
               cout << "AD  " << op2 << endl;
               break;
            case '-':
               cout << "SB  " << op2 << endl;
               break;
            case '*':
               cout << "ML  " << op2 << endl;
               break;
            case '/':
               cout << "DV  " << op2 << endl;
               break;
            default:
               break;
         }

         op3 = "TEMP";             // Create temp variables
         op3 += int2String(count); // And store them back
         ram.push(op3);            // On the stack
         cout << "ST  " << op3 << endl;
         count++;
      }
   }
   
   return;
}

/************************************************************
* Sets a new equation. Input is a string with the full
* equation.
************************************************************/
void Equation::set(string theEquation)
{
   infix = theEquation;
   convert();
   return;
}

/************************************************************
* Converts an infix equation to a postfix equation. No input
* No return.
************************************************************/
void Equation::convert(void)
{
   postfix = "";
   int size = infix.size();
   Stack<char> pile(size);
   Operat fOperator;
   Operat sOperator;

   // Look at each symbol in equation
   for (int i = 0; i < size; i++)  
   {
      if (isalpha(infix[i]))        // Add it to the postfix 
         postfix += infix[i];       // if it's a variable
      else
      {
         if (pile.empty())         // Add it to the stack 
            pile.push(infix[i]);   // if it's empty
         else                         
         {
            fOperator = decipher(pile.top()); // Determine 
            sOperator = decipher(infix[i]);   // priorities
            // ')' char has a low priority when in stack
            if (fOperator.priority == 3)  
               fOperator.priority = 0;
            // Compare priorities
            while (sOperator.priority <= fOperator.priority) 
            {
               // Add top if higher priority
               postfix += fOperator.symbol;
               // Remove parentheses
               if ((pile.top() == '(') && (infix[i] == ')')) 
               {
                  pile.pop();
                  break;
               }
               else
                  pile.pop();  // Remove top after adding it
               if (pile.empty())
                  break;
               fOperator = decipher(pile.top()); // Find 
               if (fOperator.priority == 3)  // priority for 
                  fOperator.priority = 0;    // next top
            }
            if (infix[i] != ')')      // Don't add closing 
               pile.push(infix[i]);   // parenthesis to stack
         }
      }
   }
   
   while (!pile.empty())                // Flush stack at end
   {
      fOperator = decipher(pile.top());
      postfix += fOperator.symbol;
      pile.pop();
   }
   
   return;
}

/************************************************************
* Assigns a priority and symbol to an operator. Input is a
* character operator. Returns an Operat with the resulting
* priority and symbol within.
************************************************************/
Operat Equation::decipher(char theOperator)
{
   Operat newOperat;

   switch (theOperator)
   {
      case '+':
         newOperat.priority =   1;
         newOperat.symbol   = "+";
         break;
      case '-':
         newOperat.priority =   1;
         newOperat.symbol   = "-";
         break;
      case '*':
         newOperat.priority =   2;
         newOperat.symbol   = "*";
         break;
      case '/':
         newOperat.priority =   2;
         newOperat.symbol   = "/";
         break;
      case '(':
         newOperat.priority =   3;
         newOperat.symbol   =  "";
         break;
      case ')':
         newOperat.priority =   0;
         newOperat.symbol   =  "";
         break;
      default:
         newOperat.priority =   4;
         newOperat.symbol   =  "";
         break;
   }
   
   return newOperat;
}



/************************************************************
* Constructor - Requires the size of the stack as a parameter
************************************************************/
template <class T>
Stack<T>::Stack(int size)
{
   stackItems = new T[size];
   maxSize    = size;
   myTop      = 0;
}

/************************************************************
* Copy constructor. Creates an exact replica of a stack
************************************************************/
template <class T>
Stack<T>::Stack(const Stack &aStack)
{
   maxSize = aStack.maxSize;
   stackItems = new T[maxSize];
   myTop = 0;
   for (int i = 0; i < aStack.myTop; i++)
   {
      push(aStack.stackItems[i]);
   }
}

/************************************************************
* Returns the last integer pushed onto the stack.
* If the stack is empty, returns 0. No parameters.
************************************************************/
template <class T>
T Stack<T>::top(void)
{
   if (myTop > 0)
      return (stackItems[myTop - 1]);
   else
      return 0;
}

/************************************************************
* Pushes an integer onto the stack. The integer to push onto
* the stack is the parameter. If the stack is full. It will
* display an error, and end the program.
************************************************************/
template <class T>
void Stack<T>::push(T item)
{
   if (!full())
   {
      stackItems[myTop] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(EXIT_FAILURE);
   }
}

/************************************************************
* Removes an integer from the top of the stack. Has no
* parameters or return. If the stack is empty, it will
* display an error, and end the program.
************************************************************/
template <class T>
void Stack<T>::pop(void)
{
   if (!empty())
   {
      myTop--;
   }
   else
   {
      cout << "ERROR: Stack Underflow\n";
      exit(EXIT_FAILURE);
   }
}

/************************************************************
* This function tells if the stack is empty or not. Returns
* true for empty, false for not empty.
************************************************************/
template <class T>
bool Stack<T>::empty(void)
{
   bool isEmpty = false;
   if (myTop <= 0)
      isEmpty = true;
   return isEmpty;
}

/************************************************************
* This function tells if the stack is full or not. Returns
* true for full, false for not.
************************************************************/
template <class T>
bool Stack<T>::full(void)
{
   bool isFull = false;
   if (myTop > (maxSize - 1))
      isFull = true;
   return isFull;
}

/************************************************************
* Assignment operator - Creates an exact replica of right
* operand
************************************************************/
template <class T>
Stack<T>& Stack<T>::operator = (const Stack<T>& rtSide)
{
   delete [] stackItems;
   maxSize = rtSide.maxSize;
   stackItems = new T[maxSize];
   myTop = 0;
   for (int i = 0; i < rtSide.myTop; i++)
   {
      push(rtSide.stackItems[i]);
   }
   myTop = rtSide.myTop;
   return *this;
}

/************************************************************
* Destructor - Deletes the dynamically allocated array.
************************************************************/
template <class T>
Stack<T>::~Stack(void)
{
   delete [] stackItems;
}

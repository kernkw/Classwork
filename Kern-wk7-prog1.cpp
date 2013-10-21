// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 7, Program 1
// Program Description: This program computes the sum of all even integers
//         by the use of three different method of computation.
// Input: Reads a positive number entry from user
// Processing: Prompts the user to enter a positive number and error checks
//             that they enter the correct number.  This program them processes
//             the sum of all even numbers from the number entered to 1, by use
//             of 3 different computation functions.
// Output: Displays the computed even number sums results from eachof the
//         functions.
//-----------------------------------------------------------------------------
#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()
#include <cctype>                  // for toupper()

using namespace std;

//prototypes
void FormulaEvenSum (int num);
void LoopEvenSum (int num);
int RecursiveEvenSum (int num);
// --------------------------------------------------------------------------
// Description: main reads the user's numeric input and calls three functions
//              to calculate the sum of even numbers from the user inputed
//              value to 1.  This processes this summation through the use
//              of three different functions.
// Returns: 0 if successful
// --------------------------------------------------------------------------
int main()

{
    int num;
    int nSum; // the sum value from calling the recursive function

    cout << "Program to compute sum of even integers from 1 to num"
         << endl << endl;
    //this do-while loops until users enters 0 to exit
    do
    {
        //this do-while loop, loops until a postive integer is entered
        do
        {
            cout << "Enter a positive integer (or 0 to exit): ";
            cin >> num;
            cout << endl << endl;
        } while (num < 0); //  error checks that value entered is positive

        if (num > 0)
        {
            FormulaEvenSum(num);
            LoopEvenSum (num);
            nSum = RecursiveEvenSum(num);
            cout << "Recursive result =    " << nSum << endl;
        }

        } while (num != 0);  // exits program if 0 is entered

    cout << "Goodbye!" << endl;
    cout << endl;
    system("read -p 'Hit Enter to continue. '");
    return 0;
}
// ----------------------------------------------------------------------
// FormulaEvenSum - Calculates the summation of the even integers by
//                use of a formula.  Displays the results.
// reference parameters: num- postive numeric inputed by user
// -----------------------------------------------------------------------
void FormulaEvenSum (int num)
{
    int evenSum;

    evenSum = (num / 2) * ((num / 2) + 1);
    cout << "Formula result =      " << evenSum << endl;
}
// ----------------------------------------------------------------------
// LoopEvenSum- Calculates the summation of the even integers by
//                use of a for loop. Displays the results.
// reference parameters: num- postive numeric value inputed by user
// -----------------------------------------------------------------------
void LoopEvenSum (int num)
{
    int evenSum;

    for(; evenSum == 1 ; evenSum++)
    {
        if (evenSum % 2 == 0)
        {
            evenSum += evenSum;
        }
    }
    cout << "Iterative result =    " << evenSum << endl;
}
// ----------------------------------------------------------------------
// RecursiveEvenSum - Calculates the summation of the even integers by
//                use of recursion
// reference parameters: num- postive numeric inputed by user
// returns: evenSum - the sum of the even numbers from num to 1
// -----------------------------------------------------------------------
int RecursiveEvenSum (int num)
{
    int evenSum;
      if (num == 0)
    {
        return 0;
    }
    else if (num % 2 == 0)
    {
        evenSum = num + RecursiveEvenSum(num - 2);
        return evenSum;
    }
    else
    {
        num = num - 1;
        evenSum = num  + RecursiveEvenSum(num - 2);
        return evenSum;
    }
}

// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 6, Program 1
// Program Description: Tests Ulam's algorithm by reading and validating user
//         inputs and displays Ulam's algorithm in tables.
// Input: Reads the first number to test, this number is validated.
//        Reads the last number to test, this number is also validated against
//              first entry
//        Reads the increment value to increase test by
// Processing: Prompts and validates users enteries,  then uses nested loops
//             to dispaly ulams alorigthm to each number until it is equal to
//             1.
// Output: Displays each number caluated into ulam's algortihm and diaplys
//                  in cloumns with a count of the number of terms to reach 1.
//-----------------------------------------------------------------------------
#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()
#include <cctype>                  // for toupper()

using namespace std;

//protoypes
void EnterTests (int& firstNumber, int& lastNumber);
int calculateIncrement(int firstNumber, int lastNumber);
void UlamAlgorithm (int num1, int num2, int increment);
// ----------------------------------------------------------------------
// Description: main reads the user's first and last numbers,
//              verifys they are correct value. Then populates
//              ulam's sequence tables for each user inputed increment
//              up to the last number.
// Returns: 0 if successful
// ----------------------------------------------------------------------
int main()

{
    int num1;
    int num2;
    int incrementValue;
    cout << "Program will test Ulam's algorithm" << endl << endl;

    EnterTests (num1, num2);
    incrementValue = calculateIncrement(num1, num2);
    UlamAlgorithm (num1, num2, incrementValue);

    cout << endl;
    system ("PAUSE");
    return 0;
}
//-------------------------------------------------------------------------
// EnterTests - Prompts the user to enter first and last number and error
// checks these enters and re-prompts user if they are not adequate.
// paramaters- firstNumber - number entered first btw 1 and 1000
//             secondNumber - second entry by user be btw 1 and 1000
//             and not less than firstNumber
//-------------------------------------------------------------------------
void EnterTests (int& firstNumber, int& lastNumber)
{

    cout << "Enter the first number to test: ";
    cin >> firstNumber;
    cout << endl;
    while (firstNumber <= 1 || firstNumber >= 1000)
    {
          cout << "Invalid -- must be between 1 and 1000. Try again." << endl;
          cout << endl;
          cout << "Enter the first number to test: ";
          cin >> firstNumber;
    }
    cout << "Enter the last number to test: ";
    cin >> lastNumber;
    cout << endl;
    while (lastNumber <= 1 || lastNumber >= 1000 || lastNumber < firstNumber)
    {
          cout << "Invalid -- must be between 1 and 1000 and cannot be less";
          cout << " than first number entered. Try again." << endl;
          cout << endl;
          cout << "Enter the last number to test: ";
          cin >> lastNumber;
    }
}
//------------------------------------------------------------------------------
// calculateIncrement- determines the increment value by setting to zero if
//                     conditions are met or reads input from user and va;idates
//                     that value entered is valid.
//             input- firstNumber
//                  - lastNumber
//      input/output- increment - value to increment by
//------------------------------------------------------------------------------
int calculateIncrement(int firstNumber, int lastNumber)
{
    int increment;
    if ((firstNumber == lastNumber) || ((lastNumber - 1) == firstNumber))
    {
        increment = 1;

    }
    else
    {
        cout << "Enter the increment for testing values: ";
        cin >> increment;
        cout << endl;
        while (increment < 1 || increment >= lastNumber)
        {
            cout << "Invalid -- must be between 1 and 1000. Try again." << endl;
            cout << endl;
            cout << "Enter the increment for testing values: ";
            cin >> increment;
        }
    }
    return increment;
}
//-------------------------------------------------------------------------
// UlamAlgorithm - runs nested loops that display ulams number sequence
//               and displays these numbers in a loop.
// paramaters- num1 - number entered first btw 1 and 1000
//             num2 - second entry by user be btw 1 and 1000
//             increment - user inputed value to increment by
//-------------------------------------------------------------------------
void UlamAlgorithm (int num1, int num2, int increment)
{
    int testNumber; // the starting value of number 1 entry
    int incrementValue;
    int count;

    testNumber = num1;
    incrementValue = increment;
    // outer loop will repeat as long as first number is less than final number
    while (num1 <= num2)
    {

        cout << "Series generated for " << num1 << endl;
        cout << setw(7) << num1 << setw(7);
        count = 1;
        //inner loop will repeat until first number displayed is equal to 1
        while (num1 > 1 && count)
        {

            if (num1 % 2 == 0) //even
            {
                num1 = num1 / 2;

            }
            else //odd
            {
                num1 = (num1 * 3) + 1;

            }

            cout << num1 << setw(7) ;

            if (num1 == 1)
            {
                cout << endl;
                cout << "Total number of terms: " << count + 1 << endl;
            }

            count++;
            // if displays 10 terms per line then line break
            if (count % 10 == 0)
                {
                cout << endl;
                }
        }
        cout << endl;
        increment++;
        num1 = testNumber + (incrementValue * (increment- incrementValue));
        cout << endl;
    }



}








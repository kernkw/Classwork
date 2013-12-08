// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 5, Program 1
// Program Description: Computes the juggler sequence.
// Input: Reads the user's first term
//        Reads the nu,ber of terms to calculate (after first)
//        Reads how many terms to display per line
//              or have the store do it
// Processing: Verifies that the user's input is correct with error checking
//             loop.  Then uses the user inputed data to runa  loop generating 
//             the juggler sequence for the number of terms read from user.
// Output: Displays the juggler series starting at the user read value and 
//         dispalying terms and terms per line based on user inputed values.
// ---------------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()
#include <cctype>                  // for toupper()

using namespace std;

const string ENTERFIRSTTERM = "Enter the first term: ";
const string ENTERTERMSTOCALCULATE = "Enter the number of terms to calculate (after first): ";
const string ENTERTERMSPERLINE = "Enter the terms to display per line: ";


// ------------------------------------------------------------- 
// Description: InputValid error checks the user inputed values
//              and prompts for new entry if number is 
//              non-positive or zero.
// Input parameter: Prompt - prompts the user to enter data
// Returns: num - number entered by user 
// ------------------------------------------------------------- 
int InputValid (string Prompt)
{
    int num;
    cout << Prompt;
    cin >> num;
    
    while (num <= 0)
    {
          cout << "Error-Please enter a positive, non-zero number: ";
          cin >> num;
    }
    return num;
}
// -------------------------------------------------------------
// Description: main reads the user's input and runs a loop to
//              display the data in the proper number of rows 
//              and columns.
// Returns: 0 if successful 
// -------------------------------------------------------------    
int main ()
{
   int count; 
   double firstTerm; //first term entered by user
   double termsToCalculate; //user entered number of terms to calculate
   double termPerLine; // how many terms per line
  
 
   
    //User facing program description
    cout << "Program will determine the terms in a Juggler Series" << endl << endl;
    
    int InputValid(string Prompt);
    
    firstTerm = InputValid(ENTERFIRSTTERM);
    cout << endl;
    termsToCalculate = InputValid(ENTERTERMSTOCALCULATE);
    cout << endl;
    termPerLine = InputValid(ENTERTERMSPERLINE);
    cout << endl;
    cout << "First " << termsToCalculate 
         << " terms of JUGGLER SERIES starting with "
         << firstTerm  << endl;
         
    count = 0;
    // loop determines if firstTerm is even or odd and then calculates function
    do 
    {   
        if ((count % static_cast<int>(termPerLine)) == 0)
            {
            cout << setw(15) << endl;
            }
        if( static_cast<int>(firstTerm) % 2 == 0) {
            if (firstTerm != 1) {
              firstTerm = floor(pow(firstTerm, 0.5));
              cout << setw(15) << setprecision(0) << fixed << firstTerm << setw(15);
            }
            else {
            
            cout << setw(15) << setprecision(0) << fixed << firstTerm << setw(15);
            
            }
        count++;
            
            
        }
        else {
            if (firstTerm != 1) {
              firstTerm = floor(pow(firstTerm, 1.5));
              cout << setw(15) << setprecision(0) << fixed << firstTerm << setw(15);
            }
            else {
            cout << setw(15) << setprecision(0) << fixed << firstTerm << setw(15);
            }
        count++;

        }

    } 
    while (count <= termsToCalculate);

    cout << endl;
    system ("PAUSE");
    return 0;

}

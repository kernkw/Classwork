// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 1, Program 1
// Program Description:  Displays the output of an investor's portfolio
//   Input: No Input
//   Processing: Uses output manipulators to format the portfolio's table
//   Output: Displays the investor's portfolio in a numeric table
// -----------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output

 using namespace std;
   
 // -----------------------------------------------------------
// Description: main displays the output of the investors portfolio
//   using output manipulators to format.         
//   Returns: 0 if successful
// ------------------------------------------------------------ 
 int main() 
 {
    cout << "Investor:"<< setw(13) 
         <<"John Smith"<< endl;    
    cout << "Quarter:"<< setw(14) 
         <<"Q1 2013"<< endl;   
    
    cout << endl << endl;    
    cout << setw(6) << "+" << setfill('-') 
         << setw(31) << "+" << endl; //Create dividing line
    
    cout << setfill(' ');
    cout << setw(13) << "Stock " 
         << setw(9) << "Number" 
         << setw(8) << "Price" 
         << endl; 
    cout << setw(13) << "Symbol" 
         << setw(9) << "Shares" 
         << setw(12) << "Per Share" 
         << endl;
    
    cout << setw(6) << "+" << setfill('-') 
         << setw(31) << "+" << endl; 
    
    // Set table using numeric values given
    cout << fixed << showpoint << setprecision(4); // Table formatting
    cout << setfill(' ') << right;   
    cout << setw(11) << "XYZ" 
         << setw(11) << 211 
         << setw(11) << 30.12 
         << endl; 
    cout << setw(11) << "ABC" 
         << setw(11) << 23 
         << setw(11) << 37.125 
         << endl; 
    cout << setw(11) << "MNO" 
         << setw(11) << 9 
         << setw(11) << 128.1 
         << endl; 
    cout << setw(11) << "FGH" 
         << setw(11) << 58 
         << setw(11) << 12.0155
         << endl; 
    cout << setw(11) << "DFG" 
         << setw(11) << 1102 
         << setw(11) << 8.6 
          << endl; 
           
    cout << setw(6) << "+" << setfill('-') 
         << setw(31) << "+" << endl; 
    
    cout << endl << endl;     
    system ("PAUSE");
    return 0;
  }



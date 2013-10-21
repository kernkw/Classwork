// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 1, Program 2
// Program Description:  Finds the invoice for purchasing shares of stock
//   Input: Reads the shares purchased and price per share from the user
//   Processing: Calculates the costs to determine total bill
//   Output: Displays the inovice with total bill to investor account
// -----------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output

 using namespace std;
 
 //global constants
 const int MIN_STOCK=100;          // Holds the minimum number of shares 
 const float MIN_COM=2.55;         // The minimum order commission
 const float OVERMIN_COM=0.02;     // Commission for each share over 100 shares 
 const string NAME= "Kyle Kern";   // Sets the investor's name
 const char FIRST_INITIAL = 'K'; 
 const char LAST_INITIAL = 'K'; 
 
 // -----------------------------------------------------------
// Description: main reads the total number of shares and 
//   the price per share from user and computes an inovice for
//   purchasing shares of stock.
//   Input parameter: Number of Shares - quantity 
//   Input parameter: Price per Share- in US dollars ($)                    
//   Returns: 0 if successful
// ------------------------------------------------------------ 
  
 int main() 
 {
    // Declare variables
    int totalShares;
    float priceShare, costAllShares, comMinOrder, comOverMin, totalBilled;
     
   // Read input from user
    cout << fixed << showpoint << setprecision(2); 
    cout << "Enter number of shares purchased:   ";
    cin >> totalShares; 
    cout << "Enter the price per share:   ";
    cin >> priceShare;
    
    // Computes the input costs
    costAllShares = totalShares * priceShare; 
    comMinOrder = MIN_COM; // Commission earned on the minimum order size of 100
        //Commission earned on orders over the minimum order size
    comOverMin = (totalShares - 100) * OVERMIN_COM;
       // Computes total billed to the investor's account from cost inputs
    totalBilled = costAllShares + comMinOrder + comOverMin;
   
    cout << endl << endl; 
    cout << endl << endl; 
    cout << endl << endl;
    cout << endl << endl;  
        
    // Displays the investor's name and the user entered values
    cout << "Investor:" << setw(30) << NAME << " (" << FIRST_INITIAL << LAST_INITIAL 
         << ")" << endl;
    cout << "Shares purchased:" << setw(16)<< totalShares << endl;
    cout << "Price per share:" << setw(18) << priceShare << endl;
    
    cout << endl << endl; 
    
    // Outputs the result of the investors's invoice from input calculations
    cout << "Cost for all shares" <<  setw(25) << costAllShares << endl;
    cout << "Commission for minimum order" << setw(16) << comMinOrder << endl;
    cout << "Commission for additional shares" << setw(12) << comOverMin << endl;
    cout <<  setw(37) << " " << setfill('-') << setw(8) << " " << endl; //Create dividing line
    cout << setfill(' ') << "Total Billed to Investor Account:" << setw(11) << totalBilled << endl;
    
    cout << endl << endl; 
    system ("PAUSE");
    return 0;
}
   
 
    
     

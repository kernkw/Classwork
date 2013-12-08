// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 3, Program 1
// Program Description: Computes and displays the bill for a single
//         customer at a specific local dicsount carpet store.
// Input: Reads the customer's space length and width in inches
//        Reads whether the customer wants standard or premium pading
//        Reads whether the customer wants to remove old carpet themselves
//              or have the store do it
//        Reads whether the customer or store will move furniture and if so 
//                reads how many reooms they have
// Processing: Calculates the customer's bill based on their preferences, 
//               taking in account dicsounts or extra charges where necessary
// Output: Displays the customer's bill with a break down of each charge or 
//           discount that makes up the bill
// ---------------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()
#include <cctype>                  // for toupper()

using namespace std;

// global constants
const double carpetCostPerYard= 25.94;
const double inchesToSquareFeet= 1296;
const double discountPercent= .065;
const double standPadCost= 5.25;
const double premPadCost= 6.73;
const double storeMoveCost= 26.66;
 
// ----------------------------------------------------------- 
// Description: CalculateSquareYards calculates the total
//              square yards using the user inputed deminsions
// Input parameter: spaceLength - space length in inches
//                  spaceWidth - space width in inches
// Returns:  totalSquareYards - total square yards of
//                              the user's space
// -----------------------------------------------------------
double CalculateSquareYards (double spaceLength, double spaceWidth)
{ 
    double totalSquareYards;
    totalSquareYards = (spaceLength * spaceWidth)/ inchesToSquareFeet;
    return (totalSquareYards);
}

// ------------------------------------------------------------- 
// Description: CalculatingCarpetCost calculates the carpet
//              cost of the user's carpet space 
// Input parameter: computedTotalSquareYards - total square yards
//                  calculated from CalculateSquareYards function
//                  carpetCostPerYard - global constant
// Returns: carpetCost - the cost of the carpet used in carpet
//                     installation 
// ------------------------------------------------------------- 
double CalculatingCarpetCost
        (double computedTotalSquareYards, double carpetCostPerYard)
{  
    double carpetCost;
    carpetCost = carpetCostPerYard * computedTotalSquareYards;
    return (carpetCost);
}
// ---------------------------------------------------------------
// Description: CalculateBillTotal calculates the bill total
//              taking into account users selections 
// Input parameters: giveDiscount, padType, storeMoveFurniture, 
//                     subTotal, plusStoreMove, plusStandPadCost, 
//                     plusPremPadCost, computedCarpetCost
// Returns: billingTotal - the bill total based on the users input 
// ---------------------------------------------------------------
double CalculateBillTotal
    (char giveDiscount, char padType, string storeMoveFurniture,  
    double subTotal, double plusStoreMove, double plusStandPadCost, 
    double plusPremPadCost, double computedCarpetCost)
{
    double billingTotal;
    if ((giveDiscount == 'C') && (padType == 'S') 
       && (storeMoveFurniture == "yes"))
    {
        billingTotal= subTotal + plusStandPadCost + plusStoreMove;
    }
    if ((giveDiscount == 'C') && (padType == 'P') 
       && (storeMoveFurniture == "yes")) 
    {
        billingTotal= subTotal + plusPremPadCost + plusStoreMove;
    }
    if ((giveDiscount == 'C') && (padType == 'S') 
       && (storeMoveFurniture == "no")) 
    {
        billingTotal= subTotal + plusStandPadCost; 
    }
    if ((giveDiscount == 'C') && (padType == 'P') 
       && (storeMoveFurniture == "no")) 
    {
        billingTotal= subTotal + plusPremPadCost; 
    }
    if ((giveDiscount == 'S') && (padType == 'S') 
       && (storeMoveFurniture == "yes")) 
    {
        billingTotal= computedCarpetCost + plusStandPadCost + plusStoreMove; 
    }
    if ((giveDiscount == 'S') && (padType == 'P') 
       && (storeMoveFurniture == "yes")) 
    {
        billingTotal= computedCarpetCost + plusPremPadCost + plusStoreMove; 
    }
    if ((giveDiscount == 'S') && (padType == 'S') 
       && (storeMoveFurniture == "no")) 
    {
        billingTotal= computedCarpetCost + plusStandPadCost; 
    }
    if ((giveDiscount == 'S') && (padType == 'P') 
       && (storeMoveFurniture == "no")) 
    {
        billingTotal= computedCarpetCost + plusPremPadCost;  
    }
    return (billingTotal);

}

// -------------------------------------------------------------
// Description: main reads the user's carpet space length and 
//              width and whether they want to remove furniture
//              and old carpet themselves or have the store
//              do that for them. Displays the calulated bill
//              and the associated fees and discounts 
// Returns: 0 if successful 
// -------------------------------------------------------------       
int main ()
{
    double computedCarpetCost;  // carpet cost 
    double computedTotalSquareYards; // total square yards of carpet
    double spaceLength;  
    double spaceWidth;
    char padType;
    char giveDiscount;  // defines whether user or store will remove old carpet
    string storeMoveFurniture; // defines whether the store will move furniture
    int numberRoom;  // number of rooms customer has to move
    double minusDiscount; // discount the customer receives if they remove old carpet
    double subTotal; // total of computedCarpetCost minus the minusDiscount
    double plusStoreMove; // cost incurred if the store moves customer's furniture
    double plusStandPadCost; // cost incurred if the customer uses the standard pad
    double plusPremPadCost; // cost incurred if the customer uses the premium pad
    double computedBillTotal; // total bill after discounts and fees
    
    // user input spaceLength and spaceWidth
    cout << " Carpet Purchase Bill Calculation Program" << endl;
    cout << endl;
    cout << " Enter space length and width in inches," << endl;
    cout << " separated by a space: ";
        cin >> spaceLength; 
        cout << " "; 
        cin >> spaceWidth; 
    cout << endl;
    // user selection -need to add libabry for capitalization
    cout << " Pad type: standard or premium (S/P)? "; 
        cin >> padType;
        // use cctype library to make user entry uppercase
        padType= toupper(padType);
    cout << " Who will remove the old carpet: store or customer (S/C): ";
        cin >> giveDiscount;
           // makes sure giveDiscount input is capitalized
           if (giveDiscount == 's') {
               giveDiscount = 'S';
           }
           if (giveDiscount == 'c') {
               giveDiscount = 'C';
           }
    cout << endl;
     
    cout << " Store to move furniture? (yes or no, all lowercase): ";
        cin >> storeMoveFurniture;
            if (storeMoveFurniture == "yes") {
                  cout << " Number of rooms? ";
                       cin >> numberRoom;
                  cout << endl;
            }          
    cout << endl;
       
    //Displays the bill output based on the user's inputs
    cout << fixed << showpoint << setprecision(2);          
    cout << " CARPET ORDER DETAILS" << endl;
    
    // Calls the CalculateSquareYards function to compute the total square yards 
    //       of the customer based on inputed space length and width.
    computedTotalSquareYards = CalculateSquareYards(spaceLength, spaceWidth);
    cout << " Square Yards Ordered:" << setw(22) 
         << computedTotalSquareYards << endl;
    
    cout << " Pad Type:";
        if (padType == 'S') {
            cout << setw(34) << " standard";
        }
        if (padType == 'P') {
            cout << setw(34) << " premium";
        }
    cout << endl;
    cout << endl;
        
    //Display calculated carpet bill
    cout << " CARPET BILL" << endl;
    // Calls the CalculatingCarpetCost to calculate carpet cost
    computedCarpetCost = CalculatingCarpetCost
                       (computedTotalSquareYards, carpetCostPerYard); 
    cout << " Carpet Cost:" << setw(31) << computedCarpetCost << endl;
    
    // calulates the discount and subtotal if customer removes old carpet
    if (giveDiscount == 'C') {
        minusDiscount=  discountPercent * computedCarpetCost;
        cout << " minus Discount:" << setw(28) << minusDiscount << endl;
        
        cout <<  setw(37) << " " << setfill('-') << setw(8) << " " << endl;
        
        subTotal= computedCarpetCost - minusDiscount;
        cout << setfill(' ')<< " Subtotal:" << setw(34) << subTotal << endl;
    }
    cout << " plus Pad Cost:";
        if (padType == 'S') {
            plusStandPadCost= standPadCost * computedTotalSquareYards;
            cout << setw(29) << plusStandPadCost << endl;
        }
        if (padType == 'P') {
            plusPremPadCost= premPadCost * computedTotalSquareYards;
            cout << setw(29) << plusPremPadCost << endl;
        }
    // calculates and displays moving cost fee if user wants the store to move 
    //           furniture for them
    if (storeMoveFurniture == "yes") {
        cout << " plus Moving Cost:"; 
        plusStoreMove= storeMoveCost * numberRoom;
        cout << setw(26) << plusStoreMove << endl;
        cout <<  setw(37) << " " << setfill('-') << setw(8) << " " << endl;               
    }
    else {
        cout <<  setw(37) << " " << setfill('-') << setw(8) << " " << endl;
    }
     
     // calls the CalculateBillTotal function to calulate
     //       and display the unqiue bill total   
    computedBillTotal= CalculateBillTotal(giveDiscount, padType, 
                       storeMoveFurniture, subTotal, plusStoreMove, 
                       plusStandPadCost, plusPremPadCost, computedCarpetCost);

    cout << " Bill Total:" << setfill(' ') << setw(32) 
         << computedBillTotal << endl; 
    
    cout << endl;
    system ("PAUSE");
    return 0;

}
       

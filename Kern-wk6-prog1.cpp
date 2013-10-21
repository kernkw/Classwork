// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 6, Program 1
// Program Description: Calculates and prints Rent2U rental bills.
// Input: Reads the letter for the car size rented.
//        Reads the number of days rented
//        Reads the number of miles driven
// Processing: Calualtes each unqiue bill based on the users inputed values
// Output: Displays a unqiue invoice of customer rental car bill,  omitting 
//         irrelevant fields and then prompts the user to determine if they
//         wish to exit or run program again
// ---------------------------------------------------------------------------
#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()
#include <cctype>                  // for toupper()

using namespace std;
    char compactCar = 'C';
    char midCar = 'M';
    char fullCar = 'F';
    char suvCar = 'S';
    double compactCharge = 22.91;
    double midCharge = 25.76;
    double fullCharge = 28.87;
    double suvCharge = 98.88;
       
//prototypes
char selectCarSize(char letterChoice);
double validateEntry( string prompt);
string carSizeAmount(char carSize);
double calculateMileageCharge (char carSize, double milesDriven,
    double daysRented);
double calculateTotalCarCharge (char carSize, double daysRented);
void CalculateBillTotal (double& carCharge, double& mileageCharge, 
    double& tax, double& total);      
void OutputInvoice (double daysRented, double milesDriven, double carCharge,
    double mileageCharge, double tax, double total, 
    string carSizeWord, char& anotherBill); 
// -------------------------------------------------------------
// Description: main reads the user's input and calls functions 
//              to calculate and display correct bill for car
//              rental.  Then runs a loop to determine if user
//              wants to enter another bill.
// Returns: 0 if successful 
// -------------------------------------------------------------          
int main()


{
    char userCarSelection; // car size selected by user
    char carSize;
    double daysRented;
    double milesDriven;
    double carCharge; //the car for using the rental car itself
    double tax;
    double total;
    double totalCarCharge;
    double mileageCharge;
    char anotherBill; // user enters whether they wish to process another bill
    string carSizeWord; // stores the users selected car size letter as a word

// the do- while loop will loop the entire program if anotherBill is 'y'    
do {
    cout << "This program will calculate a car rental bill for Rent2U." 
         << endl << endl;
    
    userCarSelection = selectCarSize(carSize);
    
    // if-else determines if car is an SUV then miles driven is not relevant
    if (userCarSelection == suvCar) {
        daysRented = validateEntry("Enter number of days rented: ");
        }
    else {
        daysRented = validateEntry("Enter number of days rented: ");
        milesDriven = validateEntry("Enter number of miles driven: ");
        }
    carSizeWord = carSizeAmount(userCarSelection);         
    carCharge = calculateTotalCarCharge (userCarSelection,daysRented);
    mileageCharge = calculateMileageCharge
                   (userCarSelection, milesDriven, daysRented);
    CalculateBillTotal (carCharge, mileageCharge, tax, total);
    OutputInvoice (daysRented, milesDriven, carCharge, mileageCharge,
                   tax, total,carSizeWord, anotherBill);
        
    } while (anotherBill == 'y');
    
    cout << endl;
    system ("PAUSE");
    return 0; 
}
// --------------------------------------------------------------------------
// Description: selectCarSize displays a menu of car sizes with their daily
//              cost.  Prompts user for (C,M,F or S) and error checks that a
//              valid choice is accepted. Then returns an uppercase choice.
// Input parameter: letterChoice - letter of the car size inputed by user
// Returns: carSize - uppercase validated letter choice of car size
// ---------------------------------------------------------------------------

char selectCarSize(char letterChoice)
{
    char carSize;
    
    cout << "Car sizes:" << endl << endl;
    cout << setw(5) << "C - Compact sizeat $ 22.91 per day" << endl;
    cout << setw(5) << "M - Mid size at $ 25.76 per day" << endl;
    cout << setw(5) << "F - Full size at $ 28.76 per day" << endl;
    cout << setw(5) << "S - SUV at $ 98.88 per day" << endl << endl;
    
    
    //input car letter
    cout << "Enter letter for car size rented: ";
    cin >> carSize;
    carSize = toupper(carSize);
    // validates users carSize entry
    while (carSize != compactCar && carSize != midCar 
          && carSize != fullCar && carSize != suvCar) {
    cout << "Please Re-enter letter for car size rented: ";
    cin >> carSize;
    carSize = toupper(carSize);
    }
    
    return carSize;     
}
// --------------------------------------------------------------------------
// Description: carSizeAmount - takes the user enter and validated entry and
//              outputs it as its name in letters.
// Input parameter: carSize - letter of the car size inputed by user
// Returns: carSizeWord - car size displayed in words
// ---------------------------------------------------------------------------
string carSizeAmount(char carSize)
{
    string carSizeWord;
    if (carSize == 'C')
       carSizeWord = "Compact";
    if (carSize == 'M')
       carSizeWord = "Mid size";
    if (carSize == 'F')
       carSizeWord = "Full size";
    if(carSize == 'S')
               carSizeWord = "SUV";
    
    return carSizeWord;
}
// --------------------------------------------------------------------------
// Description: validateEntry - takes number entry from user and error
//              checks it to be at least 1.
// Input parameter: prompt - prompts the user to enter a value
// Returns: num - the user inputed numeric value validated
// ---------------------------------------------------------------------------
double validateEntry( string prompt)
{
    double num;
    cout << endl;
    cout << prompt;
    cin >> num;
    
    while (num < 1) { 
    cout << "Entry must be at least 1." << endl;
    cout << prompt;
    cin >> num;
    }
    
    return num;    
}
// --------------------------------------------------------------------------
// Description: calculateMileageCharge - from the user input car size and 
//              the mileage driven, this function calculates the total
//              mileage charge.
// Input parameter: carSize - user inputed
//                  milesDriven - user inputed
//                  daysRented - user inputed
// Returns: mileageCharge - calculated fee for miles driven
// ---------------------------------------------------------------------------
double calculateMileageCharge (char carSize, double milesDriven, 
       double daysRented)
{
    double mileageCharge;
    if (carSize == compactCar) {
        if (static_cast<int>(milesDriven) / static_cast<int>(daysRented) >= 20) 
        {
        mileageCharge = ((milesDriven - (daysRented * 20)) * 0.05);
        }
        else {
        mileageCharge = 0;
        }
    }
    if (carSize == midCar) {
        if (static_cast<int>(milesDriven) / static_cast<int>(daysRented) >= 25) 
        {
        mileageCharge = ((milesDriven - (daysRented * 25)) * 0.07);
        }
        else {
        mileageCharge = 0;
        }
    }
    
    if (carSize == fullCar) {
        if (static_cast<int>(milesDriven) / static_cast<int>(daysRented) >= 30)
        {
        mileageCharge = ((milesDriven - (daysRented * 30)) * 0.09);
        }
        else {
        mileageCharge = 0;
        }
    }
    if (carSize == suvCar) {
        mileageCharge = 0;
    }
    
    return  mileageCharge; 
}
// --------------------------------------------------------------------------
// Description: calculateTotalCarCharge - from the user input car size and 
//              days rented, this function calculates the total
//              car charge.
// Input parameter: carSize - user inputed
//                  daysRented - user inputed
// Returns: totalCarCharge - calculated fee for car
// ---------------------------------------------------------------------------
double calculateTotalCarCharge (char carSize, double daysRented)
{
    double totalCarCharge;
    
    if (carSize == compactCar) {
        if (daysRented == 7) {
        totalCarCharge = (compactCharge * 6.5);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (compactCharge * 6.5) * 
            (static_cast<int>(daysRented) % 7);
            }   
            else {
            totalCarCharge =  ((compactCharge * 6.5) * 
            (static_cast<int>(daysRented) / 7)) + 
            (compactCharge * (static_cast<int>(daysRented) % 7));
            
            } 
        }
    }
    if (carSize == midCar) {
        if (daysRented == 7) {
        totalCarCharge = (midCharge * 6.5);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (midCharge * 6.5) * 
            (static_cast<int>(daysRented) % 7);
            }   
            else {
            totalCarCharge =  ((midCharge * 6.5) * 
            (static_cast<int>(daysRented) / 7)) + 
            (midCharge * (static_cast<int>(daysRented) % 7));
            
            }
        }
    }
    
    if(carSize == fullCar) {
        if (daysRented == 7) {
        totalCarCharge = (fullCharge * 6.5);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (fullCharge * 6.5) * 
            (static_cast<int>(daysRented) % 7);
            }   
            else {
            totalCarCharge =  ((fullCharge * 6.5) * 
            (static_cast<int>(daysRented) / 7)) + 
            (fullCharge * (static_cast<int>(daysRented) % 7));
            
            }
        }
    }
    if (carSize == suvCar) {
        if (daysRented == 7) {
        totalCarCharge = (suvCharge * 6.5);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (suvCharge * 6.5) * 
            (static_cast<int>(daysRented) % 7);
            }   
            else {
            totalCarCharge =  ((suvCharge * 6.5) * 
            (static_cast<int>(daysRented) / 7)) + 
            (suvCharge * (static_cast<int>(daysRented) % 7));
            
            }
        }
    }
    
    
    return  totalCarCharge;
    

}
// ----------------------------------------------------------------------
// CalculateBillTotal - Calculates the bill totals per the user's 
//                    selections, using only refenerance parameters
//
// reference parameters: carCharge - charge for the car
//                       mileageCharge - car for miles driven
//                       tax - the tax incurrec on bill
//                       total - the total cost of bill
// -----------------------------------------------------------------------
void CalculateBillTotal (double& carCharge, double& mileageCharge,
      double& tax, double& total) {

    tax = (carCharge + mileageCharge) * 0.115;
    total = carCharge + mileageCharge + tax;
}
// ----------------------------------------------------------------------
// OutputInvoice - Displays the output invoice of the rental car bill.
//               Uses nested loops to display only the invoice specific
//               billing items. Then prompts the user if they wish to 
//               process another bill or exit.
// input parameters: daysRented - days the car was rented
//                   milesDrive - miles driven
//                   mileageCharge- car for miles driven
//                   tax - the tax incurred on bill
//                   total - the total cost of bill
//                   carSizeWord - the car size in words
// refernce parameters: anotherBill - does the user want to process
//                      another bill
// -----------------------------------------------------------------------
void OutputInvoice (double daysRented, double milesDriven, 
     double carCharge, double mileageCharge, double tax, double total, 
     string carSizeWord, char& anotherBill) {      
    
    char carSize;
    char userCarSelection;
    
    CalculateBillTotal (carCharge, mileageCharge, tax, total);
    cout << endl << endl << endl;
    cout << "RENT2U RENTAL DETAILS" << endl;
    cout << setprecision(0) << fixed;
    // display of bill omits miles driven if SUV
    if (carSizeWord == "SUV") {
        cout << setw(14) << "Car Size:" << setw(17) << carSizeWord << endl;
        cout << setw(17) << "Days Rented:" << setw(14) << daysRented;
            if (daysRented == 1)
            cout << " day" << endl;
            else 
            cout << " days" << endl;
            }
    else {
        cout << setw(14) << "Car Size:" << setw(17) << carSizeWord << endl;
        cout << setw(17) << "Days Rented:" << setw(14) << daysRented;
            if (daysRented == 1)
            cout << " day" << endl;
            else 
            cout << " days" << endl;
    cout << setw(18) << "Miles Driven:" << setw(13) << milesDriven;
        if (milesDriven == 1)
        cout << " mile" << endl;
        else 
        cout << " miles" << endl;
        }
    cout << "BILL" << endl;
    cout << setprecision(2) << fixed;
    cout << setw(16) << "Car Charge:" << setw(7)<< "$" << setw(8) 
         << carCharge << endl;
    // display omits mileage charge if equal to zero
    if (mileageCharge == 0) {
        cout << setw(9) << "Tax:" << setw(14) << "$" << setw(8) 
             << tax << endl;
        cout << setw(22) << " " << setfill('-') << setw(10) << " "<< endl;  
        cout << setfill(' ') << setw(13) << "Total Bill:" << setw(10) 
             << "$" << setw(8) << total << endl;
    }
    else {
        cout << setw(20) << "Mileage Charge:" << setw(3) << "$" << setw(8) 
             << mileageCharge << endl;
        cout << setw(9) << "Tax:" << setw(14) << "$" << setw(8) 
             << tax << endl;
        cout << setw(22) << " " <<  setfill('-') << setw(10) << " "<< endl;
        cout << setfill(' ') << setw(13) << "Total Bill:" << setw(10) 
             << "$" << setw(8) << total << endl;  
        
    }
    // prompts user to enter a selection y or n and reasks if neither
    do {
        cout << endl;
        cout << "Calculate another bill (y/n)? ";
        cin >> anotherBill;
        } while (anotherBill != 'y' && anotherBill != 'n');
        cout << endl << endl;
    
} 


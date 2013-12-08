// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 5, Program 2
// Program Description: Computes the Total Amount that will be accumluated
//         for a given Monthly Amount.  Then Displays the per month caluation
//         and gives a summary of that data table.
// Input: Reads the user's dollar amount to be saved each month
//        Reads the annual interest rate (between 1 and 25)
//        Reads the dollar amount of the user;s goal.
// Processing: Read's only valid user input based on set parameters. Then 
//             calculates the monthly total accumulated per month.  Then using 
//             a loop it displays the months it will take to reach saving goal.
// Output: Displays the month number and associated Total Accumulated up to the 
//         month that they reach their goal.  Then displays some summary stats
//         on the table outputted.
// ---------------------------------------------------------------------------
#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()
#include <cctype>                  // for toupper()

using namespace std;
// ------------------------------------------------------------- 
// Description: VerifyDollar error checks the user inputed values
//              and prompts for new entry if number is 
//              not between 5 and 5000.
// Input parameter: Prompt - prompts the user to enter data
// Returns: dollarSaved - amount to save per month entered by user 
// ------------------------------------------------------------- 
double VerifyDollar (string Prompt)
{
    double dollarSaved;
    cout << Prompt;
    cin >> dollarSaved;
    
    while (dollarSaved < 5 || dollarSaved > 5000)
    {
          cout << "Invalid amount -- must save between 5 and 5000 dollars a month. Try again.";
          cout << endl;
          cout << Prompt;
          cin >> dollarSaved;
    }
    return dollarSaved;
}
// ------------------------------------------------------------- 
// Description: VerifyInterest error checks the user inputed values
//              and prompts for new entry if number is 
//              not between 1 and 25
// Input parameter: Prompt - prompts the user to enter data
// Returns: interest - interest to be earned through savings
// ------------------------------------------------------------- 
double VerifyInterest (string Prompt)
{
    double interest;
    cout << Prompt;
    cin >> interest;
    
    
    while (interest < 1 || interest > 25)
    {
          cout << "Invalid amount -- must be an annual rate between 1 and 25 percent. Try again.";
          cout << endl;
          cout << Prompt;
          cin >> interest;
    }
    return interest;
}
// ------------------------------------------------------------- 
// Description: VerifyGoalAmount error checks the user inputed values
//              and prompts for new entry if number is 
//              above 1,000,000.
// Input parameter: Prompt - prompts the user to enter data
// Returns: goalAmount - savings goal set by user
// -------------------------------------------------------------
double VerifyGoalAmount (string Prompt)
{
    double goalAmount;
    cout << Prompt;
    cin >> goalAmount;
    
    while (goalAmount >= 1000000)
    {
          cout << "Invalid amount -- must be under 1,000,000. Try again.";
          cout << endl;
          cout << Prompt;
          cin >> goalAmount;
    }
    return goalAmount;
}
// ------------------------------------------------------------------
// Description: CalculateFactor determines the factor needed
//              for equation to find the total monthly amount
// Input parameter: noMonths - # months
//                  annualInterest- inerest gained
// Returns: factor-the factor variable needed for monthly calculation
// -------------------------------------------------------------------
double CalculateFactor (int noMonths, double annualInterest)
{
       double factor;
       factor = exp(noMonths * log(1 + annualInterest));

       return factor;      
}
// --------------------------------------------------------------------------
// Description: CalculateTotalMonthly uses the factor variable to calculate
//              how much money the user will have each month
// Input parameter: factor- the factor variable needed for monthly calculation
//                  dollarSavedPerMonth- amount user will save per month
//                  annualInterest- inerest gained
// Returns: totalMonthly- the amount of money for a given month
// ---------------------------------------------------------------------------
double CalculateTotalMonthly 
       (double factor, double dollarSavedPerMonth, double annualInterest)
{
       double totalMonthly;
       totalMonthly = ((factor - 1)* dollarSavedPerMonth)/ annualInterest;
       totalMonthly = floor((totalMonthly * 100) + 0.5) / 100.0;
       return totalMonthly;      
}
// -------------------------------------------------------------
// Description: main reads the user's input and runs a loop to
//              display the data in the proper number of rows 
//              and columns.
// Returns: 0 if successful 
// -------------------------------------------------------------   
int main ()


{
    double dollarSavedPerMonth; // amount of money to be saved by user each month
    double annualInterest;// interest that year
    double dollarAmountGoal; //how much money the user's goal is for
    int noMonths; //the number of months
    double totalMonthly;
    double factor;
    

    cout << "Program will calculate the amount accumulated every month you save," 
         << "until you reach your goal." << endl << endl;
    
   
    dollarSavedPerMonth = VerifyDollar("Enter the dollar amount to be saved each month: ");
    cout << endl;
    
    annualInterest = VerifyInterest("Enter the annual interest rate (between 1 and 25): ");
    annualInterest = (annualInterest/100)/ 12;
    cout << endl;
    
    dollarAmountGoal = VerifyGoalAmount("Enter the dollar amount of your goal: ");
    
    noMonths = 0;
    
    factor = CalculateFactor (noMonths, annualInterest);
    totalMonthly = CalculateTotalMonthly (factor, dollarSavedPerMonth, annualInterest);
    
    cout << endl;
    cout << "Month" << setw(8) << "Total" << endl;
    cout << "Number" << setw(13) << "Accumulated" << endl;
    cout << setfill('-') << setw(8) << "  ";
    cout << setfill('-') << setw(11) << " "<< endl;
    
    // perform loop until reach goal (totalMonthly <= dollarAmountGoal)
    for (noMonths=1;  totalMonthly <= dollarAmountGoal; noMonths++)
        {
            factor = CalculateFactor (noMonths, annualInterest);
            totalMonthly = CalculateTotalMonthly (factor, dollarSavedPerMonth, annualInterest); 
            cout << setfill(' ');
            cout << setw(5) << noMonths;
            cout << setw(12) << setprecision(2) << fixed << showpoint;
            cout << totalMonthly << endl;
               
               }
    cout << endl;
    cout << "At an annual interest rate of" << setw(15) 
         << setprecision(3) << ((annualInterest* 100)* 12) << " %" << endl;
    cout << "With a monthly savings of" << setw(19) 
         << setprecision(2) << dollarSavedPerMonth << endl;
    cout << "It will take" << setw(32) << (noMonths - 1) << " months" << endl;
    cout << "To reach your goal of" << setw(23) << dollarAmountGoal << endl;
    cout << "With a final accumulation of" << setw(16) 
         << totalMonthly << endl;
        

    cout << endl;
    system ("PAUSE");
    return 0;
  
    
    
}

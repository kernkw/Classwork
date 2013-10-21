// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 3, Program 2 
// Program Description: Computes the deduction allocated for a student
//                      taxpayer using the logic of an IRS worksheet
// Input: Reads the student taxpayer's filing status
//        Reads the student taxpayer's interest paid on student loans
//        Reads the student taxpayer's total income
//        Reads the student taxpayer's adjustments to income
// Processing: Calculates the student taxpayers tax deductions based on the IRS
//             logic for giving deductions
// Output: Displays the student taxpayer's loan interest deduction
// -----------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()


using namespace std;

// global constants
const string filingSingle = "Single";
const string filingJointlyMarried = "Married, Filing Jointly";
const string filingHeadHousehold = "Head of Household";
const string filingWidow = "Qualifying Widow";
const string filingSeperateMarried = "Married, Filing Separately";
 
// --------------------------------------------------------------------
// Description: CalculatePercentExcluded calculates the 
//              percentage of  the deduction excluded
//              given the user inputed filing status
// Input parameter: filingNumber - user defined filing status 
//                  overAmount - amount over limit
// Returns: percentExcluded - percentage of deduction excluded
// --------------------------------------------------------------------- 
double CalculatePercentExcluded (int filingNumber, double overAmount) 
{
    double percentExcluded;
        if (filingNumber == 2) {
            percentExcluded= overAmount/30000;
        }
        else {
            percentExcluded= overAmount/15000;
        }
        if (percentExcluded > 1.000) {
            percentExcluded= 1.000;
        }    
    return (percentExcluded);
}            

// ------------------------------------------------------------------------
// Description: CalculateAdjustedIncome calculates the adjusted income
//              using the user inputed adjustmentincome
// Input parameter: incomeAdjustments - user inputed value
//                  totalIncome - user inputed value
// Returns: adjustedIncome - displays the absolute value of the 
//          incomeAdjustments minus totalIncome
// -------------------------------------------------------------------------           
 double CalculateAdjustedIncome (double incomeAdjustments, double totalIncome)
{
    double adjustedIncome;
    adjustedIncome= abs(incomeAdjustments - totalIncome); 
    return (adjustedIncome);
}

// ----------------------------------------------------------- 
// Description: FilingStatus stores the user inputed filing 
//              number as an assoicated string value
// Input parameter: filingNumber - user inputed selection
// Returns: filingName - string associated with filingNumber
// -----------------------------------------------------------
string FilingStatus(int filingNumber)
{
    string filingName;
        if (filingNumber == 1) { 
            filingName= filingSingle;
        }
        if (filingNumber == 2) { 
            filingName= filingJointlyMarried;
        }
        if (filingNumber == 3) { 
            filingName= filingHeadHousehold;
        }
        if (filingNumber == 4) { 
            filingName= filingWidow;
        } 
     return (filingName);
} 
   
// ----------------------------------------------------------- 
// Description: main reads the radius of a circle and calls 
// a function to calculate the area. Displays radius and area. 
// Returns: 0 if successful 
// ----------------------------------------------------------- 
int main ()
{
    int filingNumber;
    double interestPaid; // total interest paid on loans in 2012
    double totalIncome; // total income (from 1040 line 22)
    double incomeAdjustments; // adjustments to income 
    double incomeLimit; 
    double overAmount; // amount over income limit
    double interestDeduction;
    double computePercentExcluded; // percentage of deduction excluded
    double amountExcluded; // total amount excluded
    double computeAdjustedIncome; // incomeAdjustments - totalIncome
    string DisplayFilingStatus; // filing status string name 
      
    cout << " Student Loan Interest Deduction Worksheet Program" << endl;
    cout << " 1 - Single" << endl;
    cout << " 2 - Married, Filing Jointly" << endl;
    cout << " 3 - Head of Household" << endl;
    cout << " 4 - Qualifying Widow(er)" << endl;
    cout << " 5 - Married, Filing Separately " << endl;
    cout << " Enter your filing status from above (1-5): ";
        cin >> filingNumber;
        // calls FilingStatus function to store user inputed number as 
        //       the assoicated filing status
        DisplayFilingStatus= FilingStatus(filingNumber);
    cout << endl;
    // if user files as Married, Filing Separately
    //    display message and end program  
    if (filingNumber == 5) {
        cout << endl;
        cout << endl;
        cout << " Student Loan Interest Deduction is not allowed for Married";
        cout << " Filing Separately" << endl;
        cout << endl;
        cout << " ***Enter 0 on form 1040 line 33" << endl;
        cout << endl;
        system ("PAUSE");
        return 5;      
    }
    // otherwise prompt user to enter other inputs
    else {
        cout << " Enter Interest Paid on Student Loans:  "; 
            cin >> interestPaid;
            if (interestPaid > 2500) { // set interest paid max to 25000
                interestPaid= 2500;
            }
        cout << endl;
        cout << " Enter Total Income (from 1040 line 38):  ";
             cin >> totalIncome; 
        cout << endl;
        cout << " Enter Adjustments to Income (from 1040, lines 23-32):  ";
             cin >> incomeAdjustments; 
        cout << endl;
    
        // calls CalculateAdjustedIncome function
        computeAdjustedIncome= CalculateAdjustedIncome
        (incomeAdjustments, totalIncome); 
        
        
        if (filingNumber == 2) {  //set income limit for line 5
            incomeLimit= 120000;
        }
        else {
            incomeLimit= 60000;
        }  
        
        if (computeAdjustedIncome < incomeLimit) { // line 6 check
            interestDeduction= interestPaid;
        }
        else {
            overAmount= computeAdjustedIncome - incomeLimit;
            
            // calls CalculatePercentExcluded function
            computePercentExcluded= CalculatePercentExcluded
                                    (filingNumber, overAmount);
            // computes excluded amount and interest deduction
            //          by using computePercentExcluded
            amountExcluded= interestPaid * computePercentExcluded;
            interestDeduction= abs(amountExcluded - interestPaid);
        }   
    }
               

    cout << endl;
    cout << endl;
    cout << endl;
    
    // displays calculated output as a student loan interest deduction worksheet
    cout << "     Student Loan Interest Deduction Worksheet" << endl;
    cout << endl;
    cout << "     Filing Status:" << setw(48) << DisplayFilingStatus << endl;
    cout << endl;
    
    cout << fixed << showpoint << setprecision(2);
    cout << " 1.  Total Interest Paid on Loans in 2012:" << setw(25) 
         << interestPaid << endl;
    cout << endl;
    cout << " 2.  Total Income (from 1040 line 22): " << setw(28) 
         << totalIncome << endl;
    cout << " 3.  Adjustments to Income (from 1040 lines 23-32):" 
         << setw(16) << incomeAdjustments << endl;
    cout << " 4.  Adjusted Income:" << setw(46) 
         << computeAdjustedIncome << endl;
    cout << " 5.  Income Limit: " << setw(48) 
         << incomeLimit << endl;
    // skip 6-8 
    if (computeAdjustedIncome < incomeLimit) {
        cout << endl;
        cout << " 9.  Student Loan Interest Deduction:" << setw(30)
             << interestDeduction << endl;
        cout << endl;
        cout << " ***Enter amount from worksheet line 9 on form 1040 line 33";
        cout << endl;
    }
    // otherwise display output for 6-8
    else {
        cout << " 6.  Amount over Limit: " << setw(43) << overAmount << endl;
       
        cout << fixed << showpoint << setprecision(3);      
        cout << " 7.  Percentage of deduction excluded: " << setw(28) 
             << computePercentExcluded << endl;
             
        cout << fixed << showpoint << setprecision(2);     
        cout << " 8.  Amount excluded: " << setw(45) << amountExcluded << endl;
        cout << endl;
        
        cout << " 9.  Student Loan Interest Deduction:" 
             << setw(30) << interestDeduction << endl;
        cout << endl;
        
        cout << " ***Enter amount from worksheet line 9 on form 1040 line 33";
        cout << endl;
    }
     
      
    cout << endl;
    system ("PAUSE");
    return 0;
      
      
      
}

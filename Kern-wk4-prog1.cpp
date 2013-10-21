// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 4, Program 1 
// Program Description: This program reads what type of student the user is
//         and how many credits they are taking.  Then computes the fees 
//         charged on the student tuiton bill.
// Input: Reads whether the user is an undergraduate, graduate or non- degree
//              seeking student
//        Reads the number of credit hour that the studnet is enrolling in
// Processing: Calculates the fee rate per the users selections then calculates
//             the student fees charged to that student.
// Output: Displays the Student Fees Summary in a table ommiting otuputing 
//         the number of credit hours and rate used if the student type is
//         not degree seeking 
// -----------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()


using namespace std;

const double CREDIT_COST= 465; // cost per credit hour
const int CREDIT_HOURS_LOW = 1; // minimum number of credit hours
const int CREDIT_HOURS_LOW_MID = 4; // low-mid minimum number of credit hours
const int CREDIT_HOURS_MID = 10; // mid minimum number of credit hours
const int CREDIT_HOURS_MID_HIGH = 15; // mid-high minimum number of credit hours
const int CREDIT_HOURS_HIGH = 18; // high minium number of credit hours
const double FLAT_FEE = 100; // flat fee charged for non-degree seeking
const double RATE_LOW = 0.03; // percentage of tuition lowest credit hours
// percentage of tuition lowest to mid credit hours for undergraduates
const double RATE_UNDER_LOW_MID = 0.028;
// percentage of tuition lowest to mid credit hours for graduates
const double RATE_GRAD_LOW_MID = 0.027;
const double RATE_UNDER_MID = 0.025;
const double RATE_GRAD_MID = 0.024;
const double RATE_UNDER_MID_HIGH = 0.022;
const double RATE_GRAD_MID_HIGH = 0.021;
const double RATE_HIGH = 0.019; // percentage of tuition highest bracket credit hours



//------------------------------------------------------------------------------
// Description: ComputeFeeRate determines the fee rate to be used for 
//                each student depending on their number of credit hours 
//                and whether they are undergraduates or gradtuate students.
// Input parameter: studentType - U or G
//                  numCreditHours - user inputed credit hours taken
// Returns: feeRate - the fee rate to be used in student's tutiton calculation
//------------------------------------------------------------------------------
double ComputeFeeRate (char studentType, int numCreditHours)
{      
       double feeRate;
       if (numCreditHours > CREDIT_HOURS_HIGH)
       { 
          feeRate = RATE_HIGH;
          }
       else if (numCreditHours >= CREDIT_HOURS_MID_HIGH) {
            if (studentType == 'U') {
               feeRate = RATE_UNDER_MID_HIGH;
            }
            else {
                 feeRate = RATE_GRAD_MID_HIGH;
            }
       }
       else if (numCreditHours >= CREDIT_HOURS_MID) {
                if (studentType == 'U') {
               feeRate = RATE_UNDER_MID;
            }
            else {
                 feeRate = RATE_GRAD_MID;
            }
       }
       else if (numCreditHours >= CREDIT_HOURS_LOW_MID) {
                if (studentType == 'U') {
               feeRate = RATE_UNDER_LOW_MID;
            }
            else {
                 feeRate = RATE_GRAD_LOW_MID;
            }
       }
       else {
            feeRate = RATE_LOW;
       } 
       return (feeRate);    
}
//------------------------------------------------------------------------------
// Description: ComputeWriteStudentType - processes the student type selection
//              as a letter, then return that letter as the string of its 
//              associated word
// Input parameter: studentType - U or G
// Returns: wordStudentType - studentType stored as the word it abbreviates
//------------------------------------------------------------------------------
string ComputeWriteStudentType ( int studentType)
{
       string wordStudentType;
       if (studentType == 'U'){
          wordStudentType = "Undergraduate";
       }
       else if (studentType == 'G'){
          wordStudentType = "Graduate";
       }
       else {
       wordStudentType = "Not degree seeking";
       }
       return (wordStudentType);      
}
// --------------------------------------------------------------------- 
// Description: main reads the user inputed student type and
// then depending on their answer prompts user input number of credit
// hours. Calls functions to caluate the student tutiton rate.
// Displays the Student Fees Summary depending on users selections.
// Returns: 0 if successful 
// --------------------------------------------------------------------- 
int main ()
{
    char studentType; // is the student U, G or N
    int numCreditHours; // total credit hours to be taken by student
    double studentFee; // the cost the student has to pay
    double writeComputeFeeRate; // the computed fee rate for a particular student
    string writeStudentType; //writes the student type abbreviation as a word
    
    cout << "Student Fees Calculation Program" << endl << endl;
    cout << "Student types choices:" << endl;
    cout << "U - undergraduate" << endl;
    cout << "G - graduate" << endl;
    cout << "N - non-degree seeking" << endl << endl;
    cout << "Enter student type: ";
         cin >> studentType;
        // use cctype library to make user entry uppercase
        studentType = toupper(studentType);
        // call function to store student type int as a word string
        writeStudentType = ComputeWriteStudentType (studentType);
    cout << endl;
    // calulate studentFee depending on user input to studentType
    if ((studentType == 'U') || (studentType == 'G')) {
        cout << "Enter number of credit hours enrolled in: ";
             cin >> numCreditHours;
        cout << endl; 
        writeComputeFeeRate = ComputeFeeRate (studentType, numCreditHours);
        studentFee = (CREDIT_COST * numCreditHours) * writeComputeFeeRate;
    
    }
    else {
         studentFee = FLAT_FEE;
    }
    
    // Display output table based on users inputs
    cout << "Student Fees Summary" << endl << endl;
    if ((studentType == 'U') || (studentType == 'G')) {
        cout << setw(16) << "Student Type" << setw(30) 
             << writeStudentType << endl;
        cout << setw(17) << "Credit Hours:" << setw(29) 
             << numCreditHours << endl;
        cout << fixed << showpoint << setprecision(1);  
        cout << setw(14) << "Rate Used:" << setw(31) 
             << writeComputeFeeRate * 100 << "%" << endl << endl;
        cout << fixed << showpoint << setprecision(2);
        cout << setw(17) << "Student Fees:" << setw(29) 
             << studentFee << endl << endl; 
    }
    else {
         cout << setw(16) << "Student Type:" << setw(30) 
              << writeStudentType << endl << endl;
         cout << fixed << showpoint << setprecision(2);
         cout << setw(16) << "Student Fees:" << setw(30) 
              << studentFee << endl << endl;
         
    }
    system ("PAUSE");
    return 0;
}

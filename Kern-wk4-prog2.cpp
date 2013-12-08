// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 4, Program 2 
// Program Description: This program prompts the user to input the first 
//         letter of a color.  If they input B or G additional letters 
//         are required from the user.  This program displays the numeric 
//         digit associated with their color entry.
// Input:  Reads the first letter of the color
//         Reads the second letter of the color
//         Reads the third letter of the color
// Processing: Uses nested swtich statements to assoicate the users entry 
//             with the appropraite output statement.
// Output: Displays a string contianing the numeric value associated with 
//         the users color input
// -----------------------------------------------------------------------

#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions
#include <cstdlib>                 // for system()

using namespace std;

// -----------------------------------------------------------------------
// Description: main reads the first letter inputed by user 
//              and then using nested swtoch statements, either prompts
//              the user for more letters.  
//              Display's the numeric value assoicated with the user's
//              color selection
// Returns: 0 if successful
// ------------------------------------------------------------------------
int main ()
{
    char firstLetter; // first letter entered
    char secondLetter; // second letter entered
    char thirdLetter; // third letter entered
    
    cout << "Color Code Program" << endl << endl;
    // first required user input
    cout << "Enter the first letter of the color: ";
        cin >> firstLetter;
    cout << endl << endl;
        // use cctype library to make user entry uppercase
        firstLetter = toupper(firstLetter);

// output in nested switch statement
    switch (firstLetter) {
            
        case 'R' :
            cout << "Red stands for digit 2." << endl << endl;
            break;
        case 'O' :
            cout << "Orange stands for digit 3." << endl << endl;
            break;
        case 'Y' :
            cout << "Yellow stands for digit 4." << endl << endl;
            break;
        case 'V' :
            cout << "Violet stands for digit 7." << endl << endl;
            break;
        case 'W' :
            cout << "White stands for digit 9." << endl << endl;
            break;
        case 'B' : // if user inputs 'b' or 'B' as first letter process here
            cout << "Please enter the second letter: ";
                cin >> secondLetter;
                cout << endl << endl;
                secondLetter = toupper(secondLetter);
            
            switch (secondLetter) {
                
                case 'R' :
                    cout << "Brown stands for digit 1." << endl << endl;
                    break;
                case 'L' : // if user inputs second letter as 'L' or 'l' process here
                    cout << "Please enter third letter: ";
                    cin >> thirdLetter;
                    cout << endl << endl;
                    thirdLetter = toupper(thirdLetter);
                    // diplays output based on third letter selection
                    switch (thirdLetter) {
                        case 'A' :
                             cout << "Black stands for digit 0." << endl << endl;
                             break;
                        case 'U' :
                             cout << "Blue stands for digit 6." << endl << endl;
                             break;
                        default :
                                cout << "Unknown Color" << endl << endl;
                    }
                default :
                cout << "Unknown Color" << endl << endl;
                break;
                }
        case 'G' : // if user inputs 'g' or 'G' as first letter process here
            cout << "Please enter the next two letters: ";
                cin >> secondLetter >> thirdLetter;
                secondLetter = toupper(secondLetter);
                thirdLetter = toupper(thirdLetter);
                cout << endl << endl;
            // depends on both second and third letter entry uses a nested switch to
            // determine output
            switch (secondLetter) {
                case 'R' :
                    switch (thirdLetter) {
                        case 'A' :
                            cout << "Gray stands for digit 8." << endl << endl;
                            break;
                        case 'E' :
                            cout << "Green stands for digit 5." << endl << endl;
                            break;
                        default :
                            cout << "Unknown Color" << endl << endl;
                    }
                break;
                default :
                        cout << "Unknown Color" << endl << endl;
            break;                    
            }
        break;    
        default :
            cout << "Unknown Color" << endl << endl;           
    }


    system ("PAUSE");
    return 0;

}


// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 2, Program 2
// Program Description:  Calculates the slant height, surface area, and 
//   volume of a square pyramid from user inputed base length and height.
//   Input: Reads the user inputed base length and height.
//   Processing: Calculates the slant height, surface area, and 
//   volume using their mathematical formulas.
//   Output: Displays the inputed values and calulated dimensions of
//   the square pyramid.
// -----------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions

 using namespace std;
 
 // ----------------------------------------------------------------------
// OutputCalculations - Outputs calculated pyramid dimensions  
//
// parameters: pyramidSlantHeight - slant height of pyramid
//             pyramidSurfaceArea - surface area of pyramid
//             pyramidVolume - volume of the pyramid
// -----------------------------------------------------------------------
 void OutputCalculations 
      (float pyramidSlantHeight, float pyramidSurfaceArea, float pyramidVolume)
 {
      cout << endl; 
      cout << " Pyramid Slant Height is" << setw(9) 
           << pyramidSlantHeight << " inches" << endl;
      cout << " Pyramid Surface Area is" << setw(9) 
           <<  pyramidSurfaceArea << " square inches" << endl;     
      cout << " Pyramid Volume is" << setw(15) 
           << pyramidVolume << " cubic inches" << endl;
      return;                 
 }
// -----------------------------------------------------------
// Description: main dispalys a program description then reads 
//   pyrmaid base length and height from user, and calls
//   a function to calculate the right pyramid's slant height,
//   surface height, and volume.
//   Displays inputed values and the calculated right pyramids
//   dimensions.
//   Returns: 0 if successful
// ----------------------------------------------------------- 
 int main ()
 {
     float pyramidBaseLength;
     float pyramidHeight;
     float pyramidSlantHeight;
     float pyramidSurfaceArea;
     float pyramidVolume;
     float baseSquared;  // Pyramid base length squared
     
     // Displays program description to the user 
     cout << " This program will calculate a right pyramid's slant height, " 
          << endl;
     cout << " surface area and volume. " << endl;
     cout << endl;
     cout << " Please enter the right pyramid's base length and height in " << endl;
     cout << " inches to receive these calculations." << endl;
     cout << endl;
     cout << endl;
     cout << endl;
     
     cout << " Right Pyramid Calculations" << endl;
     cout << endl;
     
     // Prompts user to input the pyramids base length and height
     cout << " Enter pyramid base length (in inches): "; 
     cin >> pyramidBaseLength;
    
     cout << " Enter pyramid height (in inches): "; 
     cin >> pyramidHeight;
     
     cout << endl;
     cout << endl;
      
     // Displays user inputed base length and height
     cout << fixed << showpoint << setprecision(2);
     cout << " RESULTS:" << endl;
     cout << " For a Right Pyramid with" << endl;
     cout << setw(19) << "Base Length of" << setw(14) << pyramidBaseLength 
          << " inches" << endl;
     cout << setw(14) << "Height of" << setw(19) << pyramidHeight 
          << " inches" << endl;
          
     // Perfoms the needed calculations to run OutputCalculations function
     //  based on predetermined mathematical formulas
     baseSquared=  pow(pyramidBaseLength , 2);
          
     pyramidSlantHeight= sqrt(pow( pyramidHeight , 2) + (0.25 * baseSquared));
     
     pyramidSurfaceArea= pyramidBaseLength* (pyramidBaseLength 
                         + sqrt(baseSquared + 4 * pow( pyramidHeight , 2)));
         
     pyramidVolume= (baseSquared * pyramidHeight) / 3;
     
     // Displays output by calling the void OutputCalculations function
     OutputCalculations(pyramidSlantHeight, pyramidSurfaceArea, pyramidVolume);
                     
     cout << endl;   
     system ("PAUSE");
     return 0;    
 }

// ----------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 2, Program 1
// Program Description:  Calculates the magnetic field magnetic field 
//   in the center of a Helmholtz coil
//   Input: Reads the user observed values of the Helmholtz coils
//   Processing: Calculates the magnetic field in tesla
//   Output: Displays the user inputed values and the calulated magnetic 
//   field in telsa.
// -----------------------------------------------------------------------


#include <iostream>                // for I/O
#include <iomanip>                 // for formatting output
#include <cmath>                   // for pow functions

 using namespace std;
 
 
 double vacuumperm= 1.2566370614E-6; // Global constant for vacuum permeability
 
// ----------------------------------------------------------------------
// nameHeader - Displays the program's description and name
// parameter: none
// -----------------------------------------------------------------------
 
 void nameHeader()
 {     
      cout << setw(46) << "Magnetic Field within Helmholtz coils" << endl;
      cout << setw(24) << "by" << endl;
      cout << setw(28) << "Kyle Kern" << endl;
      
      cout << endl;
      
 }
// -----------------------------------------------------------
// Description: main reads the number of turns per coil, the 
//   radius of the coils, and the current in the coils and calls
//   a function to calculate the magnetic field in the center
//   of a Helmholtz coil.
//   Displays inputed values and the calculated magnetic field.
//  Returns: 0 if successful
// ----------------------------------------------------------- 
 
  int main() 
 {
      int turnsCoil;               // Number of turns in each coil
      double radiusCoil;           // Radius of the coil loops in meters
      double currentCoil;          // Current in the coils
      double magneticField;        // Magnetic flux density
      
      nameHeader(); // Calls the nameHeader function
      // Prompts the user to enter vaules from the coils   
      cout << " Enter the number of turns per coil:     ";
      cin >> turnsCoil;
      cout << endl;

      cout << " Enter the radius of the coils (in meters):     ";
      cin >> radiusCoil;
      cout << endl;

      cout << " Enter the current in the coils (in amperes):     ";
      cin >> currentCoil;
      cout << endl;
      cout << endl;
      
      // Display results
      cout << " RESULTS:"<< endl;
      cout << fixed << right << showpoint << setprecision(3);
      cout << "   Turns per coil:" << setw(22) << turnsCoil << " turns" << endl;
      cout << "   Radius of the coils:" << setw(17) << radiusCoil << " meters" << endl;
      cout << "   Current in the coils:" << setw(16) << currentCoil << " amps" << endl;
   
      cout << endl;
   
      cout << scientific << showpoint << setprecision(5);  
      cout << "   Vacuum Permeability:" << setw(17) << vacuumperm 
           << " telsa meter/ampere" << endl;
    
      cout << endl;
    
      // Calculates magnetic field formula using user inputed values
      cout << scientific << showpoint << setprecision(5);
      magneticField= pow(0.8 , 1.5) * 
                   ((vacuumperm * turnsCoil * currentCoil) / radiusCoil ) ;
                   
          
      cout << "     Magnetic Field: " << setw(19) << magneticField
           << " telsa" << endl;
      
      

      cout << endl;
      system ("PAUSE");
      return 0;
  }
      
      
      
      
      
      

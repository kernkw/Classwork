// ---------------------------------------------------------------------------
// Author: Kyle Kern
// Class:  CS361
// Assignment: Week 7, Program 2
// Program Description: This program uses many of the same functions used
//         in Rent2U company to calculate and display bills for company
//         RentItNow.  The user is asked to enter their car type, name, the
//         days they are renting the car and when they wish to pick it up.
//         Program repeats until customer enters e to exit.
// Input: Reads the letter for the car size rented.
//        Reads the customer's first and last name.
//        Reads the number of days rented.
//        Reads the year, month and day the customers wishes to pick up the car.
// Processing: Calculates rental fee and the date the cusotmer will
//             be picking up the car and returning it, inlcuding the day of the
//             week associated.
// Output: Displays the customer's bill, including any discounts or subtotals
//         required.
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
    double compactCharge = 26.82;
    double midCharge = 29.91;
    double fullCharge = 33.79;
    double suvCharge = 105.22;

//prototypes
char selectCarSize(char letterChoice);
double validateEntry( string prompt);
string carSizeAmount(char carSize);
double calculateTotalCarCharge (char carSize, double daysRented);
void CalculateBillTotal (double& carCharge, double& tax, double& total);
void OutputInvoice (double daysRented,
     double carCharge, double tax, double total,
     string carSizeWord, string firstName,
     string lastName,double month, double day, double year,
     double returnDay, double returnMonth, double returnYear,
     double weeklyCarCharge, double dayCarCharge, int nWeeks,int nDays);
void ReturnDate (double maxDays, double daysRented, double year, double month,
      double day, double& returnYear,
     double& returnMonth, double& returnDay);

double daysInMonth (double year, double month);
double GetValidNumber( string prompt, double lowerLimit, double upperLimit);
void dayOfWeek (double month, double year, double day);
double CalculateWeekCarCharge (char carSize, double daysRented);
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
    double carCharge; //the car for using the rental car itself
    double tax;
    double total;

    double year; // the year the car is picked up
    double month;// the month the car is picked up
    double day;// the day the car is picked up
    string firstName;
    string lastName;
    double maxDays; // the total number of days in a month
    double returnYear;// the year the car is returned
    double returnMonth;// the month the car is returned
    double returnDay;// the day the car is returned

    string carSizeWord; // stores the users selected car size letter as a word
    double weeklyCarCharge; // the charge of the weeks in the days rented
    double dayCarCharge; // the charge of the car rental without weekly rate
    int nWeeks; // number of weeks car was rented
    int nDays; // number of days the car was rented

// the do- while loop will loop the entire program if anotherBill is 'y'
do {
    cout << "This program will calculate a car rental bill for Rent2U."
         << endl << endl;

    userCarSelection = selectCarSize(carSize);
       if (userCarSelection == 'E')
       {
          system ("PAUSE");
          return 0;
       }
    cout << endl;
    // ignore previous cin input to use getline() for string input
    cin.ignore();
    cout << "Enter customer first name: ";
    getline (cin, firstName);

    cout << "Enter customer last name: ";
    getline(cin, lastName);
    cout << endl;

    daysRented = GetValidNumber
               ("Enter number of days rented (1-365): ", 1 , 365);
    cout << endl;
    cout << "Enter the date of pick up below" << endl;
    year = GetValidNumber
               ("     Enter pick up year (2013-2023): ", 2013 , 2023);
    month = GetValidNumber
               ("     Enter pick up month (1-12):  ", 1 , 12);
    maxDays = daysInMonth (year, month);

    // still need to input maxdays into prompt as well as
    day = GetValidNumber
               ("     Enter pick up day (1-maxDays): ", 1, maxDays);

    carSizeWord = carSizeAmount(userCarSelection);
    carCharge = calculateTotalCarCharge (userCarSelection,daysRented);
    CalculateBillTotal (carCharge, tax, total);
    ReturnDate (maxDays,daysRented,year, month, day,returnYear,
               returnMonth, returnDay);
    weeklyCarCharge = CalculateWeekCarCharge (userCarSelection, daysRented);

    OutputInvoice (daysRented, carCharge, tax, total,carSizeWord,
                   firstName, lastName, month, day, year,
                   returnDay, returnMonth, returnYear, weeklyCarCharge,
                   dayCarCharge, nWeeks, nDays);
    system ("PAUSE");
    cout << endl << endl;
     } while (userCarSelection != 'E');

    cout << endl;
    system("read -p 'Hit Enter to continue. '");
    cout << endl;
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
    cout << setw(5) << "C - Compact sizeat $ 26.82 per day" << endl;
    cout << setw(5) << "M - Mid size at $ 29.91 per day" << endl;
    cout << setw(5) << "F - Full size at $ 33.79 per day" << endl;
    cout << setw(5) << "S - SUV at $ 105.22 per day" << endl << endl;
    cout << setw(5) << "E - Exit Program" << endl << endl;


    //input car letter
    cout << "Enter letter for car size rented: ";
    cin >> carSize;
    carSize = toupper(carSize);

        // validates users carSize entry
        while (carSize != compactCar && carSize != midCar
              && carSize != fullCar && carSize != suvCar && carSize != 'E')
        {
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

    while (num < 1 || num > 365) {
    cout << "Entry must be between 1 and 365." << endl;
    cout << prompt;
    cin >> num;
    }

    return num;
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
        totalCarCharge = (compactCharge * 6.3);

        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (compactCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);
            }
            else {
            totalCarCharge =  ((compactCharge * 6.3) *
            (static_cast<int>(daysRented) / 7)) +
            (compactCharge * (static_cast<int>(daysRented) % 7));

            }
        }
    }
    if (carSize == midCar) {
        if (daysRented == 7) {
        totalCarCharge = (midCharge * 6.3);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (midCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);
            }
            else {
            totalCarCharge =  ((midCharge * 6.3) *
            (static_cast<int>(daysRented) / 7)) +
            (midCharge * (static_cast<int>(daysRented) % 7));

            }
        }
    }

    if(carSize == fullCar) {
        if (daysRented == 7) {
        totalCarCharge = (fullCharge * 6.3);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (fullCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);
            }
            else {
            totalCarCharge =  ((fullCharge * 6.3) *
            (static_cast<int>(daysRented) / 7)) +
            (fullCharge * (static_cast<int>(daysRented) % 7));

            }
        }
    }
    if (carSize == suvCar) {
        if (daysRented == 7) {
        totalCarCharge = (suvCharge * 6.3);
        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            totalCarCharge = (suvCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);
            }
            else {
            totalCarCharge =  ((suvCharge * 6.3) *
            (static_cast<int>(daysRented) / 7)) +
            (suvCharge * (static_cast<int>(daysRented) % 7));

            }
        }
    }


    return  totalCarCharge;


}
// --------------------------------------------------------------------------
// Description: CalculateWeekCarCharge-  Calculates the charges incurred at
//              week discount
// Input parameter: carSize - user inputed
//                  daysRented - user inputed
// Returns: weeklyCarCharge - calculated fee for car for the week charges
// ---------------------------------------------------------------------------
double CalculateWeekCarCharge (char carSize, double daysRented)
{
    double weeklyCarCharge;


    if (carSize == compactCar) {
        if (daysRented == 7) {
        weeklyCarCharge = (compactCharge * 6.3);


        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            weeklyCarCharge = (compactCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);
            }
            else {
            weeklyCarCharge =  ((compactCharge * 6.3) *
            (static_cast<int>(daysRented) / 7));


            }
        }
    }
    if (carSize == midCar) {
        if (daysRented == 7) {
        weeklyCarCharge = (midCharge * 6.3);

        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            weeklyCarCharge = (midCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);

            }
            else {
            weeklyCarCharge =  ((midCharge * 6.3) *
            (static_cast<int>(daysRented) / 7));


            }
        }
    }

    if(carSize == fullCar) {
        if (daysRented == 7) {
        weeklyCarCharge = (fullCharge * 6.3);

        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            weeklyCarCharge = (fullCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);

            }
            else {
            weeklyCarCharge =  ((fullCharge * 6.3) *
            (static_cast<int>(daysRented) / 7));


            }
        }
    }
    if (carSize == suvCar) {
        if (daysRented == 7) {
        weeklyCarCharge = (suvCharge * 6.3);

        }
        else {
            if ((static_cast<int>(daysRented) % 7) == 0) {
            weeklyCarCharge = (suvCharge * 6.3) *
            (static_cast<int>(daysRented) / 7);

            }
            else {
            weeklyCarCharge =  ((suvCharge * 6.3) *
            (static_cast<int>(daysRented) / 7));


            }
        }
    }




return weeklyCarCharge;


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
void CalculateBillTotal (double& carCharge, double& tax, double& total) {

    tax = carCharge * 0.125;
    total = carCharge + tax;

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
//                   returnDay - date to return car
//                   returnMonth- month to return car
//                   returnYear- year to return car in
// refernce parameters: anotherBill - does the user want to process
//                      another bill
// -----------------------------------------------------------------------
void OutputInvoice (double daysRented,
     double carCharge, double tax, double total,
     string carSizeWord, string firstName,
     string lastName,double month, double day, double year,
     double returnDay, double returnMonth, double returnYear,
     double weeklyCarCharge, double dayCarCharge, int nWeeks,int nDays) {


    string weekDay;
    double subTotal;

    CalculateBillTotal (carCharge, tax, total);

    cout << endl << endl << endl;
    cout << "Rent it Now" << endl << endl;
    cout << "RENTAL DETAILS" << endl;
    cout << setprecision(0) << fixed;
    cout << "   Customer:      " << firstName << ", " << lastName << endl;
    cout << "   Car Size:      " << carSizeWord << endl;

    cout << "   Pick up Date:  ";
    dayOfWeek (month,year,day);
    cout << ", " << month << "/" << day << "/" << year << endl;
    cout << "   Days Rented:   "<< daysRented << endl;

    cout << setw(5) << "   Return Date:   ";
    dayOfWeek (returnMonth ,returnYear,returnDay);
    cout << ", " << returnMonth << "/" << returnDay << "/"
         << returnYear << endl << endl;

    cout << "BILL" << endl;
    cout << setprecision(2) << fixed;
    cout << setw(4) << "$" << setw(9) << weeklyCarCharge;

    // calculates the number of weeks the car is rented
    nWeeks= static_cast<int>(daysRented) / 7;
    cout << setw(6) << nWeeks;

    // adds plurality or singualrity to week
     if (nWeeks == 1)
     {
        cout << " week" << endl;
        }
     else
     {
          cout << " weeks" << endl;
          }
    // calculates the charge of the car after the weekly charges
        dayCarCharge = carCharge - weeklyCarCharge;
        cout << setw(4) << "$" << setw(9) << dayCarCharge  << " +" << setw(4);
        nDays = static_cast<int>(daysRented)  % 7;
        cout << nDays;
             if (nDays == 1)
         {
            cout << " day" << endl;
            }
         else
         {
              cout << " days" << endl;
              }

    cout << setw(3) << " " << setfill('-') << setw(11) << " "<< endl;


    // week and days subtotals
    cout << setfill(' ') << setw(4) << "$" << setw(9) << carCharge << setw(15)
         << "rental fee" << endl;


    // if - else if rented for over 30 days get an additional 5% off and
    //    display subtotal
    if ( daysRented > 30)
    {
        cout << setw(4) << "$" << setw(9) << carCharge * 0.05 << " -"
             << setw(11) << "discount" << endl;
        cout << setw(3) << " " << setfill('-') << setw(11) << " "<< endl;
        subTotal = carCharge - (carCharge * 0.05);
        cout << setfill(' ') << setw(4) << "$" << setw(9)
             << subTotal << setw(13) << "subtotal" << endl;
        cout << setw(4) << "$" << setw(9) << tax << " +" << setw(6)
             << "tax" << endl;
        cout << setw(3) << " " << setfill('-') << setw(11) << " "<< endl;
        total = total - (carCharge * 0.05);
        cout << setfill(' ') << setw(4) << "$" << setw(9)
             << total << setw(10) << "total" << endl;
    }
    else
    {
    cout << setw(4) << "$" << setw(9) << tax << " +" << setw(6)
         << "tax" << endl;
    cout << setw(3) << " " << setfill('-') << setw(11) << " "<< endl;
    cout << setfill(' ') << setw(4) << "$" << setw(9)
         << total << setw(10) << "total" << endl << endl;
}




}
// --------------------------------------------------------------------------
// Description: daysInMonth Calculates the number of days in a month,
//              accounting for leap year
// Input parameter: year - the year car was picked up
//                  month - the month the car was picked up
// Returns: maxDays- the number of days in a given month given the year
// ---------------------------------------------------------------------------
double daysInMonth ( double year, double month)
{
    double maxDays;

    if ((static_cast<int>(year) % 4  != 0) && (month == 2))
    {
             maxDays = 28;
    }
    else if ((static_cast<int>(year) % 4  == 0) && (month == 2))
    {
         maxDays = 29;
         }
    else if ( month == 1 || month == 3 ||
         month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
         {
               maxDays = 31;
         }
    else
    {
         maxDays = 30;
    }

    return maxDays;
}
// --------------------------------------------------------------------------
// Description: GetValidNumber - Generic validator that prompts the user
//              and then error checks for lower and upper limits
// Input parameter: prompt - string
//                  lowerLimit -  lowest number
//                  upperLimit - highest number
// Returns: num - returned validated number
// ---------------------------------------------------------------------------
double GetValidNumber( string prompt, double lowerLimit, double upperLimit)
{
    double num;
    cout << prompt;
    cin >> num;


    while (num < lowerLimit) {
    cout << "Entry must be greater than or equal to " << lowerLimit << endl;
    cout << prompt;
    cin >> num;
    }
    while (num > upperLimit)
    {
    cout << "Entry must be less than or equal to " << upperLimit << endl;
    cout << prompt;
    cin >> num;
    }

    return num;
}
// --------------------------------------------------------------------------
// Description: ReturnDate - Calculates the day, month and year the car is
//              to be returned.  This function calls the month function in
//              order to calculate the number of days in a given month and year.
// Input parameter: maxDays- the total number of days in a month
//                  daysRented -the total number of days the car is rented
//                  year- the year when the car was picked up
//                  month- the month when the car was picked up
//                  day- the day when the car was picked up
//     output: returnYear- the year when the car needs to be returned
//             returnMonth- the month when the car needs to be returned
//             returnDay- the day when the car needs to be returned
// ---------------------------------------------------------------------------
void ReturnDate (double maxDays, double daysRented, double year,
     double month, double day, double& returnYear,
     double& returnMonth, double& returnDay)
{
     // do-while loop caluclates the day in the month that the car needs to be
     // returned given the date it was picked up and the # of days rented
     returnDay = day + daysRented;

                 do{
                     if (returnDay > maxDays)
                     {
                                   returnDay = returnDay - maxDays;
                                  month++;
                                   }

                     if(month == 13)
                     {
                              month = 1;
                              returnMonth = month;
                              year++;
                              returnYear = year;


                     }
                     else
                     {
                     returnMonth = month;
                     returnYear = year;
                     }
                                   } while ( returnDay > maxDays);
}
// --------------------------------------------------------------------------
// Description: dayOfWeek - Calculates the day of the week the car is picked
//              up and returned.
// Input parameter: month - the month the car was rented
//                  year - the year the car was rented
//                  day - the day the car was rented
// ---------------------------------------------------------------------------
void dayOfWeek (double month, double year, double day)
{
     double monthAdditionFactor;
     double sum;
     double dayWeekInt;
     string weekDay;
     // switch determines the month addition factor given the month
     switch (static_cast<int>(month)) {
      case 1:
      case 5:
        monthAdditionFactor = 0;
        break;
      case 8:
        monthAdditionFactor = 1;
        break;
      case 3:
      case 11:
        monthAdditionFactor = 2;
      case 2:
      case 6:
        monthAdditionFactor = 3;
        break;
      case 9:
      case 12:
        monthAdditionFactor = 4;
        break;
      case 4:
      case 7:
        monthAdditionFactor = 5;
        break;
      case 10:
        monthAdditionFactor = 6;
        break;
      default:
        monthAdditionFactor = 0;
    }
    // sum calulated the value need to determine the day the car was rented
    sum = year + year/4 - year/100 + year /400 + monthAdditionFactor + day;

    dayWeekInt = static_cast<int>(sum) % 7;
    if (static_cast<int>(year) % 4 != 0 && month == 2)
    {

     dayWeekInt = dayWeekInt - 1;
     }
    // switch writes weekDay and the name of the day
    switch (static_cast<int>(dayWeekInt))
    {
    case 0:
     weekDay = "Sunday";
    break;
    case 1:
     weekDay = "Monday";
    break;
    case 2:
     weekDay = "Tuesday";
    break;
    case 3:
     weekDay = "Wednesday";
    break;
    case 4:
     weekDay = "Thursday";
    break;
    case 5:
     weekDay = "Friday";
    break;
    case 6:
     weekDay = "Saturday";
    break;
    default:
    weekDay = "Not defined";
    }
    cout << weekDay;

}


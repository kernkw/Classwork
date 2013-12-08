//******************************************************************************
//  FILENAME:	 KernAssn2.cpp
//  DESCRIPTION: Program reads file line by line and places certain values in
//		an array and skips other values.  Then the array is read line by line and
//		searched for	high, low and average values.  These values are then store
//		another array which is outputted back to the program user along with
//		how many of each vehicles where inputed by input file.
//  DESIGNER:	 Kyle Kern
//  FUNCTIONS:
//		main - reads input file, puts into an array, then calls functions
//		CalculateHighest - finds the array index for the highest value
//		CalculateLowest - finds the array index for the lowest value
//		CalculateAverage - finds the sum of all values in array and average
//		DisplayResults - displays the formatted registrations values from array
//******************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// constants
const string IN_FILENAME = "VEHICLES.TXT";  // input file
const int MAX_CHARGES = 500;       // max registeration charges per array
enum registrationValues {LOW, HIGH, AVERAGE};  // values to be calculated
const int NUMBER_OF_VALUES = 3; // number of values to be calculated

//protypes
double CalculateHighest(double valueCharge[], int& count);
double CalculateLowest(double valueCharge[], int& count);
double CalculateAverage(double valueCharge[], int& count);
void DisplayResults(double resultsDisplayed[], int& count,
										string vehicleTypeString);

//******************************************************************************
//  FUNCTION:	main
//  DESCRIPTION: Reads input file, puts into an array, then calls functions to
//		perform an array search then calls functions to displays indexed arrays
//  INPUT:
//		File:	Reads the vehicle type and registration charge per vehicle
//		from IN_FILENAME: vehicleType, licenseId, and regCharges
//  CALLS TO:	CalculateHighest, CalculateLowest, CalculateAverage,DisplayResults
//		CalculateLowest
//	OUTPUT:
//		Returns: 0 on success
//******************************************************************************
int main()
{
	double regChargesAuto[MAX_CHARGES];	// array of charges automobile
	double regChargesMotor[MAX_CHARGES];	// array of charges motorcycle
	double resultsAuto[NUMBER_OF_VALUES];		// array for automobile, index enum
	double resultsMotor[NUMBER_OF_VALUES];	// array for motorcycle, index enum
	ifstream vehicleIn;	// input file
	char vehicleType;	// letter in input file is either 'A' or 'M'
	string licenseId;	// license plate id from input file
	bool errorMessage;	// determines if error message has been outputed already

	errorMessage = true;	// set to true so inputs error message unless false
	int countAuto = 0;	// auto count
	int countMotor = 0;	// motor count

	//opening statments to the program's user
	cout << endl;
	cout << "Department of Motor Vehicles Charges" << endl;
	cout << endl;
	cout << "This program was built for the county Department "
	"of Motor Vehicles and will analyze and compare car and "
	"motorcycle registrations charges. Then display the "
	"low, high and average values back to the screen "
	"organized by vehicle amount and type.";

	cout << endl << endl;
	system("read -p 'Hit Enter to display and output results. '");
	cout << endl;

	// open both the input and output files
	vehicleIn.open (IN_FILENAME.c_str());

	if (vehicleIn)
	{

		vehicleIn >> vehicleType; // prime read vehicle type

		while (vehicleIn)
		{
			if (vehicleType == 'A')
				{
					if (countAuto < MAX_CHARGES)
					{
						vehicleIn >> licenseId;
						vehicleIn >> regChargesAuto[countAuto];	// read charges into array
						countAuto++;
					}
					else
					{
						if (errorMessage)
						{
							cout << "Error: the file has too much data, this program "
								"can only store up to 500 registrations." << endl << endl;
							errorMessage = false;
						}
					}

				}
				else if (vehicleType == 'M')
				{
					if (countMotor < MAX_CHARGES)
					{
						vehicleIn >> licenseId;
						vehicleIn >> regChargesMotor[countMotor];	// read charges into array
						countMotor++;
					}
					else
					{
						if (errorMessage)
						{
							cout << "Error: the file has too much data, this program "
								"will only accept up to 500 registrations per vehicle type."
									<< endl << endl;
							errorMessage = false;
						}
					}
				}
				vehicleIn >> vehicleType; // read vehicle type
		}

		// uses enum registrationValues to create two arrays for auto and motor
		resultsAuto[LOW] = CalculateLowest(regChargesAuto, countAuto);
		resultsAuto[HIGH] = CalculateHighest(regChargesAuto, countAuto);
		resultsAuto[AVERAGE] = CalculateAverage(regChargesAuto, countAuto);

		resultsMotor[LOW] = CalculateLowest(regChargesMotor, countMotor);
		resultsMotor[HIGH] = CalculateHighest(regChargesMotor, countMotor);
		resultsMotor[AVERAGE] = CalculateAverage(regChargesMotor, countMotor);

		DisplayResults (resultsAuto, countAuto, "automobile");
		DisplayResults (resultsMotor, countMotor, "motorcycle");

		vehicleIn.close();
	}
	else
	{
		// if file doesnt exists show error message and  then exit
    cout << "Error opening input file" << endl;
	}
	cout << endl;
	system("read -p 'Hit Enter to exit. '");
	cout << endl;

	return 0;
}

//******************************************************************************
//  FUNCTION:	CalculateHighest
//  DESCRIPTION: Reads array line by line and returns an array with the
//		highest value idex
//  INPUT:
//		valueCharge[] - array from main function
//		count - reads count from main function array
//  OUTPUT:
//		Return value: valueCharge[highestCharge] - array containing highest
//		value index
//******************************************************************************
double CalculateHighest(double valueCharge[], int& count)
{
	int highestCharge;	// the highest value in the array
	int index;	// index for array
	highestCharge = 0;

	// loop reads array line by line and finds when array is highest
	for (index = 1; index < count; index++)
	{
			if (valueCharge[index] < valueCharge[count])
		  {
				highestCharge = index;
		  }
	}
	return valueCharge[highestCharge];
}

//******************************************************************************
//  FUNCTION:	CalculateLowest
//  DESCRIPTION: Reads array line by line and returns an array with
//		lowest value idex
//  INPUT:
//		valueCharge[] - array from main function
//		count - reads count from main function array
//  OUTPUT:
//		Return value: valueCharge[lowestCharge] - array containing lowest
//		value index
//******************************************************************************
double CalculateLowest(double valueCharge[], int& count)
{
	int index;	// index for array
	int lowestCharge;	//the lowest value in array
	lowestCharge = 0;

	// loop reads array line by line and finds when array is highest
	for (index = 1; index < count; index++)
	{
		if (valueCharge[index] > valueCharge[count])
		{
			lowestCharge = index;
		}
	}

	return valueCharge[lowestCharge];

}

//******************************************************************************
//  FUNCTION:	CalculateAverage
//  DESCRIPTION: Reads array line by line, finds sum then commutes average
//		and returns the average value
//  INPUT:
//		valueCharge[] - array from main function
//		count - reads count from main function array
//  OUTPUT:
//		Return value: averageCharge- the average charge of all values
//		in the processed array
//******************************************************************************
double CalculateAverage(double valueCharge[], int& count)
{
	int index;	// index for array
	double averageCharge;	// average charge in array
	double sum;	// sum of all charges in array
	sum = 0;

	// loops through array and adds all the vlaues together
	for (index = 0; index < count; index++)
	{
		sum =  sum + valueCharge[index];
	}
	// calulates average via the average formula sum divded by num of items
	averageCharge = sum / count;

	return averageCharge;

}

//******************************************************************************
//  FUNCTION:	DisplayResults
//  DESCRIPTION: Displays number of, low, high and average values for inputed
//		array
//	INPUT:
//		resultsDisplayed[] - array used to call enum values
//		count - reads count from main function array
//		vehicleTypeString - inputs string of vehicle type
//  OUTPUT:	Displays formatted values using indexed arrays
//******************************************************************************
void DisplayResults (double resultsDisplayed[], int& count,
										string vehicleTypeString)
{
	if (count >= 1)
	{
		cout << "For " << count << " " << vehicleTypeString
			<< " registration in the county:" << endl;
		cout << fixed << right << showpoint << setprecision(2);
		cout << setw(34) << "Lowest registration charge = $" << setw(10)
			<< resultsDisplayed[LOW] << endl;
		cout << setw(34) << "Highest registration charge = $" << setw(10)
			<< resultsDisplayed[HIGH] << endl;
		cout << setw(34) << "Average registration charge = $" << setw(10)
			<< resultsDisplayed[AVERAGE] << endl;
		cout << endl;
	}
	else
	{
		cout << "There were NO registration charges for any "
			<< vehicleTypeString << " in the county." << endl;
		cout << endl;
	}

}

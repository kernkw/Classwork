//******************************************************************************
//  FILENAME:	 KernAssn3.cpp
//  DESCRIPTION: Program reads file line by line and places license plate id
//	and car type into two different arrays, then sorts the parallel arrays
//	in ascending order.  The program then displays the license plates on file
// 	in ascending order.  The user is then prompted to enter a license plate
//	the input is error checked, and the reg charge is displayed back to user.
//  DESIGNER:	 Kyle Kern
//  FUNCTIONS:
//		main - reads input file, puts into an array, then calls functions
//		ReadInputData -
//		SelectSort -
//		OutputArray -
//		DisplayLicenseId - displays the license plate values from array
//		EnterLicenseId -
//		LicenseIdSearch -
//		DisplayResults -
//******************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// constants
const string IN_FILENAME = "VEHICLES.TXT";  // input file
const string OUT_FILENAME = "SORTED.TXT";  // input file
const int MAX_CHARGES = 1000;       // max registeration charges per array
const int NOT_FOUND = -1;	//

void ReadInputData (ifstream& vehicleIn, int& count,
									string licenseIdArray[], double regChargeArray[]);
void SelectSort (int count, string licenseIdArray[], double regChargeArray[]);
void OutputArray (ofstream& sortedOut, string licenseIdArray[],
									double regChargeArray[], int count);
void DisplayLicenseId (string licenseIdArray[], double regChargeArray[],
											 int count);
string EnterLicenseId (string licenseIdArray[], double regChargeArray[],
											 int count);
int LicenseIdSearch (string inputLicenseId, int count, string licenseIdArray[]);
void DisplayResults (int licenseResults, string inputLicenseId,
										 double regChargeArray[]);

//******************************************************************************
//  FUNCTION:	main
//  DESCRIPTION: Reads input file, puts into an array, then calls functions to
//		perform an array search then calls functions to displays indexed arrays
//  INPUT:
//		File:	Reads the vehicle type and registration charge per vehicle
//		from IN_FILENAME: vehicleType, licenseId, and regCharges
//  CALLS TO:	// ReadInputData -
//		SelectSort -
//		OutputArray -
//		DisplayLicenseId - displays the license plate values from array
//		EnterLicenseId -
//		LicenseIdSearch -
//		DisplayResults
//	OUTPUT:
//		Returns: 0 on success
//******************************************************************************
int main()
{
	ifstream vehicleIn;	// input file
	ofstream sortedOut;	// output file
	int count;		// counts of each line
	string licenseIdArray[MAX_CHARGES];	// array of license plates
	double regChargeArray[MAX_CHARGES];	// array of registration charges
	char vehicleType;	// the character type
	string licenseId;	// license plate id
	string inputLicenseId;	// license plate id inputed by user
	int licenseResults;	// array index from array search

		//opening statments to the program's user
	cout << endl;
	cout << "Department of Motor Vehicles Charges" << endl;
	cout << endl;
	cout << "This program allows a user to search the database "
				"for their license plate, then diplays the associated charge back.";

	cout << endl << endl;
	system("read -p 'Hit Enter to display and output results. '");
	cout << endl;

	vehicleIn.open (IN_FILENAME.c_str());
	sortedOut.open (OUT_FILENAME.c_str());

	count = 0;

	if(vehicleIn)
	{
		vehicleIn >> vehicleType;

		ReadInputData(vehicleIn, count, licenseIdArray, regChargeArray);

		SelectSort (count, licenseIdArray, regChargeArray);

		OutputArray (sortedOut, licenseIdArray, regChargeArray, count);

		do	// loop if 'Q' or 'q' exit or reprompt user
		{
			inputLicenseId = EnterLicenseId (licenseIdArray, regChargeArray, count);

			if (inputLicenseId == "Q" || inputLicenseId == "q")
			{
				vehicleIn.close();
				cout << endl;
				system ("PAUSE");
				return 0;
			}

			licenseResults = LicenseIdSearch (inputLicenseId, count, licenseIdArray);

			DisplayResults (licenseResults,inputLicenseId, regChargeArray);

		}while(inputLicenseId != "Q");

	}
	else
	{
		// if file doesnt exists show error message and  then exit
		cout << "Error opening input file" << endl;
	}

	vehicleIn.close();
	cout << endl;
	system ("PAUSE");
	return 0;

}

//******************************************************************************
//  FUNCTION:	ReadInputData
//  DESCRIPTION: Reads array line by line and returns license plate id and
//	car type to different arrays. Array bounds at 1000.
//  INPUT:
//		vehicleIn- input file
//		count - reads count from main function array
//  OUTPUT:
//		Return Reference value:	licenseIdArray -  array contains license plates
//			regChargeArray - array contains registration charges
//******************************************************************************

void ReadInputData (ifstream& vehicleIn, int& count,
									string licenseIdArray[], double regChargeArray[])
{
	string licenseId;	// license plate id
	double regCharge;	// holds the registration charge
	char vehicleType;	// the vehcile type 'A' or 'M'
	bool errorMessage;	// checks if error message has been displayed already
	int countBounds;	// counts the number of loops

	errorMessage = true;

	countBounds = 0;

	for(count = 0; count < MAX_CHARGES; count++)
	{
		vehicleIn >> licenseIdArray[count];
		vehicleIn >> regChargeArray[count];
		vehicleIn >> vehicleType;
		countBounds++;

		if(countBounds  > MAX_CHARGES - 1)
		{
			if(errorMessage)
			{
				cout << "ERROR:  The input file is too large, only the first 1000 "
				"license plates will be displayed." << endl << endl;
				errorMessage = false;
			}
		}
	}
}

//******************************************************************************
//  FUNCTION:	SelectSort
//  DESCRIPTION: Sorts parallel arrays in ascending order by license plate
//  INPUT:
//		licenseIdArray[]- array of license plates-unsorted
//		regChargeArray[]- array of reg charges-unsorted
//		count - reads count for array indexing
//  OUTPUT:
//	licenseIdArray[]- array of license plates-sorted
//		regChargeArray[]- array of reg charges-sorted
//******************************************************************************
void SelectSort (int count, string licenseIdArray[], double regChargeArray[])
{

	string temp;		// temporary license plate
	double tempCharge;	// temporary registration charge
	int curTop;	// the current top of the array
	int maxValueCur;	// the max value in the array
	int swapValue;	//
	double doubleTemp;	// temporary registration charge

	for(curTop = 0 ; curTop < count - 1; curTop++)
	{
		maxValueCur =  curTop;

		for ( swapValue = curTop + 1; swapValue < count; swapValue++)
		{
			if (licenseIdArray[swapValue] > licenseIdArray[maxValueCur])
			{
			maxValueCur = swapValue;
			}
		}
		if (maxValueCur != curTop)
		{
			//	temp swaps if value is lower
			temp = licenseIdArray[curTop];
			licenseIdArray[curTop] = licenseIdArray[maxValueCur];
			licenseIdArray[maxValueCur] = temp;

			// doubletemp if value is lower
			doubleTemp = regChargeArray[curTop];
			regChargeArray[curTop] = regChargeArray[maxValueCur];
			regChargeArray[maxValueCur] = doubleTemp;
		}
	}
  return;
} // end selectionSort

//******************************************************************************
//  FUNCTION:	OutputArray
//  DESCRIPTION: Outputs array to file and screen.
//  INPUT:
//		licenseIdArray[]- array of license plates-unsorted
//		regChargeArray[]- array of reg charges-unsorted
//		count - reads count for array indexing
//  OUTPUT:
//		Return value: sortedOut - output file
//******************************************************************************
void OutputArray (ofstream& sortedOut, string licenseIdArray[],
									 double regChargeArray[], int count)
{
	int index;	// index for the license plate loop

	cout << "LICENSE PLATES on File are:" << endl;
	for(index = 0; index < count; index++)
	{
		sortedOut << licenseIdArray[index] << " " << regChargeArray[index] << endl;

		cout << licenseIdArray[index] << " ";
	}

	cout << endl;
	return;
}

//******************************************************************************
//  FUNCTION:	EnterLicenseId
//  DESCRIPTION: Prompts user to enter license plate or 'Q' to quit.  This
//		function will also error check user input.
//  INPUT:
//		licenseIdArray[]- array of license plates-sorted
//		regChargeArray[]- array of reg charges-sorted
//		count - reads count for array indexing
//  OUTPUT:	inputLicenseId - the user entered, validated license plate id
//******************************************************************************
string EnterLicenseId (string licenseIdArray[], double regChargeArray[],
											 int count)
{
	string inputLicenseId;	// license plate id entered by user
	int index;	 // index for input license plate loop
	int inputLength;	// the length of the license plate inputed
	char ch;	// character in the inputed license plate id
	bool validCheck;	// input error checker
	int sumValidCheck;	// input error checker

	validCheck = 0;
	sumValidCheck = 0;

	do
	{
			cout << endl;
			cout << "Enter a license plate (or Q to quit): ";
			cin >> inputLicenseId;

			if(inputLicenseId == "Q" || inputLicenseId == "q")
			{
				return inputLicenseId;
			}

			inputLength = inputLicenseId.length();

			if (inputLength < 6)
			{
				cout << endl;
				cout << "License " << inputLicenseId << " is too short." << endl;
				cout << "Must be 3 letters followed by 3 digits. Try again." << endl;

				validCheck = 1;
			}
			else if (inputLength > 6)
			{
				cout << endl;
				cout << "License " << inputLicenseId << " is too long." << endl;
				cout << "Must be 3 letters followed by 3 digits. Try again." << endl;

				validCheck = 1;
			}
			else
			{
				for(index = 0; (index <= 2); index++)
				{
					inputLicenseId[index] = toupper(inputLicenseId[index]);

					ch = inputLicenseId[index];	// ch is uppercase

						if (isalpha(ch))
						{
							validCheck = 0;
						}
						else
						{
							validCheck = 1;
							sumValidCheck = sumValidCheck + validCheck; // stores check totals
						}
				}
				for(index = 3; (index < 6); index++)
				{
					inputLicenseId[index] = toupper(inputLicenseId[index]);

					ch = inputLicenseId[index];

						if (isdigit(ch))
						{
							validCheck = 0;
						}
						else
						{
							validCheck = 1;
							sumValidCheck = sumValidCheck + validCheck; // stores check totals
						}
				}

				if (sumValidCheck >= 1)
				{
					cout << endl;
					cout << "License " << inputLicenseId << " is formatted incorrectly."
						<< endl;
					cout << "Must be 3 letters followed by 3 digits. Try Again." << endl;
				}
		 }

	}while((validCheck != 0) || (sumValidCheck != 0));

	return inputLicenseId;
}


//******************************************************************************
//  FUNCTION:	LicenseIdSearch
//  DESCRIPTION: Searches sorted arrays using binary search to find index
//		of desired array
//	INPUT:
//		licenseIdArray[]- array of license plates-sorted
//		regChargeArray[]- array of reg charges-sorted
//		count - reads count for array indexing
//  OUTPUT:	infoPlace - index for desired license plate id
//******************************************************************************
int LicenseIdSearch (string inputLicenseId, int count, string licenseIdArray[])
{
	int infoPlace = NOT_FOUND;	// if not found display -1
	int high, low, middle;	// highest, middle, and lowest indexs for array

	low = 0;
	high = count - 1;

	while ((low <= high) && (infoPlace == NOT_FOUND))
	{
		middle = (low + high) / 2;

		if (inputLicenseId < licenseIdArray[middle])
		{
			low  = middle + 1;
		}
		else if (inputLicenseId > licenseIdArray[middle])
		{
			high = middle - 1;
		}
		else
		{
			infoPlace = middle;
		}

	}

	return infoPlace;
}

//******************************************************************************
//  FUNCTION:	DisplayResults
//  DESCRIPTION: Displays number of, low, high and average values for inputed
//		array
//	INPUT:
//		licenseIdArray[]- array of license plates-sorted
//		regChargeArray[]- array of reg charges-sorted
//		count - reads count for array indexing
//  OUTPUT:	Displays formatted values using indexed arrays or displays
//		that license plate id is not in database.
//******************************************************************************
void DisplayResults (int licenseResults, string inputLicenseId,
										 double regChargeArray[])
{
	if (licenseResults == NOT_FOUND) // -1 if not in database
	{
		cout << endl;
		cout << "License " << inputLicenseId << " not in database." << endl;
	}
	else
	{
		cout << endl;
		cout << "Vehicle with license " << inputLicenseId
		<< " was charged $ " << regChargeArray[licenseResults] << endl;
	}
}

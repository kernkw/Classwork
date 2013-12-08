//******************************************************************************
//  FILENAME:	 KernAssn5.cpp
//  DESCRIPTION: This program will read existing rental car database, if there is
//		one, or will create a rental car database bin file. The program will
//		display the existing database and prompt user to either turn in a car or
//		rent a car.  In both cases the program will search the database (2D array)
// 		and display availability back to the user. The program will loop until
//		users decides to exit.  When the program exits it will create or overwrite
//		data to a bin formatted file.
//  DESIGNER:	 Kyle Kern
//  FUNCTIONS:
//	fillGarageArray - reads exisitng file and writes to 2D array, or sets to full
//	displayGarageArray - displays the 2D array in a table
//	storeMenuChoice - stores the main menu choice
//	carTypeChoice - stores the car size choice
//	carTurnedIn - allows user to turn in rental car and checks availability
//	newRentalCar - allows user to rent a car, and checks availability
//	saveToFile - saves new 2D array values in a .bin file
//******************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

const int NUM_LEVELS = 6; // number of level in rental car garage
const int NUM_CAR_SIZES = 4;// number of different car types
const string OUTFILE = "KernGARAGE.BIN";  // output file in .bin format

enum carSize {COMPACT, MIDSIZE, FULLSIZE, SUV, NONE};
const string CAR_STRINGS[] = {"Compact", "Mid-size", "Full Size", "SUV"};



void fillGarageArray(ifstream& binFile, int garageArray[][NUM_LEVELS],
										int levelArray[NUM_LEVELS]);
void displayGarageArray(int array[][NUM_LEVELS], int levelArray[NUM_LEVELS],
												 int& totalCount);
char storeMenuChoice(int count);
int carTypeChoice ();
void carTurnedIn(int array[][NUM_LEVELS], int carTypeLetter, int levelArray[]);
void newRentalCar(int array[][NUM_LEVELS], int carTypeLetter, int levelArray[]);
void saveToFile(ofstream& binFile, int array[][NUM_LEVELS], int levelArray[]);

//******************************************************************************
//  FUNCTION:	main
//  DESCRIPTION: Reads input file into an array of records, then calls functions
//		to display a menu which loops until exit.  This will allow you to add,
//		remove or diaply all current records in array. Also call fuction to
//		save to a file.
//  INPUT:
//		binFileIn - this binary file is formatted sequentiallyin this order: level
//								index,the row index, and the number of cars in that level/row
//	OUTPUT:
//		binFileOut - this binary file is formatted sequentiallyin this order: level
//								index,the row index, and the number of cars in that level/row
//  CALLS TO:
//	fillGarageArray - reads exisitng file and writes to 2D array, or sets to full
//	displayGarageArray - displays the 2D array in a table
//	storeMenuChoice - stores the main menu choice
//	carTypeChoice - stores the car size choice
//	carTurnedIn - allows user to turn in rental car and checks availability
//	newRentalCar - allows user to rent a car, and checks availability
//	saveToFile - saves new 2D array values in a .bin file
//	OUTPUT:
//		Returns: 0 on success
//******************************************************************************
int main()
{
	int garageArray[NUM_CAR_SIZES][NUM_LEVELS]; // cars per type and level
	int levelArray[NUM_LEVELS];	// number of levels
	char letterChoice; // letter choice from main menu
	ifstream binFileIn;	// input file
	ofstream binFileOut;	// output file
	int carType; // user selected car size
	int totalCount; // total count of cars in garage
	bool exitCheck = false; // exit loop true or false

	cout << endl;
	cout << "Rental Car Program" << endl;
	cout << endl;
	cout << "This program will read input file of car rental database. "
	"Then it will allow you to choose to return or rent cars by showing "
	"you what is currently available and where that car is to be rented "
	"from or returned to.";

	cout << endl << endl;
	system("read -p 'Hit Enter to Continue. '");
	cout << endl;

	binFileIn.open (OUTFILE.c_str(), ios::binary | ios::in);
	fillGarageArray(binFileIn, garageArray, levelArray);

	// do while displays main menu and and runs other functions, until user exists
	do
	{
		displayGarageArray(garageArray, levelArray, totalCount);

		letterChoice = storeMenuChoice(totalCount);
		letterChoice = toupper(letterChoice);

		if (letterChoice == 'R')
		{
			carType = carTypeChoice ();
			if (carType == 4)
				exitCheck = false;
			else
				newRentalCar(garageArray, carType, levelArray);
				exitCheck = false;
		}

		else if (letterChoice == 'T')
		{
			carType = carTypeChoice ();
			// when carType returns 4 return to main menu
			if (carType == 4)
				exitCheck = false;
			else
				carTurnedIn(garageArray, carType, levelArray);
				exitCheck = false;
		}
		else if (letterChoice == 'E')
		{
			binFileOut.open (OUTFILE.c_str(), ios::binary | ios::out);
			saveToFile(binFileOut, garageArray, levelArray);
			exitCheck = true;
		}
		else
		{
			exitCheck = false;
		}

	} while (exitCheck == false);


	cout << endl;
	system ("PAUSE");
	return 0;

}

//******************************************************************************
//  FUNCTION:	fillGarageArray
//  DESCRIPTION: Reads if binary file exists, if it does read into 2D array
//		If not then set 2D array to full.
//  INPUT:
//		binFileIn - this binary file is formatted sequentiallyin this order: level
//								index,the row index, and the number of cars in that level/row
//	OUTPUT:
//		garageArray - contains num of cars per car type per level
//		levelArray - contains the num of levels in the parking garage
//******************************************************************************
void fillGarageArray(ifstream& binFile, int garageArray[][NUM_LEVELS],
										 int levelArray[])
{
	int numCars; // number of cars in array
	int levelIndex; // index of parking garage level
	int rowCount; // row index of parking garage

	if (!binFile)
	{
		//set garage full if not input file exists
		for (int row = 0; row < NUM_CAR_SIZES; row++)
		{
			for (int col = 0; col < NUM_LEVELS; col++)
			{
				levelArray[col] = col;
				garageArray[row][col] = 5;
			}
		}

	}
	else
	{
		//if bin file exists set garage to empty first
		for (int row = 0; row < NUM_CAR_SIZES; row++)
		{
			for (int col = 0; col < NUM_LEVELS; col++)
			{
				levelArray[col] = col;
				garageArray[row][col] = 0;
			}

		}

		// while reads 3 data types from binary where not empty
		while (binFile)
		{
				binFile.read (reinterpret_cast<char*> (&levelIndex), sizeof(int));
				binFile.read (reinterpret_cast<char*> (&rowCount), sizeof(int));
				binFile.read (reinterpret_cast<char*> (&numCars), sizeof(int));

				// read temp variables into 2D array
				levelArray[levelIndex] = levelIndex;
				garageArray[rowCount][levelIndex] = numCars;
		}

		binFile.close();
		cout << "All data has been read." << endl << endl;
		cout << endl << endl;
		system("read -p 'Hit Enter to Continue. '");
		cout << endl;
	}
	return;
}

//******************************************************************************
//  FUNCTION:	displayGarageArray
//  DESCRIPTION:	Displays the 2D array containing the level headers and then
//		the number of cars per level, per car size. Then will check for an open
//		car on an open level starting with level 5.
//  INPUT:
//		array - garage array contains number of cars per level
//	OUTPUT:
//		levelArray - contains the levels of the parking garage
//		totalCount - refernce parameter that keeps the total num of cars
//******************************************************************************
void displayGarageArray(int array[][NUM_LEVELS], int levelArray[NUM_LEVELS],
												 int& totalCount)
{
	int countCar = 0; // total car count per car type
	totalCount = 0;
	int length; // total length of string name

	cout << "Level:" << setw(9);
	for (int col = 0; col < NUM_LEVELS; col++)
	{
		cout << levelArray[col] << setw(5);
	}
	cout << setw(10) << "Total" << endl << endl;

	for (int row = 0; row < NUM_CAR_SIZES; row++)
	{
		cout << CAR_STRINGS[row];
		length = CAR_STRINGS[row].length();
		cout << setw(15 - length); // formatting table

		for (int col = 0; col < NUM_LEVELS; col++)
		{
			cout  << array[row][col] << setw(5);
			totalCount += array[row][col];
			countCar += array[row][col];
		}
			cout << setw(10) << countCar;
			countCar = 0;
			cout << endl;
  }    // end outer for

	cout << "Total Cars Available for Rental" << setw(19) << totalCount << endl;

	cout << endl << endl;
	return;
}

//******************************************************************************
//  FUNCTION:	storeMenuChoice
//  DESCRIPTION: Displays the main menu and error checks input, also displays
//		different menu based on whether the garage is full or empty
//  INPUT:
//		count - total account of cars in garage
//	OUTPUT:
//		letterChoice - letter choice of the main menu
//******************************************************************************
char storeMenuChoice (int count)
{
	char letterChoice; // letter choice of main menu
	bool goodCode = true; // exit loop variable

	if (count == 0)
	{
		do
		{
			cout << endl;
			cout << "T-Turn in a car" << endl;
			cout << "E-Exit the program" << endl;
			cout << endl;
			cout << "Enter letter of choice: ";
			cin >> letterChoice;

			switch (letterChoice)
			{
					case 'T':
					case 't':
										 return letterChoice;
										 break;
					case 'E':
					case 'e':
										 return letterChoice;
										 break;
					default:   goodCode = false;
			}	// end switch

			if (!goodCode)
					cout << "Invalid Entry.  Try again."  << endl;

		} while (!goodCode);
	}
	else if (count == 120)
	{
		do
		{
			cout << endl;
			cout << "R-Rent a car" << endl;
			cout << "E-Exit the program" << endl;
			cout << endl;
			cout << "Enter letter of choice: ";
			cin >> letterChoice;

			switch (letterChoice)
			{
					case 'R':
					case 'r':
										 return letterChoice;
										 break;
					case 'E':
					case 'e':
										 return letterChoice;
										 break;
					default:   goodCode = false;
			}	// end switch

			if (!goodCode)
					cout << "Invalid Entry.  Try again."  << endl;

		} while (!goodCode);
	}
	else
	{
		do
		{

			cout << endl;
			cout << "R-Rent a car" << endl;
			cout << "T-Turn in a car" << endl;
			cout << "E-Exit the program" << endl;
			cout << endl;
			cout << "Enter letter of choice: ";
			cin >> letterChoice;

			switch (letterChoice)
			{
					case 'R':
					case 'r':
										 return letterChoice;
										 break;
					case 'T':
					case 't':
										return letterChoice;
										 break;
					case 'E':
					case 'e':
										return letterChoice;
										 break;
					default:   goodCode = false;
			}	// end switch

			if (!goodCode)
					cout << "Invalid Entry.  Try again."  << endl;

		} while (!goodCode);
	}



}

//******************************************************************************
//  FUNCTION:	carTypeChoice
//  DESCRIPTION: Displays sub menu and error checks the letter choice.
//	OUTPUT:
//		carTypeNum - integer value of the index for the car size menu chosen
//******************************************************************************
int carTypeChoice ()
{
	char carTypeLetter; // letter choice from sub menu of car size
	int carTypeNum; // index associated with car size
	bool goodCode; // exit code
	// if no cars available for rent dont display R, full not T
	do
	{
		goodCode = true;

		cout << endl;
		cout << "(C)OMPACT" << endl;
		cout << "(M)ID_SIZE" << endl;
		cout << "(F)ULL SIZE" << endl;
		cout << "(S)UV" << endl;
		cout << "(R)eturn to main menu" << endl;
		cout << endl;
		cout << "Enter letter of choice: ";
		cin >> carTypeLetter;

		switch (carTypeLetter)
		{
					case 'C':
					case 'c':  carTypeNum = 0;
										 break;
					case 'M':
					case 'm':  carTypeNum = 1;
										 break;
					case 'F':
					case 'f':	carTypeNum = 2;
										 break;
					case 'S':
					case 's':  carTypeNum = 3;
										 break;
					case 'R':
					case 'r':	carTypeNum = 4;
										break;
					default:   goodCode = false;
			}	// end switch

			if (!goodCode)
					cout << "Invalid Entry.  Try again."  << endl;

		} while (!goodCode);

  return carTypeNum;

}

//******************************************************************************
//  FUNCTION:	carTurnedIn
//  DESCRIPTION: Displays table of current number of cars stored per level.
//		Ask the user which level they want to park on and then error checks
//		that the level is available to hold another.
//  INPUT:
//		garageArray - garage array contains number of cars per level
//		carTypeLetter - takes carTypeLetter from sub menu
//		levelArray - hold the number of levels in an array
//	OUTPUT:
//		garageArray - garage array contains number of cars per level
//******************************************************************************
void carTurnedIn(int array[][NUM_LEVELS], int carTypeLetter,
								int levelArray[NUM_LEVELS])
{
	int countCar = 0; // total car count per car size
	int length; // length of string name for car type
	int levelChoice; // level selected by user to park car
	int newCarCount; // temp variable used to increase countCar by 1
	bool exit = false; // exit variable for loop

	// displays level and headers for table
	cout << "Level:" << setw(9);
	for (int col = 0; col < NUM_LEVELS; col++)
	{
		cout << levelArray[col] << setw(5);
	}
	cout << setw(10) << "Total" << endl << endl;

	// displays car type sizes
	for (int row = carTypeLetter; row < (carTypeLetter + 1); row++)
	{
		cout << CAR_STRINGS[row];
		length = CAR_STRINGS[row].length();
		cout << setw(15 - length);

		for (int col = 0; col < NUM_LEVELS; col++)
		{
			cout << array[row][col]<< setw(5);
			countCar += array[row][col];
		}

		cout << setw(10) << countCar << endl;
		cout << endl;
	}    // end outer for

	// if number of cars for a car type is full, then display error
	if(countCar == 30)
	{
		cout << endl;
		cout << "Error, this car is being returned to the wrong company." << endl;
		cout << endl;
		system("read -p 'Hit Enter to Continue. '");
		cout << endl;
	 }
	 else
	 {
	 	// do-while checks if level is open to park in, if not displays error
	 	do
		{
			cout << "Which level would you like to park your car on? ";
			cin >> levelChoice;
			if (array[carTypeLetter][levelChoice] < 5)
			{
			newCarCount = array[carTypeLetter][levelChoice];
			newCarCount++;
			countCar++;
			array[carTypeLetter][levelChoice] = newCarCount;
			cout << endl;
			cout << "Okay to park car in " << CAR_STRINGS[carTypeLetter]
				<< " row of level " << levelChoice << endl;
			cout << countCar << " " << CAR_STRINGS[carTypeLetter]
				<< " cars will now be available. " << endl;
			cout << endl;
			system("read -p 'Hit Enter to Continue. '");
			cout << endl;
			exit = true;
			}
			else
			{
			cout << endl;
			cout << "Error- Level " << levelChoice << " already contains 5 cars."
				<< endl;
			cout << "Pick a level with less than 5 cars already parked."
				<< endl << endl;
			system("read -p 'Hit Enter to Continue. '");
			cout << endl;
			}
		} while (exit == false);
	 }
}

//******************************************************************************
//  FUNCTION:	newRentalCar
//  DESCRIPTION:  Displays current number of cars per car size. Starting with
//		level 5 then if there is an available car decrease number of car.
//  INPUT:
//		garageArray - garage array contains number of cars per level
//		carTypeLetter - takes carTypeLetter from sub menu
//		levelArray - hold the number of levels in an array
//	OUTPUT:
//		garageArray - garage array contains number of cars per level
//******************************************************************************
void newRentalCar(int array[][NUM_LEVELS], int carTypeLetter,
									int levelArray[NUM_LEVELS])
{
	int countCar = 0; // number of cars per car type
	int length; // lenght of car size name
	int newCarCount; // temp variable to decrease garage array

	// displays table headers, loop displays level array
	cout << "Level:" << setw(9);
	for (int col = 0; col < NUM_LEVELS; col++)
	{
		cout << levelArray[col] << setw(5);
	}

	cout << setw(10) << "Total" << endl << endl;

	// displays name of selected row and values per level
	for (int row = carTypeLetter; row < (carTypeLetter + 1); row++)
	{
		cout << CAR_STRINGS[row];
		length = CAR_STRINGS[row].length();
		cout << setw(15 - length);

		for (int col = 0; col < NUM_LEVELS; col++)
		{
			cout << array[row][col]<< setw(5);
			countCar += array[row][col];
		}

		cout << setw(10) << countCar << endl;
		cout << endl;
	}    // end outer for

	// if 0 cars then no more cars to rent of that type
	if(countCar == 0)
	{
		cout << endl;
		cout << "There are no more " << CAR_STRINGS[carTypeLetter]
			<<" cars to rent." << endl << endl;
		system("read -p 'Hit Enter to Continue. '");
		cout << endl;
	}
	else
	{
		// loops through levels and finds first available rental car- level 5 down
		for (int col = 5; col >= 0; col--)
		{
			if(array[carTypeLetter][col] > 0)
			{
				newCarCount = array[carTypeLetter][col];
				newCarCount--;
				countCar--;
				array[carTypeLetter][col] = newCarCount;
				cout << endl;
				cout << "Pick up car from " << CAR_STRINGS[carTypeLetter]
					<< " row of level " << col << endl;
				cout << countCar << " " << CAR_STRINGS[carTypeLetter]
					<< " cars will now be available." << endl << endl;
				system("read -p 'Hit Enter to Continue. '");
				cout << endl;
				col = -1; // to exit for loop
			}
		}
	}
}

//******************************************************************************
//  FUNCTION:	saveToFile
//  DESCRIPTION:
//  INPUT:
//		garageArray - garage array contains number of cars per level
//		levelArray - hold the number of levels in an array
//	OUTPUT:
//		garageArray - garage array contains number of cars per level
//		binFileOut - this binary file is formatted sequentiallyin this order: level
//								index,the row index, and the number of cars in that level/row
//******************************************************************************
void saveToFile(ofstream& binFile, int array[][NUM_LEVELS], int levelArray[])
{
	int numCars; // number of cars in array
	int levelIndex; // index of parking garage level
	int rowCount = 0; // row index of parking garage

	for (int row = 0; row < NUM_CAR_SIZES; row++)
	{
		for (int column = 0; column < NUM_LEVELS; column++)
		{
			numCars = array[row][column];

			if (numCars != 0)
			{

			//read level Index
			levelIndex = levelArray[column];
			binFile.write (reinterpret_cast<char*> (&levelIndex), sizeof(int));

			// read row index
			binFile.write (reinterpret_cast<char*> (&rowCount), sizeof(int));

			// read number of cars index
			binFile.write (reinterpret_cast<char*> (&numCars), sizeof(int));
			}
		}
		rowCount++;
	}

	cout << endl;
	cout << "All data has been saved." << endl << endl;

	binFile.close();
}



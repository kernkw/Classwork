//******************************************************************************
//  FILENAME:	 KernAssn4.cpp
//  DESCRIPTION: This program will allow realtors to store there properties
//		in a database.  They will be prompted to view, display, or add properties.
//		they will only be allowed to add 750 properties, and each entry is error
//		checked.  This program will use an array of records to store and access
//		this data more effeciently.
//  DESIGNER:	 Kyle Kern
//  FUNCTIONS:
//		readListings- Reads currrent file into an array of recrods
//		displayMenu- Display a menu and prompts user for entry
//		displayAll- Displays the current database
//		addRecord- Adds a record to current array
//		removeRecord- Removes a record for the current array
//		exitProgram- Exits the program, but asks if want to save to file first
//		validateMls- error checks the mls is correct length
//		validatePrice- prompts user for price entry
//		validateStatus- prompts user for enum entry of property status
//		validateZipCode- prompts user to enter zip code, and error checks format
//		validateCompanyName- prompts users for compnay name and error checks
//		saveToFile- opens and saves to output file
//******************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>

using namespace std;

// constants
const string IN_FILE = "LISTINGS.TXT";  // input file
enum status {AVAILABLE, CONTRACT, SOLD};
const string StatusString[] = {"AVAILABLE", "CONTRACT", "SOLD"};

const int MAX = 750;


// global structure definition
struct listingRec
{
    int numMLS;
    double price;
	status listing_status;
    string zipCode;
    string companyName;
};

void readListings (ifstream& listIn, listingRec listingInfo[], int& num);
char displayMenu();
void displayAll(listingRec listingInfo[], int count);
void addRecord(listingRec listingInfo[], int& count);
void removeRecord(listingRec listingInfo[], int& count);
void exitProgram(listingRec listingInfo[], int count);
int validateMls ();
double validatePrice ();
status validateStatus ();
string validateZipCode ();
string validateCompanyName ();
void saveToFile (ofstream& listIn, listingRec listingInfo[], int count);

//******************************************************************************
//  FUNCTION:	main
//  DESCRIPTION: Reads input file into an array of records, then calls functions
//		to display a menu which loops until exit.  This will allow you to add,
//		remove or diaply all current records in array. Also call fuction to
//		save to a file.
//  INPUT:
//		 IN_FILENAME: listIn
//	OUTPUT:
//		IN_FILENAME: listIn
//  CALLS TO:
//		readListings- Reads currrent file into an array of recrods
//		displayMenu- Display a menu and prompts user for entry
//		displayAll- Displays the current database
//		addRecord- Adds a record to current array
//		removeRecord- Removes a record for the current array
//		exitProgram- Exits the program, but asks if want to save to file first
//		validateMls- error checks the mls is correct length
//		validatePrice- prompts user for price entry
//		validateStatus- prompts user for enum entry of property status
//		validateZipCode- prompts user to enter zip code, and error checks format
//		validateCompanyName- prompts users for compnay name and error checks
//		saveToFile- opens and saves to output file
//	OUTPUT:
//		Returns: 0 on success
//******************************************************************************
int main()
{

	ifstream listIn;	// input file
	char loadFile; // to load or not load input file
	int houseNum; // counter that counts number of houses inputed
	char letterChoice; // letter choice for menu selection
	bool exitCheck; // for looping menu
	char exitEarly; // for looping menu

	listingRec listingInfo[MAX];
	exitCheck  = false; // for menu loop

	listIn.open (IN_FILE.c_str()); // open input file
	
	cout << endl;
	cout << "This Program will display a menu with options for managing your properties." << endl << endl;

	cout << "Load existing data from a file (Y/N)? ";
	cin >> loadFile;
	loadFile = toupper(loadFile);
	

		if (loadFile == 'Y')
		{
			if(listIn)
			{
				readListings (listIn, listingInfo, houseNum);
				exitEarly = 'Y';
			}
			else
			{
				cout << endl;
				cout << "The input file doesn't exist.  Would you like to proceed without input data (Y/N)? ";
				cin >> exitEarly;
				if (exitEarly == 'Y')
				{
					cout << endl;
					cout << "Program will proceed without input data." << endl << endl;
					exitEarly = 'Y';
				}

			}
		}
		else
		{
			cout << endl;
			cout << "Program will proceed without input data." << endl << endl;
			exitEarly = 'Y';
		}

if (exitEarly == 'Y')
{
	do
	{
		letterChoice = displayMenu();

		switch (letterChoice) {
		case 'D':
		displayAll(listingInfo, houseNum);
		break;

		case 'A':
		addRecord(listingInfo, houseNum);
		displayAll(listingInfo, houseNum);
		break;

		case 'R':
		removeRecord(listingInfo, houseNum);
		displayAll(listingInfo, houseNum);
		break;

		case 'E':
		exitProgram(listingInfo, houseNum);
		exitCheck = true;
		break;

		default:
		cout << "Enter a valid letter choice.";
		}

	}while (exitCheck  != true);
}
	cout << endl;
	system ("PAUSE");
	return 0;

}

//******************************************************************************
//  FUNCTION:	readListings
//  DESCRIPTION: Reads array line by line and stores in an array of records
//  INPUT:
//		listingInfo- input file
//  OUTPUT:
//		Return Reference value:	num - count for num of recrods added
//******************************************************************************
void readListings (ifstream& listIn, listingRec listingInfo[], int& num)
{
	bool exitCheck; // exit loop variable
	int temp; // temp variable for enum
	char trash;
	bool maxRecords = false;
	
	num = 0;

	listIn >> temp;

	while ( listIn)
	{
  
        if (num < MAX && !maxRecords)
        {
        
           listingInfo[num].numMLS = temp;
		   listIn >> listingInfo[num].price;
	       listIn >> temp;
	       listingInfo[num].listing_status = static_cast<status>(temp);
      	   listIn >> listingInfo[num].zipCode;
      	   listIn.get(trash);                           // THIS READS THE SPACE BETWEEN THE ZIP AND COMPANY SO IT DOES NOT BECOME PART OF THE COMPANY NAME
	       getline(listIn, listingInfo[num].companyName);
	       num++;
	    }
	    else
	      maxRecords = true;
	    
		listIn >> temp;
	}
	
	if (maxRecords)
	  cout << "The maximum data was read from the file, all remaining data was ignored!" << endl;
	
	listIn.close();

}

//******************************************************************************
//  FUNCTION:	displayMenu
//  DESCRIPTION: Display menu and prompts user to enter letter, returns choice
//  OUTPUT:
//	letterChoice - letter chioce for menu
//******************************************************************************
char displayMenu()
{
	char letterChoice;

	cout << "   Menu" << endl;
	cout << "-----------" << endl;
	cout << "(D)isplay All" << endl;
	cout << "(A)dd" << endl;
	cout << "(R)emove" << endl;
	cout << "(E)xit" << endl;

	cout << endl;
	cout << "Enter first letter of choice: ";
	cin >> letterChoice;
	
	letterChoice = toupper(letterChoice);

	return letterChoice;

}

//******************************************************************************
//  FUNCTION:	displayAll
//  DESCRIPTION: Display all recrod in array
//  INPUT:
//		listingInfo - array of records
//		count - size of current array
//******************************************************************************
void displayAll(listingRec listingInfo[], int count)
{
	status temp; // status enum

	if (count == 0)
    {
	   cout << endl;
	   cout << "No records to display." << endl;
    }
    else
    {
	   cout << endl;
	   cout << "MLS#" << setw(10) << "Asking" << setw(10) << "Listing" << setw(13) << "Zip Code" << setw(12) << "Realtor" << endl;
	   cout << setw(13)<< "Price" << setw(11) << "Status"<< endl;
	   cout << "------" << setw(10) << "--------" << setw(12) << "-----------" << setw(13)  << "------------" << setw(13)  << "------------" << endl;
	   
	   for (int num = 0; num < count; num++)
	   {
           cout << listingInfo[num].numMLS
	            << setw(8) << listingInfo[num].price
	       
		   
		   // BASED UPON THE VALUE STORED IN listing_status you need to display a string that has the correct status name AVAILABLE, CONTRACT, SOLD      
	       // USE SELECTION TO DETERMINE THE CORRECT STRING TO DISPLAY     
	       //<< setw(6) << listingInfo[num].listing_status
	       
	       
	       << setw(19) << listingInfo[num].zipCode
	       << setw(15) << listingInfo[num].companyName << endl;
		}   // end for

}

  cout << endl;
  return;

}

//******************************************************************************
//  FUNCTION:	addRecord
//  DESCRIPTION: Adds record into array of record
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	count - passes back new size of array
//******************************************************************************
void addRecord(listingRec listingInfo[], int& count)
{
	int mlsNum; // mls number for property
	double price; // price of property
	string zipCode; // zipcode of porperty
	string companyName; // name of rental company
	char exit; // for exiting loop
	status temp; // status of contract for porperty

	do
	{

		if (count >= MAX)
		{
			cout << endl;
			cout << "The file is full, you must remove some"
							"data before you can add new data." << endl << endl;
		}

		else
		{
			mlsNum = validateMls();
			listingInfo[count].numMLS = mlsNum;

			price = validatePrice();
			listingInfo[count].price= price;

			temp = validateStatus();
			listingInfo[count].listing_status = temp;

			zipCode = validateZipCode();
			listingInfo[count].zipCode = zipCode;

			companyName = validateCompanyName();
			listingInfo[count].companyName = companyName;
			count++;
		}

		cout << "Do you wish to exit (E) or add another record (A)? ";
		cin >> exit;

	}while (exit != 'E');


  cout << endl;
  return;

}

//******************************************************************************
//  FUNCTION:	removeRecord
//  DESCRIPTION: Removes record into array of record
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	count - passes back new size of array
//******************************************************************************
void removeRecord(listingRec listingInfo[], int& count)
{
	int mlsNum; // mls number of property
	bool deleted; // where mls is deleted or not
	int placeFound; // the index where mls record was founf

	placeFound = 0;
	deleted = true;

	if (count == 0)
	{
		cout << endl;
		cout << "No Listings stored." << endl;
	}
	else
	{
		do
		{
			cout << "MLS on File" << endl;
			for (int num = 0; num < count; num++) {
			cout << setw(5) << listingInfo[num].numMLS << " ";
			}
			cout << endl;
			cout << "Enter the MLS# you wish to delete." << endl;
			mlsNum = validateMls();



			while ((placeFound < count) && (listingInfo[placeFound].numMLS != mlsNum))
			{
				placeFound++;
			}

			cout << "placeFound: " << placeFound << endl;
			cout << "count: " << count << endl;

			if (placeFound < count)
			{
				listingInfo[placeFound] = listingInfo[count - 1];

				count--;

				cout << "MLS Number " << listingInfo[0].numMLS << endl;
				deleted = true;
			}
			else
			{
				cout << "That record doesnt exits, please try again.";
				deleted = false;
			}
		} while (deleted != true);
	}

}

//******************************************************************************
//  FUNCTION:	exitProgram
//  DESCRIPTION: Exits program and asks if user would like to save array to file
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//******************************************************************************
void exitProgram(listingRec listingInfo[], int count)
{
	ofstream listIn; // output file
	char saveResults; // save results exit loop

	do
	{
		cout << "Do you wish to save the results to the LISTINGS.TXT file (Y or N)? ";
		cin >> saveResults;
		switch (saveResults)
		{
		case 'Y':
			saveToFile (listIn, listingInfo, count);
		break;
		case 'N':
			cout << "You will lose all unsaved data, do you wish to continue (Y or N)? ";
			cin >> saveResults;
		break;
		default:
			cout << "Please enter Y or N.";
		}
	}while (saveResults != 'Y');


}

//******************************************************************************
//  FUNCTION:	validateMls
//  DESCRIPTION: Prompts user for mls number and error checks
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	mlsNum - the mls number of the record
//******************************************************************************
int validateMls ()
{
	int mlsNum; // mls number of property
	bool valid; // exit loop variable

	valid = 0;

	do
	{
		cout << "Enter the MLS number: ";
		cin >> mlsNum;

		if((mlsNum >= 100000) && (mlsNum <= 999999))
		{
			valid = 1;
		}
		else
		{
			cout << "Error, the entry must be 6 digits long." << endl;
			valid = 0;
		}
	} while (valid != 1);

	return mlsNum;
}

//******************************************************************************
//  FUNCTION:	validatePrice
//  DESCRIPTION: Prompts user for price
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	price - the price of house
//******************************************************************************
double validatePrice()
{
	double price; // price of the property

    do
    {
        cout << "Enter the price: ";
	    cin >> price;
	    cout << endl;
	    
	    if(price <= 0)
		 cout << "The listing price should be greater than zero!  Please try again." << endl; 

    }
    while (price <= 0);

	return price;
}

//******************************************************************************
//  FUNCTION:	validateStatus
//  DESCRIPTION: Prompts user for status and error checks
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	status - the price of property
//******************************************************************************
status validateStatus ()
{
	int input; // status of property
	status temp;
	
	do
	{
	   cout << "Enter: 0-AVAILABLE 1-CONTRACT 2-SOLD" << endl;
	   cout << "Enter the status: ";
	   cin >> input;
	   cout << endl;
	   
	   if (input < 0 || input > 2)
	     cout << "You did enter enter a valid value, please try again." << endl;
    }
    while (input < 0 || input > 2);
    
    temp = static_cast<status>(temp);
    
	return temp;
}

//******************************************************************************
//  FUNCTION:	validateZipCode
//  DESCRIPTION: Prompts user for zip code and error checks
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	zipCode - the zip code of property
//******************************************************************************
string validateZipCode ()
{
	string zipCode; // zip code of property
	char ch; // used for character operation
	int index; // index of the array
	bool errorZip; // to exit loop

	zipCode[9]; // sets max on zipcode size
	index = 0;

	// while loop loops through zip code entry error checking
	while (index < 9)
	{
		index = 1;
		cout << "Enter the Zip Code: ";
		cin >> zipCode;

		if(zipCode.length() != 10)
		{
			cout << "The Zip Code must be in correct format. XXXXX-XXXX" << endl;
			index = 0;
		}

		while ((index < 9) && (index != 0))
		{
			ch = zipCode[index];
			if(isdigit(ch))
			{
				index++;
			}
			else
			{
				if(zipCode[5] != '-')
				{
					cout << "The Zip Code must be in correct format. XXXXX-XXXX" << endl;
					index = 0;
				}

				index++;
			}

		}
	}

	return zipCode;
}

//******************************************************************************
//  FUNCTION:	validateCompanyName
//  DESCRIPTION: Prompts user for company name and error checks
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	companyName - the property's company name
//******************************************************************************
string validateCompanyName ()
{
	string companyName; // company name for property
	bool error; // exit loop variable
	int index; // index for string array

	index = 0;
	char ch;

	error = 0;
	companyName[20];

	do
	{
		cout << "Enter the Company Name: ";
		cin.ignore();
		getline(cin, companyName);

		if (companyName.length() > 20)
		{
			cout << "Error: The Company Name must be under 20 characters." << endl;
			error = 0;
		}
		else
		{
			error = 1;
		}
	} while (error != 1);

companyName[0] = toupper(companyName[0]);

while (index < 20 && ch != '\n')
{
	ch = companyName[index];
	if (isspace(ch))
	{
		companyName[index + 1] = toupper(companyName[index + 1]);
	}
	index++;

}

	return companyName;
}

//******************************************************************************
//  FUNCTION:	saveToFile
//  DESCRIPTION: Opens input file and rights array data to file, then closes
//  INPUT:
//		listingInfo - adds record into array
//		count - reads count for array indexing
//  OUTPUT:
//	listIn - the output file
//******************************************************************************
void saveToFile (ofstream& listIn, listingRec listingInfo[], int count)
{
	listIn.open (IN_FILE.c_str()); // open output file

  for (int num = 0; num < count; num++) {
      listIn << setw(5) << listingInfo[num].numMLS
	       << setw(15) << listingInfo[num].price
	       << setw(16) << listingInfo[num].listing_status
	       << setw(18) << listingInfo[num].zipCode
	       << setw(15) << listingInfo[num].companyName << endl;
  }

	listIn.close ();

	cout << endl;
	return;
}

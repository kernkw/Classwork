//******************************************************************************
//  FILENAME:	 KernAssn6.cpp
//  DESCRIPTION:  This program will allow the user to upload data from a choosen
//		file, and will display the events to a screen.  Then the user will be
//		able to add new list, remove listings, or update listing to match the
//		most current asking price.  The user can then choose to save to a file
//		and will be able to select the file they wish to save to.
//  DESIGNER:	 Kyle Kern
//  FUNCTIONS:
//		readListings- Reads currrent file into a linked list
//		displayMenu- Display a menu and prompts user for entry
//		displayAll- Displays the current database
//		addRecord- Adds a record to current linked list
//		removeRecord- Removes a record for the current linked list
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

using namespace std;

// constants
const string UPDATE_FILE = "CHANGES.TXT";
enum status {AVAILABLE, CONTRACT, SOLD};
const string StatusString[] = {"AVAILABLE", "CONTRACT", "SOLD"};
const int MIN_MLS = 100000;
const int MAX_MLS = 999999;
const int MLS_WID = 6;
const int ZIP_INDEX = 9;
const int COMPANY_LENGTH = 20;


// global structure definition
struct listingRec
{
    int numMLS;
    double price;
		int listing_status;
    string zipCode;
    string companyName;
    listingRec* next;
};

void readListings (ifstream& listIn, listingRec* &firstNode, listingRec* &lastNode);
char displayMenu();
void displayAll(listingRec* &firstNode);
void addRecord(listingRec* &firstNode, listingRec* &lastNode);
void removeRecord(listingRec* &firstNode);
void changePrice(ifstream& changeIn, listingRec* &firstNode);
int validateMls ();
double validatePrice ();
status validateStatus ();
string validateZipCode ();
string validateCompanyName ();
string fileNameCheck ();
void saveToFile (listingRec *firstNode, string filename, char &overwrite);

//******************************************************************************
//  FUNCTION:	main
//  DESCRIPTION: This calls the separate functions, looping through them,
//		until they meet proper variables. This will determine the structure of
//		program by determine what functions ot call based on the users input.
//  INPUT:
//		 listIn- user determined file : TXT format with format per line
//			mls number, price, zip code, then realtor company name per line
//			ex. 111111 229700 0 80501-2345 Jones Realty
//					345678 176900 1 80513-2918 Metro Brokers
//		changeIn - input file CHANGES.TXT
//				file format:  numMLS price
//				ex:  111111 25000
//						 222222 10000
//	OUTPUT:
//		listIn- user determined file : TXT format with format per line
//			mls number, price, zip code, then realtor company name per line
//			ex. 111111 229700 0 80501-2345 Jones Realty
//					345678 176900 1 80513-2918 Metro Brokers
//  CALLS TO:
//		readListings- Reads currrent file into a linked list
//		displayMenu- Display a menu and prompts user for entry
//		displayAll- Displays the current database
//		addRecord- Adds a record to current linked list
//		removeRecord- Removes a record for the current linked list
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
	ifstream changeIn; // input file for the chnages in asking prices
	ifstream listIn;  // input file for listing records
	char loadFile;  // variable where users chooses to load file or not
	char letterChoice; // letter choice for menu selection
	bool exitCheck; // for looping menu
	char exit; // for exiting loop
	char exitMenu; // for exiting the menu loop
	string listName; // list name for the file choosen by user
	string filename;  // file name choosen by user
	char ans;  // holds answer selection for exiting or adding to loop
	char overwrite;  // determines when to overwrite files or not
	exitCheck  = false; // for menu loop
	listingRec* firstNode = NULL;
	listingRec* lastNode = NULL;

	cout << endl;
	cout << "This Program will display a menu with options for managing your "
		"properties. You will be able to upload house listings files and "
		"manage these files by removing or adding to your list." << endl << endl;

	cout << endl << endl;
	system("read -p 'Hit Enter to Continue. '");
	cout << endl;

	do
	{
		cout << "Load existing data from a file (Y/N)? ";
		cin >> loadFile;
		loadFile = toupper(loadFile);
		if (loadFile != 'N' && loadFile != 'Y')
		{
			cout << endl;
			cout << "You did not enter Y or an N!" << endl;
			cout << "Please try again." << endl;
		}
	}while (loadFile != 'N' && loadFile != 'Y');
	if (loadFile == 'Y')
	{
		do
		{
			listName = fileNameCheck ();

			listIn.clear();
			ifstream listIn;
			listIn.open (listName.c_str()); // open input file

			if (listIn)  // if file name entered exists proceed
			{
				exitMenu = 'Y';
				readListings (listIn, firstNode, lastNode);
				displayAll(firstNode);
			}
			else  // if file name doesnt exist, ask user to go on or reenter filename
			{
				 do
        {
					cout << "Filename doesnt exist, go on without it (Y/N)? ";
					cin >> exitMenu;
					exitMenu = toupper(exitMenu);
					if (exitMenu != 'N' && exitMenu != 'Y')
					{
						 cout << endl;
						 cout << "You did not enter Y or an N!" << endl;
						 cout << "Please try again." << endl;
					}
        }while (exitMenu != 'N' && exitMenu != 'Y');

				if (exitMenu == 'Y')
				{
					lastNode = NULL;
					firstNode = NULL;
				}
			}
		} while (exitMenu == 'N');
	}

	do
	{
		letterChoice = displayMenu();

		switch (letterChoice) {

		case 'D':
			displayAll(firstNode);
		break;

		case 'A':
		do
		{
			addRecord(firstNode, lastNode);
			displayAll(firstNode);
			do
			{
				cout << "Do you wish to exit (E) or add another record (A)? ";
				cin >> exit;
				exit = toupper(exit);
				if (exit != 'E' && exit != 'A')
				{
					cout << endl;
					cout << "You did not enter E or an A!" << endl;
					cout << "Please try again." << endl;
				}
			}while(exit != 'E' && exit != 'A');
		}while (exit != 'E');
		break;

		case 'R':
		removeRecord(firstNode);
		displayAll(firstNode);
		break;

		case 'E':
		do
		{
			cout << "Do you wish to save the listings data to a file (Y/N)? ";
			cin >> ans;
			ans = toupper(ans);
			if (ans != 'N' && ans != 'Y')
			{
				cout << endl;
				cout << "You did not enter Y or an N!" << endl;
				cout << "Please try again." << endl;
			}
		}while (ans != 'N' && ans != 'Y');

		if (ans == 'Y')
		{
			do {
				filename = fileNameCheck ();
				saveToFile (firstNode, filename, overwrite);
			}while (overwrite == 'N');  // loop until user chooses to overwrite or
																// enters a vlaid filename

			exitCheck = true;
		}
		else
		{
			exitCheck = true;
		}
		break;

		case 'C':
		changePrice(changeIn, firstNode);
		break;

		default:
		cout << "Enter a valid letter choice.";
		}

	}while (exitCheck  != true);

	cout << endl;
	system ("PAUSE");
	return 0;

}

//******************************************************************************
//  FUNCTION:	readListings
//  DESCRIPTION: Reads array line by line and stores in an array of records
//  INPUT:
//		listIn- input file
//  OUTPUT:
//		Return Reference value:	firstNode - first node in listingRec linked list
//			lastNode - last node in listingRec linked list
//******************************************************************************
void readListings (ifstream& listIn, listingRec* &firstNode, listingRec* &lastNode)
{
	char pauseChar; // pause char if heap error occurs
	int tempMLS;	// temporary variable to store mls from listIn file
	double tempPrice;	// temporary variable to store price from listIn file
	int tempStatus;	// temporary variable to store status from listIn file
	string tempZip;	// temporary variable to store zip code from listIn file
	string tempName;	// temporary variable to store company name from listIn file
	char trash;	// to account from space between zip code and company name
	listingRec *newNode;  // to store temporary variable for the listingRec node
	lastNode = NULL; // start empty set to NULL
	firstNode = NULL; // start empty set to NULL

	if (!listIn)
	{
		cout << "Error opening data file" << endl << endl;
	}
	else
	{

		do{
			listIn >> tempMLS;
			listIn >> tempPrice;
			listIn >> tempStatus;
			listIn >> tempZip;
			listIn.get(trash);
			getline(listIn, tempName);

			if (listIn) {
				newNode = new (nothrow) listingRec;  // create new node

				if (newNode == NULL) {
					cout << "Heap error - could not allocate memory" << endl;
					cin >> pauseChar;
				}
		  else {
					newNode->numMLS = tempMLS;
					newNode->price = tempPrice;
					newNode->listing_status = tempStatus;
					newNode->zipCode = tempZip;
					newNode->companyName = tempName;
					newNode->next = NULL;

					if (firstNode == NULL) {
						lastNode = newNode;
						firstNode = newNode;
					}
					else {
						lastNode->next = newNode;
						lastNode = newNode;
					}
				} // end bigger else
			}

		} while ( listIn && (newNode != NULL));

		listIn.close();

	}

	return;

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

	cout << endl;
	cout << "   Menu" << endl;
	cout << "-----------" << endl;
	cout << "(D)isplay All" << endl;
	cout << "(A)DD" << endl;
	cout << "(R)emove" << endl;
	cout << "(C)hange Price" << endl;
	cout << "(E)xit" << endl;

	cout << endl;
	cout << "Enter first letter of choice: ";
	cin >> letterChoice;

	letterChoice = toupper(letterChoice);

	return letterChoice;

}

//******************************************************************************
//  FUNCTION:	displayAll
//  DESCRIPTION: Display all records in linked list listingRec
//  INPUT:
//		firstNode - set from readlisitngRec, first record in linked list
//******************************************************************************
void displayAll(listingRec* &firstNode)
{
	int temp; // temp status enum
	listingRec* tempRec = firstNode;  // set first Node to temproary variable

	if (tempRec == NULL){
		cout << endl;
		cout << "There are no records on file." << endl << endl;
	}
	else {
		cout << endl;
		cout << "MLS#" << setw(4) <<  ' ' << "Asking" << setw(3) << ' ' << "Listing"
		<< setw(5) << ' ' << "Zip Code" << setw(5) << ' ' << "Realtor" << endl;
		cout << setw(8) << ' ' << "Price" << setw(4) << ' ' << "Status"<< endl;
		cout << "------" << ' ' << "--------" << ' ' << "----------"
			<< ' ' << "------------" << ' '  << "------------" << endl;
			while (tempRec != NULL){
					 cout << setw(6) << tempRec->numMLS;
					 cout << setw(2) << ' ' << tempRec->price;
					 temp = tempRec->listing_status;
					 cout << left << setw(3) << ' ' << setw(11) << StatusString[temp];
					 cout << setw(13) << tempRec->zipCode;
					 cout << tempRec->companyName;
					 cout << endl;

					 tempRec = tempRec->next;
		}   // end while
	}

  cout << endl;
  return;

}

//******************************************************************************
//  FUNCTION:	addRecord
//  DESCRIPTION: Adds record into array of record
//  INPUT:
//		firstNode- first node in linked list listingRec
//		lastNode-  first node in linked list listingRec  - NULL
//	Functions:
//		validateMls- error checks the mls is correct length
//		validatePrice- prompts user for price entry
//		validateStatus- prompts user for enum entry of property status
//		validateZipCode- prompts user to enter zip code, and error checks format
//		validateCompanyName- prompts users for compnay name and error checks
//  OUTPUT:
//	firstNode- passes back new first node after addition
//	lastNode- passes back  new last node after addition
//******************************************************************************
void addRecord(listingRec* &firstNode, listingRec* &lastNode)
{
	char pauseChar; // pause char if heap error occurs
	int tempMLS;	// temporary variable to store mls from listIn file
	double tempPrice;	// temporary variable to store price from listIn file
	int tempStatus;	// temporary variable to store status from listIn file
	string tempZip;	// temporary variable to store zip code from listIn file
	string tempName;	// temporary variable to store company name from listIn file

	listingRec *newNode;  // to store temporary variable for the listingRec node

	if (firstNode == NULL) {
		newNode = new (nothrow) listingRec; // if linked list empty add new node

	}
	else { // if not empty add node to end of linked list
		lastNode->next = newNode;
		newNode = NULL;
		newNode = new (nothrow) listingRec;
	}
	if (newNode == NULL) { // check if can allocate memory for linked list
		cout << "Heap error - could not allocate memory" << endl;
		cin >> pauseChar;
	}
	else {
			tempMLS = validateMls();
			newNode->numMLS = tempMLS;

			tempPrice = validatePrice();
			newNode->price = tempPrice;

			tempStatus = validateStatus();
			newNode->listing_status = tempStatus;

			tempZip = validateZipCode();
			newNode->zipCode = tempZip;

			tempName = validateCompanyName();
			newNode->companyName = tempName;

			newNode->next = NULL;

			if (firstNode == NULL) {
				lastNode = newNode;
				firstNode = newNode;
			}
			else {
				lastNode->next = newNode;
				lastNode = newNode;
			}
	}

	return;

}

//******************************************************************************
//  FUNCTION:	removeRecord
//  DESCRIPTION: Removes record from linked list listingRec
//  INPUT:
//		firstNode - first node in linked list listingRec
//  OUTPUT:
//	firstNode - new first node in linked list listingRec
//******************************************************************************
void removeRecord(listingRec* &firstNode)
{
	listingRec *tempRec = firstNode;  // set top node to temporary variable
			listingRec *here = NULL, 	// Node being checked
		*prev = NULL;  	// Node prior to node being checked

	bool success = false; // exit loop varaible
	int delMLS; // varaible searching for

	if (tempRec == NULL){
				cout << endl;
				cout << "There are no MLS records on file." << endl << endl;
			}
	else{
				listingRec *here, 	// Node being checked
				*prev; 	// Node prior to node being checked

				cout << endl;
				cout << "MLS on File" << endl << endl;
				while (tempRec != NULL){
					cout << setw(6) << tempRec->numMLS << ' ' ;
					tempRec = tempRec-> next;
				}

				cout << endl << endl;
				cout << "Enter the MLS# you wish to delete." << endl;
				delMLS = validateMls();

				if ( firstNode->numMLS == delMLS) { // If delName found in first node,
							here = firstNode;
							firstNode = firstNode->next;	//  Delete top item
							delete here;
							success = true;
						}

				else {                                   // Not top item, so search...
							prev = firstNode;                      // Initialize prev and here to
							here = firstNode->next;                // first 2 nodes in list

						// Look for delMLS (while not end of list and name doesn't match)
						while ( (here != NULL) && (here->numMLS != delMLS) ) {
							prev = here;               // move prev down one
							here = here->next;         // move here down one
							}

						if (here != NULL) {               // If found, delete item from list
							prev->next = here->next;
							delete here;
							success = true;
							}
						else {
							cout << delMLS << " not found in list." << endl;
							}                             // Otherwise, give error message
					}	// End else (not top Item)
		}
}

//******************************************************************************
//  FUNCTION:	changePrice
//  DESCRIPTION: Searches for matching MLS number, if found it will chnage the
//		asking price of that record to the last MLS number on file.
//  INPUT:
//		changeIn - input file CHANGES.TXT
//				file format:  numMLS price
//
//		firstNode- the first node in the linked list
//  OUTPUT:
//	firstNode - the new first node in the linked list
//******************************************************************************
void changePrice(ifstream& changeIn, listingRec* &firstNode)
{
		changeIn.open (UPDATE_FILE.c_str()); // open input file
		int findMLS; // mls searching for
		double changePrice; // the pirce to chnage
		bool found;  //  determines if found or not
		bool header = false;  // determines whether header has already been displayed

		if (!changeIn)
		{
			cout << endl;
			cout << "The file doesnt exist, returning to main menu." << endl << endl;
		}
		else {

			changeIn >> findMLS >> changePrice;  // inputs first line of changeIn file

		while (changeIn)
		{
			found = false;

				listingRec *tryRec = firstNode;  // sets first node of listingRec to temp

				listingRec *foundNode = NULL;

				while(!found && (tryRec != NULL))  // searches for matching MLS numbers
				{

					if (tryRec->numMLS == findMLS)
					{
						foundNode = tryRec;
						foundNode->price = changePrice;
						cout << endl;
						if (!header)
						{
							cout << "MLS#" << setw(4) <<  ' ' << "New" << endl;
							cout << setw(8) << ' ' << "Price" << setw(4) << endl;
							cout << "------" << ' ' << "--------" << endl;
							header = true;
							cout << setw(6) << tryRec->numMLS << ' '  << tryRec->price << endl;
							found = true;
						}
						else
						{
							cout << setw(6) << tryRec->numMLS << ' '  << tryRec->price << endl;
							found = true;
						}
					}
					else
					{
						tryRec = tryRec->next;
					}
				}

				changeIn >> findMLS >> changePrice;
		}
		if (!found)
		{
			cout << endl;
			cout << "None of the MLS records match, so no price reductions were made!"
				<< endl << endl;
		}
		changeIn.close(); // close input file
	}
}

//******************************************************************************
//  FUNCTION:	validateMls
//  DESCRIPTION: Prompts user for mls number and error checks
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
		cout << endl;
		cout << "Enter the MLS number: ";
		cin >> mlsNum;
		cout << endl;

		if((mlsNum >= MIN_MLS) && (mlsNum <= MAX_MLS))
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
//  OUTPUT:
//	price - the price of house
//******************************************************************************
double validatePrice ()
{
	double price; // price of the property

	do
	{
		cout << "Enter the price: ";
		cin >> price;
		cout << endl;

		if (price <= 0)
		{
		cout << "The listing price should be greater than zero!"
		"Please try again." << endl;
		}

	} while (price <= 0);

	return price;

}

//******************************************************************************
//  FUNCTION:	validateStatus
//  DESCRIPTION: Prompts user for status and error checks
//  OUTPUT:
//	status - the price of property
//******************************************************************************
status validateStatus ()
{
	int input;
	status temp;

	do
	{
		cout << "Enter: 0-AVAILABLE 1-CONTRACT 2-SOLD" << endl;
		cout << "Enter the status: ";
		cin >> input;
		cout << endl;

		if ((input < 0) || (input > 2))
		{
			cout << "PLease enter a vaild value." << endl;
		}
	} while ((input < 0) || (input > 2));

	temp = static_cast<status>(temp);

	return temp;

}

//******************************************************************************
//  FUNCTION:	validateZipCode
//  DESCRIPTION: Prompts user for zip code and error checks
//  OUTPUT:
//	zipCode - the zip code of property
//******************************************************************************
string validateZipCode ()
{
	string zipCode; // zip code of property
	char ch; // used for character operation
	int index; // index of the array
	bool errorZip; // to exit loop

	index = 0;

	// while loop loops through zip code entry error checking
	while (index <= ZIP_INDEX)
	{
		index = 0;
		cout << "Enter the Zip Code: ";
		cin >> zipCode;
		cout << endl;

		if(zipCode.length() != (ZIP_INDEX + 1))
		{
			cout << "The Zip Code must be in correct format. XXXXX-XXXX" << endl;
			index = -1;
		}
		while(index <= ZIP_INDEX && index != -1)
		{
			ch = zipCode[index];
			if(index <= 4)
			{
				if(isdigit(ch))
				{
					index++;
				}
				else
				{
					cout << "The Zip Code must be in correct format. XXXXX-XXXX" << endl;
					index = -1;
				}
			}
			if (zipCode[5] == '-')
			{
					index++;
			}
				else
				{
					cout << "The Zip Code must be in correct format. XXXXX-XXXX" << endl;
					index = -1;
				}
			}
			if (index > 5)
			{
				if(isdigit(ch))
				{
					index++;
				}
				else
				{
					cout << "The Zip Code must be in correct format. XXXXX-XXXX" << endl;
					index = -1;
				}
			}
		}

	return zipCode;

}

//******************************************************************************
//  FUNCTION:	validateCompanyName
//  DESCRIPTION: Prompts user for company name and error checks
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

	cin.ignore();

	do
	{
		error = 1;
		cout << "Enter the Company Name: ";
		getline(cin, companyName);



		if (companyName.length() > COMPANY_LENGTH)
		{
			cout << "Error: The Company Name must be under 20 characters." << endl;
			error = 0;
		}
		companyName[0] = toupper(companyName[0]);

		index = 1;

		while (index < companyName.length())
		{
			if (isspace(companyName[index - 1]))
			{
				companyName[index] = toupper(companyName[index]);
				index++;
			}
			else
			{
				index++;
			}
		}
		index = 0;
		while (index < companyName.length() && (error != 0))
		{
			ch = companyName[index];
			if (isalnum(ch))
			{
				index++;
				error = 1;
			}
			else if (isspace(ch))
			{
				index++;
				error = 1;
			}
			else
			{
				cout << "Error:  company name must be an alphanumeric character." << endl;
				error = 0;
			}
		}

} while (error != 1);

	return companyName;

}

//******************************************************************************
//  FUNCTION:	fileNameCheck
//  DESCRIPTION: Prompts user to enter filename
//  OUTPUT:
//	fileName - the file name inputed by user
//******************************************************************************
string fileNameCheck ()
{
	string fileName;
	ifstream fileCheck;

	cout << "Enter the filename: ";
	cin >> fileName;

	return fileName;
}

//******************************************************************************
//  FUNCTION:	saveToFile
//  DESCRIPTION: Opens input file and rights array data to file, then closes
//  INPUT:
//		firstNode - first node in file
//		filename - the string entered by user
//  OUTPUT:
//	overwrite - return user choice to overwrite file or not
//******************************************************************************
void saveToFile (listingRec *firstNode, string filename, char &overwrite)
{
    ifstream textin;  // file input
    ofstream textout;  // file output
    bool success = true; // exit loop varaible
    listingRec *nextNode; // temporary node for listingRec linked list
    char ans; // variabel for answering question to save file or not

		textin.clear();  // clears stream from input file
		textin.open (filename.c_str());
		if (!textin)  // if text input file doesnt exist already create and populate
		{
				textin.close();
					textout.open(filename.c_str());
					nextNode = firstNode;
				while (nextNode != NULL)
					{
						textout << nextNode->numMLS << ' ' << nextNode->price << ' ';
						textout << nextNode->listing_status << ' ' << nextNode->zipCode;
						textout << nextNode->companyName;
						nextNode = nextNode->next;
						if (nextNode != NULL)
						{
							textout << endl;
						}
					}
					textout.close();
		}
		else  // if file name already exists ask if user want to overwrite or not
		{
			cout << "This file already exists!" << endl;
			cout << endl;
			do
			{
				cout << "Do you want to overwrite the file? Y/N" << endl;
				cin >> overwrite;
				overwrite = toupper(overwrite);
				if (overwrite != 'N' && overwrite != 'Y')
				{
					 cout << endl;
					 cout << "You did not enter Y or an N!" << endl;
					 cout << "Please try again." << endl;
					 }
			}while (overwrite != 'N' && overwrite != 'Y');

			if (overwrite == 'Y')
			{
					textin.close();
					textout.open(filename.c_str());
					nextNode = firstNode;
				while (nextNode != NULL)
					{
						textout << nextNode->numMLS << ' ' << nextNode->price << ' ';
						textout << nextNode->listing_status << ' ' << nextNode->zipCode;
						textout <<  ' ' << nextNode->companyName;
						nextNode = nextNode->next;
						if (nextNode != NULL)
						{
							textout << endl;
						}
					}
					textout.close();
			}
		}
}






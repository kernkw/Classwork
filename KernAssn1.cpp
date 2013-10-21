//******************************************************************************
//  FILENAME:	 KernAssn1.cpp
//  DESCRIPTION: Program reads file and parses the data to calculate the
//							charge per household and per vehicle, based on the ownership
//							tax.  Then outputs the charges to two formatted files.
//  DESIGNER:	 Kyle Kern
//  FUNCTIONS:	 main - main program logic - processes data file
//              	CalcOwnershipTax - Calculates ownership tax based on vehicle
//																type and MSRP
//							CalculateVehicleCharge - Processes all fees associated with
//																			each vehicle
//							ProcessVehicleOutput - Loops through input file and line by
//																		line outputs to file VEHICLE.TXT
//							ProcessHouseOutput - Use ProcessVehicleOutput sum of each
//																	vehicle loop to output the total
//																	charge for each household, to file
//																	HOUSEHOLD.TXT
//******************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// constants filenames
const string IN_FILENAME = "REGISTER.TXT";
const string OUT_FILENAME_VEHICLES = "VEHICLES.TXT";
const string OUT_FILENAME_HOUSES = "HOUSEHOLDS.TXT";

//constants fee associated with vehicle charges
const double ROAD_FEE_A = 24;
const double ROAD_FEE_M = 12;
const double LICENSE_RATE = .0025;

//constants for car ownership tax
const double AGE_CURRENT = 2013; // current year

//constants used for automotives
const double AGE_5 = 5;
const double TAXRATE_5 = 0.03;
const double TAX_DOWN_RATE_5 = 0.0015;
const double AGE_10 = 10;
const double TAXRATE_10 = 0.0275;
const double TAX_DOWN_RATE_10 = 0.0012;
const double AGE_15 = 15;
const double TAXRATE_15 = 0.025;
const double TAX_DOWN_RATE_15 = 0.0009;
const double TAX_MAX = 20;

//constants use for motorcycles
const double TAX_DOWN_MOTOR_RATE = 0.0009;
const double TAXRATE_DOWN_MOTOR = 0.005;
const double TAX_MAX_MOTOR = 10;

// prototypes
double CalcOwnershipTax(double modelYear, char carType, double MSRP);
double CalculateVehicleCharge (double ownerTax, char carType, double MSRP);
void ProcessVehicleOutput (ifstream& textIn, ofstream& vehicleOut,
													 int& innerNumCars, double& sumVehicleCharge);
void ProcessHouseOutput (ofstream& houseOut,double& sumVehicleCharge,
												 double& vehicleCharge, int& houseId,
												 int& innerNumCars, double& totalChargePerHouse);

//******************************************************************************
//  FUNCTION:	  main
//  DESCRIPTION:  Opens input and output files.  Calls CalcOwnershipTax,
//								CalculateVehicleCharge, ProcessVehicleOutput, and
//								ProcessHouseOutput for each line in the file.
//								Then outputs result to output file and displays
//								on console. Closes files.
//  INPUT: File:  Opens input data file
//                The number of lines in the file is unknown
//  CALLS TO:	 ProcessVehicleOutput
//						CalcOwnershipTax
//						CalculateVehicleCharge
//						ProcessHouseOutput
//******************************************************************************
int main()
{
		ifstream textIn;                  // input file stream variable
    ofstream vehicleOut;							 // output file stream variable
    ofstream houseOut;                // output file stream variable
    int houseId;
    char carType;
    string licenseId;
    double modelYear;
    double MSRP;
    char ch;
    double ownerTax;
    double vehicleCharge;
		double sumVehicleCharge;
    int innerNumCars;
    double totalChargePerHouse;
    double totalChargeCounty;
    int countLines;

    countLines = 0;
    totalChargeCounty = 0;

    // open both the input and output files
    textIn.open (IN_FILENAME.c_str());
    vehicleOut.open (OUT_FILENAME_VEHICLES.c_str());
    houseOut.open (OUT_FILENAME_HOUSES.c_str());

    if (textIn)
    {
				cout << setw(11) << "Household" << setw(11)
						<< "Vehicles" << setw(9) << "Total" << endl;
        cout << setw(11) << "ID Number" << setw(13)
						<< "Registered" << setw(9) << "Charges" << endl;

				//use iomanip formatting to create table lines
        cout << "  " << setfill('-') << setw(12) << "  " << setfill('-')
						<< setw(12) << "  " << setw(12) << setfill('-')
						<< setw(12) << "  " << endl;

				// prime text input
        textIn >> houseId >> carType >> licenseId >> modelYear >> MSRP;

        while (textIn && (ch != '\n'))
        {
            cout << fixed << setprecision(2);
            vehicleOut << fixed << showpoint << right << setprecision(2);

            // call functions to calculate ownership tax and vehicle charge
            ownerTax = CalcOwnershipTax (modelYear, carType, MSRP);
            vehicleCharge = CalculateVehicleCharge (ownerTax, carType, MSRP);

            // output first line in outer loop
            vehicleOut << carType << " " << licenseId << setw(8)
											<< vehicleCharge << endl;

            // call functions to run loop on file input that will ouput to
            //	files and screen
						ProcessVehicleOutput (textIn,vehicleOut,
																	innerNumCars, sumVehicleCharge);

						ProcessHouseOutput (houseOut, sumVehicleCharge,
																			vehicleCharge, houseId,
																			innerNumCars, totalChargePerHouse);

						totalChargeCounty += totalChargePerHouse;
						countLines ++;

						// displays full screen and then outputs it
						if (countLines % 17 == 0)
						{
							cout << endl;
							system("read -p 'Hit Enter to continue. '");
							cout << endl;

							cout << setw(11) << "Household" << setw(11)
									<< "Vehicles" << setw(9) << "Total" << endl;
							cout << setw(11) << "ID Number" << setw(13)
									<< "Registered" << setw(9) << "Charges" << endl;

							//use iomanip formatting to create table lines
							cout << "  " << setfill('-') << setw(12) << "  " << setfill('-')
							<< setw(12) << "  " << setw(12) << setfill('-')
							<< setw(12) << "  " << endl;
						}

						// prime text input
            textIn >> houseId >> carType >> licenseId >> modelYear >> MSRP;
        }

        cout << setw(10) << "Total County Collected" << setw(5)
						<< "$" << setw(9) << totalChargeCounty;

        textIn.close();
        vehicleOut.close();
        houseOut.close();
    }

    else
    {
    cout << "Error opening input file" << endl;
    }

    cout << endl;
    system("read -p 'Hit Enter to continue. '");
    cout << endl;

    return 0;
}

//******************************************************************************
//  FUNCTION:	 CalcOwnershipTax
//  DESCRIPTION: Calulates the ownership tax of each vehicle
//  INPUT:       Parameter:    double modelYear
//													  char carType
//														double MSRP
//  OUTPUT: 	 Return value: ownerTax - given the vehicle type A or M
//******************************************************************************
double CalcOwnershipTax (double modelYear, char carType, double MSRP)
{
    double ownerTax;
    double yearsOld; // how man years old the vehicle is

    yearsOld = AGE_CURRENT - modelYear;

    if (carType == 'A')
    {
        if (yearsOld <= AGE_5)
        {
            ownerTax = (TAXRATE_5 * MSRP)
										- (TAX_DOWN_RATE_5 * (MSRP *yearsOld));
        }
        else if (yearsOld <= AGE_10)
        {
            ownerTax = (TAXRATE_10 * MSRP)
										- (TAX_DOWN_RATE_10 * (MSRP *yearsOld));
        }
        else if (yearsOld <= AGE_15)
        {
            ownerTax = (TAXRATE_15 * MSRP)
										- (TAX_DOWN_RATE_15 * (MSRP *yearsOld));
        }
        else if (yearsOld > AGE_15)
        {
            ownerTax = TAX_MAX;
        }
        else
        {
            cout << "ERROR";
        }

    }
    else
    {

        if (yearsOld <= AGE_5)
        {
            ownerTax = ((TAXRATE_5 - TAXRATE_DOWN_MOTOR) * MSRP)
											- (TAX_DOWN_MOTOR_RATE * (MSRP *yearsOld));
        }
        else if (yearsOld <= AGE_10)
        {
            ownerTax = ((TAXRATE_10 - TAXRATE_DOWN_MOTOR) * MSRP)
											- (TAX_DOWN_MOTOR_RATE * (MSRP *yearsOld));
        }
        else if (yearsOld <= AGE_15)
        {
            ownerTax = ((TAXRATE_15 - TAXRATE_DOWN_MOTOR) * MSRP)
											- (TAX_DOWN_MOTOR_RATE * (MSRP *yearsOld));
        }
        else if (yearsOld > AGE_15)
        {
            ownerTax = TAX_MAX_MOTOR;
        }
        else
        {
            cout << "ERROR";
        }
    }

    return ownerTax;
}

//******************************************************************************
//  FUNCTION:	 CalculateVehicleCharge
//  DESCRIPTION: Caculates the vehicle charge based on associated fees
//  INPUT:       Parameter:    double ownerTax
//														char carType
//														double MSRP
//  OUTPUT: 	 Return value: vehicleCharge - total vehicle charge for
//																				each vehicle
//******************************************************************************
double CalculateVehicleCharge (double ownerTax, char carType, double MSRP)
{
    double vehicleCharge;

    if (carType == 'A')
    {
        vehicleCharge = ROAD_FEE_A + (MSRP* LICENSE_RATE) + (ownerTax);
    }
    else
    {
        vehicleCharge = ROAD_FEE_M + (MSRP* LICENSE_RATE) + (ownerTax);
    }

    return vehicleCharge;
}

//******************************************************************************
//  FUNCTION:	 ProcessVehicleOutput
//  DESCRIPTION: Outputs the charge for each vehicle
//  INPUT:       File:                    REGISTER.TXT
//							Reference Parameters:    ifstream& textIn
//																			ofstream& vehicleOut
//																			int& innerNumCars
//																			double& sumVehicleCharge
//  OUTPUT: 	 To VEHICLE.TXT file formatted display of vehcile type
//					license plate id and the charge per vehicle
//******************************************************************************
void ProcessVehicleOutput (ifstream& textIn, ofstream& vehicleOut,
													int& innerNumCars, double& sumVehicleCharge)
{
    int houseId;
    char ch;
    char carType;
    string licenseId;
    double modelYear;
    double MSRP;
    double vehicleCharge;
    double ownerTax;
    double totalCountyCollected;

    //initalize values
    innerNumCars = 0;
    sumVehicleCharge = 0;

    textIn.get(ch);   // read space between house-id and car type

    while (textIn && (ch != '\n'))  // once line end is read loop will exit
    {
				// intial file input for function
        textIn >> carType >> licenseId >> modelYear >> MSRP;

        ownerTax = CalcOwnershipTax (modelYear, carType, MSRP);
        vehicleCharge = CalculateVehicleCharge (ownerTax, carType, MSRP);

        //format and output to vehcile file
        vehicleOut << fixed << showpoint << right <<  setprecision(2);
        vehicleOut << carType << " " << licenseId << setw(8)
									<< vehicleCharge << endl;

        // counts loops
        innerNumCars ++;
        sumVehicleCharge += vehicleCharge;

        textIn.get(ch);
    }

    return;
}

//******************************************************************************
//  FUNCTION:	 ProcessHouseOutput
//  DESCRIPTION: Outputs the household id and charge per house to the
//							console and outputs the household id and charge per
//							house to the output file.
//  INPUT:       Parameter:    ofstream& houseOut
//														double& sumVehicleCharge
//														double& vehicleCharge
//														int& houseId
//														int& innerNumCars
//  OUTPUT: 	 		File:					HOUSEHOLDS.TXT
//							Console:       displays charges per household
//******************************************************************************
void ProcessHouseOutput (ofstream& houseOut,double& sumVehicleCharge,
                         double& vehicleCharge, int& houseId, int& innerNumCars, double& totalChargePerHouse)
{

    double totalCountyCollected;

		// adds vehicle charge from outer loop
    totalChargePerHouse = sumVehicleCharge + vehicleCharge;

    //output to HOUSEHOLD.TXT file
    houseOut << fixed << showpoint << right << setprecision(2);
    houseOut << houseId << setw(8) << totalChargePerHouse << endl;

			// output to display screen
    cout << setfill(' ') << showpoint;

    // adds plus 1 to account for outer loop
    cout << setw(10) << houseId << " " << setw(8) << innerNumCars + 1
        << "    " << setw(4) << "$" << setw(9) << totalChargePerHouse << endl;


    return;
}




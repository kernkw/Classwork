#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

struct BT_node {

	int data;
	BT_node* leftChild;
	BT_node* rightChild;

}; // end BT_node

//prototypes
void readDataIntoTree(BT_node* &rootNode, ifstream& fileIn);
void CreateTree(BT_node* &rootNode);
bool IsEmpty(BT_node* &rootNode);
void InsertNode(BT_node* &binTreeTop, int insertData);
void InOrderDisplay(BT_node* &rootNode);
BT_node* FindNode(BT_node* rootNode, int searchData);
char displayMenu();

int main()
{
	ifstream fileIn;
	bool exitCheck; // for looping menu
	char letterChoice; // letter choice for menu selection
	int data;
	BT_node* rootNode;
	BT_node* foundNode;

	exitCheck  = false; // for menu loop
	CreateTree(rootNode);
	readDataIntoTree(rootNode, fileIn);
	do
	{
		letterChoice = displayMenu();

		switch (letterChoice) {
		case 'S':
		if(IsEmpty(rootNode))
		{
			cout << "Binary search tree is empty. " << endl;
		}
		else
		{
			cout << "Values stored in entire binary search tree are:" << endl;
			InOrderDisplay(rootNode);
		}
		break;

		case 'A':
		cout << "Enter the integer to add to the tree: ";
		cin >> data;
		// Check if duplicate
		foundNode = FindNode(rootNode,data);
		if(foundNode == NULL)
		{
			InsertNode(rootNode, data);
		}
		else
		{
			cout << endl << endl;
			cout << "Integer " << data << " is a duplicate and";
			cout << " will not be added to the tree." << endl;
		}
		break;

		case 'D':
		cout << "delete" << endl;
		break;

		case 'F':
		cout << "Enter value to find: ";
		cin >> data;
		foundNode = FindNode(rootNode,data);
		if (foundNode == NULL)
		{
			cout << "Integer not found." << endl;
		}
		else
		{
			cout << "Values stored subtree with root " << foundNode->data << " are:" << endl;
			InOrderDisplay(foundNode);
		}
		break;

		case 'E':
		cout << "exit" << endl;
		exitCheck = true;
		break;

		default:
		cout << "Enter a valid letter choice.";
		}

	}while (exitCheck  != true);

	cout << endl;
	system ("PAUSE");
	return 0;

}

void CreateTree(BT_node* &rootNode)
{
	rootNode = NULL;
}
bool IsEmpty(BT_node* &rootNode)
{
	if (rootNode == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void InsertNode(BT_node* &rootNode, int insertData)
{
		BT_node* current;
		BT_node* trailCurrent;

		BT_node* newNode = new BT_node;
		if (newNode != NULL) {         // check valid allocation
			newNode->data = insertData;     // dependant on data type
			newNode->leftChild = NULL;
			newNode->rightChild = NULL;
		}
		else
		{
			return;
		}
	if (IsEmpty(rootNode))
	{
		rootNode = newNode;
	}
	else
	{
		current = rootNode;

		while (current != NULL)
		{
			trailCurrent = current;

			if(current->data == insertData)
			{
				return;
			}
			else if(current->data > insertData)
			{
				current = current->leftChild;
			}
			else
			{
				current = current->rightChild;
			}
		}
		if(trailCurrent->data > insertData)
		{
			trailCurrent->leftChild = newNode;
		}
		else
		{
			trailCurrent->rightChild = newNode;
		}
	}

}

void readDataIntoTree(BT_node* &rootNode, ifstream& fileIn)
{
	int data;
	string fileName;
	BT_node* foundNode;
	bool success;
	do
	{
		cout << "Enter filename to be put into binary search tree: ";
		cin >> fileName;
		fileIn.open (fileName.c_str()); // open input file

		if (!fileIn)
		{
		cout << endl;
		cout << "Error-- file doesnt exist!" << endl;
		success = false;
		}
		else
		{
		success = true;
		}
	} while (!success);

	fileIn >> data;
	while(fileIn)
	{
		foundNode = FindNode(rootNode,data);
		if(foundNode == NULL)
		{
			InsertNode(rootNode, data);
		}
		else
		{
			cout << "Integer " << data << " is a duplicate and will be ignored." << endl;
		}
		fileIn >> data;
	}
	fileIn.close();
}

void InOrderDisplay(BT_node* &rootNode)
{
	if(!IsEmpty(rootNode))
	{
		InOrderDisplay(rootNode->leftChild);
		cout << rootNode->data << " ";
		InOrderDisplay(rootNode->rightChild);
	}

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
	cout << endl << endl;
	cout << "   Menu for Binary Search Tree" << endl;
	cout << "--------------------------------" << endl;
	cout << "(S)how all integers in tree" << endl;
	cout << "(A)dd integer to tree" << endl;
	cout << "(D)elete integer from tree" << endl;
	cout << "(F)ind integer in tree" << endl;
	cout << "(E)xit" << endl;

	cout << endl;
	cout << "Enter first letter of choice: ";
	cin >> letterChoice;

	letterChoice = toupper(letterChoice);

	return letterChoice;

}

BT_node* FindNode(BT_node* rootNode, int searchData)
{
	if(IsEmpty(rootNode))
	{
		// search data not found in tree
		return NULL;
	}
	else if (searchData < rootNode->data)
	{
		// search left subtree
		return FindNode(rootNode->leftChild, searchData);
	}
	else if (searchData > rootNode->data)
	{
		// search right subtree
		return FindNode(rootNode->rightChild, searchData);
	}
	else
	{
		// key found
		return rootNode;
	}
}

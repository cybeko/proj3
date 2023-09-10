#include <iostream>
#include "header.h"
using namespace std;

int main()
{
	int userCh;
	while (true)
	{
		printMenu();

		cout << "\nChoose option: ";
		cin >> userCh;

		switch (userCh)
		{
		case codeAddEmployee:
			addEmployee(pathData);
			break;
		case codeDelEmployee:
			delEmployee(pathData, pathTemp);
			break;
		case codePrintAll:
			printAllEmployee(pathData);
			break;
			break;
		case codeExit:
			cout << "\nFarewell!";
			return 0;
			break;
		default:
			cout << "This option does not exist." << endl;
			break;
		};
	}
}
void printMenu()
{
	cout << "\tMenu:" << endl;
	cout << "[" << codeAddEmployee << "] - Add employee" << endl;
	cout << "[" << codeDelEmployee << "] - Delete employee" << endl;
	cout << "[" << codePrintAll << "] - Print all employee" << endl;
	cout << "[" << codeExit << "] - Exit" << endl;
}

void addEmployee(const char pathData[])
{
	FILE* file;
	errno_t code = fopen_s(&file, pathData, "ab");

	if (code == 0)
	{
		Employee point;
		bool inpCheck = false;

		cout << "Enter first name: ";
		cin >> point.name;
		cout << "Enter last name: ";
		cin >> point.lastName;
		do 
		{
			cout << "Enter phone number: ";
			cin >> point.phoneNum;
			if (strlen(point.phoneNum) != 10)
			{
				cout << "Phone number must consist of 10 digits." << endl;
			}
			else
			{
				inpCheck = true;
			}
		} while (inpCheck == false);
		cout << "Enter salary: ";
		cin >> point.salary;
		fwrite(&point, sizeof(Employee), 1, file);
		fclose(file);
	}
	else
	{
		cout << "Error. Couldn't open the file." << endl;
	}
}

void printAllEmployee(const char pathData[])
{
	FILE* file;
	errno_t code = fopen_s(&file, pathData, "rb");

	if (code == 0)
	{
		Employee point;
		int counter = 1;

		while (!feof(file))
		{
			if (fread(&point, sizeof(Employee), 1, file))
			{
				printf("\tEmployee #%d\n", counter++);
				printStruct(point);
				cout << endl;
			}
		}
		fclose(file);
	}
	else
	{
		cout << "Error. Couldn't open the file." << endl;
	}
}
void printStruct(Employee point)
{
	printf("Name: %s\n", point.name);
	printf("Last name: %s\n",point.lastName);
	printf("Phone number: %s\n", point.phoneNum);
	printf("Salary: %f\n", point.salary);
}

void delEmployee(const char pathData[], const char pathTemp[])
{
	FILE* file;
	FILE* temp;
	bool findCheck = false;

	errno_t fileCode = fopen_s(&file, pathData, "rb");
	errno_t tempCode = fopen_s(&temp, pathTemp, "wb");

	if (fileCode == 0 && tempCode == 0)
	{
		char name[SIZE_STR];
		char lastName[SIZE_STR];

		cout << "First name: ";
		cin >> name;
		cout << "Last name: ";
		cin >> lastName;

		Employee point;
		while (!feof(file))
		{
			if (fread(&point, sizeof(Employee), 1, file))
			{
				Employee pointTemp = point;
				if (strcmp(name, pointTemp.name) == 0 && strcmp(lastName, pointTemp.lastName) == 0)
				{
					findCheck = true;
				}
				else
				{
					fwrite(&point, sizeof(Employee), 1, temp);
				}
			}
		}
		fclose(file);
		fclose(temp);
		if (findCheck)
		{
			int userCh = 0;
			bool confCheck = false;
			while (!confCheck)
			{
				cout << "\n\tDo you want to delete employee: " << name << " "<< lastName << "?";
				cout << "\n[1] - Yes" << "\n[2] - No";
				cout << "\nChoose option: ";
				cin >> userCh;
				cout << endl;
				if (userCh == 1)
				{
					cout << "\nDeleting..." << endl;
					confCheck = true;
				}
				else
				{
					cout << "This option does not exist." << endl;
				}

			}
			fileCode = fopen_s(&file, pathData, "wb");
			tempCode = fopen_s(&temp, pathTemp, "rb");

			if (fileCode == 0 && tempCode == 0)
			{
				Employee point;
				while (!feof(temp))
				{
					if (fread(&point, sizeof(Employee), 1, temp))
					{
						fwrite(&point, sizeof(Employee), 1, file);
					}
				}
				fclose(file);
				fclose(temp);
				cout << "The employee has been deleted." << endl;
			}
		}
		else
		{
			cout << "Employee not found.";
		}
	}
	else
	{
		cout << "Error. Couldn't open the file." << endl;
	}
}

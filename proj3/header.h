#pragma once

const int SIZE_PHONE = 10;
const int SIZE_STR = 100;
const char pathData[] = "Data.txt";
const char pathTemp[] = "Temp.txt";

struct Employee
{
	char name[SIZE_STR];
	char lastName[SIZE_STR];
	char phoneNum[SIZE_PHONE];
	double salary;
};

enum actionsCodeMain
{
	codeAddEmployee = 1, codeDelEmployee, codePrintAll, codePrintSingular, codeSearchBySalary, codeExit
};

void addEmployee(const char pathData[]);
void delEmployee(const char pathData[], const char pathTemp[]);

void printAllEmployee(const char pathData[]);

void printStruct(Employee point);
void printMenu();

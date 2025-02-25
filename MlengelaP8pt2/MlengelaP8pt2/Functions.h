/*************************************************************************************
* Program: Research Web Data. 
* Programmer: Daudi Mlengela(dmlengela@cnm.edu)
* Date 8 December 2021. 
* Purpose: Web Research and Reading and Writing Data files. 
**************************************************************************************/

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
 
using namespace std;

void WriteHeader();
bool getRowsAndColumns(const string& fileName, int* rowsPtr, int* columnsPtr, string& errMsg);
void getValues(const string& line, string* theValues);
string addCommas(int64_t value);

#endif // !_FUNCTIONS_H


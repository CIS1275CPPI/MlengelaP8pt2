/*************************************************************************************
* Program: Research Web Data.
* Programmer: Daudi Mlengela(dmlengela@cnm.edu)
* Date 8 December 2021.
* Purpose: Web Research and Reading and Writing Data files.
**************************************************************************************/
#include "Functions.h"
using namespace std;

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

void WriteHeader()

{
    cout << "This is the project that will read date on Bitcoin from 2014 to 2021. It will read the number "
        << "\n of rows and columns in a csv.file to dynamically locate 'maximum loss', 'maximumu gain'"
        << "\n and 'maximum volume' in the data occured on. In this project, the date,"
        << "\n and the amount in $ determine the 'maxLoss', 'maxGain', and 'MaxVolume' "
        << "\n of the bitcoin sold except for the maxVolume which is"
        << "\n in high and low number in this csv.file. \n";

}
void Goodbye()
{
    cout << "\n\n Goodbye. I hope you enjoy the statistics of selling of bitcom! " << endl << endl;
}
/*********************************************************************************************
* Get the Rows and Columns
**********************************************************************************************/

bool getRowsAndColumns(const string & fileName, int* rowsPtr, int* columnsPtr, string & errMsg)
{
    *rowsPtr = *columnsPtr = 0;

    ifstream in(fileName);

    if (!in)
    {
        errMsg = "Could not open file: [" + fileName + "]";
        return(false);
    }

    string line;

    while (getline(in, line))
    {
        if (*columnsPtr == 0)
        {
            int nCommas = 0;

            for (char c : line)
                if (c == ',')
                    nCommas++;

            *columnsPtr = nCommas + 1;
        }

        ++(*rowsPtr);
    }

    return(true);
}

/********************************************************************************************
* getValues
*********************************************************************************************/

void getValues(const string& line, string* theValues)
{
    string current;

    for (size_t i = 0, j = 0; i < line.size(); i++)
    {
        if (line[i] != ',')
        {
            current += line[i];

            if (i + 1 == line.size() || line[i + 1] == ',')
            {
                theValues[j++] = current;
                current = "";
            }
        }
    }
}

/************************************************************************************
* addCommas
*************************************************************************************/


string addCommas(int64_t value)
{
    ostringstream out;

    out << value;

    string s = out.str();
    string result;

    for (int i = s.size() - 1, j = 1; i >= 0; i--, j++)
    {
        result = s[i] + result;

        if (j % 3 == 0 && i > 0)
            result = "," + result;
    }

    return(result);
}







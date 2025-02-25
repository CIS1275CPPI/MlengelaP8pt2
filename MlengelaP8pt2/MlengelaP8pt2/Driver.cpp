/*************************************************************************************
* Program: Research Web Data.
* Programmer: Daudi Mlengela(dmlengela@cnm.edu)
* Date 8 December 2021.
* Purpose: Web Research and Reading and Writing Data files.
**************************************************************************************/

#include "Functions.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std; 

    int main()
    {
        /**********************************************************************************
         * For the purpose of this project, the following is the source of the data file 
         * (btc-usd.csv) used in this program:
         * https://finance.yahoo.com/quote/BTC-USD/history?period1=1410825600&period2=1637539200&interval=1d&filter=history&frequency=1d&includeAdjustedClose=true
        ***************************************************************************************************/

         static const string FILE_NAME = "BTC-USD.csv";

        /*************************************************************************
        * Determine the number of rows and columns in our csv file, we'll
        * use this information to dynamically allocate our: 'date', 'open'
        * and 'volume' arrays as well as our 'values' array for each row
        ****************************************************************************/
        
        int rows = 0;
        int columns = 0;

        string errMsg;

        if (!getRowsAndColumns(FILE_NAME, &rows, &columns, errMsg))
        {
            cout << errMsg << "\n";
            return(1);
        }

        /********************************************************************************
        * The number of rows includes the first line which
        * contains the column names
        *********************************************************************************/

        int nLines = (rows - 1);

        if (nLines < 2)
        {
            cout << "No data found in input file: " << FILE_NAME << "\n";
            return(1);
        }

        /************************************************************************
        * Allocate space for our arrays
        ************************************************************************/

        string* date = new string[nLines];
        double* open = new double[nLines];
        int64_t* volume = new int64_t[nLines];

        for (int i = 0; i < nLines; i++)
        {
            open[i] = 0.0;
            volume[i] = 0;
        }

        ifstream in(FILE_NAME);

        if (!in)
        {
            cout << "Could not open file: " << FILE_NAME << "\n";
            return(1);
        }

        string line;

        int i = 0;

        while (getline(in, line))
        {
            /*****************************************************************
            * Skip the first line, it has only column names - no data
            ******************************************************************/
            
            if (i > 0)
            {
                string* values = new string[columns];

                getValues(line, values);

                date[i - 1] = values[0];

                /**************************************************************************
                * Only convert our input to numbers if the input
                * is not "null" (which occurs in some of the rows of
                * our input file)
                ***************************************************************************/

                if (values[1] != "null")
                {
                    open[i - 1] = atof(values[1].c_str());
                    volume[i - 1] = stoull(values[6]);
                }

                delete[] values;
            }

            i++;
        }

        /************************************************************************************
        * Change 'false' to 'true' below to dump the contents of our arrays
        *************************************************************************************/

        bool showDebugOutput = false;

        if (showDebugOutput)
        {
            for (int i = 0; i < nLines; i++)
                cout << date[i] << "|" << open[i] << "|" << volume[i] << "\n";

            cout << "\n";
        }

        /*************************************************************************************
        * Find the day that had the highest volume, also find the day of
        * the largest gain and the day of the largest loss
        **************************************************************************************/

        int64_t maxValue = 0;
        double maxLoss = 0.0;
        double maxGain = 0.0;

        string maxValueDate;
        string maxLossDate;
        string maxGainDate;

        for (int i = 0; i < nLines; i++)
        {
            if (volume[i] > maxValue)
            {
                maxValue = volume[i];
                maxValueDate = date[i];
            }

            if (i + 1 < nLines)
            {
                /*********************************************************************************
                * Rows that had "null" will have an opening price of zero, ignore those rows
                **********************************************************************************/

                if (open[i] == 0.0 || open[i + 1] == 0.0)
                    continue;

                double delta = abs(open[i + 1] - open[i]);

                if (open[i] < open[i + 1])
                {
                    if (delta > maxGain)
                    {
                        maxGain = delta;
                        maxGainDate = date[i];
                    }
                }
                else if (open[i] > open[i + 1])
                {
                    if (delta > maxLoss)
                    {
                        maxLoss = delta;
                        maxLossDate = date[i];
                    }
                }
            }
        }

        cout << "Max volume: " << addCommas(maxValue) << " occurred on: " << maxValueDate << "\n";

        cout << fixed << setprecision(2);

        cout << "Max gain  : $" << maxGain << " occurred on: " << maxGainDate << "\n";
        cout << "Max loss  : $" << maxLoss << " occurred on: " << maxLossDate << "\n";

        delete[] date;
        delete[] open;
        delete[] volume;

        return(0);
    }

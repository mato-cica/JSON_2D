#include "Write_JSON.h"
#include <iostream>
#include <map>
using namespace std;

Write_JSON::Write_JSON()
{
    //constructor
}

//Writes an 2D array from ordered associative map 'm_mapAllRows' to screen. Integer 'Number_Of_Columns'
//helps to distinct rows.
void Write_JSON::array_from_JSON_string(const map<int, int> &mapAllRows, const int &Number_Of_Columns)
{
    cout << " ***************** " << '\n';
    cout << " It represents a 2D array of integer as follows: " << '\n';
    cout << " " << '\n';

    int nColumnCounter {1};             //Count columns to distinct rows
    map<int, int>::const_iterator it;   //Iterate
    it = mapAllRows.begin();            //thorough mapAllRows
    while (it != mapAllRows.end())      //until the end of ordered associative map
    {
        if (nColumnCounter % Number_Of_Columns == 0)  //When nColumnCounter = NoOFColumns x n
        {
            cout << " " << it->second << endl;        //write array member and go to new row (endl)
            ++it;                                     //go further
            ++nColumnCounter;                         //increment counter
        }
        else                                  //still in actuall row
        {
            cout << " " << it->second;        //write array member
            ++it;                             //and go further
            ++nColumnCounter;                 //increment counter
        }
    }
}

//Writes arranged 2D array from 'm-mapArranged2Darray' to screen. Integer 'Number_Of_Columns'
//helps to distinct rows.
void Write_JSON::arranged_array_from_JSON_string(const map<int, int> &mapArranged2Darray, const int &Number_Of_Columns)
{
    cout << " ***************** " << '\n';
    cout << " After required actions your 2D array of integer looks as follows: " << endl;
    cout << " " << '\n';

    int nColumnCounter {1};
    map<int, int>::const_iterator it;
    it = mapArranged2Darray.begin();
    while (it != mapArranged2Darray.end())
    {
        if (nColumnCounter % Number_Of_Columns == 0)
        {
            cout << " " << it->second << endl;
            ++it;
            ++nColumnCounter;
        }
        else
        {
            cout << " " << it->second;
            ++it;
            ++nColumnCounter;
        }
    }
}

//Writes coordinates of array member whose values are 9 from unordered map 'm_map9coordinates' to the screen.
//Integer 'Number_Of_Columns' just limits number of coordinates in one row to No of columns. This function
//make and write sum of 'nine coordinates' too. It's not a good programmers manner but I did like that
//because of performance benefit (speed).
void Write_JSON::write_coordinates_of_9(const multimap<int, int> &map9coordinates, const int &Number_Of_Columns)
{
    cout << " ***************** " << '\n';
    cout << '\n';
    cout << " The coordinates of nines are: " << endl;

    int nColumnCounter {1}, nSumOf9coordinates {0};
    multimap<int, int>::const_iterator it;
    it = map9coordinates.begin();
    while (it != map9coordinates.end())
    {
        if (nColumnCounter % Number_Of_Columns == 0)
        {
            cout << " (" << it->first << "," << it->second << ")" << endl;
            nSumOf9coordinates += (it->first + it->second);
            ++it;
            ++nColumnCounter;
        }
        else
        {
            cout << " (" << it->first << "," << it->second << ")";
            nSumOf9coordinates += (it->first + it->second);
            ++it;
            ++nColumnCounter;
        }
    }
    cout << " " << '\n';
    cout << " So, the total of all nine coordinates is: " << nSumOf9coordinates << endl;
    cout << " ***************** " << '\n';
}

//This function should write sum of '9 coordinates' but I've changed my mind. That task did a previous one.
void Write_JSON::write_sum_of_coordinates()
{
    cout << endl << " That's it!" << endl;
    cout << " ***************** " << '\n';
}

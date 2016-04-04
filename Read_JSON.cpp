#include "Read_JSON.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()
using namespace std;

//Constructor with a task in it. The task is reading file from disc and storing it in
//member variable 'm_str_JSON_2D'
Read_JSON::Read_JSON()
: m_str_JSON_2D {""}
{
    cout << "********** JSON_2D Version 1.1.0 ************" << endl << "Enter the path to the JSON file relative to folder which this program is in." << endl << "If the JSON file is in the same folder as program just enter the name of the" << endl << "file (JSON_2D.txt or some other)" << endl;
    string JSON_file;    //Prepare variable for user input
    cin >> JSON_file;    //User input to variable

    ifstream inf(JSON_file);    //Prepare buffer for reading file from disc
    if (!inf)                   //If buffer can not open the file
    {
        cerr << "JSON txt file could not be opened for reading!" << endl;
        exit(1);
    }
    while (inf)                  //If everything's OK
    {
        inf >> m_str_JSON_2D;    //file from buffer to clas member variable
    }//ctor
}

//Write JSON string to screen
void Read_JSON::write_JSON_string()
{
    cout << " ***************** " << '\n';
    cout << " Your JSON string is as follows: " << '\n';
    cout << " " << '\n';

    string::const_iterator it;          //Iterate
    it = m_str_JSON_2D.begin();         //from begin
    while (it != m_str_JSON_2D.end())   //to the end of JSON string
    {
        if (*it == '}')                 //If the character is '}'
        {
            cout << *it << endl;        //write it and go to new line
            ++it;                       //go further
        }
        else                            //when char is not '}'
        {
            cout << *it;                //just write it
            ++it;                       //and go further
        }
    }
}

//Getter reference
string &Read_JSON::get_str_JSON_2D() {return m_str_JSON_2D;}

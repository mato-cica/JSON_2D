#include "Read_JSON.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // for exit()

using namespace std;
//string Read_JSON::m_str_JSON_2D {""};
Read_JSON::Read_JSON()
: m_str_JSON_2D {""}
{
    cout << "Enter the path to the JSON file relative to folder which this program is in." << endl << "If the JSON file is in the same folder as program just enter the name of the" << endl << "file (JSON_2D.txt)" << endl;
    string JSON_file;
    cin >> JSON_file;
    //ifstream inf("JSON_2D.txt");
    ifstream inf(JSON_file);
    if (!inf)
    {
        cerr << "JSON_2D.txt could not be opened for reading!" << endl;
        exit(1);
    }
    while (inf)
    {
        inf >> m_str_JSON_2D;
    }//ctor
}
void Read_JSON::write_JSON_string()
{
    cout << " ***************** " << '\n';
    cout << " Your JSON string is as follows: " << '\n';
    cout << " " << '\n';
    string::const_iterator it;
    it = m_str_JSON_2D.begin();
    while (it != m_str_JSON_2D.end())
    {
        if (*it == '}')
        {
            cout << *it << endl;
            ++it;
        }
        else
        {
            cout << *it;
            ++it;
        }
    }
}
string Read_JSON::getJSON_string() {return m_str_JSON_2D;}

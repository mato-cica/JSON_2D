#include "Parse_JSON.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

// ***** inline function converts any type to string type ( in this case char to string ) **********
template <typename T>
inline std::string ToString(T tX)
{
    std::ostringstream oStream;
    oStream << tX;
    return oStream.str();
}
// ***** converts string type to any type and gives bool 1 if success ( in this case string to integer ) *****
template <typename T>
inline bool FromString(const std::string& sString, T &tX)
{
    std::istringstream iStream(sString);
    return (iStream >> tX) ? true : false;
}

Parse_JSON::Parse_JSON()
{
    //constructor
}

//We need 1st row to make arrangement key. So, we will parse JSON string for 1st row of 2D array. This
//function will make an ordered associative map 'm_map_1st_row'. The key of map will be members of 1st row
//and value will be columns of 1st row. Map is ordered upon keys.
map<int, int> &Parse_JSON::take_1st_row(const string &str_JSON_2D)
{
    // Number of quotation marks. It's important whether it's even or odd to distinct column and array member.
    int nQuotation {0};
    // Number of opened and closed parenthesis. Important to distinct row and column.
    int nClosed {0}, nOpened {0};
    // Values for array member and array column will be stored in 'm_map_1st_row' (associative map)
    int nArrayColumn {0}, nArrayMember {0};

    string::const_iterator it;
    it = str_JSON_2D.begin();          // Iterate through JSON array
    while (nClosed == 0)               // Until first closed parenthesis (it's first row of 2d array)
    {
        if (nOpened < 2)               //When it's less then 2 opened parenthesis
        {
            if (*it == '{')            //If char is opened parenthesis
                {
                  nOpened++;           //Just count parenthesis.
                  it++;                //and go further
                }

            else                       //If char is not opened parenthesis
                it++;                  //just go further
        }
        else                           //After 2 opened parenthesis there are 1st row members
        {
            if ((*it == ',') | (*it == ':'))     //If ',' or ':'
                it++;                            //just go further
            else
            {
                if (*it == '}')        //If closed parenthesis
                    nClosed++;         //count it (don't go further, it's end of 1st row)
                else
                    if (*it == '"')          //If quotation
                       {
                        nQuotation++;        //count it
                        it++;                //and go further
                       }
                    else                         //If not '{','}',',',':','"' it must be a number
                    {
                     if ((nQuotation % 2)>0)                   //If No of quotation marks is odd
                     {
                        string sIt(ToString(*it));             //convert char to string
                        if (FromString(sIt, nArrayColumn));    //then string to integer because it's column
                            it++;                              //and go further (we need array member too)
                     }
                     else    //If No of quotation marks is even
                     {
                        string sIt(ToString(*it));            //convert char to string
                        if (FromString(sIt, nArrayMember))    //then string to integer because it's array member
                            m_map_1st_row.insert(make_pair(nArrayMember, nArrayColumn));  //store pair in map
                        it++;                                                             //and go further
                     }
                    }
            }
        }
    }
    return m_map_1st_row;    //We don't need this reference. Just because of clearness.
}

//This function makes ordered associative map 'm_mapArrangement_Key'. The key column of map is made
//from value column of 'm_map_1st_row' which is ordered upon array members. Value column is position
//of column in ordered associative map 'm_map_1st_row'. So, we will get associative ordered
//map 'm_mapArrangement_Key' whose key column will represent column number which will be changed
//with column number in value column in the arranged 2D row (key out value in at arranged 2D array).
//This is the most important thing in whole program.
map<int, int> &Parse_JSON::make_arrangement_key()
{
    int nI {1};                           //Position in the 'm_map_1st_row'
    map<int, int>::const_iterator it;
    it = m_map_1st_row.begin();           //Iterator at begin
    while (it != m_map_1st_row.end())     //Iterate to the end of map
    {
        m_mapArrangement_Key.insert(make_pair(it->second, nI));  //Key Out Value In
        ++nI;
        ++it;
    }
    return m_mapArrangement_Key;     //We don't need that. Just because of clearness.
}

//Number of rows in ordered associative map 'm_mapArrangement_Key' is the number of columns in the
//arranged 2D array
void Parse_JSON::set_Number_Of_Columns()
{
    m_Number_Of_Columns = m_mapArrangement_Key.size();
}

//Parsing the whole array. But, we have arrangement key, so we'll make arranged array at the same time.
//We will make map of number 9 coordinates too. It is not a good programmers manner but it is performance
//benefit (speed). This function will make two ordered associative map: 'm_mapAllRows' and
//'m_mapArranged2Darray', for 2D array and arranged 2D array respectively, and one unordered associative
//map (multimap) 'm_map9coordinates' with coordinates of member whose value is 9.
map<int, int> &Parse_JSON::take_all_rows(const string &str_JSON_2D)
{
    //Number of quotation marks. It's important whether it's even or odd to distinct column and array member.
    int nQuotation {0};
    //Number of opened and closed parenthesis. Important to distinct row and column.
    int nClosed {0}, nOpened {0};
    //Coordintes of row and column and array member of 2D array of integer
    int nRow_2D {0}, nColumn_2D {0}, nArrayMember {0};
    //Coordinates of row and column of array member whose value is 9
    int nRowOf9 {0}, nColumnOf9 {0};

    string::const_iterator it;              //Iterator
    it = str_JSON_2D.begin();               //will iterate from begin
    while (it != str_JSON_2D.end())         //to the end of JSON string
    {
        if ((*it == ':') | (*it == ','))    //If ',' or ':'
            ++it;                           //just go further
        else
        {
            if (*it == '{')                 //if '{'
            {
                ++nOpened;                  //increment nOpened (No of opened parenthesis)
                ++it;                       //and go further
            }
            else
            {
                if (*it == '}')             //if '{'
                {
                    ++nClosed;              //increment nClosed (No of closed parenthesis)
                    ++it;                   //and go further
                }
                else
                {
                    if (*it == '"')         //if '"'
                    {
                        ++nQuotation;       //increment  No of quotation marks
                        ++it;               //and go further
                    }
                    else                    // if it is not {},:" then it is a number
                    {
                        if (nOpened == nClosed +1)        //then it is Row coordinate
                        {
                            string sIt(ToString(*it));    //Function makes chr *it to string sIt
                            if (FromString(sIt, nRow_2D)) //Function makes string sIt to integer nRow_2D
                            {
                                nRow_2D *= 10;            //Row coordinate *10 to get 2 digits number
                                ++it;                     //Go further. We need Column coordinate too
                            }
                            else        //If function 'FromString' fails (hope it will never)
                            {
                                cout << "Conversion string to integer was not succesful!" << endl;
                            }
                        }
                        else            //if nOpened == nClosed + 2 then it's Column coordinate or array member
                            {
                                if (nQuotation % 2 > 0)    //if No of quotation is odd it's a Column coordinate
                                {
                                    string sIt(ToString(*it));       //Function makes chr *it to string sIt
                                    if (FromString(sIt, nColumn_2D)) //makes string sIt to integer nColumn_2D
                                    {
                                        nRow_2D += nColumn_2D;       //Row + Column = 2 digits coordinate
                                        ++it;                        //Go further (we have coordinate of row and
                                    }                                //column as a 2 digit integer)
                                    else
                                    {                                //If 'FromString' fails (hope never)
                                        cout << "Conversion string to integer was not succesful!" << endl;
                                    }
                                }
                                else                       //when No of quotation is even it's an array member
                                {
                                    string sIt(ToString(*it));         //Function makes chr *it to string sIt
                                    if (FromString(sIt, nArrayMember)) //string sIt to integer nArrayMember
                                    {
                                        //pair (coordinate, array member) in the ordered associative map
                                        m_mapAllRows.insert(make_pair(nRow_2D, nArrayMember));
                                        //Prepare a variable for coordinate of arranged 2D array
                                        int nArrangedCoordinate;
                                        //Making Arranged map using Arrangement Key
                                        nArrangedCoordinate = nRow_2D - (nRow_2D % 10) + m_mapArrangement_Key[nColumn_2D];
                                        //Pair (ArrangedCoordinate, ArrayMember) to the ordered associative map
                                        m_mapArranged2Darray.insert(make_pair(nArrangedCoordinate, nArrayMember));
                                        //Take coordinates of members whose value is 9
                                        if ( nArrangedCoordinate > 20)      //we don't need first row
                                        {
                                            if ( nArrayMember == 9 )        //If member value is 9
                                            {
                                                //make 1-digit row coordinte
                                                nRowOf9 = (nArrangedCoordinate - nArrangedCoordinate % 10)/10;
                                                //make 1-digit column coordinte
                                                nColumnOf9 = nArrangedCoordinate % 10;
                                                //Pair of 1-digit coordinate (row, column) to the unordered associative map
                                                m_map9coordinates.insert(make_pair(nRowOf9, nColumnOf9));
                                            }
                                        }
                                        nRow_2D -= nColumn_2D;             //let it row be x0 (10, 20, 30...)
                                        ++it;                              //go further
                                    }
                                    else
                                    {              //If 'FromString' fails (hope it'll never)
                                        cout << "Conversion string to integer was not succesful!" << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    return m_mapAllRows; //We don't need this reference. Just because of clearness.
}

map<int, int> &Parse_JSON::get_mapAllRows() { return m_mapAllRows; }
map<int, int> &Parse_JSON::get_mapArranged2Darray() { return m_mapArranged2Darray; }
map<int, int> &Parse_JSON::get_map_1st_row() { return m_map_1st_row; }
map<int, int> &Parse_JSON::get_mapArrangement_Key() { return m_mapArrangement_Key; }
multimap<int, int> &Parse_JSON::get_map9coordinates() { return m_map9coordinates; }
int &Parse_JSON::get_Number_Of_Columns() { return m_Number_Of_Columns; }

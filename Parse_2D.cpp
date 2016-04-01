#include "Parse_2D.h"
#include <iostream>
#include <sstream>
#include "Parse_2D.h"
#include <string>
#include <map>
#include <iostream>


using namespace std;
template <typename T>
inline std::string ToString(T tX)
{
    std::ostringstream oStream;
    oStream << tX;
    return oStream.str();
}
template <typename T>
inline bool FromString(const std::string& sString, T &tX)
{
    std::istringstream iStream(sString);
    return (iStream >> tX) ? true : false;
}
Parse_2D::Parse_2D()
{
    //ctor
}
void Parse_2D::take_1st_row(string m_str_JSON_2D)
{
    int nQuotation {0}, nClosed {0}, nOpened {0}, nArrayColumn {0}, nArrayMember {0};
    string::const_iterator it;
    it = m_str_JSON_2D.begin();
    while (nClosed == 0)
    {
        if (nOpened < 2)
        {
            if (*it == '{')
                {
                  nOpened++;
                  it++;
                }

            else
                it++;
        }
        else
        {
            if ((*it == ',') | (*it == ':'))
                it++;
            else
            {
                if (*it == '}')
                    nClosed++;
                else
                    if (*it == '"')
                       {
                        nQuotation++;
                        it++;
                       }
                    else
                    {
                     if ((nQuotation % 2)>0)
                     {
                        string sIt(ToString(*it));
                        if (FromString(sIt, nArrayColumn));
                            it++;//nArrayColumn = *it;

                     }
                     else
                     {
                        string sIt(ToString(*it));
                        if (FromString(sIt, nArrayMember))
                            m_mapArrangement.insert(make_pair(nArrayMember, nArrayColumn));
                         it++;
                         //m_mapArrangement.insert(make_pair(nArraymember, );
                     }
                    }
            }
        }
    }
}

void Parse_2D::make_key()
{
    int nI {1};
    map<int, int>::const_iterator it;
    it = m_mapArrangement.begin();
    while (it != m_mapArrangement.end())
    {
        m_mapArrangement_Key.insert(make_pair(it->second, nI));//KeyOut ValueIn
        ++nI;
        ++it;
    }
    m_Number_Of_Columns = nI - 1;
}
void Parse_2D::take_all_rows(string m_str_JSON_2D)
{
    int nQuotation {0}, nClosed {0}, nOpened {0}, nRow_2D {0}, nColumn_2D {0}, nArrayMember {0}, nRowOf9 {0}, nColumnOf9 {0};
    string::const_iterator it;
    it = m_str_JSON_2D.begin();
    while (it != m_str_JSON_2D.end())
    {
        if ((*it == ':') | (*it == ',')) //If , or : just go further
            ++it;
        else
        {
            if (*it == '{') //if { increment nOpened Number of opened parenthesis
            {
                ++nOpened;
                ++it;
            }
            else
            {
                if (*it == '}') //if { increment nClosed Number of closed parenthesis
                {
                    ++nClosed;
                    ++it;
                }
                else
                {
                    if (*it == '"') //if " increment  Number of quotation marks
                    {
                        ++nQuotation;
                        ++it;
                    }
                    else // if it is not {},:" then it is a number
                    {
                        if (nOpened == nClosed +1) //then it is Row coordinate
                        {
                            string sIt(ToString(*it)); //Function makes chr *it to string sIt
                            if (FromString(sIt, nRow_2D)) //Function makes string sIt to integer nRow_2D
                            {
                                nRow_2D *= 10; //Row coordinate *10 to get 2 digits number
                                ++it;
                            }
                            else
                            {
                                cout << "Conversion string to integer was not succesful!" << endl;
                            }
                        }
                        else // if nOpened == nClosed + 2 then it is Column coordinate or array member
                            {
                                if (nQuotation % 2 > 0) //if No of quotation is odd it is a Column coordinate
                                {
                                    string sIt(ToString(*it)); //Function makes chr *it to string sIt
                                    if (FromString(sIt, nColumn_2D)) //makes string sIt to integer nColumn_2D
                                    {
                                        nRow_2D += nColumn_2D; //Row + Column = 2 digits coordinate
                                        ++it;
                                    }
                                    else
                                    {
                                        cout << "Conversion string to integer was not succesful!" << endl;
                                    }
                                }
                                else //when No of quotation is even it is an array member
                                {
                                    string sIt(ToString(*it)); //Function makes chr *it to string sIt
                                    if (FromString(sIt, nArrayMember)) //makes string sIt to integer nArrayMember
                                    {
                                        //pair (coordinate, array member) in the map
                                        m_mapAllRows.insert(make_pair(nRow_2D, nArrayMember));
                                        int nArrangedCoordinate;
                                        //Making Arranged map using Arrangement Key
                                        nArrangedCoordinate = nRow_2D - (nRow_2D % 10) + m_mapArrangement_Key[nColumn_2D];
                                        m_mapArranged2Darray.insert(make_pair(nArrangedCoordinate, nArrayMember));
                                        //Take coordinates of 9
                                        if ( nArrangedCoordinate > 20) //we don't need first row
                                        {
                                            if ( nArrayMember == 9 )
                                            {
                                                nRowOf9 = (nArrangedCoordinate - nArrangedCoordinate % 10)/10;
                                                nColumnOf9 = nArrangedCoordinate % 10;
                                                m_map9coordinates.insert(make_pair(nRowOf9, nColumnOf9));
                                            }
                                        }
                                        nRow_2D -= nColumn_2D; //let it be x0 + Column
                                        ++it;
                                    }
                                    else
                                    {
                                        cout << "Conversion string to integer was not succesful!" << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
}
map<int, int> Parse_2D::get_mapAllRows() { return m_mapAllRows; }
map<int, int> Parse_2D::get_mapArranged2Darray() { return m_mapArranged2Darray; }
multimap<int, int> Parse_2D::get_map9coordinates() { return m_map9coordinates; }
int Parse_2D::get_Number_Of_Columns() { return m_Number_Of_Columns; }
void Parse_2D::array_from_JSON_string()
{
    cout << " ***************** " << '\n';
    cout << " It represents a 2D array of integer as follows: " << '\n';
    cout << " " << '\n';
    int nColumnCounter {1};
    map<int, int>::const_iterator it;
    it = m_mapAllRows.begin();
    while (it != m_mapAllRows.end())
    {
        if (nColumnCounter % m_Number_Of_Columns == 0)
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
void Parse_2D::arranged_array_from_JSON_string()
{
    cout << " ***************** " << '\n';
    cout << " After required actions your 2D array of integer looks as follows: " << endl;
    cout << " " << '\n';
    int nColumnCounter {1};
    map<int, int>::const_iterator it;
    it = m_mapArranged2Darray.begin();
    while (it != m_mapArranged2Darray.end())
    {
        if (nColumnCounter % m_Number_Of_Columns == 0)
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
void Parse_2D::write_coordinates_of_9()
{
    cout << " ***************** " << '\n';
    cout << " The coordinates of nines are: " << endl;
    int nColumnCounter {1}, nSumOf9coordinates {0};
    multimap<int, int>::const_iterator it;
    it = m_map9coordinates.begin();
    while (it != m_map9coordinates.end())
    {
        if (nColumnCounter % m_Number_Of_Columns == 0)
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
}
void Parse_2D::write_sum_of_coordinates()
{
    cout << " ***************** " << '\n';
    cout << " That's it!" << '\n';
    cout << " ***************** " << '\n';
}

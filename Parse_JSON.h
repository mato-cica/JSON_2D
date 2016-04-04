#ifndef PARSE_JSON_H
#define PARSE_JSON_H
#include <string>
#include <map>
using namespace std;

class Parse_JSON
{
    public:
        Parse_JSON();
        map<int, int> &take_1st_row(const string &str_JSON_2D);
        map<int, int> &get_map_1st_row();
        map<int, int> &make_arrangement_key();
        map<int, int> &take_all_rows(const string &str_JSON_2D);
        map<int, int> &get_mapAllRows();
        map<int, int> &get_mapArranged2Darray();
        map<int, int> &get_mapArrangement_Key();
        multimap<int, int> &get_map9coordinates();
        void set_Number_Of_Columns();
        int &get_Number_Of_Columns();
    protected:
    private:
        map<int, int> m_map_1st_row;
        map<int, int> m_mapArrangement_Key;
        map<int, int> m_mapAllRows;
        map<int, int> m_mapArranged2Darray;
        multimap<int, int> m_map9coordinates;
        int m_Number_Of_Columns;
};

#endif // PARSE_JSON_H

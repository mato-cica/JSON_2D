#ifndef PARSE_2D_H
#define PARSE_2D_H
#include <string>
#include <map>
using namespace std;

class Parse_2D
{
    public:
        Parse_2D();
        void take_1st_row(string m_str_JSON_2D);
        void make_key();
        void take_all_rows(string m_str_JSON_2D);
        map<int, int> get_mapAllRows();
        map<int, int> get_mapArranged2Darray();
        multimap<int, int> get_map9coordinates();
        int get_Number_Of_Columns();
        void array_from_JSON_string();
        void arranged_array_from_JSON_string();
        void write_coordinates_of_9();
        void write_sum_of_coordinates();
        //string m_str_JSON_2D;
        //Make_Arrangement_Key Of_2D_array;
        //map<int, int> m_mapArrangement;
    protected:
    private:
        map<int, int> m_mapArrangement;
        map<int, int> m_mapArrangement_Key;
        map<int, int> m_mapAllRows;
        map<int, int> m_mapArranged2Darray;
        multimap<int, int> m_map9coordinates;
        int m_Number_Of_Columns;
};

#endif // PARSE_2D_H

#include <iostream>
#include "Read_JSON.h"
#include "Parse_JSON.h"
#include "Write_JSON.h"
using namespace std;

int main()
{
    char yn = 'y';
    while(yn == 'y')
    {
        Read_JSON from_file;
        from_file.write_JSON_string();
        Parse_JSON parse_JSON;
        parse_JSON.take_1st_row(from_file.get_str_JSON_2D());
        parse_JSON.make_arrangement_key();
        parse_JSON.set_Number_Of_Columns();
        parse_JSON.take_all_rows(from_file.get_str_JSON_2D());
        Write_JSON write_2D;
        write_2D.array_from_JSON_string(parse_JSON.get_mapAllRows(), parse_JSON.get_Number_Of_Columns());
        write_2D.arranged_array_from_JSON_string(parse_JSON.get_mapArranged2Darray(), parse_JSON.get_Number_Of_Columns());
        write_2D.write_coordinates_of_9(parse_JSON.get_map9coordinates(), parse_JSON.get_Number_Of_Columns());
        write_2D.write_sum_of_coordinates();
        cout << " Any key besides 'y' for exit..." << endl;
        cin >> yn;
    }

    return 0;
}

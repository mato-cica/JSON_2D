#include <iostream>
#include "Read_JSON.h"
#include "Parse_2D.h"
#include "Write_JSON.h"
#include <map>
using namespace std;

int main()
{
    char yn = 'y';
    while(yn == 'y')
    {
        Read_JSON from_file;
        from_file.write_JSON_string();
        Parse_2D First_Row;
        First_Row.take_1st_row(from_file.getJSON_string());
        First_Row.make_key();
        First_Row.take_all_rows(from_file.getJSON_string());
        First_Row.array_from_JSON_string();
        First_Row.arranged_array_from_JSON_string();
        First_Row.write_coordinates_of_9();
        First_Row.write_sum_of_coordinates();
        cout << "Any key beside 'y' for exit..." << endl;
        cin >> yn;
    }

    return 0;
}

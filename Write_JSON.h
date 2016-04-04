#ifndef WRITE_JSON_H
#define WRITE_JSON_H
#include <map>
using namespace std;

class Write_JSON
{
    public:
        Write_JSON(); //Write_2D
        void array_from_JSON_string(const map<int, int> &mapAllRows, const int &Number_Of_Columns);
        void arranged_array_from_JSON_string(const map<int, int> &mapArranged2Darray, const int &Number_Of_Columns);
        void write_coordinates_of_9(const multimap<int, int> &map9coordinates, const int &Number_Of_Columns);
        void write_sum_of_coordinates();
    protected:
    private:

};

#endif // WRITE_JSON_H

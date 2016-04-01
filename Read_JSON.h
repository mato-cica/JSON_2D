#ifndef READ_JSON_H
#define READ_JSON_H
#include <string>
using namespace std;

class Read_JSON
{
    public:
        Read_JSON();
        void write_JSON_string();
        string getJSON_string();
        //string m_str_JSON_2D;
    protected:
    private:
        string m_str_JSON_2D;
        //string m_JSON_file;

};

#endif // READ_JSON_H

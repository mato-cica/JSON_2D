#ifndef READ_JSON_H
#define READ_JSON_H
#include <string>
using namespace std;

class Read_JSON
{
    public:
        Read_JSON();
        void write_JSON_string();
        string &get_str_JSON_2D();
    protected:
    private:
        string m_str_JSON_2D;
};

#endif // READ_JSON_H

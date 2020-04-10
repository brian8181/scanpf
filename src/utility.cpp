#include <string>

using namespace std;

void replace_all(string& s, const string& sub_str, const string& replace_str)
{
    size_t pos = 0;
    size_t len = s.length();
   
    pos = s.find(sub_str, pos);
    while(pos < len)
    {
        s.replace(pos, sub_str.length(), replace_str);
        pos += replace_str.length();
        pos = s.find(sub_str, pos);
    }
}
#include <string>
#include <map>

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


struct token
{
    string value;
    size_t start;
    size_t end;
    token(const string& val, size_t start_pos, size_t end_pos)
        : value(val), start(start_pos), end(end_pos) {}
};

map<string, token> prec =
{
    {"+", token("+", 0, 2)},
    {"-", token("-", 3, 7)},
    {"*", token("*", 8, 13)},
    {"/", token("/", 14, 20)}
};

void shunting(const string& in)
{
    // Tokenize the input string
    vector<token> tokens;
    size_t pos = 0;s
    while(pos < in.length())
    {
        // Skip whitespace
        if(isspace(in[pos]))
        {
            pos++;
            continue;
        }

        // Check for operators
        for(const auto& p : prec)
        {
            const string& op = p.first;
            if(in.substr(pos, op.length()) == op)
            {
                tokens.emplace_back(op, pos, pos + op.length());
                pos += op.length();
                break;
            }
        }
    }

    // Print the tokens
    for(const auto& t : tokens)
    {
        cout << "Token: " << t.value << ", Start: " << t.start << ", End: " << t.end << endl;
    }
}
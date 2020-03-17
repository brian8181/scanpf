#include <iostream>
#include <string>
#include <regex>
#include <map>

using namespace std;

void replace_all(string& s, const string& sub_str, const string& replace_str);

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return 0;

    string pattern_str(argv[1]);
    string input_str(argv[2]);

    const string FMT_FG_GREEN  = "\e[32m";
    const string FMT_UNDERLINE = "\e[4m";
    const string FMT_BOLD      = "\e[1m";
    const string FMT_RESET     = "\e[0m";

     cout << "\n" << FMT_BOLD << "create_map" << FMT_RESET << " " 
          << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " " 
          << FMT_UNDERLINE << "INPUT"   << FMT_RESET << "\n\n";

    // regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
    // ~!@#$%^&*()_+`-=[]\{}|;':",./<>?"
    // ~!@#\\$%\\^&\\*\\(\\)_\\+`-=\\[\\]\\\\\{\\}\\|;':"\\,\\./<>\\?" ESCAPED

    // character sets allowed pattern for tag names
    const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";
    const string DELIMITING_CHARS = R"([A-z0-9 \^\$\.\*\+\:\'\[\]\{\}\|;,@#_-])";

    // create regx from pattern
    replace_all(pattern_str, ".", "\\.");
    const regex TAG_EXP(TAG_MATCH_EXP_STR);
    const string REPLACE_EXP_STR 
        = "^" + regex_replace(pattern_str, TAG_EXP, "(" + DELIMITING_CHARS + "*)" ) + "$";
    const regex REPLACE_EXP (REPLACE_EXP_STR);
    
    // create smatch
    smatch sm;    
    regex_match (input_str, sm, REPLACE_EXP);
    
    // iterate through tag matches and create map
    int idx = 1;
    auto begin = sregex_iterator(pattern_str.begin(), pattern_str.end(), TAG_EXP);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
        map<string,string> tag_map;
        tag_map.insert(make_pair(match.str(1), sm.str(idx)));
      
        cout << FMT_BOLD + FMT_FG_GREEN << match.str(1) << FMT_RESET << " = " 
                  << tag_map[match.str(1)] << endl;
        ++idx;
    }
    
    cout << "\n";
}

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

/*
USAGE:
./create_map "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main Street-Brown Sugar.mp3"
./create_map "<test>" "ABCDEFGHIJKLMPNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_-*^|:[]{}'"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>" "A B.C:D_E-F@G%H=J^K"

./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>" "A B.C:D_E-F@G%H=J^K\\!L"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>" "A B.C:D_E-F@G%H=J^K\\!L+M"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>" "A B.C:D_E-F@G%H=J^K\\!L+M=N"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>\\\\<s>" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R\\S"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>\\\\<s>~<t>\\:<u>;<v>" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R\\S~T:U;V"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>\\\\<s>~<t>\\:<u>;<v>\\\"<w>" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R\\S~T:U;V\"W"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>\\\\<s>~<t>\\:<u>;<v>\\\"<w>\\\'<x>" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R\\S~T:U;V\"W\\'X"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>\\\\<s>~<t>\\:<u>;<v>\\\"<w>\\\'<x>\\,<y>" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R\\S~T:U;V\"W\\'X,Y"
./create_map "<a> <b>.<c>:<d>_<e>-<f>@<g>%<h>=<j>\\^<k>\\\!<l>\\+<m>\\=<n>\\(<o>\\)\\[<p>\\]\\{<q>\\}\\|<r>\\\\<s>~<t>\\:<u>;<v>\\\"<w>\\\'<x>\\,<y>\\?Z" "A B.C:D_E-F@G%H=J^K\\!L+M=N(O)[P]{Q}|R\\S~T:U;V\"W\\'X,Y?Z"

# holding on chars [<>`!]

./create_map '<a>\\!<b>' 'A\!B'
./create_map "<a>\\^<j>" "A^J"

ISSUES:
./create_map "<a> <b>.<c>:<d>_<e>-<f>*<g>" "A B.C:D_E-F*G"
./create_map "<first> <last>:<phone> <sex>" "Alfred E. Numan:555-555-9696 M" "Sex : <sex>    Name :<last>, <first>    Phone : <phone>"

./create_map "<a>*<b>" "A*B"
./create_map "<a>+<b>" "A+B"
./create_map "<a>^<j>" "A^J"




*/
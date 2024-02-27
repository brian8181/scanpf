#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <fstream>
#include <getopt.h>
#include "bash_color.h"
#include "scanpf.hpp"

using namespace std;


// file special chars =  / \ " ' * ; - ? [ ] ( ) ~ ! $ { } < > # @ & |
// regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
// character sets allowed pattern for tag names
//const string MATCH_EXP_OPTIONAL = R"(\[?([A-z]+[A-z0-9]*)\]?)";
const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";                    // conservative match
//const string TAG_MATCH_EXP_STR = R"((^|[^\[])<([A-z]+[A-z0-9]*)>($|[^\]]))";  // conservative match
const string TAG_VALUE_EXP_STR = R"(.*)";                                       // value between tags
const regex TAG_EXP(TAG_MATCH_EXP_STR);

const int DEFAULT_ARGC = 3;

// declare functions prototypes
void replace_all(string& s, const string& sub_str, const string& replace_str);
map<string, string>& create_map(const string& pattern, const string& s, map<string, string>& map);
string& create_formated_output(const string& s, map<string, string>& map, string& formated_output);

static struct option long_options[] =
{
    {"verbose", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"file", no_argument, 0, 'f'}
};

/*

 scanpf [opts] INPUT_PATTERN OUTPUT_PATTERN [INPUT ... ]

*/

void print_help()
{
    cout << "\n"
         << FMT_BOLD << "scanpf" << FMT_RESET << " "
         << "[OPTIONS] "
         << FMT_UNDERLINE << "INPUT_PATTERN" << FMT_RESET << " "
         << FMT_UNDERLINE << "OUTPUT_PATTERN" << FMT_RESET << " "
         << FMT_UNDERLINE << "[INPUT ...]" << FMT_RESET << "\n\n";
}

int parse_options(int argc, char* argv[])
{
    int opt = 0;
    int option_index = 0;
    bool file_flag = false;
    bool verbose_flag = false;

    while((opt = getopt_long(argc, argv, "hvf", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help();
            return 0;
        case 'v':
            verbose_flag = true;
            break;
        case 'f':
            file_flag = true;
            break;
        default: // unknown option before args
            fprintf(stderr, "Unexpected option, -h for help\n");
            return -1;
        }
    }

    if (optind != (argc - DEFAULT_ARGC)) // not correct number of args
    {
        fprintf(stderr, "Expected argument after options, -h for help\n");
        return -1;
    }

    if (verbose_flag)
    {
        print_help();
    }

    string input_pattern_str(argv[optind]);
    string output_pattern_str(argv[optind + 1]);
    string input_str(argv[optind + 2]);

    if (!file_flag)
    {
        map<string, string> tag_map;
        create_map(input_pattern_str, input_str, tag_map);
        string formated_out;
        create_formated_output(output_pattern_str, tag_map, formated_out);
        cout << formated_out << endl;
    }
    else
    {
        // iter all lines
        map<string, string> tag_map;
        string formated_out;
        std::ifstream file(input_str);
        while (std::getline(file, input_str))
        {
            tag_map.clear();
            create_map(input_pattern_str, input_str, tag_map);
            // open file iter
            create_formated_output(output_pattern_str, tag_map, formated_out);
            cout << formated_out << endl;
        }
    }
    return 0;
}

map<string, string>& create_map(const string &pattern, const string &s, map<string, string> &map)
{
    // create copy of pattern
    string pattern_cpy = pattern;
    // create regx from pattern
    replace_all(pattern_cpy, ".", "\\.");
    const string REPLACE_EXP_STR = "^" + regex_replace(pattern_cpy, TAG_EXP, "(" + TAG_VALUE_EXP_STR + ")") + "$";
    const regex REPLACE_EXP(REPLACE_EXP_STR);
    // create smatch
    smatch sm;
    regex_match(s, sm, REPLACE_EXP);
    // iterate through tag matches and create map
    int idx = 1;

    auto begin = sregex_iterator(pattern_cpy.begin(), pattern_cpy.end(), TAG_EXP);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
        map.insert(make_pair(match.str(1), sm.str(idx++)));
    }
    return map;
}

string& create_formated_output(const string& s, map<string, string>& map, string& formated_output)
{
    auto begin = sregex_iterator(s.begin(), s.end(), TAG_EXP);
    auto end = sregex_iterator();
    formated_output = s;
    int format_str_pos = 0;
    int format_str_end = 0;
    int output_str_pos = 0;
    int relative_pos = 0;

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        // get second match
        string tag_value = map[match.str(1)];
        // get current match position
        format_str_pos = match.position();
        // set realtive to last end
        relative_pos = format_str_pos - format_str_end;
        output_str_pos += relative_pos;
        // set new end
        format_str_end = format_str_pos + match.length();
        // replace <tag> with tag value
        formated_output.replace(output_str_pos, match.length(), tag_value);
        // set pos to end of replace
        output_str_pos += tag_value.length();
        formated_output = s;
    }
    return formated_output;
}

void replace_all(string& s, const string& sub_str, const string& replace_str)
{
    size_t pos = 0;
    size_t len = s.length();

    pos = s.find(sub_str, pos);
    while (pos < len)
    {
        s.replace(pos, sub_str.length(), replace_str);
        pos += replace_str.length();
        pos = s.find(sub_str, pos);
    }
}

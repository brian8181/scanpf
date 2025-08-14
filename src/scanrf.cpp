#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <fstream>
#include <getopt.h>
#include "bash_color.h"
#include "scanrf.hpp"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::regex;
using std::smatch;
using std::sregex_iterator;

// patterns
const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";                    // conservative match
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

int parse_options(int argc, char* argv[])
{
    cout << "parse options : " << argc  << endl;
    // int opt = 0;
    // int option_index = 0;
    // bool file_flag = false;
    // bool verbose_flag = false;

    // optind = 0;
    // while((opt = getopt_long(argc, argv, "hvf", long_options, &option_index)) != -1)
    // {
    //     switch (opt)
    //     {
    //     case 'h':
    //         print_help();
    //         return 0;
    //     case 'v':
    //         verbose_flag = true;
    //         break;
    //     case 'f':
    //         file_flag = true;
    //         break;
    //     default: // unknown option before args
    //         fprintf(stderr, "Unexpected option, -h for help\n");
    //         return -1;
    //     }
    // }

    // if (optind != (argc - DEFAULT_ARGC)) // not correct number of args
    // {
    //     fprintf(stderr, "Expected argument after options, -h for help\n");
    //     return -1;
    // }

    // if (verbose_flag)
    // {
    //     print_help();
    // }

    // if (file_flag)
    // {
    //     cout << "File option is not implemented yet." << endl;
    //     return -1;
    // }
    string patterns_file(argv[1]);
    string target_file(argv[2]);
    string formated_output;
    string line;
    // iter all lines
    map<string, string> tag_map;
    std::ifstream file(patterns_file);
    std::ifstream target_strm(target_file);

    string group_name;
    cout << __FILE__ << " : " << __LINE__ << " : " << patterns_file << endl;
    while (std::getline(file, line))
    {
        cout << __FILE__ << " : " << __LINE__ << " : " << patterns_file << endl;
        tag_map.clear();
        // skip empty lines
        string GRP_EXPR = R"(\[(.*)\])";
        string NAME_VALUE_EXPR = R"((\w+)\s*=\s*(\w+))";
        string EXPR_STR = "^\\s*((" + GRP_EXPR + ")" + "|" + "(" + NAME_VALUE_EXPR + "))\\s*$";
        regex  EXPR(".*");
        // create smatch
        smatch sm;
        regex_match(line, sm, EXPR);
        cout << sm.str(1) << endl;

        // auto begin = sregex_iterator(line.begin(), line.end(), EXPR);
        // auto end = sregex_iterator();

        // for (sregex_iterator i = begin; i != end; ++i)
        // {
        //     smatch match = *i;
        //     if (match[1].matched) // group match
        //     {
        //         group_name = match[1].str();
        //         cout << "Group: " << group_name << endl;
        //     }
        //     else if (match[2].matched && match[3].matched) // name value match
        //     {
        //         string name = match[2].str();
        //         string value = match[3].str();
        //         tag_map[name] = value;
        //         cout << "Tag: " << name << " = " << value << endl;
        //     }
        //}
        // if (sm[1].matched)
        // {
        //     group_name = sm[1].str();
        // }
        // else if (sm[2].matched && sm[3].matched)
        // {
        //     string name = sm[2].str();
        //     string value = sm[3].str();
        //     tag_map[name] = value;
        // }
    }

    //testing
    // for (const auto& pair : tag_map)
    // {
    //     cout << pair.first << " = " << pair.second << endl;
    // }

    return 0;
}

map<string, string>& create_map(const string &pattern, const string &s, map<string, string> &map)
{
//     // create copy of pattern
//     string pattern_cpy = pattern;
//     // create regx from pattern
//     replace_all(pattern_cpy, ".", "\\.");
//     const string REPLACE_EXP_STR = "^" + regex_replace(pattern_cpy, TAG_EXP, "(" + TAG_VALUE_EXP_STR + ")") + "$";
//     const regex REPLACE_EXP(REPLACE_EXP_STR);
//     // create smatch
//     smatch sm;
//     regex_match(s, sm, REPLACE_EXP);
//     // iterate through tag matches and create map
//     int idx = 1;

//     auto begin = sregex_iterator(pattern_cpy.begin(), pattern_cpy.end(), TAG_EXP);
//     auto end = sregex_iterator();

//     for (sregex_iterator i = begin; i != end; ++i)
//     {
//         smatch match = *i;
//         map.insert(make_pair(match.str(1), sm.str(idx++)));
//     }
     return map;
}

string& create_formated_output(const string& s, map<string, string>& map, string& formated_output)
{
    // auto begin = sregex_iterator(s.begin(), s.end(), TAG_EXP);
    // auto end = sregex_iterator();

    // // std::string::const_iterator begin = s.begin();
    // // std::string::const_iterator end = s.end();
    // formated_output = s;
    // int format_str_pos = 0;
    // int format_str_end = 0;
    // int output_str_pos = 0;
    // int relative_pos = 0;

    // for (sregex_iterator iter = begin; iter != end; ++iter)
    // {
    //     smatch match = *iter;
    //     // get second match
    //     string tag_value = map[match.str(1)];
    //     // get current match position
    //     format_str_pos = match.position();
    //     // set realtive to last end
    //     relative_pos = format_str_pos - format_str_end;
    //     output_str_pos += relative_pos;
    //     // set new end
    //     format_str_end = format_str_pos + match.length();
    //     // replace <tag> with tag value
    //     formated_output.replace(output_str_pos, match.length(), tag_value);
    //     // set pos to end of replaceFF
    //     output_str_pos += tag_value.length();
    //     formated_output = s;
    // }
    return formated_output;
}

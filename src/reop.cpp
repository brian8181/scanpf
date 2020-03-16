#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <fstream>
#include <unistd.h>

using namespace std;

// shell color constants
const string FMT_FG_GREEN  = "\e[32m"; 
const string FMT_UNDERLINE = "\e[4m";
const string FMT_BOLD      = "\e[1m";
const string FMT_RESET     = "\e[0m";

// regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
// ~!@#$%^&*()_+`-=[]\{}|;':",./<>?"
// ~!@#\\$%\\^&\\*\\(\\)_\\+`-=\\[\\]\\\\\{\\}\\|;':"\\,\\./<>\\?" ESCAPED

// character sets allowed pattern for tag names
const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";
const string SPECIAL_CHARS_STR = R"([A-z0-9 \^\$\.\*\+\:\'\[\]\{\}\|;,@#_-])";
const regex TAG_EXP(TAG_MATCH_EXP_STR);

// declare functions prototypes
void replace_all(string& s, const string& sub_str, const string& replace_str);
map<string, string>& create_map(const string& pattern, const string& s, map<string, string>& map);
string& create_formated_output(const string& s, map<string, string>& map, string& formated_output);
void print_help();

/*

create_remap [opts] INPUT_PATTERN OUTPUT_PATTERN [INPUT ... ]

*/

int main(int argc, char* argv[]) 
{
    int opt;
    bool file_flag = false;
    bool verbose_flag = false;
    bool help_flag = false;
    while ((opt = getopt(argc, argv, "hvfn:")) != -1) 
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
        default: /* '?' */
            fprintf(stderr, "Unexpected arguments check, -h for help\n");
            return EXIT_FAILURE;
        }
    }

    if (optind >= argc) 
    {
        fprintf(stderr, "Expected argument after options, -h for help\n");
        exit(EXIT_FAILURE);
    }

    if(verbose_flag)
    {
        print_help();
    }
    
    string input_pattern_str(argv[optind]);
    string output_pattern_str(argv[optind+1]);
    string input_str(argv[optind+2]);

    if(!file_flag)
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
            formated_out;
            create_formated_output(output_pattern_str, tag_map, formated_out);
            cout << formated_out << endl;
        }
    }
    exit(EXIT_SUCCESS);
}

map<string, string>& create_map(const string& pattern, const string& s, map<string, string>& map)
{
    // create copy of pattern
    string pattern_cpy = pattern;
    // create regx from pattern
    replace_all(pattern_cpy, ".", "\\.");
    const string REPLACE_EXP_STR 
        = "^" + regex_replace(pattern_cpy, TAG_EXP, "(" + SPECIAL_CHARS_STR + "*)" ) + "$";
    const regex REPLACE_EXP (REPLACE_EXP_STR);
    
    // create smatch
    smatch sm;    
    regex_match (s, sm, REPLACE_EXP);
    
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
    formated_output = s; // copy s
    int format_str_pos = 0;
    int format_str_end = 0;
    int output_str_pos = 0;
    int relative_pos = 0;

    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
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
    }

    return formated_output;
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

void print_help()
{
    cout << "\n" 
        << FMT_BOLD << "create_remap" << FMT_RESET << " "
        << "[OPTIONS] " 
        << FMT_UNDERLINE << "INPUT_PATTERN"  << FMT_RESET << " " 
        << FMT_UNDERLINE << "OUTPUT_PATTERN" << FMT_RESET << " "
        << FMT_UNDERLINE << "[INPUT ...]"    << FMT_RESET << "\n\n";
}

/*
USAGE
./create_remap -f "<track>: <artist> - <date> - <album> - <title>.<type>" "/<artist>/<date> - <album>/<track>. <title>.<type>" "remap_test_case_file_names.txt"
./create_remap "<track>. <artist>-<album>-<title>.<type>" "/<artist>/<album>/<track>. <title>.<type>" "$(./create_remap "/<artist>/<album>/<track>. <title>.<type>"  "<track>. <artist>-<album>-<title>.<type>" "/Pink Floyd/The Wall/10. Run Like Hell.mp3")"


OLD USAGE  !!!WRONG ARG ORDER!!:
./create_remap "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main Street-Brown Sugar.mp3" "<track>: <title>.<type>"
./create_remap "<first> <last>:<phone> <sex>" "Alfred E. Numan:555-555-9696 M" "Sex : <sex>    Name :<last>, <first>    Phone : <phone>"
./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "/<artist>/<album>/<track>. <title>.<type>"
./create_remap "/<artist>/<album>" "/Bob Dylan/Highway 61 Revisited" "<artist>-<album>"
./create_remap "/<artist>/<album>/<track>. <title>.<type>" "/Bob Dylan/1965 - Highway 61 Revisited/01. Like a Rolling Stone.mp3" "<track>: <artist>-<album>-<title>.<type>"

-FILE INPUT:
./create_remap -f "/<artist>/<album>/<track>. <title>.<type>" "remap_test_cases.txt" "<track>: <artist>-<album>-<title>.<type>"
./create_remap -f "<track>: <artist>-<album>-<title>.<type>" "/<artist>/<album>/<track>. <title>.<type>" "remap_test_case_files_to_dirs.txt" 

-TEST CREATING COMMANDS
mkdir -p "$(./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "./<artist>/<album>/")" 
touch "$(./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "./<artist>/<album>/<track>. <title>.<type>")"

-CREATE COPY COMMAND
./create_remap -f "/<artist>/<album>/<track>. <title>.<type>" \
"remap_test_cases.txt" \
"mkdir -p \"/home/brian/tmp/<artist>/<album>/\" & cp \"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<track>. <title>.<type>\" \"/home/brian/tmp/<artist>/<album>/<track>: <artist>-<album>-<title>.<type>\""\
> copy.sh

--RUN IT?
#chmod +x copy.sh
#./copy.sh

//DEMO OUTPUT
bash>$ cat remap_test_case_file_names.txt
01: Bob Dylan - 1965 - Highway 61 Revisited - Like a Rolling Stone.mp3
02: Bob Dylan - 1965 - Highway 61 Revisited - Tombstone Blues.mp3
03: Bob Dylan - 1965 - Highway 61 Revisited - It Takes a Lot to Laugh, It Takes a Train to Cry.mp3
04: Bob Dylan - 1965 - Highway 61 Revisited - From a Buick 6.mp3
05: Bob Dylan - 1965 - Highway 61 Revisited - Ballad of a Thin Man.mp3
06: Bob Dylan - 1965 - Highway 61 Revisited - Queen Jane Approximately.mp3
07: Bob Dylan - 1965 - Highway 61 Revisited - Highway 61 Revisited.mp3
08: Bob Dylan - 1965 - Highway 61 Revisited - Just Like Tom Thumb's Blues.mp3
09: Bob Dylan - 1965 - Highway 61 Revisited - Desolation Row.mp3
bash>$ ./create_remap -f "<track>: <artist> - <date> - <album> - <title>.<type>" "/<artist>/<date> - <album>/<track>. <title>.<type>" "remap_test_case_file_names.txt"
/Bob Dylan/1965 - Highway 61 Revisited/01. Like a Rolling Stone.mp3
/Bob Dylan/1965 - Highway 61 Revisited/02. Tombstone Blues.mp3
/Bob Dylan/1965 - Highway 61 Revisited/03. It Takes a Lot to Laugh, It Takes a Train to Cry.mp3
/Bob Dylan/1965 - Highway 61 Revisited/04. From a Buick 6.mp3
/Bob Dylan/1965 - Highway 61 Revisited/05. Ballad of a Thin Man.mp3
/Bob Dylan/1965 - Highway 61 Revisited/06. Queen Jane Approximately.mp3
/Bob Dylan/1965 - Highway 61 Revisited/07. Highway 61 Revisited.mp3
/Bob Dylan/1965 - Highway 61 Revisited/08. Just Like Tom Thumb's Blues.mp3
/Bob Dylan/1965 - Highway 61 Revisited/09. Desolation Row.mp3

*/

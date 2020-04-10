#include <iostream>
#include <string>
#include <regex>
#include <unistd.h>

using namespace std;

// shell color constants
const string FMT_FG_GREEN  = "\e[32m"; 
const string FMT_UNDERLINE = "\e[4m";
const string FMT_BOLD      = "\e[1m";
const string FMT_RESET     = "\e[0m";
const string CURRENT_FG_COLOR = FMT_FG_GREEN + FMT_UNDERLINE;

void print_help();

int main(int argc, char* argv[]) 
{
    int opt;
    //bool file_flag = false;
    bool verbose_flag = false;
    //bool help_flag = false;
    while ((opt = getopt(argc, argv, "hvn:")) != -1) 
    {
        switch (opt) 
        {
        case 'h':
            print_help();
            return 0;
        case 'v':
            verbose_flag = true;
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

    string exp(argv[optind]);
    string src(argv[optind+1]);

    
    cout << "pattern: " << "\"" << exp << "\"" << " -> " 
         << "input: " << "\"" << src << "\"" << "\n\n";

    int idx = 0;
    string bash_str = src;
    regex src_epx(exp);
    auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
    auto end = sregex_iterator();
    
    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
                
        int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + FMT_RESET.length()));
        int len = match.length();

        // set bash green start postion
        bash_str.insert(pos, CURRENT_FG_COLOR);

        // reset bash color position
        pos = pos + CURRENT_FG_COLOR.length() + len;
        bash_str.insert(pos, FMT_RESET);

        cout << idx << ": " << src.substr(match.position(), match.length()) << endl; 
       
        ++idx;
    }

    cout << "\nFound " << std::distance(begin, end) << " matches:\n";
    cout << bash_str << "\n\n";
}

void print_help()
{
    cout << "\n" << FMT_BOLD << "regx" << FMT_RESET << " " 
         << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " " 
         << FMT_UNDERLINE << "INPUT"   << FMT_RESET << "\n\n";
}

/*

#MATCH
./regx "a\\\\b" "a\\b"
./regx "a\\*b" "a*b"
./regx "a\\=b" "a=b"
./regx "a\\+b" "a+b"
./regx "a~b" "a~b"
./regx "a~b" "a~b"
./regx 'a`b' 'a`b'
./regx 'a-b' 'a-b'
./regx "a-b" "a-b"
./regx "a#b" "a#b"
./regx "a@b" "a@b"
./regx "a\\$" "a$"
./regx "a&b" "a&b"
./regx "a\\&b" "a&b"
./regx "a\\(b" "a(b"
./regx "a\\)b" "a)b"
./regx "a\(b\)c" "a(b)c"
./regx "a\[b\]c" "a[b]c"
./regx "a\{b\}c" "a{b}c"

# STRANGE BOTH MATCH
./regx 'a"b' 'a"b'
./regx 'a\"b' 'a"b'

#NO MATCH
#./regx "a\\!b" "a!b"
# ./regx "a`b" "a`b"
# ./regx "a\\$b" "a$b"

# GREEDY TESTING
./regx "a.*?b" "axbb" // MATCH = axb

# TAGS
## OK
./regx "\\<([A-z]+[A-z0-9]*)\\>" "<tag1> <tag2>"
./regx "\\<([A-z]+[A-z0-9]*)\\>" "<tag1> <tag2><tag3>"

# FUNNY
./regx "\\<([A-z]+[A-z0-9\\<\\>]*?)+\\>" "<tag1<tag4>> <tag2><tag3>"

# WORKS WITH WORD BOUNDRAY \b
./regx "\\<\b([A-z]+[A-z0-9\\<\\>]*?)+\b\\>" "<tag1>. <tag2><tag3>*<tag5>&<tag6>^<tag7>|<tag8>"

*/
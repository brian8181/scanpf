#include <iostream>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include "scanpf.hpp"
#include "../config.h"

using std::cin;

int _main(int argc, char* argv[])
{
    termios t;
    if (tcgetattr(STDIN_FILENO, &t) < 0)
    { 
        // get input from pipe
        char buffer[BUFFER_LEN]; // buffer for pipe  
        cin >> buffer;
					
        // add piped buffer to end of args
        char* argvtmp[sizeof(char*) * argc+1];
        memcpy(argvtmp, argv, sizeof(char*) * argc);
        argvtmp[argc] = buffer;
        argv = argvtmp;

        return parse_options(++argc, argv);
    }
    return parse_options(argc, argv);
}

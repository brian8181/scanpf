#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>         /* for STDIN_FILENO */
#include <sys/select.h>     /* for pselect   */
#include "main.hpp"

using std::cin;
using std::string;

int stdin_ready (int filedes)
{
    fd_set set;
    /* declare/initialize zero timeout */
    struct timespec timeout = { .tv_sec = 0 };
    /* Initialize the file descriptor set. */
    FD_ZERO (&set);
    FD_SET (filedes, &set);
    /* check whestdin_ready is ready on filedes */
    return pselect (filedes + 1, &set, NULL, NULL, &timeout, NULL);
}

int main(int argc, char* argv[])
{
	try
	{
		if(stdin_ready (STDIN_FILENO))
		{
				string buffer;
				cin >> buffer;
				// add piped buffer to end of argv
				char* argvtmp[sizeof(char*) * argc+1];
				memcpy(argvtmp, argv, sizeof(char*) * argc);
				argvtmp[argc] = &buffer[0];
				argv = argvtmp;
				++argc;
		}
		return parse_options(argc, argv);
	}
	catch(std::logic_error& ex)
	{
	 	std::cout << ex.what() << std::endl;
	}
}

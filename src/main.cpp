#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>         /* for STDIN_FILENO */
#include <sys/select.h>     /* for pselect   */
#include "scanpf.hpp"

using std::cin;
using std::string;


int stdin_ready (int filedes)
{
	// initialize the file descriptor set
	fd_set set;
	FD_ZERO(&set);
	FD_SET(filedes, &set);
#ifndef CYGWIN
	// declare/initialize timespec
	struct timespec timeout = { .tv_sec = 0 };
	return pselect(filedes + 1, &set, NULL, NULL, &timeout, NULL);
#else
	// declare/initialize timeout
	struct timeval timeout = { .tv_sec = 0 };
	return select(filedes + 1, &set, NULL, NULL, &timeout);
#endif
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

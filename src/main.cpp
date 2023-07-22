#include "../inc/Archive.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

	if (argc == 2)
	{
		archive a(argv[1]);
		a.work();
	}

	getchar();
	return 0;
}

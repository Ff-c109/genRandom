#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	if(argc == 2) {
		string cmd = string("env PORT=") + string(argv[1]) + string(" node data-server-provide.js");
		system(cmd.c_str());
		return 1;
	}
	else return -1;
}

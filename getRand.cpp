#include <cpp-httplib/httplib.h>
#include <iostream>
#include <string>
#include <cfgdb.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
	if(argc == 3) {
		httplib::Client cli("127.0.0.1", stoi(argv[1]));
		if(auto res = cli.Get("/genRandom")) {
			sleep(10);
			string cmd = string(argv[0]) + string(" ") + string(argv[1]) + string(" close");
			system(cmd.c_str());
		}
		else {
			cfgdb::Cfg cfg = cfgdb::get();
			string url = string("http://127.0.0.1:") + to_string(cfg.port);
			httplib::Client cli(url.c_str());
			string path = string("/return/") + string(argv[1]);
			cli.Get(path.c_str());
			return 0;
		}
	}
	else if(argc == 2) {
		httplib::Client cli("127.0.0.1", stoi(argv[1]));
		if(auto res = cli.Get("/genRandom")) {
			if(res->status == httplib::StatusCode::OK_200) {
				cout << res->body << endl;
				string cmd1 = string(argv[0]) + string(" ") + string(argv[1]) + string(" close");
				system(cmd1.c_str());
			}
			else {
				cout << "[::STCD]" << endl;
			}
		}
		else {
			usleep(1000);
			string cmd = string(argv[0]) + string(" ") + string(argv[1]);
			system(cmd.c_str());
		}
	}
	else {
		cfgdb::Cfg cfg = cfgdb::get();
		string url = string("http://127.0.0.1:") + to_string(cfg.port);
		httplib::Client cli(url.c_str());
		auto res = cli.Get("/get");
		string dataPort = res->body;
		string cmd = string(argv[0]) + string(" ") + dataPort;
		system(cmd.c_str());
	}
}

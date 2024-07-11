#include "cpp-httplib/httplib.h"
#include <string>
#include <cfgdb.h>
#include <iostream>
#include <map>

namespace randd {
	using namespace httplib;
	using namespace std;
	map<int, void*> portRegistry;
	int getPort() {
		map<string, int> *range = (map<string,int>*)(portRegistry[0]);
		map<int, bool> *portList = (map<int, bool>*)(portRegistry[1]);
		int port = (*range)["from"];
		while((*portList)[port]) port++;
		(*portList)[port] = true;
		return port;
	}
	void returnPort(int port) {
		map<int, bool> *portList = (map<int, bool>*)(portRegistry[1]);
		(*portList)[port] = false;
	}
	void controlS() {
		Server svr;
		int randpipe[2];
		char base64Rand[32];
		cfgdb::Cfg cfg = cfgdb::get();
		int location = cfg.portArea.find('-');
		int from = stoi(cfg.portArea.substr(0, location));
		int to = stoi(cfg.portArea.substr(location+1, cfg.portArea.length() - (location + 1)));
		map<string, int> range;
		range["from"] = from;
		range["to"] = to;
		map<string, int> *prange = new map<string, int>;
		*prange = range;
		portRegistry[0] = prange;
		map<int, bool> portList;
		for(int i = from; i <= to; i++) {
			portList[i] = false;
		}
		map<int, bool> *pportList = new map<int, bool>;
		*pportList = portList;
		portRegistry[1] = pportList;

		svr.Get("/get", [](const httplib::Request &, httplib::Response &res) {
			string port = to_string(getPort());
			string cmd = string("./data-server-provide ") + port + string("&");
			system(cmd.c_str());
			cout << port << endl;
			res.set_content(port.c_str(), "text/plain");
		});
		svr.Get(R"(/return/(\d+))", [&](const Request& req, Response& res) {
		    int port = stoi(req.matches[1]);
		    res.set_content(to_string(port).c_str(), "text/plain");
		    returnPort(port);
		});
		svr.Get(R"(/push/(\d+))", [&](const Request& req, Response& res) {
			string port = req.matches[1];
			string cmd = string("./data-server-recive ") + port + string("&");
			system(cmd.c_str());
			res.set_content("OK", "text/plain");
		});
		cout << cfg.port << endl;
		svr.listen("localhost", cfg.port);
	}

}

int main(void) {
	randd::controlS();
	return 0;
}

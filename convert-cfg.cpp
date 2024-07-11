#include "cfgdb.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <math.h>

namespace convertCfg {
	using namespace std;
	cfgdb::Cfg cfg;
	void convert() {
		system("cat /etc/genRand/config.yaml");
		ifstream cfgFile("/etc/genRand/config.yaml");
		const string flag00 = "port";
		const int flag00_length = flag00.length();
		char buffer[flag00_length*3];
		int p = 0;
		while (true) {
			cfgFile.seekg(p);
			cfgFile.read(buffer, flag00_length);
			buffer[flag00_length] = 0;
			p++;
			if(string(buffer) == flag00) {
				while(cfgFile.read(buffer, 1), buffer[0] == ' ')
					NULL;
				if(buffer[0] == ':') {
					while(cfgFile.read(buffer, 1), buffer[0] == ' ')
						NULL;
					char port[6];
					char* port_p = port;
					*port_p = buffer[0];
					port_p++;
					while(cfgFile.read(buffer, 1), buffer[0] != '\n') {
						*port_p = buffer[0];
						port_p++;
					}
					*port_p = 0;
					const int port_length = string(port).length();
					cfg.port = 0;
					for(int i = 0; i < port_length; i++)
						cfg.port += (port[i] - '0') * pow(10, port_length - i - 1);
					break;
				}
			}
		}
		cfgFile.seekg(0);
		const string flag01 = "port-area";
		const int flag01_length = flag01.length();
		char buffer1[flag01_length];
		int p1 = 0;
		while (true) {
			cfgFile.seekg(p1);
			cfgFile.read(buffer1, flag01_length);
			buffer1[flag01_length] = 0;
			p1++;
			if(string(buffer1) == flag01) {
				while(cfgFile.read(buffer1, 1), (buffer1[0] == ' ')) NULL;
				if(buffer1[0] == ':') {
					while(cfgFile.read(buffer1, 1), (buffer1[0] == ' ')) NULL;
					char portArea[14];
					char* portArea_p = portArea;
					*portArea_p = buffer1[0];
					portArea_p++;
					while(cfgFile.read(buffer1, 1), (buffer1[0] != '\n')) {
						*portArea_p = buffer1[0];
						portArea_p++;
					}
					*portArea_p = 0;
					cfg.portArea = portArea;
					break;
				}
				else continue;
			}
		}
		cout << cfg.port << endl;
		cout << cfg.portArea << endl;
		cfgFile.close();
		cfgdb::init();
		cfgdb::set(cfg);
	}
}

int main(void) {
	convertCfg::convert();
	return 0;
}

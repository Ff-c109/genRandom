#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

namespace cfgdb {
	using namespace std;
	struct Cfg {
		int port;
		string portArea;
	};
	Cfg cfg;
	void read(void) {
		ifstream f_cfg("/var/genRand/config.dat", std::ifstream::binary);
		f_cfg.read((char*)&cfg.port, sizeof(int));
		int length;
		f_cfg.read((char*)&length, sizeof(int));
		char portArea[length + 1];
		f_cfg.read(portArea, length);
		portArea[length] = 0;
		cfg.portArea = portArea;
		f_cfg.close();
	}
	Cfg get(void) {
		read();
		return cfg;
	}
	void write(void) {
		ofstream f_cfg("/var/genRand/config.dat", std::ofstream::binary);
		f_cfg.write((char*)&cfg.port, sizeof(int));
		int length = cfg.portArea.length();
		f_cfg.write((char*)&length, sizeof(int));
		f_cfg.write(cfg.portArea.c_str(), cfg.portArea.length());
		f_cfg.close();
	}
	void set(Cfg ncfg) {
		cfg.port = ncfg.port;
		cfg.portArea = ncfg.portArea.c_str();
		write();
	}
	void init(void) {
		cfg.port = 23114;
		cfg.portArea = "43000-43010";
		write();
	}
}

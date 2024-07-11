#include <string>

namespace cfgdb {
	using namespace std;
	struct Cfg {
		int port;
		string portArea;
	};
	void read(void);
	Cfg get(void);
	void write(void);
	void set(Cfg ncfg);
	void init(void);
}

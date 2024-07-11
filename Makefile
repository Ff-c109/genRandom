genRandom: randd randc

randd: cbuild/control-server cbuild/convert-cfg cbuild/genRand-d

randc: cbuild/getRand cbuild/gnrd

cbuild/control-server: cbuild/libcfgdb.so cbuild/data-server-provide
	g++ -c -Iinclude control-server.cpp -o cbuild/control-server.o
	cd cbuild && g++ control-server.o -L. -lcfgdb -o control-server && cd ..

cbuild/libcfgdb.so:
	g++ -Iinclude -fPIC -shared cfgdb.cpp -o cbuild/libcfgdb.so

cbuild/convert-cfg: cbuild/libcfgdb.so
	g++ -c -Iinclude convert-cfg.cpp -o cbuild/convert-cfg.o
	cd cbuild && g++ convert-cfg.o -L. -lcfgdb -o convert-cfg && cd ..

cbuild/data-server-provide: cbuild/data-server-provide.js cbuild/genRand
	g++ data-server-provide.cpp -o cbuild/data-server-provide

cbuild/data-server-provide.js: 
	cp data-server-provide.js cbuild/data-server-provide.js

cbuild/genRand: 
	g++ genRand.cpp -o cbuild/genRand

cbuild/getRand: cbuild/libcfgdb.so
	g++ -c -Iinclude getRand.cpp -o cbuild/getRand.o
	cd cbuild && g++ getRand.o -L. -lcfgdb -o getRand && cd ..

cbuild/genRand-d:
	cp genRand-d.sh cbuild/genRand-d
	chmod +x cbuild/genRand-d

cbuild/gnrd:
	cp gnrd.sh cbuild/gnrd
	chmod +x cbuild/gnrd

clean:
	rm -rf cbuild/*

cleanMake: clean
	make genRandom

install: /opt/genRandom/install /usr/bin/genRand

/opt/genRandom/install: genRandom
	mkdir /opt/genRandom
	cp -r cbuild/* /opt/genRandom/
	echo install > /opt/genRandom/install

/usr/bin/genRand:
	cp genRand.sh /usr/bin/genRand
	chmod +x /usr/bin/genRand

uninstall:
	rm -rf /opt/genRandom
	rm /usr/bin/genRand



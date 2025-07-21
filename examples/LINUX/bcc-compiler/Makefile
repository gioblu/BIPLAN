all:
	g++	-DLINUX	-I.	-I ../../../src	-std=gnu++11 bcc.cpp -o bcc -O1
	$(info bcc compiler compilation started!)
fast:
	g++	-DLINUX	-I.	-I	../../../src -std=gnu++11 bcc.cpp -o bcc -O2
	$(info bcc compiler compilation started! (target: fast))
compact:
	g++	-DLINUX	-I.	-I ../../../src -std=gnu++11 bcc.cpp -o	bcc	-Os -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--strip-all
	$(info bcc compiler compilation started! (target: compact))

install:	
	rm -rf /usr/local/BIPLAN
	cp bcc /usr/local/bin
	cp -R ../../../src/utils/libraries/ /usr/local/BIPLAN	
	$(info bcc compiled successfully, installing libraries in /usr/local/BIPLAN.)
	@./../tests/examples-compilation.sh
clean:
	rm bcc
	rm -rf /usr/local/BIPLAN
	rm -rf /usr/local/bin/bcc
	$(info removing bcc)
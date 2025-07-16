all:
	g++	-DLINUX	-I.	-I	../../../src -std=c++17 biplan.c -o biplan -lm -lrt
fast: 
	g++	-DLINUX	-I.	-I	../../../src -std=c++17 biplan.c -o biplan -lm -lrt -O2 -DBIP_FAST
compact: 
	g++	-DLINUX	-I.	-I	../../../src -std=c++17 biplan.c -o biplan -lm -lrt -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--strip-all
install:
	cp biplan /usr/local/bin
	@./../tests/examples-interpretation.sh
clean:
	rm biplan
	rm -rf /usr/local/bin/biplan
all:
	$(info BIPLAN compilation started!)
	g++	-DLINUX	-I.	-I	../../../src -std=c++17 biplan.cpp -o biplan -lm -lrt -g
fast: 
	$(info BIPLAN compilation started! (target: fast))
	g++	-DLINUX	-I.	-I	../../../src -std=c++17 biplan.cpp -o biplan -lm -lrt -O2 -DBIP_FAST
compact: 
	$(info BIPLAN compilation started! (target: compact))
	g++	-DLINUX	-I.	-I	../../../src -std=c++17 biplan.cpp -o biplan -lm -lrt -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--strip-all
install:
	cp biplan /usr/local/bin
	@./../tests/examples-interpretation.sh
	@./../tests/syntax-interpretation.sh
	@./../benchmarks/biplan-python.sh
	@echo "biplan installation completed, digit biplan -h to learn more. Have fun! \n\n"
clean:
	rm biplan
	rm -rf /usr/local/bin/biplan
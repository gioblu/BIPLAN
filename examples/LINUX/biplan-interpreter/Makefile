all:
	g++	-DLINUX	-I.	-I	../../../src	-std=gnu++11	biplan.c	-o	biplan	-lpthread	-lcrypt	-lm	-lrt
	@./../tests/examples-interpretation.sh
inline: 
	g++	-DLINUX	-I.	-I	../../../src	-std=gnu++11	biplan.c	-o	biplan	-lpthread	-lcrypt	-lm	-lrt -O2 -DBIP_INLINE
	@./../tests/examples-interpretation.sh
install:
	cp biplan /usr/local/bin
clean:
	rm biplan
	rm -rf /usr/local/bin/biplan
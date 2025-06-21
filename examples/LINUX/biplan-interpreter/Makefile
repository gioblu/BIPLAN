all:
	g++	-DLINUX	-I.	-I	../../../src	-std=gnu++11	biplan.c	-o	biplan	-lpthread	-lcrypt	-lm	-lrt
inline: 
	g++	-DLINUX	-I.	-I	../../../src	-std=gnu++11	biplan.c	-o	biplan	-lpthread	-lcrypt	-lm	-lrt -O2 -DBIP_INLINE
install:
	cp biplan /usr/local/bin
	@./../tests/examples-interpretation.sh
clean:
	rm biplan
	rm -rf /usr/local/bin/biplan
all:
	g++	-DLINUX	-I.	-I	../../../src	-std=gnu++11	bcc.cpp	-o	bcc	-lpthread	-lcrypt	-lm	-lrt -O1
	$(info bcc compiler compilation started!)
install:	
	cp bcc /usr/local/bin
	rm -r /usr/local/BIPLAN
	cp -R ../../../src/utils/libraries/ /usr/local/BIPLAN	
	$(info bcc compiled successfully, installing libraries in /usr/local/BIPLAN.)

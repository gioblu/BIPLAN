all:
	g++ -I.	-I	../../../src	-std=gnu++11	bcc.cpp	-o	bcc	-lpthread -O1
	$(info bcc compiler compilation started!)
install:	
	rm -r /usr/local/BIPLAN
	cp bcc /usr/local/bin
	cp -R ../../../src/utils/libraries/ /usr/local/BIPLAN	
	$(info bcc compiled successfully, installing libraries in /usr/local/BIPLAN.)

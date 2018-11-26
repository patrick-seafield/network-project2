
ftserver: ftserver_bind.o ftserver_parse.o ftserver_respond.o constants.h
	gcc -o ftserver ftserver.c ftserver_bind.o ftserver_parse.o ftserver_respond.o -lssl -lcrypto

ftserver_bind.o: ftserver_bind.h
	gcc -c ftserver_bind.c

ftserver_parse.o: ftserver_parse.h constants.h
	gcc -c ftserver_parse.c

ftserver_respond.o: ftserver_respond.h constants.h
	gcc -c ftserver_respond.c

clean:
	rm -f ftserver *.o


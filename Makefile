
ftserver: ftserver_bind.o ftserver_respond.o constants.h
	gcc -o ftserver ftserver.c ftserver_bind.o ftserver_respond.o

ftserver_bind.o: ftserver_bind.h
	gcc -c ftserver_bind.c

ftserver_respond.o: ftserver_respond.h constants.h
	gcc -c ftserver_respond.c

clean:
	rm -f ftserver *.o


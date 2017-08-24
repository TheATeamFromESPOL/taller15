daemon:daemon.c
	gcc -Wall -g daemon.c -o $@
clean:
	rm ./daemon

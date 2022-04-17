gcc  -c main.c  -I../include -I../lib  -D DETACH  -D NOSLEEP  -O0

gcc  -c detach.c  -I../include -I../lib  -D DETACH  -D NOSLEEP   -O0

gcc -Og main.o detach.o  -lpthread -L../include -L../lib 

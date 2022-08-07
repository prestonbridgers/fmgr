CC=gcc
LFLAGS=-lncurses -lpanel -lmenu
CFLAGS=-g -c -Wall

all: main.o files.o util.o
	$(CC) $^ $(LFLAGS) -o fmgr

main.o: main.c fmgr.h
	$(CC) $(CFLAGS) $< -o $@

files.o: files.c fmgr.h
	$(CC) $(CFLAGS) $< -o $@

util.o: util.c fmgr.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm fmgr
	
run:
	@./fmgr

memcheck:
	@valgrind --leak-check=full ./fmgr	

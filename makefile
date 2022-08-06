CC=gcc
LFLAGS=-lncurses -lpanel -lmenu
CFLAGS=-c -Wall

all: main.o files.o
	$(CC) $^ $(LFLAGS) -o fmgr

main.o: main.c files.h
	$(CC) $(CFLAGS) $< -o $@

files.o: files.c files.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm fmgr
	
run:
	@./fmgr

memcheck:
	@valgrind --leak-check=full ./fmgr	

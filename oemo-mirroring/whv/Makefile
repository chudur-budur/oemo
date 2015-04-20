# Makefile for PREMO

# Compiler
CC = gcc

# Compiler options
CFLAGS = -g -Wall -std=gnu99
LDFLAGS = -lm

# all object files
SEL_OBJECTS = hyp_ind.o premo_wdfs.o

all: hyp_ind

hyp_ind: $(SEL_OBJECTS)
	$(CC) $(CFLAGS) $(SEL_OBJECTS) -o hyp_ind $(LDFLAGS)

premo_wdfs.o: premo_wdfs.c premo_wdfs.h
	$(CC) $(CFLAGS) -c $(LDFLAGS) premo_wdfs.c 

hyp_ind.o : hyp_ind.c premo_wdfs.h
	$(CC) $(CFLAGS) -c $(LDFLAGS) hyp_ind.c

clean:
	rm -f *~ *.o

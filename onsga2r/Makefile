# Makefile for compiling NSGA-II source code
CC = gcc
LD = gcc
RM = rm -f
# CFLAGS=-Wall -ansi -pedantic -g
CFLAGS = -Wall -ansi -pedantic -g -std=gnu99
LDFLAGS = -lm
OBJS := $(patsubst %.c, %.o, $(wildcard src/*.c))
MAIN = nsga2r

all: $(MAIN)

$(MAIN): $(OBJS)
	 $(LD) $(CFLAGS) $(OBJS) -o $(MAIN) -lm

%.o: src/%.c src/global.h src/rand.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJS)

clean-all:
	$(RM) $(OBJS)
	rm -rf *.out
	rm -f nsga2r

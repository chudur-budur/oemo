# onsga2r stuffs
CC 		:= gcc
INCLUDES 	:= $(wildcard src/*.h)
COMMON_FILES 	:= allocate.c auxiliary.c crossover.c crowddist.c decode.c display.c\
			dominance.c eval.c fillnds.c initialize.c list.c merge.c misc.c\
			mutation.c opposition.c poplist.c problemdef.c rand.c rank.c\
			report.c sort.c tourselect.c vecutils.c
SRC		:= $(addprefix src/,$(COMMON_FILES))
IFLAGS 		:= $(addprefix -I/,$(INCLUDES))
CFLAGS 		:= -g -Wall -pedantic -std=gnu99 $(IFLAGS)
LDFLAGS 	:= -lm
OBJ 		:= $(patsubst %c,%o,$(SRC))
DEPS		:= $(OBJ:.o=.d)

.PHONY: clean all wfg

all: nsga2r onsga2r nsga2re onsga2rw onsga2rwdom
wfg: wfg-1.10/wfg

onsga2r: $(OBJ) src/onsga2r.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	strip onsga2r

onsga2rw: $(OBJ) src/onsga2rw.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	strip onsga2rw

onsga2rwdom: $(OBJ) src/onsga2rwdom.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	strip onsga2rwdom

nsga2r: $(OBJ) src/nsga2r.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	strip nsga2r

nsga2re: $(OBJ) src/nsga2re.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	strip nsga2re

src/onsga2r.o: src/onsga2r.c
	$(CC) $(CFLAGS) -c $< -o $@

src/onsga2rw.o: src/onsga2rw.c
	$(CC) $(CFLAGS) -c $< -o $@

src/onsga2rwdom.o: src/onsga2rwdom.c
	$(CC) $(CFLAGS) -c $< -o $@

src/nsga2r.o: src/nsga2r.c
	$(CC) $(CFLAGS) -c $< -o $@

src/nsga2re.o: src/nsga2re.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

wfg-1.10/wfg: wfg-1.10/wfg.c wfg-1.10/read.c
	$(CC) -g -Wall -pedantic -std=gnu99 -I/wfg-1.10/wfg.h $^ -o $@ $(LDFLAGS)
	cp wfg-1.10/wfg .

-include $(DEPS)

clean:
	rm -f src/*.d
	rm -f src/*.gc*
	rm -f $(OBJ) src/*.o
	rm -f onsga2r onsga2rw onsga2rwdom nsga2re nsga2r
	rm -f *.out
	rm -f *~
	rm -f \#*\#
	rm -f input_data/*~
	rm -f input_data/\#*\#

clean-all: clean
	rm -f wfg-1.10/*.o wfg-1.10/wfg wfg

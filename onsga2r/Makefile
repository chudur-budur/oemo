# onsga2r stuffs
CC 		:= gcc
INCLUDES 	:= $(wildcard src/*.h)
COMMON_FILES 	:= allocate.c auxiliary.c crossover.c crowddist.c decode.c display.c\
			dominance.c euclideancd.c euclideanfillnds.c euclideanrank.c eval.c fillnds.c\
			initialize.c list.c merge.c misc.c mutation.c opposition.c poplist.c\
			problemdef.c rand.c rank.c report.c rga.c sort.c tourselect.c vectorop.c
SRC		:= $(addprefix src/,$(COMMON_FILES))
IFLAGS 		:= $(addprefix -I/,$(INCLUDES))
CFLAGS 		:= -g -Wall -pedantic -std=gnu99 $(IFLAGS)
LDFLAGS 	:= -lm 
# OBJ 		:= $(SRC:.c=.o)
OBJ 		:= $(patsubst %c,%o,$(SRC))
DEPS		:= $(OBJ:.o=.d)

.PHONY: clean all wfg whv

all: nsga2re onsga2r
wfg: wfg-1.10/wfg
whv: whv-pisa/hyp_ind

onsga2r: $(OBJ) src/onsga2r.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

nsga2re: $(OBJ) src/nsga2re.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

src/nsga2re.o: src/nsga2re.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/onsga2r.o: src/onsga2r.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

wfg-1.10/wfg: wfg-1.10/wfg.c wfg-1.10/read.c
	$(CC) -g -Wall -pedantic -std=gnu99 -I/wfg-1.10/wfg.h $^ -o $@ $(LDFLAGS)
	mv wfg-1.10/wfg .

whv-pisa/hyp_ind: whv-pisa/premo_wdfs.c whv-pisa/hyp_ind.c
	$(CC) -g -Wall -pedantic -std=gnu99 -I/whv-pisa/premo_wdfs.h $^ -o $@ $(LDFLAGS)
	mv whv-pisa/hyp_ind .

-include $(DEPS)

clean:
	rm -f $(DEPS)
	rm -f $(OBJ) src/nsga2r.o src/onsga2r.o
	rm -f nsga2r onsga2r
	rm -f *.out
	rm -f *~
	rm -f \#*\#
	rm -f input_data/*~
	rm -f input_data/\#*\#
	rm -f wfg-1.10/*.o wfg-1.10/wfg wfg
	rm -f whv-pisa/*.o whv-pisa/hyp_ind hyp_ind

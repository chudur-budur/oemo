# onsga2r stuffs
CC 		:= gcc
MCC		:= mcc
INCLUDES 	:= $(wildcard src/*.h)
COMMON_FILES 	:= allocate.c auxiliary.c crossover.c crowddist.c decode.c display.c\
			dominance.c euclideancd.c euclideanfillnds.c euclideanrank.c eval.c fillnds.c\
			initialize.c list.c merge.c misc.c mutation.c opposition.c poplist.c\
			problemdef.c rand.c rank.c report.c rga.c sort.c tourselect.c vecutils.c
SRC		:= $(addprefix src/,$(COMMON_FILES))
IFLAGS 		:= $(addprefix -I/,$(INCLUDES))
CFLAGS 		:= -g -Wall -pedantic -std=gnu99 $(IFLAGS)
LDFLAGS 	:= -lm
MCFLAGS		:= -D_GNU_SOURCE  -DUNIX -DX11 -pthread -O -DNDEBUG
SOSOLVEROBJ	:= src/sosolver/libsosolver.so
MIFLAGS		:= -I"/opt/MATLAB/R2014a/extern/include"\
			-I"/opt/MATLAB/R2014a/simulink/include"\
			-I./src/sosolver
MLDFLAGS	:= -pthread -Wl,-rpath-link,/opt/MATLAB/R2014a/bin/glnxa64 -O\
			$(SOSOLVEROBJ) -L"/opt/MATLAB/R2014a/runtime/glnxa64" -lmwmclmcrrt
# OBJ 		:= $(SRC:.c=.o)
OBJ 		:= $(patsubst %c,%o,$(SRC))
DEPS		:= $(OBJ:.o=.d)

.PHONY: clean all wfg whv sosolv

all: nsga2re onsga2r nsga2r
wfg: wfg-1.10/wfg
whv: whv-pisa/hyp_ind
sosolv: $(SOSOLVEROBJ)

onsga2r: $(OBJ) src/onsga2r.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)

nsga2re: $(OBJ) src/nsga2re.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)

nsga2r: $(OBJ) src/nsga2r.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)

src/onsga2r.o: src/onsga2r.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/nsga2re.o: src/nsga2re.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/nsga2r.o: src/nsga2r.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/sosolver.o: src/sosolver.c
	$(CC) $(CFLAGS) $(MCFLAGS) $(MIFLAGS) -c -MMD -MP $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(MIFLAGS) -c -MMD -MP $< -o $@

$(SOSOLVEROBJ): src/sosolver/*.m
	$(MCC) -B csharedlib:libsosolver -v $^
	mv libsosolver.* src/sosolver/
	mv mcc* src/sosolver/
	mv readme.txt src/sosolver/

wfg-1.10/wfg: wfg-1.10/wfg.c wfg-1.10/read.c
	$(CC) -g -Wall -pedantic -std=gnu99 -I/wfg-1.10/wfg.h $^ -o $@ $(LDFLAGS)
	mv wfg-1.10/wfg .

whv-pisa/hyp_ind: whv-pisa/premo_wdfs.c whv-pisa/hyp_ind.c
	$(CC) -g -Wall -pedantic -std=gnu99 -I/whv-pisa/premo_wdfs.h $^ -o $@ $(LDFLAGS)
	mv whv-pisa/hyp_ind .

-include $(DEPS)

clean:
	rm -f src/*.d
	rm -f src/*.gc*
	rm -f $(OBJ) src/*.o src/sosolver/*.o
	rm -f onsga2r nsga2re nsga2r
	rm -f *.out
	rm -f *~
	rm -f \#*\#
	rm -f input_data/*~
	rm -f input_data/\#*\#
	rm -f wfg-1.10/*.o wfg-1.10/wfg wfg
	rm -f whv-pisa/*.o whv-pisa/hyp_ind hyp_ind

clean-sosolv:
	rm -rf src/sosolver/libsosolver.*
	rm -rf src/sosolver/mcc*
	rm -f src/sosolver/readme.txt


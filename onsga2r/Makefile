# onsga2r stuffs
CC 		:= gcc
MCC		:= mcc
INCLUDES 	:= $(wildcard src/*.h)
COMMON_FILES 	:= allocate.c auxiliary.c crossover.c crowddist.c decode.c display.c\
			dominance.c eval.c fillnds.c initialize.c list.c merge.c misc.c\
			mutation.c opposition.c poplist.c problemdef.c rand.c rank.c\
			report.c sort.c tourselect.c vecutils.c
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

.PHONY: clean all wfg sosolv

all: onsga2r onsga2rso onsga2rw nsga2re nsga2rew nsga2r onsga2rwdom onsga2rdi onsga2rdr
wfg: wfg-1.10/wfg
whv: whv-pisa/hyp_ind
sosolv: $(SOSOLVEROBJ)

onsga2r: $(OBJ) src/onsga2r.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip onsga2r

onsga2rso: $(OBJ) src/onsga2rso.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip onsga2rso

onsga2rw: $(OBJ) src/onsga2rw.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip onsga2rw

onsga2rwdom: $(OBJ) src/onsga2rwdom.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip onsga2rwdom

onsga2rdi: $(OBJ) src/onsga2rdi.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip onsga2rdi

onsga2rdr: $(OBJ) src/onsga2rdr.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip onsga2rdr

nsga2re: $(OBJ) src/nsga2re.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip nsga2re

nsga2rew: $(OBJ) src/nsga2rew.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip nsga2rew

nsga2r: $(OBJ) src/nsga2r.o src/sosolver.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(MLDFLAGS)
	strip nsga2r

src/onsga2r.o: src/onsga2r.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/onsga2rso.o: src/onsga2rso.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/onsga2rw.o: src/onsga2rw.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/onsga2rwdom.o: src/onsga2rwdom.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/onsga2rdi.o: src/onsga2rdi.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/onsga2rdr.o: src/onsga2rdr.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/nsga2re.o: src/nsga2re.c
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

src/nsga2rew.o: src/nsga2rew.c
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
	cp wfg-1.10/wfg .

whv-pisa/hyp_ind: whv-pisa/premo_wdfs.c whv-pisa/hyp_ind.c
	$(CC) -g -Wall -pedantic -std=gnu99 -I/whv-pisa/premo_wdfs.h $^ -o $@ $(LDFLAGS)
	cp whv-pisa/hyp_ind whv

-include $(DEPS)

clean:
	rm -f src/*.d
	rm -f src/*.gc*
	rm -f $(OBJ) src/*.o src/sosolver/*.o
	rm -f onsga2r onsga2rso onsga2rw nsga2re nsga2rew nsga2r onsga2rwdom onsga2rdi onsga2rdr
	rm -f *.out
	rm -f *~
	rm -f \#*\#
	rm -f input_data/*~
	rm -f input_data/\#*\#

clean-sosolv:
	rm -rf src/sosolver/libsosolver.*
	rm -rf src/sosolver/mcc*
	rm -f src/sosolver/readme.txt

clean-all: clean
	rm -f wfg-1.10/*.o wfg-1.10/wfg wfg
	rm -f whv-pisa/*.o whv-pisa/hyp_ind whv

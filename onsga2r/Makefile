# onsga2r stuffs
cc			:= gcc
cxx			:= g++
common 		:= allocate.c auxiliary.c crossover.c crowddist.c decode.c display.c\
				dominance.c eval.c fillnds.c initialize.c list.c localsearch.c\
				merge.c misc.c mutation.c poplist.c problemdef.c rand.c rank.c\
				report.c sort.c tourselect.c vecutils.c
commonsrc	:= $(addprefix src/,$(common))
cflag 		:= -g -Wall -pedantic -std=gnu99
cxxflag 	:= -g -Wall -pedantic -std=c++11
ldflag		:= -lm
commonobj 	:= $(patsubst %c,%o,$(commonsrc))
deps		:= $(commonobj:.o=.d)
# wfg hv code stuffs
wfghvsrc	:= $(wildcard wfg-1.10/*.c)
wfghvobj	:= $(patsubst %c,%o,$(wfghvsrc))
wfghvdeps	:= $(wfghvobj:.o=.d)
# wfg problem suite stuffs
wfgsrc		:= $(wildcard src/wfg-suite/Toolkit/*.cpp)
wfgobj 		:= $(patsubst %cpp,%o,$(wfgsrc))
wfgdeps		:= $(wfgobj:.o=.d)

.PHONY: all test debug

all: nsga2r onsga2r nsga2re onsga2rw onsga2rwdom computehv

test: nsga2r wfg

debug:
	$(info $$wfgsrc: ${wfgsrc})
	$(info $$wfgobj: ${wfgobj})
	$(info $$wfgdeps: ${wfgdeps})
	$(info $$commonsrc: ${commonsrc})
	$(info $$commonobj: ${commonobj})
	$(info $$deps: ${deps})

onsga2r: $(commonobj) $(wfgobj) src/onsga2r.o
	$(cxx) $(cxxflag) $^ -o $@ $(ldflag)
	strip onsga2r

onsga2rw: $(commonobj) $(wfgobj) src/onsga2rw.o
	$(cxx) $(cxxflag) $^ -o $@ $(ldflag)
	strip onsga2rw

onsga2rwdom: $(commonobj) $(wfgobj) src/onsga2rwdom.o
	$(cxx) $(cxxflag) $^ -o $@ $(ldflag)
	strip onsga2rwdom

nsga2r: $(commonobj) $(wfgobj) src/nsga2r.o
	$(cxx) $(cxxflag) $^ -o $@ $(ldflag)
	strip nsga2r

nsga2re: $(commonobj) $(wfgobj) src/nsga2re.o
	$(cxx) $(cxxflag) $^ -o $@ $(ldflag)
	strip nsga2re

src/onsga2r.o: src/onsga2r.c
	$(cc) $(cflag) -c $< -o $@

src/onsga2rw.o: src/onsga2rw.c
	$(cc) $(cflag) -c $< -o $@

src/onsga2rwdom.o: src/onsga2rwdom.c
	$(cc) $(cflag) -c $< -o $@

src/nsga2r.o: src/nsga2r.c
	$(cc) $(cflag) -c $< -o $@

src/nsga2re.o: src/nsga2re.c
	$(cc) $(cflag) -c $< -o $@

%.o: %.c
	$(cc) $(cflag) -I./src/wfg-suite/Toolkit -c $< -o $@

# wfg hv executable recipe
computehv: $(wfghvobj)
	$(cc) $(cflag) $^ -o $@ $(ldflag)
	strip $@

wfg-1.10/%.o: wfg-1.10/%.c
	$(cc) $(cflag) -c $< -o $@ $(ldflag)

# wfg test-suite recipe
src/wfg-suite/Toolkit/%.o: src/wfg-suite/Toolkit/%.cpp
	$(cxx) $(cxxflag) -c $< -o $@

-include $(deps)
-include $(wfgdeps)

clean: clean-exp clean-wfg-hv clean-wfg-suite

clean-exp:
	rm -f src/*.gc*
	rm -f $(commonobj) src/*.o
	rm -f onsga2r onsga2rw onsga2rwdom nsga2re nsga2r
	rm -f *.out
	rm -f *~
	rm -f \#*\#
	rm -f input_data/*~
	rm -f input_data/\#*\#

clean-wfg-hv:
	rm -f wfg-1.10/*.o wfg

clean-wfg-suite:
	rm -f $(wfgobj)


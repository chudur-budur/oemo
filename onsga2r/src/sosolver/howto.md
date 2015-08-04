howto
=====

mcc -B csharedlib:libsosolver *.m -v

mbuild test.c libsosolver.so -v

howto
=====

This file shows how to compile the matlab implementation of finding extreme solutions on the true pareto-front.

1. To make the `libsosolver.so`, `libsosolver.c` and `libsosolver.h`:
```
user@pc:~$ mcc -B csharedlib:libsosolver *.m -v
```

2. To compile the tester:
```
user@pc:~$ mbuild test.c libsosolver.so -v
```

3. You may need to specify the dynamic shared lib path:
```
user@pc:~$ LD_LIBRARY_PATH="$LD_LIBRARY_PATH:." ./test
```

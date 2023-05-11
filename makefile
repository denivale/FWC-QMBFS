#CC	= g++
CC	= gcc
CFLAGS	= -Wall
#LDFLAGS	= -L/usr/local/lib/ -lgsl -lgslcblas -lm
LDFLAGS	= -lm -Wno-deprecated 
EXEC	= run test_index test_comb test_point test_operator
#DEPS	= line.h operator.h phase.h point.h shalloc.h wick.h
#SRC	= line.c operator.c phase.c point.c shalloc.c wick.c main.c 
DEPS	= combinatorics.h line.h point.h operator.h shalloc.h canonical.h contraction.h draw.h reading.h transindex.h calc_wick.h latex.h output.h kronecker.h preparation.h calculation.h
SRC	= combinatorics.c line.c point.c operator.c shalloc.c main.c canonical.c contraction.c draw.c reading.c transindex.c calc_wick.c latex.c output.c kronecker.c full_contraction.c preparation.c calculation.c

DEPS_TEST1	= operator.h reading.h transindex.h shalloc.h
SRC_TEST1	= operator.c reading.c transindex.c shalloc.c test_index.c 

DEPS_TEST2	= shalloc.h combinatorics.h
SRC_TEST2	= shalloc.c combinatorics.c test_comb.c

DEPS_TEST3	= point.h operator.h
SRC_TEST3	= point.c operator.c test_point.c

DEPS_TEST4	= operator.h
SRC_TEST4	= operator.c test_operator.c

all:	$(EXEC)

run:	$(DEPS) $(SRC)
  $(CC) -o $@ $(SRC) $(CFLAGS) $(LDFLAGS)

test_index:	$(DEPS_TEST1) $(SRC_TEST1)
  $(CC) -o $@ $(SRC_TEST1) $(CFLAGS) $(LDFLAGS)

test_comb:	$(DEPS_TEST2) $(SRC_TEST2)
  $(CC) -o $@ $(SRC_TEST2) $(CFLAGS) $(LDFLAGS)

test_point:	$(DEPS_TEST3) $(SRC_TEST3)
  $(CC) -o $@ $(SRC_TEST3) $(CFLAGS) $(LDFLAGS)

test_operator:	$(DEPS_TEST4) $(SRC_TEST4)
  $(CC) -o $@ $(SRC_TEST4) $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *~

mrproper: clean
	rm -rf $(EXEC)

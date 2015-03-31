# To run with valgrind:
V =
# V = valgrind -q

# Linux test coverage
CC = gcc
CFLAGS = -O2 -fprofile-arcs -ftest-coverage \
    	-Wall -W -Wshadow -Wmissing-prototypes -Wstrict-prototypes \
    	-Wredundant-decls -Wnested-externs -Wdisabled-optimization -ansi \
	-Wno-unused-parameter -I../Include -I../Demo

<<<<<<< HEAD
ex: $(CS) cs_ex2.1 cs_ex2.2 cs_ex2.3 cs_ex2.4 cs_ex2.5 test_cs_expand
=======
ex: $(CS) cs_ex2.1 cs_ex2.2 cs_ex2.3 cs_ex2.4 cs_ex2.5
>>>>>>> 2bf6615f0b36fdcc8d712bfd6fd96eb37dbac007
	find . -name "*.gcda" | xargs -r rm
	find . -name "*.gcov" | xargs -r rm

run: all run1 runbook run3 runtest
	./covall

all: cs_demo1 cs_demo2 cs_demo3 cstcov_test 

CS = cs_add.o cs_amd.o cs_chol.o cs_cholsol.o cs_counts.o cs_cumsum.o \
	cs_droptol.o cs_dropzeros.o cs_dupl.o cs_entry.o \
	cs_etree.o cs_fkeep.o cs_gaxpy.o cs_happly.o cs_house.o cs_ipvec.o \
	cs_lsolve.o cs_ltsolve.o cs_lu.o cs_lusol.o cs_util.o cs_multiply.o \
	cs_permute.o cs_pinv.o cs_post.o cs_pvec.o cs_qr.o cs_qrsol.o \
	cs_scatter.o cs_schol.o cs_sqr.o cs_symperm.o cs_tdfs.o \
	cs_transpose.o cs_compress.o cs_usolve.o cs_scc.o cs_maxtrans.o \
	cs_dmperm.o cs_updown.o cs_print.o cs_norm.o cs_load.o cs_dfs.o \
	cstcov_malloc_test.o cs_utsolve.o cs_reach.o cs_spsolve.o cs_ereach.o \
	cs_leaf.o cs_randperm.o \
<<<<<<< HEAD
	cs_expand.o \
=======
>>>>>>> 2bf6615f0b36fdcc8d712bfd6fd96eb37dbac007
	cs_entry_submatrix.o cs_gatxpy.o cs_gaxpy_symm.o cs_find.o cs_scale.o

CS_EX = cs_ex2.1 cs_ex2.2

$(CS): ../Include/cs.h cstcov_malloc_test.h

.PRECIOUS: cs_%.c cs_dem%.c cs_ex%.c

cs_dem%.c:
	- ln -s ../Demo/$@

<<<<<<< HEAD
cs_expand.c:
	- ln -s ../Source/$@

test_cs_expand.c:
	- ln -s ../Demo/$@	
=======
#cs_expand.c:
#	- ln -s ../Source/$@
>>>>>>> 2bf6615f0b36fdcc8d712bfd6fd96eb37dbac007

cs_ex%.c:
	- ln -s ../Demo/$@

cs_%.c:
	- ln -s ../Source/$@

cs_demo1: $(CS) cs_demo1.c
	$(CC) $(CFLAGS) -o cs_demo1 cs_demo1.c $(CS) -lm

cs_demo2: $(CS) cs_demo2.c cs_demo.c
	$(CC) $(CFLAGS) -o cs_demo2 cs_demo2.c cs_demo.c $(CS) -lm

cs_demo3: $(CS) cs_demo3.c cs_demo.c
	$(CC) $(CFLAGS) -o cs_demo3 cs_demo3.c cs_demo.c $(CS) -lm

<<<<<<< HEAD
test_cs_expand: $(CS) test_cs_expand.c
	$(CC) $(CFLAGS) -o test_cs_expand test_cs_expand.c $(CS) -lm

=======
>>>>>>> 2bf6615f0b36fdcc8d712bfd6fd96eb37dbac007
cs_ex2.1: $(CS) cs_ex2.1.c
	$(CC) $(CFLAGS) -o cs_ex2.1 cs_ex2.1.c $(CS) -lm

cs_ex2.2: $(CS) cs_ex2.2.c
	$(CC) $(CFLAGS) -o cs_ex2.2 cs_ex2.2.c $(CS) -lm

cs_ex2.3: $(CS) cs_ex2.3.c
	$(CC) $(CFLAGS) -o cs_ex2.3 cs_ex2.3.c $(CS) -lm

cs_ex2.4: $(CS) cs_ex2.4.c
	$(CC) $(CFLAGS) -o cs_ex2.4 cs_ex2.4.c $(CS) -lm
	
cs_ex2.5: $(CS) cs_ex2.5.c
	$(CC) $(CFLAGS) -o cs_ex2.5 cs_ex2.5.c $(CS) -lm
	
cstcov_test: $(CS) cstcov_test.c cs_demo.c
	$(CC) $(CFLAGS) -o cstcov_test cstcov_test.c cs_demo.c $(CS) -lm

# tiny tests
run1: all
	- $(V) ./cs_demo1 < nil
	- $(V) ./cs_demo1 < zero
	- $(V) ./cs_demo2 < nil
	- $(V) ./cs_demo2 < zero
	- $(V) ./cs_demo3 < nil

# test coverage for book:
runbook: all
	- $(V) ./cs_demo1 < ../Matrix/t1
	- $(V) ./cs_demo2 < ../Matrix/bcsstk01
	- $(V) ./cs_demo2 < ../Matrix/fs_183_1
	- $(V) ./cs_demo2 < ../Matrix/mbeacxc
	- $(V) ./cs_demo2 < ../Matrix/west0067
	- $(V) ./cs_demo2 < ../Matrix/lp_afiro
	- $(V) ./cs_demo3 < ../Matrix/bcsstk16

# other tests
run3: all
	- $(V) ./cs_demo2 < ../Matrix/t1
	- $(V) ./cs_demo2 < ../Matrix/ash219
	- $(V) ./cs_demo3 < ../Matrix/bcsstk01
	- $(V) ./cs_demo2 < ../Matrix/bcsstk16
	- $(V) ./cs_demo2 < ../Matrix/ibm32a
	- $(V) ./cs_demo2 < ../Matrix/ibm32b

# exhaustive memory tests
runtest: all
	- $(V) ./cstcov_test nil > test_nil.out
	- $(V) ./cstcov_test zero > test_zero.out
	- $(V) ./cstcov_test ../Matrix/t1 > test_t1.out
	- $(V) ./cstcov_test ../Matrix/bcsstk01 > test_k1.out
	- $(V) ./cstcov_test ../Matrix/fs_183_1 > test_fs.out
	- $(V) ./cstcov_test ../Matrix/west0067 > test_we.out
	- $(V) ./cstcov_test ../Matrix/ash219 > test_ash.out
	- $(V) ./cstcov_test ../Matrix/lp_afiro > test_afiro.out

readhb: readhb.f
	f77 -o readhb readhb.f

readhb.f:
	- ln -s readhb.f

clean:
	- $(RM) *.o *.bbg *.da *.gcov *.gcda *.gcno

purge: distclean

# remove everything for distribution, including all symbolic links
distclean: clean
	- $(RM) cs_demo1 cs_demo2 readhb *.out *.a cs_demo3 cstcov_test cov.sort
	- $(RM) -r cs_*.c *.dSYM

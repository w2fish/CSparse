# To run with valgrind:
V =
# V = valgrind -q

# Linux test coverage
CC = gcc
CFLAGS = -g -fprofile-arcs -ftest-coverage \
    	-Wall -W -Wshadow -Wmissing-prototypes -Wstrict-prototypes \
    	-Wredundant-decls -Wnested-externs -Wdisabled-optimization -ansi \
	-Wno-unused-parameter -I../Include -I../Demo

ex: $(CS) cs_ex2.1 cs_ex2.2 cs_ex2.3 cs_ex2.4 cs_ex2.5 \
	cs_ex2.6 cs_ex2.7 cs_ex2.8 cs_ex2.9 cs_ex2.10 \
	cs_ex2.11 cs_ex2.12 cs_ex2.13 cs_ex2.14 cs_ex2.15 \
	cs_ex2.16 cs_ex2.18 cs_ex2.19 cs_ex2.20 cs_ex2.21 \
	cs_ex2.22 cs_ex2.23 cs_ex2.24 cs_ex2.25 cs_ex2.26 \
	test_cs_expand test_create_fileMatrix
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
	cs_expand.o \
	cs_band.o cs_compress2.o cs_copy.o cs_dot.o \
	cs_entry_submatrix.o cs_gatxpy.o cs_gaxpy_symm.o cs_gaxpy_triplet.o \
	cs_find.o cs_hcat.o \
	cs_issorted.o cs_issym.o cs_multiply2.o cs_multiply3.o \
	cs_ok.o cs_permtranspose.o cs_saxpy.o cs_scale.o \
	cs_scatter2.o cs_sort.o cs_sort2.o \
	cs_sort_fast.o cs_sort_slow.o cs_spcolm.o cs_subm.o cs_subm2.o \
	cs_subm3.o \
	cs_transpose_triplet.o \
	cs_vcat.o \
	util_compare_double.o

CS_EX = cs_ex2.1 cs_ex2.2

$(CS): ../Include/cs.h cstcov_malloc_test.h

.PRECIOUS: cs_%.c cs_dem%.c cs_ex%.c

cs_dem%.c:
	- ln -s ../Demo/$@

cs_expand.c:
	- ln -s ../Source/$@

test_%.c:
	- ln -s ../Demo/$@	

cs_ex%.c:
	- ln -s ../Demo/$@

cs_%.c:
	- ln -s ../Source/$@

util_%.c:
	- ln -s ../Source/$@

cs_demo1: $(CS) cs_demo1.c
	$(CC) $(CFLAGS) -o cs_demo1 cs_demo1.c $(CS) -lm

cs_demo2: $(CS) cs_demo2.c cs_demo.c
	$(CC) $(CFLAGS) -o cs_demo2 cs_demo2.c cs_demo.c $(CS) -lm

cs_demo3: $(CS) cs_demo3.c cs_demo.c
	$(CC) $(CFLAGS) -o cs_demo3 cs_demo3.c cs_demo.c $(CS) -lm

test_cs_expand: $(CS) test_cs_expand.c
	$(CC) $(CFLAGS) -o test_cs_expand test_cs_expand.c $(CS) -lm

test_create_fileMatrix: test_create_fileMatrix.c
	$(CC) $(CFLAGS) -o test_create_fileMatrix test_create_fileMatrix.c

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
	
cs_ex2.6: $(CS) cs_ex2.6.c
	$(CC) $(CFLAGS) -o cs_ex2.6 cs_ex2.6.c $(CS) -lm
	
cs_ex2.7: $(CS) cs_ex2.7.c
	$(CC) $(CFLAGS) -o cs_ex2.7 cs_ex2.7.c $(CS) -lm
	
cs_ex2.8: $(CS) cs_ex2.8.c
	$(CC) $(CFLAGS) -o cs_ex2.8 cs_ex2.8.c $(CS) -lm
	
cs_ex2.9: $(CS) cs_ex2.9.c
	$(CC) $(CFLAGS) -o cs_ex2.9 cs_ex2.9.c $(CS) -lm
	
cs_ex2.10: $(CS) cs_ex2.10.c
	$(CC) $(CFLAGS) -o cs_ex2.10 cs_ex2.10.c $(CS) -lm
	
cs_ex2.11: $(CS) cs_ex2.11.c
	$(CC) $(CFLAGS) -o cs_ex2.11 cs_ex2.11.c $(CS) -lm
	
cs_ex2.12: $(CS) cs_ex2.12.c
	$(CC) $(CFLAGS) -o cs_ex2.12 cs_ex2.12.c $(CS) -lm
	
cs_ex2.13: $(CS) cs_ex2.13.c
	$(CC) $(CFLAGS) -o cs_ex2.13 cs_ex2.13.c $(CS) -lm
	
cs_ex2.14: $(CS) cs_ex2.14.c
	$(CC) $(CFLAGS) -o cs_ex2.14 cs_ex2.14.c $(CS) -lm
	
cs_ex2.15: $(CS) cs_ex2.15.c
	$(CC) $(CFLAGS) -o cs_ex2.15 cs_ex2.15.c $(CS) -lm
	
cs_ex2.16: $(CS) cs_ex2.16.c
	$(CC) $(CFLAGS) -o cs_ex2.16 cs_ex2.16.c $(CS) -lm
	
cs_ex2.18: $(CS) cs_ex2.18.c
	$(CC) $(CFLAGS) -o cs_ex2.18 cs_ex2.18.c $(CS) -lm
	
cs_ex2.19: $(CS) cs_ex2.19.c
	$(CC) $(CFLAGS) -o cs_ex2.19 cs_ex2.19.c $(CS) -lm
	
cs_ex2.20: $(CS) cs_ex2.20.c
	$(CC) $(CFLAGS) -o cs_ex2.20 cs_ex2.20.c $(CS) -lm
	
cs_ex2.21: $(CS) cs_ex2.21.c
	$(CC) $(CFLAGS) -o cs_ex2.21 cs_ex2.21.c $(CS) -lm
	
cs_ex2.22: $(CS) cs_ex2.22.c
	$(CC) $(CFLAGS) -o cs_ex2.22 cs_ex2.22.c $(CS) -lm
	
cs_ex2.23: $(CS) cs_ex2.23.c
	$(CC) $(CFLAGS) -o cs_ex2.23 cs_ex2.23.c $(CS) -lm
	
cs_ex2.24: $(CS) cs_ex2.24.c
	$(CC) $(CFLAGS) -o cs_ex2.24 cs_ex2.24.c $(CS) -lm
	
cs_ex2.25: $(CS) cs_ex2.25.c
	$(CC) $(CFLAGS) -o cs_ex2.25 cs_ex2.25.c $(CS) -lm
	
cs_ex2.26: $(CS) cs_ex2.26.c
	$(CC) $(CFLAGS) -o cs_ex2.26 cs_ex2.26.c $(CS) -lm
	
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
	- $(RM) *.o *.bbg *.da *.gcov *.gcda *.gcno cs_* test_*  \
	        *.exe .*.un~ *~ Makefile~ .*.swp
	- $(RM) ../Demo/.*.un~ ../Demo/*.c~
	- $(RM) ../Source/.*.un~ ../Source/cs_*.c~
	- $(RM) ../Include/.*.un~ ../Include/cs.h~

purge: distclean

# remove everything for distribution, including all symbolic links
distclean: clean
	- $(RM) cs_demo1 cs_demo2 readhb *.out *.a cs_demo3 cstcov_test cov.sort
	- $(RM) -r cs_*.c *.dSYM


.PHONY = all clean
FLAGS = -O2 -I/usr/include/eigen3

%.o: %.cc %.h
	clang++ ${FLAGS} -c $< -o $@

verify: ../carfac.o ../ear.o log_sql.o verify.o
	clang++ ${FLAGS} $^ -o $@ -lvsqlitepp -lfmt

all: verify

clean:
	rm -f *.o ../*.o verify verify.db

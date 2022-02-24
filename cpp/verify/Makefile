
.PHONY = all clean
FLAGS = -O2 -I/usr/include/eigen3

%.o: %.cc
	c++ -DSQLITE3_VERIFY=1 ${FLAGS} -c $< -o $@

verify: ../carfac.o ../ear.o log_sql.o verify.o
	c++ ${FLAGS} $^ -o $@ -lvsqlitepp -lfmt

all: verify

clean:
	rm -f *.o ../*.o verify verify.db

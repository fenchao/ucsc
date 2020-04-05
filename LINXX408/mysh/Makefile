VPATH=./src

all: run clean

man_mysh:
	groff -man -Tascii ./man_pages/mysh.1 | more
man_mycat:
	groff -man -Tascii ./man_pages/mycat.1 | more
man_mywc:
	groff -man -Tascii ./man_pages/mywc.1 | more
man_myls:
	groff -man -Tascii ./man_pages/myls.1 | more

run: mysh 
	./mysh

#mycat : mycat.c
#	gcc -c mycat.c
#myls : myls.c
#	gcc -c myls.c
#mywc : mywc.c
#	gcc -c mywc.c
mysh : mysh.o myls.o mywc.o mycat.o
	gcc -o mysh mysh.o myls.o mywc.o mycat.o

clean:
	rm -f my*.o mysh

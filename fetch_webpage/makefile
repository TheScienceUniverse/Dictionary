a.out : helper.o helper.h main.c
	gcc helper.o main.c

helper.o : helper.h helper.c
	gcc -c helper.c

filter : filter.c
	gcc -o filter filter.c

clean :
	rm *.o a.out
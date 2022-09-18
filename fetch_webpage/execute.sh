rm filter
gcc -o filter filter.c

make clean
make

./a.out words.txt 2>&1 | tee output.log
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BYTE unsigned char

unsigned char W [50];	// Word
int lW = 0;				// Length of Word

BYTE state_transition (BYTE, BYTE);

/*
State Transition Table:

	+---+---+---+---+---+---+---+---+---+
	| <	| /	| m	| a	| i	| n	| 	| >	| X	|
+---+---+---+---+---+---+---+---+---+---+
| 0	| 1   0   0   0   0   0   0   0   0	|
+---+									+
| 1	| 0   2   3   0   0   0   0   0   0	|
+---+									+
| 2	| 0   0   3   0   0   0   0   0   0	|
+---+									+
| 3	| 0   0   0   4   0   0   0   0   0	|
+---+									+
| 4	| 0   0   0   0   5   0   0   0   0	|
+---+									+
| 5	| 0   0   0   0   0   6   0   0   0	|
+---+									+
| 6	| 0   0   0   0   0   0   7   8   0	|
+---+									+
| 7	| 7   7   7   7   7   7   7   8   7	|
+---+-----------------------------------+

*/

BYTE transition_table [8][9] = {
	{1, 0, 0, 0, 0, 0, 0, 0, 0}
	, {0, 2, 3, 0, 0, 0, 0, 0, 0}
	, {0, 0, 3, 0, 0, 0, 0, 0, 0}
	, {0, 0, 0, 4, 0, 0, 0, 0, 0}
	, {0, 0, 0, 0, 5, 0, 0, 0, 0}
	, {0, 0, 0, 0, 0, 6, 0, 0, 0}
	, {0, 0, 0, 0, 0, 0, 7, 8, 0}
	, {7, 7, 7, 7, 7, 7, 7, 8, 7}
};


int main (int argc, char *argv[]) {
	if (argc < 3) {
		perror ("File not specified!\n");
		exit (1);
	}

	BYTE c;
	FILE *fpi = fopen (argv[1], "rb+");

	if (fpi == NULL) {
		perror ("Can't open input file!\n");
		exit (1);
	}

	FILE *fpo = fopen (argv[2], "wb+");

	if (fpo == NULL) {
		perror ("Can't open output file!\n");
		exit (1);
	}

	fprintf (fpo, "<main");

	fseek (fpi, 1, SEEK_END);
	// unsigned long f_ic = 0;		// File Index Counter
	long f_sz = ftell (fpi);	// File SiZe
	//printf ("File Size: %ld bytes.\n", f_sz);
	rewind (fpi);
	
	long i;
	BYTE state = 0;
	ssize_t sz;
	bool flag_copy = false;

	for (i = 0; i < f_sz; i++) {
		sz = fread (&c, 1, 1, fpi);
		state = state_transition (state, c);
		//printf ("%c %d\n", c, state);

		if (state == 8) {
			flag_copy = !flag_copy;
		}

		if (flag_copy) {
			fwrite (&c, 1, 1, fpo);
		}
	}

	fprintf (fpo, ">");

	fclose (fpo);
	fclose (fpi);

	return 0;
}

BYTE state_transition (BYTE current_state, BYTE symbol) {
	BYTE next_state = 0;
	BYTE symbol_index = 0;

	switch (symbol) {
		case '<':
			symbol_index = 0;
			break;
		case '/':
			symbol_index = 1;
			break;
		case 'm':
			symbol_index = 2;
			break;
		case 'a':
			symbol_index = 3;
			break;
		case 'i':
			symbol_index = 4;
			break;
		case 'n':
			symbol_index = 5;
			break;
		case ' ':
			symbol_index = 6;
			break;
		case '>':
			symbol_index = 7;
			break;
		default:
			symbol_index = 8;
			break;
	}

	next_state = transition_table [current_state][symbol_index];

	return next_state;
}
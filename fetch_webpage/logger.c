#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BYTE unsigned char

void print_string (int length, char string[]) {
	for (int i = 0; i < length; i++) {
		printf ("%c", string [i]);
	}
}

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

	fseek (fpi, 1, SEEK_END);
	// unsigned long f_ic = 0;		// File Index Counter
	long f_sz = ftell (fpi);	// File SiZe
	//printf ("File Size: %ld bytes.\n", f_sz);
	rewind (fpi);
	
	long i;
	BYTE state = 0;
	ssize_t sz;
	bool flag_copy = false;

	char word [50], status [50];
	int word_index = 0, status_index = 0;
	BYTE flag = 0;

	word [word_index] = 0;
	status [status_index] = 0;

	for (i = 0; i < f_sz; i++) {
		sz = fread (&c, 1, 1, fpi);

		if (c == ' ' || c == '\n') {
			++ flag;
		}

		if (flag == 0) {
			word [word_index ++] = c;
			word [word_index] = 0;
		} else if (flag == 1) {
			word [word_index ++] = 0;
		} else if (flag == 2 && c != ' ' && c != '\n') {
			status [status_index ++] = c;
			status [status_index] = 0;
		} else if (flag == 3) {
			if (status [0] == 'S') {
				status [strlen (status)] = '\0';
				fprintf (fpo, "[%s]\t:\t%s\n", status, word);
			} else {
				fprintf (fpo, "[%s]\t\t:\t%s\n", status, word);
			}

			word_index = 0;
			status_index = 0;
			flag = 0;

			while (c != '\n') {
				sz = fread (&c, 1, 1, fpi);
				++i;
			}
		}
	}

	fclose (fpo);
	fclose (fpi);

	return 0;
}
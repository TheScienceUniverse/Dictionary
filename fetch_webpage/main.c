#include "helper.h"

int main (int argc, char *argv[]) {
	if (argc < 2) {
		perror ("File not specified!\n");
		exit (1);
	}

	char W [WORD_MAX];	// Word
	int lW = 0;     // Length of Word
	char c;
	char buffer [BUFFER_MAX];
	int buffer_size = 0;

	FILE *fpi = fopen (argv[1], "rb+");
	if (fpi == NULL) {
		perror ("Can't open input file!\n");
		exit (1);
	}

	fseek (fpi, 1, SEEK_END);
	unsigned long f_ic = 0;		// File Index Counter
	long f_sz = ftell (fpi);	// File SiZe
	printf ("File Size: %ld bytes.\n", f_sz);

	long i;
	int j;
	size_t sz;
	rewind (fpi);
	String command;
	char *word;

	for (i = 0; i < f_sz; i++) {
		sz = fread (&c, 1, 1, fpi);

		if (c >= 0x61 && c <= 0x7a) {
			W [lW++] = c;
		} else if ((c < 0x61 || c > 0x7a) && (lW > 0)) {
			word = array_to_pointer (lW, W);
			//print_string_pointer (word);

			//command = concatenate_strings (2, "php fetch.php ", word);
			concatenate_strings (&buffer_size, buffer, 2, "php fetch.php ", word);
			// print_string_pointer (buffer);
			system (buffer);
			//free (command .container);

			concatenate_strings (&buffer_size, buffer, 3, "./output/", word, ".txt");

			if (access (buffer, F_OK) == 0) {
				concatenate_strings (&buffer_size, buffer, 5, "./filter ./output/", word, ".txt ./output/", word, ".html");
				//print_array (command);
				system (buffer);
				//free (command .container);

				concatenate_strings (&buffer_size, buffer, 3, "rm ./output/", word, ".txt");
				//print_string (command);
				system (buffer);
				//free (command .container);
			}

			lW = 0;
			free (word);
		}
	}

	printf ("********* DONE **********\n");

	fclose (fpi);
	// fclose(fpo);

	return 0;
}
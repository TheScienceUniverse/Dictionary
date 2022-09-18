#include "helper.h"

void print_string (String string) {
	for (int i = 0; i < string .length; i++) {
		printf ("%c", *(string .container + i));
	}

	printf ("\n");
}

void print_array (int length, char S[]) {
	for (int i = 0; i < length; i++) {
		printf ("%c", S [i]);
	}

	printf ("\n");
}

void print_string_pointer (char *string) {
	for (int i = 0; i < strlen (string); i++) {
		printf ("%c", *(string + i));
	}

	printf ("\n");
}

String concatenate_strings_faulty (int string_count, ...) {
	va_list string_list;
	char buffer [BUFFER_MAX];
	int buffer_index = 0, i;
	int string_index = 0, string_length = 0;
	char *string;

	String command;
	command .length = 0;
//	command .container = (char *) malloc (1);

	va_start (string_list, string_count);

	while (string_index < string_count) {
		string = va_arg (string_list, char *);
		string_length = strlen (string);

		for (i = 0; i < string_length; i++) {
			buffer [buffer_index ++] = *(string + i);
		}

		//command .length += string_length;

		//command .container = (char *) realloc (command .container, command .length);
		//strncat (command .container, string, string_length);

		/*i = buffer_index;

		while (i < BUFFER_MAX) {
			buffer [i++] = 0;
		}*/

		++ string_index;
	}

	buffer [buffer_index] = 0;

	command .container = (char *) malloc (buffer_index);

	//free (string);
	va_end (string_list);
	
	return command;
}

void concatenate_strings (int *buffer_size, char *buffer, int string_count, ...) {
	va_list string_list;
	int buffer_index = 0, i;
	int string_index = 0, string_length = 0;
	char *string;

	va_start (string_list, string_count);

	while (string_index < string_count) {
		string = va_arg (string_list, char *);
		string_length = strlen (string);

		for (i = 0; i < string_length; i++) {
			*(buffer + buffer_index ++) = *(string + i);
		}

		++ string_index;
	}

	va_end (string_list);

	buffer [buffer_index] = 0;
	*buffer_size = buffer_index;
}

char *array_to_pointer (int length, char S[]) {
	char *string = (char *) malloc (length + 1);

	for (int i = 0; i < length; i++) {
		*(string + i) = S [i];
	}

	*(string + length) = '\0';

	return string;
}
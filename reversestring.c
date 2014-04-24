/*
 * reversestring.c
 *
 * MIT Hacking a Google Interview Handout 2
 * Question: Create a function that reverses the order of words of a
 * string in place (complete words, not simply reversing the entire array
 * of characters; e.g. convert "the quick fox jumped" into "jumped fox
 * quick the").
 * Solution: first reverse the entire string, swapping the first with the
 * last character, the second with the second-to-last, etc. Then look for
 * whitespace, to find where the words begin and end. Put the words in the
 * correct order by again reversing, but this time word by word.
 *
 * Input: to have the program read the character string in a single array,
 * pass it enclosed in quotes, e.g.
 *     $> ./hgi_reverse "the quick fox jumped"
 * Otherwise it will read in 4 separate strings, one for each word.
 */
#include <stdio.h>
#include <stdlib.h>

int stringlen(char *);
int swapchars(char *, int, int, int);


int main(int argc, char **argv)
{
	int i, size, check, first, last;
	char temp;


	/* Input section: read the string input by the user, checking that the
	   user actually did input something */
	if (argc < 2) {
		fprintf(stderr, "Error: no string given - Exit\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	if (argc > 2) {
		fprintf(stderr, "Error: please enter the string enclosed in "
				"quotation marks - Exit\n"); fflush(stderr);
		exit(EXIT_FAILURE);
	}

	/* First step: reverse the entire string. To swap the first character
	   with the last one etc. we first need to determine how long the
	   string is. That is done by strlen provided by string.h, but let's
	   suppose we're not allowed to use that. In that case, the function
	   stringlen defined below will do the trick */
	size = stringlen(*(argv+1));
	printf("Size of input string: %d\n", size); fflush(stdout);

	check = swapchars(*(argv+1), size, 0, size-1);
	if (check < 0) {
		fprintf(stderr, "Error: could not reverse input string - Exit\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	printf("Inverted string: %s\n", *(argv+1)); fflush(stdout);

	/* Step two: find out where words begin and end to put them back in
	   the proper order */
	first = 0;
	for (i=0; i<=size; i++) {
		if (argv[1][i] == ' ' || argv[1][i] == '\0') {
			last = i-1;
			printf("%d %d\n", first, last);
			check = swapchars(*(argv+1), size, first, last);
			first = i+1;
		}
	}
	printf("With words in proper order: %s\n", *(argv+1)); fflush(stdout);

	return EXIT_SUCCESS;
}


/*
 * Returns the length of the string. This is apparently more efficient
 * than just going over the entire character array looking for the '\0'
 * string terminator
 */
int stringlen(char *str)
{
	char *s;

	for (s=str; *s; ++s);
	return (s - str);
}


/*
 * Invert the order of the characters in an array of given size between
 * indices first and last. Returns 0 on success, -1 if an error occurs
 */
int swapchars(char *str, int size, int first, int last)
{
	int i, j;
	char temp;

	if (first > last || last >= size) {
		fprintf(stderr, "Error (swapchars): invalid indices given\n");
		fflush(stderr);
		return -1;
	}
	if (first == last) return 0; /* Nothing to do */

	for (i=first, j=last; i<=first+(last-first)/2; i++, j--) {
			temp = str[i];
			str[i] = str[j];
			str[j] = temp;
	}

	return 0;
}

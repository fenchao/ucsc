#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Not enough arguments!\n");
	}

	// redirect stdin to input file
	close(0);
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		fprintf(stderr, "%s: No such file or directory.\n", argv[1]);
	}

	// redirect stdout to file
	close(1);
	FILE *output = fopen(argv[2], "w");

	int line = 0;
	char c;
	while((c = getchar()) != EOF) {
		putchar(c);
		if (c == '\n') {
			fprintf(stderr, "#%d copied.\n", line++);
		}
	}
	return 0;
}

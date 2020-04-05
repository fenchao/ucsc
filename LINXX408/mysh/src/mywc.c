#include <stdio.h>
#include <stdbool.h>

#define MAX_FILENAME 1024

int mywc(int argc, char *argv[]) {
	bool char_flag = false, word_flag = false, line_flag = false;
	char *filenames[MAX_FILENAME];
	int filenum = 0;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {	
			for (int j = 1; argv[i][j]; ++j) {
				switch(argv[i][j]) {
					case 'm':
						char_flag = true;
						break;
					case 'l':
						line_flag = true;
						break;
					case 'w':
						word_flag = true;
						break;
					default:
						fprintf(stderr, "'%s' is invalid option!\n", argv[i]);
						return -1;
				}
			}
		} else {
			if (filenum < MAX_FILENAME) {
				filenames[filenum++] = argv[i];
			} else {
				fprintf(stderr, "More input files than supported size %d.\n", MAX_FILENAME);
				break;
			}
		}
	}

	if (!(char_flag || word_flag || line_flag)) {
		char_flag = true;
		word_flag = true;
		line_flag = true;
	}

	for (int i = 0; i < filenum; ++i) {
		FILE *file = fopen(filenames[i], "r");
		if (file == NULL) {
			fprintf(stderr, "%s: No such file or directory.\n", filenames[i]);
		} else {
			int chars = 0, lines = 0, words = 0;
			char prev = 0, cur;
			while( (cur = fgetc(file)) != EOF) {
				++chars;
				if (cur == '\n') {
					++lines;
				}
				if (prev != ' ' && (cur == ' ' || cur == '\n')) {
					++words;
				}
				prev = cur;
			}
			fclose(file);
			if (line_flag) {
				printf(" %d", lines);
			}
			if (word_flag) {
				printf(" %d", words);
			}
			if (char_flag) {
				printf(" %d", chars);
			}
			printf(" %s\n", filenames[i]);
		}
	}

	return 0;
}

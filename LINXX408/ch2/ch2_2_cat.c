#include <stdio.h>
#include <stdbool.h>

#define MAX_FILENAME 1024

int main(int argc, char *argv[]) {
	bool line_flag = false;
	char *filenames[MAX_FILENAME];
	int filenum = 0;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {	
			for (int j = 1; argv[i][j]; ++j) {
				switch(argv[i][j]) {
					case 'l':
						line_flag = true;
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

	for (int i = 0; i < filenum; ++i) {
		FILE *file = fopen(filenames[i], "r");
		if (file == NULL) {
			fprintf(stderr, "%s: No such file or directory.\n", filenames[i]);
		} else {
			char line[1024];
			int line_num = 0;
			if (filenum > 1) {
				printf("%s:\n", filenames[i]);
			}
			while(fgets(line, sizeof(line), file) != NULL) {
				if (line_flag) {
					printf("%4d: ", line_num++);
				}
				printf("%s", line);
			}
			fclose(file);
		}
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

void ls_print(const char* path, bool option,
	      int nlink_indent, int size_indent,
	      int owner_indent, int group_indent) {
	if (!option) {
		printf("%s", path);
	} else {
		// long listing print
		struct stat file_stat;
		stat(path, &file_stat);
		mode_t mode = file_stat.st_mode;
		char *last_change = ctime(&file_stat.st_ctime);
		last_change[16] = '\0';
		printf(
			"%c%c%c%c%c%c%c%c%c%c %*ld %*s %*s %*ld %s %s",
			S_ISDIR(mode)  ? 'd' :
 			S_ISFIFO(mode) ? 'p' :
 			S_ISLNK(mode)  ? 'l' :
 			S_ISBLK(mode)  ? 'b' :
 			S_ISCHR(mode)  ? 'c' :
 			S_ISSOCK(mode) ? 's' :
 			S_ISREG(mode)  ? '-' :
		       	'!',
			(mode & S_IRUSR) ? 'r' : '-',
			(mode & S_IWUSR) ? 'w' : '-',
			(mode & S_IXUSR) ? 'x' : '-',
			(mode & S_IRGRP) ? 'r' : '-',
			(mode & S_IWGRP) ? 'w' : '-',
			(mode & S_IXGRP) ? 'x' : '-',
			(mode & S_IROTH) ? 'r' : '-',
			(mode & S_IWOTH) ? 'w' : '-',
			(mode & S_IXOTH) ? 'x' : '-',
			nlink_indent, file_stat.st_nlink,
			owner_indent, getpwuid(file_stat.st_uid)->pw_name,
			group_indent, getgrgid(file_stat.st_gid)->gr_name,
			size_indent, file_stat.st_size,
			&last_change[4],
			path
		);
	}
}

int myls(int argc, char *argv[]) {
	bool options[1] = {false}; // -l option only for now
	int path_num = argc - 1;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			--path_num;
			for (int j = 1; argv[i][j]; ++j) {
				switch(argv[i][j]) {
					case 'l':
						options[0] = true;
						break;
					default:
						fprintf(stderr, " illegal option: '%s'\n", argv[i]);
						return -1;
				}
			}
		}
	}

	struct stat file_stat;
	char **paths = (char **) malloc(path_num * sizeof(char *));
	path_num = 0;
	errno = 0;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] != '-') {	
			if (stat(argv[i], &file_stat) == 0) {
				paths[path_num++] = argv[i];
			} else {
				errno = ENOENT;
				perror(argv[i]);
			}
		}
	}

	// Default: current directory if no specific path
	if (!path_num && errno != ENOENT) {
		paths[path_num++] = ".";
	}

	for (int i = 0; i < path_num; ++i) {
		if (i) {
			printf("\n"); // extra line separator for different path
		}
		DIR *dr = opendir(paths[i]);
		if (dr == NULL) {
			// It's regular file
			ls_print(paths[i], options[0], 0, 0, 0, 0);
		} else {
			// It's directory
			printf("%s:\n", paths[i]);
			
			struct dirent *dp;

			// Get indents for formatting
			long max_st_size = 0, max_nlink = 0;
			int owner_indent = 0, group_indent = 0;
			while((dp = readdir(dr)) != NULL) {
				stat(dp->d_name, &file_stat);
				max_st_size = file_stat.st_size > max_st_size ? file_stat.st_size : max_st_size;
				max_nlink = file_stat.st_nlink > max_nlink ? file_stat.st_nlink : max_nlink;
				int len = strlen(getpwuid(file_stat.st_uid)->pw_name);
				owner_indent = len > owner_indent ? len : owner_indent;
				len = strlen(getgrgid(file_stat.st_gid)->gr_name);
				group_indent = len > group_indent ? len : group_indent;
			}
			int size_indent = 0;
			while (max_st_size) {
				++size_indent;
				max_st_size /= 10;
			}
			int nlink_indent = 0;
			while (max_nlink) {
				++nlink_indent;
				max_nlink /= 10;
			}

			// Print info for each path under directory
			rewinddir(dr);
			int prev_line_size = 0;
			while((dp = readdir(dr)) != NULL) {
				int file_name_size = strlen(dp->d_name);
				if (prev_line_size != 0) {
					#define MAX_LINE_SIZE 100
					if (options[0] || prev_line_size + file_name_size > MAX_LINE_SIZE) {
						printf("\n");
						prev_line_size = 0;
					} else {
						printf(" ");
					}
				}
				prev_line_size += file_name_size + 1;
				ls_print(dp->d_name, options[0], nlink_indent, size_indent, owner_indent, group_indent);
			}
			closedir(dr);
		}
		printf("\n");
	}

	free(paths);
	return 0;
}


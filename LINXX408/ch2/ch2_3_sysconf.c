#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Max # of open files: %ld\n", sysconf(_SC_OPEN_MAX));
	return 0;
}

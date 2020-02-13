#include <iostream>

using namespace std;

bool above_threshold(const char *line, int column, int threshold) {
    char buffer[20];
    int pos = 0;
    int i = 0;

    while (column && line[pos]) {
        if (line[pos] != ' ' && (pos == 0 || line[pos-1] == ' ')) {
            --column;
        }
        ++pos;
    }

    if (column) {
        cout << "Invalid Column" << endl;
        exit(1);
    }

    --pos;
    while(line[pos] != ' ' && line[pos] != '\n') {
        buffer[i] = line[pos];
        ++i;
        ++pos;
    }

    buffer[i] = '\0';

    return (atoi(buffer) > threshold);
}

// assume valid lines only have space or digits and are non-empty
bool valid_line(const char *line) {
    int pos = 0;
    while(line[pos] != '\n') {
        if (line[pos] != ' ' && (line[pos] < '0' || line[pos] > '9')) {
            return false;
        }
        ++pos;
    }
    return pos;
}

int main(int argc, const char *argv[]) {
    char line[100];
    int cur_n = 0;

    int column = atoi(argv[1]);
    int threshold = atoi(argv[2]);
    int n = atoi(argv[3]);

    while(fgets(line, 100, stdin) != NULL) {
        if (valid_line(line) && above_threshold(line, column, threshold)) {
            ++cur_n;
            if (cur_n == n) {
                // only report n consecutive times. keep quiet for > n
                cout << "Column " << column << " above threshold "
                     << threshold << " " << cur_n << " times." << endl;
            }
        } else {
            cur_n = 0;
        }
    }
    return 0;
}

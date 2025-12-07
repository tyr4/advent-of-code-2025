#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1000
#define max(a,b) ((a) > (b) ? (a) : (b))

int isSameDigits(int num) {
    // single digit case
    if (num == num % 10) return 0;

    int starting = num % 10;

    while (num) {
        if (num % 10 != starting) {
            return 0;
        }

        num /= 10;
    }

    return 1;
}

int getNumDigits(long num) {
    return (int)floor(log10(num)) + 1;
}

long getFirstHalf(long num) {
    char buff[50];

    // funny trick
    sprintf(buff, "%ld", num);
    // input 777 -> returns 77
    // input 7777 -> still returns 77
    buff[max(strlen(buff) & 1? strlen(buff) / 2 + 1 : strlen(buff) / 2, 1)] = '\0';

    return atol(buff);
}

long duplicateNumber(long num) {
    char buff[50];

    sprintf(buff, "%ld%ld", num, num);

    return atol(buff);
}

long duplicateToFill(int num, int len) {
    char buff[50] = "", charNum[10];

    sprintf(charNum, "%d", num);

    while (strlen(buff) < len) {
        strcat(buff, charNum);
    }

    return atol(buff);
}

long nextDigit(long num) {
    int len = getNumDigits(num);

    return (long)pow(10, len);
}

int main() {
    FILE *file = fopen("../input.txt", "r");
    char buff[BUFFER_SIZE], num[20];
    long leftId = 0, rightId = 0;
    long long sum = 0;

    if (!file) {
        perror("file");
        exit(1);
    }

    // the input is on a single line
    fgets(buff, BUFFER_SIZE, file);

    char *p = strtok(buff, ",");
    while (p) {
        // i hate strtok
        for (int i = 0; i < strlen(p); i++) {
            if (p[i] == '-') {
                // split the range like 11-22 in "11'\0'22'\0'"
                p[i] = '\0';

                strcpy(num, p);
                leftId = atol(num);

                strcpy(num, p + i + 1);
                rightId = atol(num);

                break;
            }
        }

        p = strtok(NULL, ",");

        while (leftId < rightId) {
            long rightFirstHalf = getFirstHalf(rightId);

            for (int i = 1; i <= rightFirstHalf; i++) {
                // avoid duplicates like filling with 1 and then with 11 producing
                // the same number
                if (isSameDigits(i)) continue;

                long duplicated = duplicateToFill(i, getNumDigits(leftId));

                if (duplicated >= leftId && duplicated <= rightId) {
                    sum += duplicated;
                }
                else if (duplicated > rightId) {
                    i = (int)nextDigit(i);
                }
            }

            leftId = nextDigit(leftId);
        }
    }

    printf("the sum is only %lld", sum);

    fclose(file);
    return 0;
}
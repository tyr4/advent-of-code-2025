#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1000
#define max(a,b) ((a) > (b) ? (a) : (b))

int getNumDigits(long num) {
    return (int)floor(log10(num)) + 1;
}

long getFirstHalf(long num) {
    char buff[50];

    // funny trick
    sprintf(buff, "%ld", num);
    buff[max(strlen(buff) / 2, 1)] = '\0';

    return atol(buff);
}

long mirrorNumber(long num) {
    char buff[50];

    sprintf(buff, "%ld%ld", num, num);

    return atol(buff);
}

long nextDigit(long num) {
    char buff[50];
    int len = getNumDigits(num);

    return (long)pow(10, len);
}

int main() {
    FILE *file = fopen("../input.txt", "r");
    FILE *debug = fopen("../debug.txt", "w");
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

        // long rez = mirrorFirstHalf(leftId);
        // long rez2 = nextDigit(leftId);
        // printf("magic num %ld next %ld\n", rez, rez2);
        printf("\n%ld %ld\n", leftId, rightId);

        p = strtok(NULL, ",");

        // handle the action computation
        // the digits must be even
        if (getNumDigits(leftId) & 1) {
            leftId = nextDigit(leftId);
        }

        while (leftId < rightId) {
            long firstHalf = getFirstHalf(leftId);
            long maxRange = nextDigit(firstHalf);

            printf("%ld %ld %ld\n", leftId, firstHalf, maxRange);

            // cant think of a better way to account for all numbers
            for (long i = firstHalf; i < maxRange; i++) {
                long duplicated = mirrorNumber(i);

                if (duplicated >= leftId && duplicated <= rightId) {
                    fprintf(debug,"START %ld END %ld %ld\n", leftId, rightId, duplicated);
                    sum += duplicated;
                }
                else if (duplicated > rightId) {
                    break;
                }
            }

            // continue ensuring even digits
            leftId = nextDigit(nextDigit(leftId));
        }
    }

    printf("am %lld mere", sum);

    fclose(file);
    return 0;
}
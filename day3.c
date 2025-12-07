#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define NUM_OF_DIGITS 12 // can change this to 2 for part 1
#define ARRAY_MAX 150

void copyArray(int *src, int *dst, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

long computeNum(char *nums, int *turnedOn, int size) {
    long result = 0;

    for (int i = 0; i < size; i++) {
        if (turnedOn[i]) {
            result = result * 10 + (nums[i] - '0');
        }
    }

    return result;
}

// checks which next digit turned on yields the max number
long findMaxNewNumber(char *nums, int *src, int *dst, int size) {
    int tempTurnedOn[size], maxTurnedOn[size];
    long maxNum = 0;

    copyArray(src, tempTurnedOn, size);

    for (int i = 0; i < size; i++) {
        // this digit is already turned on
        if (tempTurnedOn[i]) continue;

        tempTurnedOn[i] = 1;

        long currentNum = computeNum(nums, tempTurnedOn, size);

        if (maxNum < currentNum) {
            maxNum = currentNum;
            copyArray(tempTurnedOn, maxTurnedOn, size);
        }

        tempTurnedOn[i] = 0;
    }

    copyArray(maxTurnedOn, dst, size);
    return maxNum;
}

int main() {
    FILE *file = fopen("../input.txt", "r");
    char buff[BUFFER_SIZE];
    int len = 0;
    long maxNum = 0, sum = 0;

    if (!file) {
        perror("file");
        exit(1);
    }

    while (fgets(buff, BUFFER_SIZE, file)) {
        int turnedOn[ARRAY_MAX] = {0};

        buff[strcspn(buff, "\n")] = '\0';
        len = strlen(buff);

        for (int i = 0; i < NUM_OF_DIGITS; i++) {
            maxNum = findMaxNewNumber(buff, turnedOn, turnedOn, len);
            printf("%ld\n", maxNum);
        }

        sum += maxNum;
        printf("\n");
    }

    printf("sum %ld", sum);

    fclose(file);
    return 0;
}
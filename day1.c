#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int rotateLeft(int *num, int value) {
    int rotations = 0;

    for (int i = 0; i < value; i++) {
        *num = (*num - 1 + 100) % 100;

        if (*num == 0) rotations++;
    }

    return rotations;
}

int rotateRight(int *num, int value) {
    int rotations = 0;

    for (int i = 0; i < value; i++) {
        *num = (*num + 1) % 100;

        if (*num == 0) rotations++;
    }

    return rotations;
}


int main() {
    FILE *file = fopen("../input.txt", "r");

    if (!file) {
        perror("file");
        exit(1);
    }

    char buff[BUFFER_SIZE];
    int count = 0, startingValue = 50;

    while (fgets(buff, BUFFER_SIZE, file)) {
        buff[strcspn(buff, "\n")] = '\0';

        int value = atoi(buff + 1);

        if (buff[0] == 'L') {
            count += rotateLeft(&startingValue, value);
        }
        else {
            count += rotateRight(&startingValue, value);
        }
    }

    printf("the %d\n", count);
    fclose(file);

    return 0;
}

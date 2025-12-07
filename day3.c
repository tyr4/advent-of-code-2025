#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main() {
    FILE *file = fopen("../input.txt", "r");
    char buff[BUFFER_SIZE];
    int rightMax = 0, leftMax = 0, sum = 0;

    if (!file) {
        perror("file");
        exit(1);
    }

    while (fgets(buff, BUFFER_SIZE, file)) {
        buff[strcspn(buff, "\n")] = '\0';
        // init them
        leftMax = buff[0] - '0';
        rightMax = buff[1] - '0';

        for (int i = 2; i < strlen(buff); i++) {
            int curr = buff[i] - '0';

            if (rightMax > leftMax) {
                leftMax = rightMax;
                rightMax = curr;
            }

            if (rightMax < curr) {
                rightMax = curr;
            }
        }

        sum += leftMax * 10 + rightMax;
        printf("%d%d\n", leftMax, rightMax);
    }

    printf("sum %d", sum);

    fclose(file);
    return 0;
}
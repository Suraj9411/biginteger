#include <stdio.h>
#include <string.h>
#include "bigInt.h"

int main() {
    char num1[1000], num2[1000], result[1001], remainder[1001];
    int choice;

    printf("Enter the first number: ");
    scanf("%s", num1);

    printf("Enter the second number: ");
    scanf("%s", num2);

    printf("Choose operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter your choice (1/2/3/4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addBigInt(num1, num2, result);
            printf("Result of addition: %s\n", result);
            break;

        case 2:
            subtractBigInt(num1, num2, result);
            printf("Result of subtraction: %s\n", result);
            break;

        case 3:
            multiplyBigInt(num1, num2, result);
            printf("Result of multiplication: %s\n", result);
            break;

        case 4:
            divideBigInt(num1, num2, result, remainder);
            printf("Quotient of division: %s\n", result);
            printf("Remainder of division: %s\n", remainder);
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

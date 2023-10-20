#include "bigInt.h"

void addBigInt(const char* num1, const char* num2, char* result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int maxSize = (len1 > len2) ? len1 : len2;
    int carry = 0;
    int i, j, k = 0;

    for (i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0; i--, j--) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[k++] = (sum % 10) + '0';
    }

    if (carry > 0) {
        result[k++] = carry + '0';
    }

    result[k] = '\0';

    // ------------------------------------ Reverse the result string
    for (i = 0, j = k - 1; i < j; i++, j--) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}

void subtractBigInt(const char* num1, const char* num2, char* result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int maxSize = (len1 > len2) ? len1 : len2;
    int borrow = 0;
    int i, j, k = 0;

    for (i = len1 - 1, j = len2 - 1; i >= 0; i--, j--) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[k++] = diff + '0';
    }

    while (k > 1 && result[k - 1] == '0') {
        k--; //------------------- Remove leading zeros
    }

    result[k] = '\0';

    // ---------------------------Reverse the result string
    for (i = 0, j = k - 1; i < j; i++, j--) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}

void multiplyBigInt(const char* num1, const char* num2, char* result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int maxSize = len1 + len2;
    int* product = (int*)calloc(maxSize, sizeof(int));

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int digit1 = num1[i] - '0';
            int digit2 = num2[j] - '0';
            int productDigit = digit1 * digit2;

            int index1 = i + j;
            int index2 = i + j + 1;
            product[index1] += productDigit / 10;
            product[index2] += productDigit % 10;
        }
    }

    int carry = 0;
    for (int i = maxSize - 1; i >= 0; i--) {
        int sum = product[i] + carry;
        product[i] = sum % 10;
        carry = sum / 10;
    }

    int k = 0;
    for (int i = 0; i < maxSize; i++) {
        if (k == 0 && product[i] == 0) {
            continue;  // ----------------------------------Skip leading zeros
        }
        result[k++] = product[i] + '0';
    }

    if (k == 0) {
        result[k++] = '0';  //----------------------------- The result is zero
    }

    result[k] = '\0';
    free(product);
}

int compareBigInt(const char* num1, const char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 > len2) return 1;
    if (len1 < len2) return 0;

    // If the lengths are the same, compare digit by digit
    for (int i = 0; i < len1; i++) {
        if (num1[i] > num2[i]) return 1;
        if (num1[i] < num2[i]) return 0;
    }

    return 1; // If all digits are equal
}

void divideBigInt(const char* numerator, const char* denominator, char* quotient, char* remainder) {
    int lenNumerator = strlen(numerator);
    int lenDenominator = strlen(denominator);

    if (lenNumerator < lenDenominator || (lenNumerator == lenDenominator && strcmp(numerator, denominator) < 0)) {
        strcpy(quotient, "0");
        strcpy(remainder, numerator);
        return;
    }

    char* tempNumerator = strdup(numerator);
    char* tempQuotient = (char*)malloc(lenNumerator + 1);
    tempQuotient[0] = '\0';

    while (compareBigInt(tempNumerator, denominator)) {
        char digit = '0';
        char tempResult[2] = "0";
        char tempRemainder[1000] = "0";

        while (compareBigInt(tempNumerator, tempResult)) {
            digit++;
            addBigInt(tempResult, denominator, tempResult);
        }
        
        if (tempNumerator[0] == '0' && strlen(tempNumerator) > 1) {
            strcpy(tempNumerator, tempNumerator + 1);
        }

        strcpy(tempRemainder, tempNumerator);
        subtractBigInt(tempRemainder, tempResult, tempRemainder);

        strcat(tempQuotient, &digit);
        strcpy(tempNumerator, tempRemainder);
    }

    strcpy(quotient, tempQuotient);
    strcpy(remainder, tempNumerator);

    free(tempNumerator);
    free(tempQuotient);
}

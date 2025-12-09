#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include <ctype.h>

void ClearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int InputLength(int num, int len) {
    if (num == 0) return len == 1 ? 1 : 0;

    int i = 0;
    while (num != 0) {
        num /= 10;
        i += 1;
    }
    return i == len ? 1 : 0;
}

int InputDiff(int num, int len) {
    int user_number[5];
    int used[10] = { 0 };

    for (int i = len - 1; i >= 0; i--) {
        user_number[i] = num % 10;
        num /= 10;

        if (used[user_number[i]]) {
            return 0;
        }
        used[user_number[i]] = 1;
    }
    return 1;
}

int Digits(int len) {
    char input[20];
    int number;
    int valid_input;

    printf("Try to guess the number of size %d (without repeating digits): ", len);

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error. Please try again: ");
            ClearInputBuffer();
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            printf("Empty input! Please enter a number: ");
            continue;
        }

        valid_input = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit((unsigned char)input[i])) {
                valid_input = 0;
                break;
            }
        }

        if (!valid_input) {
            printf("Invalid input! Please enter only digits: ");
            ClearInputBuffer(); 
            continue;
        }

        if (len > 1 && input[0] == '0') {
            printf("Invalid input! Number cannot start with 0: ");
            ClearInputBuffer(); 
            continue;
        }

        char* endptr;
        number = (int)strtol(input, &endptr, 10);

        if (*endptr != '\0') {
            printf("Conversion error. Please try again: ");
            ClearInputBuffer(); 
            continue;
        }

        if (number < 0) {
            printf("Incorrect input!!! The number must be positive: ");
            ClearInputBuffer(); 
            continue;
        }

        if (InputLength(number, len) == 0) {
            printf("Incorrect input!!! The number must have exactly %d digits: ", len);
            ClearInputBuffer(); 
            continue;
        }

        if (InputDiff(number, len) == 0) {
            printf("Incorrect input!!! The number must not contain repeated digits: ");
            ClearInputBuffer(); 
            continue;
        }

        return number;
    }
}

int main() {
    srand(time(NULL));

    int number;
    int len;
    int arr[5] = { 0 };
    int bulls = 0;
    int cows = 0;
    int user_number[5];
    char len_input[20];
    int valid_len;

    printf("Enter the length of the number (2-5): ");

    while (1) {
        if (fgets(len_input, sizeof(len_input), stdin) == NULL) {
            printf("Input error. Please enter a number between 2 and 5: ");
            ClearInputBuffer(); 
            continue;
        }

        len_input[strcspn(len_input, "\n")] = 0;

        if (strlen(len_input) == 0) {
            printf("Empty input! Please enter a number between 2 and 5: ");
            continue;
        }

        valid_len = 1;
        for (int i = 0; len_input[i] != '\0'; i++) {
            if (!isdigit((unsigned char)len_input[i])) {
                valid_len = 0;
                break;
            }
        }

        if (!valid_len) {
            printf("Invalid input! Please enter only digits (2-5): ");
            ClearInputBuffer(); 
            continue;
        }

        char* endptr;
        len = (int)strtol(len_input, &endptr, 10);

        if (*endptr != '\0') {
            printf("Conversion error. Please enter a number between 2 and 5: ");
            ClearInputBuffer(); 
            continue;
        }

        if (len > 5 || len < 2) {
            printf("Incorrect input! Please enter a number between 2 and 5: ");
            ClearInputBuffer(); 
            continue;
        }

        break;
    }

    char used_digits[10] = { 0 };
    int digit;

    do {
        digit = rand() % 9 + 1;
    } while (used_digits[digit]);

    arr[0] = digit;
    used_digits[digit] = 1;

    for (int i = 1; i < len; i++) {
        do {
            digit = rand() % 10;
        } while (used_digits[digit]);

        arr[i] = digit;
        used_digits[digit] = 1;
    }

    while (bulls != len) {
        bulls = 0;
        cows = 0;
        number = Digits(len);

        for (int i = len - 1; i >= 0; i--) {
            user_number[i] = number % 10;
            number /= 10;
        }

        for (int i = 0; i < len; i++) {
            if (user_number[i] == arr[i]) {
                bulls++;
            }
        }

        int secret_count[10] = { 0 };
        int guess_count[10] = { 0 };

        for (int i = 0; i < len; i++) {
            if (user_number[i] != arr[i]) {
                secret_count[arr[i]]++;
                guess_count[user_number[i]]++;
            }
        }

        for (int digit = 0; digit < 10; digit++) {
            if (secret_count[digit] > 0 && guess_count[digit] > 0) {
                cows += (secret_count[digit] < guess_count[digit]) ? secret_count[digit] : guess_count[digit];
            }
        }

        printf("Number of cows = %d, number of bulls = %d.\n", cows, bulls);

        if (bulls == len) {
            printf("Congratulations! You win!!!\n");
            printf("The secret number was: ");
            for (int i = 0; i < len; i++) {
                printf("%d", arr[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

int InputLength(int num, int len) {
    int i = 0;
    while (num != 0) {
        num /= 10;
        i += 1;
    }
    if (i == len) {
        return 1;
    }
    else {
        return 0;
    }
}

int InputDiff(int num, int len) {
    int user_number[5];
    for (int i = len - 1; i >= 0; i--) {
        user_number[i] = num % 10;
        num /= 10;
    }
    for (int i = 0; i < len - 1; i++) {
        int j = i + 1;
        while (j < len) {
            if (user_number[j] == user_number[i]) {
                return 0;
            }
            j++;
        }
    }
    return 1;
}

int Digits(int len) {
    int number;
    int c;
    printf("Try to guess the number the size %d(without repeatings): ", len);
    while (1) {
        while ((c = getchar()) != '\n') {}
        scanf("%d", &number);
        if (number < 0) {
            printf("Incorrect input!!! The number must be positive\n");
        }
        else if (InputLength(number, len) == 0) {
            printf("Incorrect input!!! The length must be between 2 and 5\n", len);
        }
        else if (InputDiff(number, len) == 0) {
            printf("Incorrect input!!! The number must not contain repeated digits.\n");
        }
        else {
            return number;
        }
    }
}

int main() {
    srand(time(NULL));

    int number;
    int len;
    int arr[5];
    int bulls = 0;
    int cows = 0;
    int user_number[5];
    int c;

    printf("Enter the length of the number(2-5): ");
    scanf("%d", &len);

    while (len > 5 || len < 2) {
        printf("Incorrect input! Please try again.\n");
        while ((c = getchar()) != '\n') {}
        scanf("%d", &len);
    }

    char t;
    char i = 0;
    char num[10] = { 0 };

    while (i < len) {
        if (num[t = rand() % 10] == 0 && (t > 0 || i > 0)) {
            num[arr[i++] = t] += 1;
        }
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
            printf("Congratulations You win!!!\n");
        }
    }

    return 0;
}
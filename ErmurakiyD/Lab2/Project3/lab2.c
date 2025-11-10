#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {  

    printf("Input gamemode. (1 - User guesses a hidden number. 2 - Program guesses a hidden number.)\n");
    int gamemode = 0;
    char c;

    
    while (scanf("%d", &gamemode) != 1 || (gamemode != 1 && gamemode != 2)) {
        printf("Incorrect input. Please try again.\n");
        while ((c = getchar()) != '\n') {}; 
    }

    int number = -1;
    int guess = -1;

    switch (gamemode) {

    case 1: 
        srand(time(NULL));
        number = rand() % 1000 + 1; 
        guess = -1;
        int guess_sum = 1; 

        printf("Computer has chosen a number between 1 and 1000.\n");

        while (number != guess) {
            printf("Attempt %d: Enter your guess: ", guess_sum);

           
            while (scanf("%d", &guess) != 1) {
                printf("Incorrect input. Please enter a number: ");
                while ((c = getchar()) != '\n') {};
            }

            if (guess > number) {
                printf("Hidden number is LESS than your guess.\n");
            }
            else if (guess < number) {
                printf("Hidden number is HIGHER than your guess.\n");
            }
            else {
                printf("You WON! Hidden number is %d. It took %d guesses.\n", number, guess_sum);
                break;
            }
            guess_sum++;
        }
        break;

    case 2: 
        printf("Pick a number between 0 and 1000\n");

        
        while (scanf("%d", &number) != 1 || number < 1 || number > 1000) {
            printf("Incorrect input. Please enter a number between 1 and 1000: ");
            while ((c = getchar()) != '\n') {};
        }

        int min = 1;   
        int max = 1000;   
        int try = 1;
        char c;

        printf("Now I will try to guess your number %d.\n", number); 
        printf("Answer with: '<' if your number is less, '>' if greater, '=' if equal.\n");

        getchar(); 

        while (1) {
            
            if (min > max) {
                printf("Error\n");
                break;
            }

            
            guess = (min + max) / 2;
            printf("Try %d: Is your number %d? ", try, guess);

            
            c = getchar();
            getchar(); 

            
            if (c == '<') {
                max = guess - 1;
            }
            else if (c == '>') {
                min = guess + 1;
            }
            else if (c == '=') {
                if (guess == number) {
                    printf("I am CHAMPION!Your number is %d. It took me %d attempts.\n", guess, try);
                    break;
                }
                else {
                    printf("Are you sure?Double-check your answer\n");
                }
            }
            else {
                printf("Incorrect input.Please use only '<', '>' or '='.\n");
                continue; 
            }

            try++;

            
                if (try > 20) {
                    printf("Too many attempts. Something went wrong.\n");
                    break;
                }
        }
        break;
    }

    return 0; 
}
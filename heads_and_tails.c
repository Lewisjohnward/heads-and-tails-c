#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define clear() printf("\033c")
struct termios original;

void enable_raw_mode()
{
    tcgetattr(STDIN_FILENO, &original);
    struct termios raw = original;
    raw.c_iflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    printf("\033[0m");
}

void print_stats(int winning_streak, int high_score)
{
    printf("user: lewis\n");
    printf("High score: %d\n", high_score);
    if(winning_streak)
        printf("Winning streak: %d\n", winning_streak);
    else
        printf("No winning streak.\n");
}

int main (void)
{
    enable_raw_mode();
    int toss_result;
    int guess;
    int correct;
    char c;
    char prev_vals[25];
    int prev_vals_count = 0;
    prev_vals[25] = '\0';
    int winning_streak = 0;
    int high_score = 0;
    srand(time(NULL));
    //printf("%d\n", rand() % 2);
    clear();
    print_stats(winning_streak, high_score);
    while ((c = getchar()) != EOF && c != 'q')
    {
        //toss result 1 for heads 0 for tails
        toss_result = rand() % 2;
        if(toss_result)
        {
            strcat(prev_vals, "H ");
        }
        else
        {
            strcat(prev_vals, "T ");
        }

        if (c == 'h')
            guess = 1;
        if (c == 't')
            guess = 0;

        clear();
        print_stats(winning_streak, high_score);
        clear();

        if(guess && toss_result)
        {
            winning_streak++;
            correct = 1;
        }
        else if(!guess && !toss_result)
        {
            winning_streak++;
            correct = 1;
        }
        else
        {
            winning_streak = 0;
            correct = 0;
        }

        if(winning_streak > high_score)
            high_score = winning_streak;

        print_stats(winning_streak, high_score);
        printf("Prev vals %s\n", prev_vals);
        printf("You guessed %s\n", guess ? "heads" : "tails");
        if(correct)
        {
            printf("Well done correct!! \n");
        }
        else
        {
            printf("Maybe you should find another hobby...\n");
        }
        
    }
    clear();

    disable_raw_mode();
    return 0;
}

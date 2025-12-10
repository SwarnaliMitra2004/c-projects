#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    int random,guess,no_of_guess=0;
    srand(time(NULL));
    printf("Welcome to the world of guessing numbers.");
    random=rand()%100+1; // Generating between 0 to 100
    do{
        printf("Please enter your guess(1 to 100) : ");
        scanf("%d",&guess);
        no_of_guess++;
        if(guess<random){
            printf("Guess larger number.\n");
        }else if(guess>random){
            printf("Guess a smaller number.\n");
        }else {
            printf("Congratulations !!! You have successfully giessed the number in %d attempts.",no_of_guess);
        }
        
    }while(guess!=random);
    printf("\n Bye Bye, Thanks for playing.");
    printf("\n Developed by : Swarnali Ghosh");
}
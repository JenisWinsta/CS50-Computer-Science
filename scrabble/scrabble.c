#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int points[]={1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int get_score(string s);
int main(void)
{
    string player1=get_string("Player1: ");
    string player2=get_string("Player2: ");

    int score1= get_score(player1);
    int score2=get_score(player2);

    // printf("sore1:%i score2:%i\n",score1,score2);

    if(score1>score2){
        printf("Player 1 wins!\n");
    }
    else if(score1<score2){
        printf("Player 2 wins!\n");
    }
    else{
        printf("Tie!\n");
    }
}

int get_score(string s){
    int score=0;
    int index=0;

    for(int i=0, len=strlen(s); i<len;i++){
        if(islower(s[i])){
            score += points[s[i]-'a'];
        }
        else if(isupper(s[i])){
            score += points[s[i]-'A'];
        }
    }
    return score;
}

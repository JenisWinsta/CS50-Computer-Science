#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int letters(string s);
int words(string s);
int sentences(string s);

int main(void)
{
    string passage=get_string("Text: ");
    int len=strlen(passage);

    // Count the number of letters, words, and sentences in the text
    int n_letters= letters(passage);
    int n_words= words(passage);
    int n_sen=sentences(passage);

    float L = (float)n_letters/n_words*100.0;
    // printf("L:%i\n",L);


    float S=100.0* n_sen/n_words;
    // printf("S:%f\n",S);

    // Compute the Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade=round(index);
    // printf("grade:%i\n",index);

    if(grade<1){
        printf("Before Grade 1\n");
    }
    else if(grade>=16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n",grade);
    }
}

int letters(string s){
    int letter=0;
    for(int i=0, len=strlen(s);i<len;i++){
        if(islower(s[i])){
            letter++;
        }
        else if(isupper(s[i])){
            letter++;
        }
    }
    return letter;
}

int words(string s){
    int word=1;
    for(int i=0, len=strlen(s);i<len;i++){
        if(s[i]==' '){
            word++;
        }
    }
    return word;
}

int sentences(string s){
    int sentence=0;
    for(int i=0, len=strlen(s);i<len;i++){
        if(s[i]=='.' || s[i]=='?' || s[i]=='!'){
            sentence++;
        }
    }
    return sentence;
}

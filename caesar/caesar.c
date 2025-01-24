#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

char rotate(char s, int k);
int only_digits(string s);

int main(int argc, string argv[])
{
    // printf("%i",only_digits(argv[1]));

    if(argc==2 && isdigit(*argv[1])){
        // printf("hello\n");
        // printf("%i",*argv[1]);
        if(only_digits(argv[1])==1){
            printf("Usage: ./caesar key\n");
            return 1;
        }
        int k= atoi(argv[1]);

        k=k%26;
        // printf("key:%i\n",k);
        string plain=get_string("plaintext:  ");
        // char c='e';
        // char value=c-'a'+k;
        // value=value+'a'-26;
        // printf("%i\n",'a');
        // printf("%c\n",value);

        printf("ciphertext: ");


        for(int i=0, len=strlen(plain);i<len;i++){
            printf("%c",rotate(plain[i],k));
        }
        printf("\n");

    }
    else{
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

char rotate(char s, int k){
    char ch;
    if(islower(s)){
        ch= s-'a'+k;
        if(ch>=26){
            ch=ch+'a'-26;
        }
        else{
            ch=ch+'a';
        }
        return ch;
    }
    else if(isupper(s)){
        ch= s-'A'+k;
        if(ch>=26){
            ch=ch+'A'-26;
        }
        else{
            ch=ch+'A';
        }
        return ch;
    }
    else{
        return s;
    }
}


int only_digits(string s){

    for(int i=0, len=strlen(s);i<len;i++){
        if(isdigit(s[i])){

        }
        else{
            return 1;
        }
    }
    return 0;

}

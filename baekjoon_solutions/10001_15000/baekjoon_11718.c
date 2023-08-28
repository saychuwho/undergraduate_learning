#include <stdio.h>

int main(){
    char str[101];
    while(gets(str) != NULL){
        printf("%s\n", str);
    }
}
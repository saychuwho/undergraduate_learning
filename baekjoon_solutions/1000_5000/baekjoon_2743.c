#include <stdio.h>

int main(){
    char str[100];
    int counter = 0;
    scanf("%s", str);
    for(int i=0;str[i]!='\0';i++){
        counter++;
    }
    printf("%d", counter);
}
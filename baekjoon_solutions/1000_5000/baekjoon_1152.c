#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* str = (char*)malloc(1000001*sizeof(char));
    int counter = 0;

    // if using fgets, '\n' can be get. so increase the size of array    
    fgets(str, 1000001, stdin);
    int strend = strlen(str);
    if(str[strend - 1] == '\n') strend--;
    for(int i=0; i<strend;i++){
        if(((str[i] != 32) && (str[i+1] == 32 || str[i+1] == '\0'))
            || (str[i] != 32 && str[i+1] == 10)){
            counter++;
        }
    }
    printf("%d", counter);

    free(str);
}
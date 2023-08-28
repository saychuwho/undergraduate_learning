#include <stdio.h>
#include <string.h>

int main(){
    // NULL error. need to set array size sufficient
    char str[102];
    fgets(str, 102, stdin);
    int length = strlen(str) - 1;
    int result = 1;
    for(int i=0;i<length;i++){
        if(str[i] != str[length-1-i]){
            result = 0;
            break;
        }

    }
    printf("%d\n", result);
}
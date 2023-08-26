#include <stdio.h>

int main(){
    int byte = 0;
    scanf("%d", &byte);
    for(int i=0;i<(byte/4);i++){
        printf("long ");
    }
    printf("int\n");
}
#include <stdio.h>

int main(){
    char str[1000];
    int i_num = 0;
    scanf("%s", str);
    scanf("%d", &i_num);
    printf("%c", str[i_num - 1]);
}
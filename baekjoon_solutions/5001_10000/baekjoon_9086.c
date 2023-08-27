#include <stdio.h>
#include <stdlib.h>

int main(){
    int testnum = 0;
    scanf("%d", &testnum);
    for(int i=0;i<testnum;i++){
        char* str = (char*)malloc(1000*sizeof(char));
        int counter = 0;
        scanf("%s", str);

        for(int j=0;str[j] != '\0';j++)
            counter++;
        
        printf("%c%c\n", str[0], str[counter - 1]);

        free(str);
    }
}
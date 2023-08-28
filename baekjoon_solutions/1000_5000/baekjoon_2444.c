#include <stdio.h>

int main(){
    int n_num = 0;
    scanf("%d", &n_num);
    // upper part
    for(int i=0;i<n_num;i++){
        for(int j=0;j<2*n_num-1;j++){
            if((j >= n_num - i - 1) && (j <= n_num + i - 1)){
                printf("*");
                if(j == n_num + i - 1)
                    break;
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    // lower part
    for(int i=n_num-2;i>=0;i--){
        for(int j=0;j<2*n_num-1;j++){
            if((j >= n_num - i - 1) && (j <= n_num + i - 1)){
                printf("*");
                if(j == n_num + i - 1)
                    break;
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
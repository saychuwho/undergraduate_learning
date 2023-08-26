#include <stdio.h>
#include <stdlib.h>

int main(){
    int N = 0, M = 0;
    int* array;

    scanf("%d %d", &N, &M);
    array = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        array[i] = 0;
    }

    int I = 0, J = 0, K = 0;
    for(int i=0;i<M;i++){
        scanf("%d %d %d", &I, &J, &K);
        for(int j=I-1;j<=J-1;j++){
            array[j] = K;
        }
    }

    for(int i=0;i<N;i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
}
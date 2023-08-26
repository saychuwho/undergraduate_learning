#include <stdio.h>
#include <stdlib.h>

int main(){
    int N = 0, M = 0;
    int* array;

    scanf("%d %d", &N, &M);
    array = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        array[i] = i+1;
    }

    int I = 0, J = 0, tmp = 0;
    for(int i=0;i<M;i++){
        scanf("%d %d", &I, &J);
        tmp = array[I-1];
        array[I-1] = array[J-1];
        array[J-1] = tmp;
    }

    for(int i=0;i<N;i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
}
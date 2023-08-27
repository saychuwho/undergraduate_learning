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

    int I = 0, J = 0;
    int* tmp;
    for(int i=0;i<M;i++){
        scanf("%d %d", &I, &J);
        tmp = (int*)malloc((J-I+1)*sizeof(int));

        for(int j=0;j<J-I+1;j++){
            tmp[j] = array[J-1-j];
        }

        for(int j=0;j<J-I+1;j++){
            array[I-1+j] = tmp[j];
        }
        
        free(tmp);
    }

    for(int i=0;i<N;i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
}
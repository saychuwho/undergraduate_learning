// 자료구조와 함께 배우는 알고리즘 입문 1장 연습문제
#include <stdio.h>

// Q1
int max4(int a, int b, int c, int d){
    int tmp1, tmp2;
    if (a>b) 
        tmp1 = a;
    else 
        tmp1 = b;
    if(c>d) 
        tmp2 = c;
    else 
        tmp2 = d;
    if(tmp1>tmp2)
        return tmp1;
    else
        return tmp2;
}

// Q2
int min3(int a, int b, int c){
    int tmp1;
    if(a>b)
        tmp1 = b;
    else 
        tmp1 = a;
    if(tmp1>c)
        return c;
    else
        return tmp1;
}

// Q3
int min4(int a, int b, int c, int d){
    int tmp1, tmp2;
    if (a<b) 
        tmp1 = a;
    else 
        tmp1 = b;
    if(c<d) 
        tmp2 = c;
    else 
        tmp2 = d;
    if(tmp1<tmp2)
        return tmp1;
    else
        return tmp2;
}

int main(){
    printf("%d\n", max4(1,2,3,4));
    printf("%d\n", min3(1,2,3));
    printf("%d\n", min4(1,2,3,4));
}

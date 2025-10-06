#include <stdio.h>

int getSum;

void setSum(int sum){
   getSum = sum;
}

int add (int sum){
   return getSum + sum;
}


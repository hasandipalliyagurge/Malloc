#include<stdio.h>
#include"malloc.h"
void main()
{
  
  char* add1=MyMalloc(8);
  char* add2=MyMalloc(400);
  char* add3=MyMalloc(100);
  //printf("base %d \n",base);
  //printf("8 %d  \n",add1);
  //printf("400 %d \n",add2);
  //printf("100 %d\n",add3);
  MyFree(add3);
   MyFree(add2);
  char* add4=MyMalloc(500);
  //printf("500 %d\n",add4);
  
}

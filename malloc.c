#include<stdio.h>
#include<stdbool.h>
#include "malloc.h"


char mallocArray[25000]={'\0'};   //to show that the array is free from its first index
char *base=mallocArray;

char freeflag='f';
char allocate='a';

char* find_block(size_t size)
{
 	char *mover; //to find the free memory part we should go through the whole memory.for that mover pointer is used
 	mover=base;  //as it starts from first block mover is initialized as base
 	
 	int num=0;
 	while(true)
	 {
 			num=*(int*)(mover+1);  //size of the current block
 			if(*mover==freeflag&&num>=size+5)  //we cant allocate 20 in 10bytes.n of free memory must be greater than the size that we find to allocate
			{
   						return (mover);
 			}
 			mover=mover+num+5;  //go to the next block. if currnet mover isn't enough to allocate then jump to next block
 	}
 	
}

void split_block(char* b,size_t s) //pointer to the block whch we need to split,size want to allocate
{
  		char* temp;
  		
  		int b_size=*(int*)(b+1);
  		b_size=b_size -s -5;
  		temp=b+s+5;    //pointer to next free part
 		*temp=freeflag;
 		 *(int*)(temp+1)=b_size;
  		*(int*)(b+1)=s;  //size of the allocated part is set
  		*b=allocate;

}

char *MyMalloc(size_t size)
{
 	
 		if(*base=='\0')
		{
 			*base=freeflag;
 			*(int*)(base+1)=25000-5;
 		}
 		
 		char* b=find_block(size);  //returns a pointer to that block which is matching to the size the user is searching for
	
 		if(*b=='f')
		{
 			if(*(int*)(b+1)>size)
			{
  				split_block(b,size);
			}
			else if(*(int*)(b+1)==size)
			{
				*b=allocate;
			}
			printf("meta:%c %d %d--> data: %d\n",*b,size,b,b+5);   //b is the address of which meta data starts
				return (b);
 		}
		else
		{
    		return NULL;
 		}
  		
}

void MyFree(char* address)
{
   char *mover,*previous,*next;   //store the addresses of previous and next blocks,mover to loop through the array
   mover=base;  //start from the first block
  
   int n=0;
   while(true)
    {
    n=*(int *)(mover+1);  //get the size   of current block
    if(mover==address)  //given address
    {
     break;
    }
	else if(!*mover) //reached to the end off block
     break;
    else
	{
         previous=mover;
         mover=mover+n+5;
         next=mover+*(int*)(mover+1)+5;
    }
    
    }
    if(*next==freeflag)
    {
     *mover=freeflag;  //make the current block also free as the next block
     *(int*)(mover+1)=*(int*)(mover+1)+*(int*)(next+1)+5;  //size  of the current block+size of next block which is free 
    
    }
    if(*previous==freeflag)
    {
      *mover=freeflag;
      *(int *)(previous+1)=*(int*)(mover+1)+*(int*)(previous+1)+5;  //changing the size of the previuos block
     
    }
	else
	   {
       *address=freeflag;
       mover=address;
	   }
    
    
   		printf("meta:%c %d %d--> data: %d\n",*mover,*(int*)(mover+1),mover,mover+5);
}


#include<stdio.h>
#include<stdbool.h>
#include"arraystackADT.h"

int main()
{
	STACK *s;
	int *data;
	bool res;
	int stacksize,ch,i;
	printf("Implementation of Integer Stack using ADT\n");
	printf("Enter Stack Size: \n");
	scanf("%d",&stacksize);
	s=stackcreate(stacksize);
	if(!s)
	{
		printf("Stack Creation Failed!\n");
		return(1);
	}
	printf("Stack Creation Successful\n");
	
	while(1)
	{
		printf("1. Push\n 2. Pop\n 3. Stack-Top\n 4. Stack-Count\n 5. StackFull\n 6. StackEmpty\n 7. Display\n 8. Destroy\n 9. Exit\n");
	    scanf("%d", &ch);
	    
	    switch(ch)
	    {
			case 1  : data=(int*)malloc(sizeof(int));
			           if(!data)
			             {
							 printf("Memory Allocation Unsuccessful\n");
						 }
					   else
					   {   if(fullstack(s))
						   {
							   printf("Queue Overflow\n");
						   }
						   else
						   {
						   printf("Enter the Element to be Pushed\n");
						   scanf("%d",data);
						   res=pushstack(s,data);
						   if(res)
						      printf("Element Pushed Successfully\n");
						   else
						      printf("Push Operation has Failed\n");
						  }
					  }
						  break;
			case 2  : data=(int*)popstack(s);
			          if(!data)
			          {
						  printf("Stack Pop has Failed\n");
					  }
					  else
					  {
						  printf("Element Popped from Stack: %d\n", *data);
	                      free(data);
					  }
					  break;
		    case 3  : data=(int*)stacktop(s);
		              if(!data)
		                printf("Stack is Empty\n");
		              else
		                printf("Stack Top Element: %d\n", *data);
		               break;
		    case 4  : printf("Stack Count: %d\n", stackcount(s));
		               break;
		    case 5  : if(fullstack(s))
		                 printf("Stack Full\n");
		              else
		                 printf("Stack is Not Full\n");
		              break;
		    case 6  : if(emptystack(s))
		                printf("Stack is Empty\n");
		              else
		                printf("Stack is Not Empty");
		              break;
		    case 7  : if(!s->count)
                          printf("Stack is Empty\n");
                      else
                          {
							  printf("Stack Contents are\n");
							  for(i=s->top; i>=0; i--)
							    printf("%d\n", *((int*)s->sarray[i]));
							}
					  break;
		    case 8  : res=destroystack(s);
		              if(res)
		                printf("Stack Destroyed Successfully\n");
		               else
		                printf("Stack Doesn't Exist\n");
		               return(1);
		    default  : printf("Invalid Choice\n");
		}
	}
	return 0;
}  	    
		                 					

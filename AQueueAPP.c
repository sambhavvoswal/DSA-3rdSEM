#include"AqueueADT.h"
#include<string.h>

bool comp(void* data, void* key)
{
	if(!strcmp((char*)data,(char*)key))
	   return true;
	return false;
}

int main()
{
  AQUEUE *phead;
  int size,choice;
  char key[35];
  void *dq;
  printf("\nImplementation of Queue on Strings\n\n");
  printf("Enter the size of Queue: ");
  scanf("%d",&size);
  phead=Createqueue(size);
  char *dptr;
   if(phead)
  {
    while(1)
     {
         printf("\n1-Enqueue\n2-Dequeue\n3-Queue Front\n4-Queue Rear\n5-Queue Count\n6-Display\n7-Queue full\n8-Queue empty\n9-Destroy\n10-Queue Search\n");
         printf("Enter your choice: \n");
         scanf("%d",&choice);
          switch(choice)
            {
                  case 1: if(queuefull(phead))
                          {
							  printf("Enqueue failed because Queue is Full\n");
						  }
						  else
						  {
                          printf("Enter the string : ");
                          dptr = (char*)calloc(20,sizeof(char));
                          scanf("%s",dptr);
                          if(enqueue(phead,dptr))
                            printf("Enqueued successfull\n");
                          else
                             printf("Enqueue failed\n");
						 } 
                          break;
                  case 2: dq=(char*)calloc(20,sizeof(char));
                          dq=dequeue(phead);
                          if(dq)
                           printf("Dequeued element : %s\n",(char*)dq);
                          else
                           printf("Dequeue Failed because Queue is Empty\n"); 
                          break;
                  case 3: dq=queuefront(phead);
                          if(dq)
                           printf("Queue front : %s\n",(char*)dq);
                          else
                           printf("Queue is empty\n");
                          break; 
                  case 4: dq=queuerear(phead);
                          if(dq)
                           printf("Queue front : %s\n",(char*)dq);
                          else
                           printf("Queue is empty\n");
                          break;
                  case 5: printf("Count : %d\n",queuecount(phead));
                          break;
                  case 6: for(int i=0; i<phead->count; i++)
                          {
                            printf("%s\t",(char*)(phead->parray[i]));
                            printf("\n");
					   	  }
                          break;
                  case 7: if(queuefull(phead))
                           printf("Queue is full\n");
                          else
                           printf("Queue is not full\n");
                          break;
                  case 8: if(qempty(phead))
                           printf("Queue is empty\n");
                          else
                           printf("Queue is not empty\n");
                          break;
                  case 9: if(destroyqueue(phead))
                          {
                             printf("Destroy successfull\n");
                           }
                           else
                             printf("Destroy failed!\n");
                          exit(0);
                case 10: printf("Enter the string to be Searched: ");
                         scanf("%s",key);
                         if(qusearch(phead,key,comp))
                                printf("String Found\n");
                         else
                               printf("String Not Found\n");
                         break;
                default: printf("Invalid choice\n");
            }
         }
    }
return 0;
}

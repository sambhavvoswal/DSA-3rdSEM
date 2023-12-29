#include"LinkedqueueADT.h" 
#include<string.h>

bool comp(void* data, void* key)
{
	if(*(float*)data==*(float*)key)
	   return true;
	return false;
}

int main() 
{ 
  QHEAD* pQHEAD; 
  float *dptr,key; 
  int choice; 
  QNODE *temp; 
  printf("Implementation of Queue using linked list on Floating Integers\n");
  pQHEAD=createqueue(); 
   if(pQHEAD) 
  { 
     while(1) 
    { 
        printf("\n1-Enqueue\n2-Dequeue\n3-Queue Front\n4-Queue Rear\n5-Queue count\n6-Queue Empty\n7-Queue Full\n8-Destroy Queue\n9-Display\n10-Exit\n11-Queue Search\nEnter your choice: \n"); 
        scanf("%d",&choice); 
              switch(choice) 
            { 
               case 1: if(qfull(pQHEAD))
                       {
						   printf("Enqueued Failed Because Queue is Full\n"); 
						}
					   else
					   {   
                       printf("Enter the element to be inserted\n"); 
                       dptr=(float*)malloc(sizeof(float)); 
                       scanf("%f",dptr); 
                       if(enqueue(pQHEAD,dptr)) 
                            printf("Data inserted successfully\n"); 
                       else 
                            printf("Data not inserted\n"); 
                        }
                       break;  
               case 2: printf("The element Dequeued is: %.3f\n",*(float*)dequeue(pQHEAD)); 
                       break; 
               case 3: printf("Queue Front: %.3f\n",*(float*)qf(pQHEAD)); 
                       break; 
               case 4: printf("Queue Rear: %.3f\n",*(float*)qr(pQHEAD)); 
                       break; 
               case 5: printf("Queue count is: %d\n",qcount(pQHEAD)); 
                       break; 
               case 6: if(qempty(pQHEAD)) 
                        printf("Queue is empty\n"); 
                       else 
                        printf("Queue is not empty\n"); 
                       break; 
               case 7: if(qfull(pQHEAD)) 
                         printf("Queue is full\n"); 
                       else 
                         printf("Queue is not full\n"); 
                       break; 
               case 8: if(DestroyQueue(pQHEAD)) 
                        printf("Queue destroyed successfully\n"); 
                       else 
                        printf("Queue not destroyed\n"); 
                       break; 
               case 9: temp=pQHEAD->f; 
                       while(temp) 
                       { 
                         printf("%.3f\t",*(float*)temp->dptr); 
                         temp=temp->link; 
                        } 
                       printf("\n"); 
                       break; 
               case 10: exit(0); 
               case 11: printf("Enter the Element to be Searched: ");
                         scanf("%f",&key);
                         if(qusearch(pQHEAD,&key,comp))
                                printf("Element Found\n");
                         else
                               printf("Element Not Found\n");
                         break;
               default: printf("Invalid input\n"); 

            } 
        } 
    } 
return 0; 
}


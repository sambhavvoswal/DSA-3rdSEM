#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct
{
int count,front,rear,maxsize;
void **parray;
}AQUEUE;

AQUEUE* Createqueue(int size)
{
   AQUEUE* t;
   t=(AQUEUE*)malloc(sizeof(AQUEUE));
  if(t)
 {
 t->count=0;
 t->front=-1;
 t->rear=-1;
 t->maxsize=size;
 t->parray=(void**)calloc(size,sizeof(void*));
 return t;
}
 return NULL;
}

bool enqueue(AQUEUE* t,void* datain)
{
    if(t->count==t->maxsize)
   {
        printf("Queue is full\n");
        return false;
   }
     if(t->count==0)
   {
         t->front=0;
   }
      t->rear++;
      t->parray[t->rear]=datain;
      t->count++;
        return true;
}

void* dequeue(AQUEUE* t)
{
      if(t->count==0)
    {
      printf("Queue is empty\n");
        return NULL;
    }
     void* temp;
     temp=t->parray[t->front];
     t->front++;
     t->count--;
return temp;
}

void* queuerear(AQUEUE* t)
{
     return t->parray[t->rear];
}

void* queuefront(AQUEUE* t)
{
     return t->parray[t->front];
}

int queuecount(AQUEUE* t)
{
     return t->count;
}
bool qempty(AQUEUE* t)
{
      if(t->count==0) 
        return true;
          return false;
}
bool qusearch(AQUEUE* t, void *key, bool(*comp)(void*,void*))
{
	int i;
	if(qempty(t))
	    return false;
	for(i=t->front; i!=t->rear; i=(i+1)%t->maxsize)
	{
		if(comp(t->parray[i],key))
		return true;
	}
	if(comp(t->parray[i],key))
	  return true;
	return false;
}



bool queuefull(AQUEUE* t)
{
      if(t->count==t->maxsize)
            return true;
        return false;
}

bool destroyqueue(AQUEUE* t)
{
      if(t)
    {
       while(t->count!=0)
     {
         free(t->parray[t->rear]);
         t->rear--;
     }
        free(t);
       return true;
    }
 return false;
}


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct QNODE
{
	 struct QNODE *link;
     void *dptr;
}QNODE;

typedef struct
{
     int count;
     QNODE *f,*r;
}QHEAD;

QHEAD* createqueue()
{
     QHEAD* pQHEAD;
     pQHEAD=(QHEAD*)malloc(sizeof(QHEAD));
     if(pQHEAD)
  {
    pQHEAD->f=NULL;
    pQHEAD->r=NULL;
    pQHEAD->count=0;
  }
  return pQHEAD;
}

bool enqueue(QHEAD* pQHEAD,void* datain)
{
   if(pQHEAD)
 {
   QNODE* newQNODE;
   newQNODE=(QNODE*)malloc(sizeof(QNODE));
     if(newQNODE)
       {
         newQNODE->dptr=datain;
         newQNODE->link=NULL;
           if(pQHEAD->count==0)
             {
               pQHEAD->f=newQNODE;
              }
           else
               pQHEAD->r->link=newQNODE;
               pQHEAD->r=newQNODE;
               pQHEAD->count++;
        }
     return true;
  }
  return false;
}

void *dequeue(QHEAD *pQHEAD)
{
   if(pQHEAD->count==0)
 {
   printf("Queue is empty\n");
    return NULL;
 }
  QNODE *temp;
  temp=pQHEAD->f;
  void *dout=temp->dptr;
  pQHEAD->f=temp->link;
  pQHEAD->count--;
  free(temp);
  return dout;
}

void* qr(QHEAD* pQHEAD)
{
 return(pQHEAD->r->dptr);
}

void* qf(QHEAD* pQHEAD)
{
 return(pQHEAD->f->dptr);
}

int qcount(QHEAD* pQHEAD)
{
 return(pQHEAD->count);
}

bool qempty(QHEAD* pQHEAD)
{
    if(pQHEAD->count==0)
      return true;
   return false;
}

bool qfull(QHEAD* pQHEAD)
{
   QNODE* temp;
   temp=(QNODE*)malloc(sizeof(QNODE));
   if(temp)
{
   free(temp);
   return false;
}
   return true;
}

bool qusearch(QHEAD* t, void *key, bool(*comp)(void*, void*))
{
	QNODE *pnode;
	if(qempty(t))
	    return false;
	pnode=t->f;
	do
	{
		if(comp(pnode->dptr,key))
		     return true;
		pnode=pnode->link;
	}while(pnode);
	return false;
}

bool DestroyQueue(QHEAD *pQHEAD)
{
   QNODE *temp;
     if(pQHEAD)
       {
         while(pQHEAD->f!=NULL)
          {
            temp=pQHEAD->f;
            pQHEAD->f=temp->link;
            free(temp->dptr);
             free(temp);
          }
        pQHEAD->count=0;
          return true;
       }
  return false;
}

void qdisplay(QHEAD *q, void(*print)(void*))
{
	QNODE *pQNODE;
	if(qempty(q))
	{
		printf("Empty\n");
		return;
	}
	printf("Queue Contents are \n");
	pQNODE=q->f;
	do
	{
		print(pQNODE->dptr);
		pQNODE=pQNODE->link;
	}while(pQNODE);
}

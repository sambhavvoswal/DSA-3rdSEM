//program on array stack adt
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
typedef struct
{
    int top;
    int size,count;
    void **sarray;
}STACK;

STACK* stackcreate(int s)
{
    STACK *t;
    t=(STACK*)malloc(sizeof(STACK));
    if(t==NULL)
        return NULL;
    t->top=-1;
    t->size=s;
    t->count=0;
    t->sarray=(void **)calloc(s,sizeof(void *));
    if(t->sarray==NULL)
    {
        free(t);
        return NULL;
	}
        return(t);
}

bool pushstack(STACK *t,void *data)
{
    if(t->top==t->size-1)
        return(false);
    t->count++;
    t->top++;
    t->sarray[t->top]=data;
    return(true);
}

void * popstack(STACK *t)
{
    if(t->top==-1)
        return NULL;
    void *data;
    t->count--;
    data=t->sarray[t->top];
    t->top--;
    return(data);

}

void * stacktop(STACK *t)
{
    if(t->top==-1)
        return NULL;
    return(t->sarray[t->top]);

}


int stackcount(STACK *t)
{
    return(t->count);
}

bool emptystack(STACK *t)
{
    return(t->top==-1);
}

bool fullstack(STACK *t)
{
    return(t->count==t->size);
}

bool searchstack(STACK *t,void *key,bool (*compare)(void *,void *))
{
    if(emptystack(t))
        return false;
    int i;
    for(i=t->top;i>=0;i--)
    {
        if(compare(t->sarray[i],key))
            return true;
    }
    return false;
}

void displaystack(STACK *t,void (*print)(void *))
{
    if(emptystack(t))
    {
        printf("Stack is empty\n");
        return;
    }
    int i;
    for(i=t->top;i>=0;i--)
        print(t->sarray[i]);
}

bool destroystack(STACK* t)
{
    if(t==NULL)
        return false;
    while(t->top>=0)
    {
    free(t->sarray[t->top--]);
    free(t->sarray);
    }
    free(t);
    
  return true;

}

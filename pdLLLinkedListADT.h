#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    void *data;
    struct node *link;
}LNODE;
typedef struct header
{
    LNODE *head;
    int count;
}LHEADER;

LHEADER* createlist()
{
    LHEADER *l;
    l=(LHEADER*)malloc(sizeof(LHEADER));
    if(!l)
       return NULL;
    l->head=NULL;
    l->count=0;
    return(l);
}

bool insert_beginning(LHEADER *l,void *din)
{
    LNODE *newnode;
    newnode=(LNODE*)malloc(sizeof(LNODE));
    if(!newnode)
       return false;
    newnode->data=din;
    if(l->count==0)
    {
        l->head=newnode;
        newnode->link=NULL;
        l->count++;
        return true;
    }
    newnode->link=l->head;
    l->head=newnode;
    l->count++;
    return true;
}

bool insert_middle(LHEADER *l,void *key,void *din,bool (*comp)(void*,void*))
{
    LNODE *newnode,*temp;
    newnode=(LNODE*)malloc(sizeof(LNODE));
    if(!newnode)
       return false;
    newnode->data=din;
    if(l->count==0)
    {
        l->head=newnode;
        newnode->link=NULL;
        l->count++;
        return true;
    }
    temp=l->head;
    while(temp!=NULL)
    {
        if(comp(temp->data,key))
        {
            newnode->link=temp->link;
            temp->link=newnode;
            l->count++;
            return true;
        }
        temp=temp->link;
    }
    return false;
}

bool insert_end(LHEADER *l,void *din)
{
    LNODE *newnode,*temp;
    newnode=(LNODE*)malloc(sizeof(LNODE));
    if(!newnode)
       return false;
    newnode->data=din;
    if(l->count==0)
    {
        l->head=newnode;
        newnode->link=NULL;
        l->count++;
        return true;
    }
    temp=l->head;
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    temp->link=newnode;
    newnode->link=NULL;
    l->count++;
    return true;
}

void* delete_beginning(LHEADER *l)
{
    LNODE *deletenode;
    void *dout;
    if(!l)
       return NULL;
    deletenode=l->head;
    l->head=deletenode->link;
    dout=deletenode->data;
    free(deletenode);
    l->count--;
    return(dout);
}

/*void* delete_middle(LHEADER *l,void *key,bool (*comp)(void*,void*))
{
    LNODE *deletenode,*temp,*pprev;                                                      //call delete at the beginning function if the first node is selected
    void *dout;
    if(!l->head)
       return NULL;
    temp=l->head;
    pprev=NULL;
    while(temp!=NULL)
    {
        pprev=temp;
        if(comp(temp->data,key))
        {
            if(pprev==NULL)
            {
                l->head=NULL;
                l->count--;
            }
            else if(comp(l->head,key))
            {
				dout=delete_beginning(l);
                return(dout);
			}
            else
            {
               deletenode=temp;
               pprev->link=deletenode->link;
               dout=deletenode->data;
               free(deletenode);
               l->count--;
               return(dout);
            }
        }
        temp=temp->link;
    }
    return NULL;
}*/

void* delete_middle(LHEADER *l,void *key,bool (*comp)(void*,void*))
{
    LNODE *temp,*prev;
    void *dout;
    if(!l->head)
    {
        return NULL;
    }
    temp=l->head;
    prev=NULL;
    while(temp)
    {
        if(comp(temp->data,key))
           break;
        prev=temp;
        temp=temp->link;
    }
    if(!temp)
       return NULL;
    if(!prev)
    {
        dout=delete_beginning(l);
        return(dout);
    }
    prev->link=temp->link;
    dout=temp->data;
    temp->link=NULL;
    free(temp);
    l->count--;
    return(dout);
}

void* delete_end(LHEADER *l)
{
    LNODE *deletenode,*temp,*pprev;
    void *dout;
    if(!l->head)
       return NULL;
    temp=l->head;
    pprev=NULL;
    while(temp->link!=NULL)
    {
        pprev=temp;
        temp=temp->link;
    }
    deletenode=temp;
    dout=deletenode->data;
    if(!pprev)
       l->head=NULL;
    else
       pprev->link=NULL;
    free(deletenode);
    l->count--;
    return(dout);
}

int listcount(LHEADER *l)
{
    return(l->count);
}

bool listempty(LHEADER *l)
{
    return(l->head==NULL);
}
bool listfull()
{
    LNODE *p;
    p=(LNODE*)malloc(sizeof(LNODE));
    if(!p)
       return true;
    free(p);
    return false;
}

void displaylist(LHEADER *l,void(*print)(void*))
{
    LNODE *temp;
    temp=l->head;
    while(temp!=NULL)
    {
        print(temp->data);
        temp=temp->link;
    }
}

bool searchlist(LHEADER *l,void *key,bool (*comp)(void*,void*))
{
    LNODE *temp;
    if(!l->head)
    {
        printf("List is empty\n");
        return false;
    }
    temp=l->head;
    while(temp!=NULL)
    {
        if(comp(temp->data,key))
        {
            return true;
        }
        temp=temp->link;
    }
    return false;
}

void destroylist(LHEADER *l)
{
    if(!l)
       return;
    LNODE *temp;
    temp=l->head;
    while(temp!=NULL)
    {
        free(temp->data);
        temp=temp->link;
    }
    free(temp);
    free(l);  
}

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"LLqueueADT.h"

typedef struct tnode
{
    void *dp;
    struct tnode *left;
    struct tnode *right;
}TNODE;

typedef struct
{
    int count;
    TNODE *root;
    bool (*compare)(void*,void*);
    void (*print)(void*);
}BTREE;

BTREE* createtree(bool (*comp)(void*,void*),void (*prt)(void*))
{
    BTREE *bt;
    bt=(BTREE*)malloc(sizeof(BTREE));
    if(bt)
    {
        bt->count=0;
        bt->root=NULL;
        bt->compare=comp;
        bt->print=prt;
    }
    return(bt);
}

bool insert_node(BTREE *bt,void *datain)
{
    TNODE *newnode,*traverse,*parent;
    int ch;
    traverse=bt->root;
    while(traverse)
    {
        printf("Enter 1-Left\n2->right\n");
        scanf("%d",&ch);
        if(ch==1)
        {
            parent=traverse;
            traverse=traverse->left;
        }
        else if(ch==2)
        {
            parent=traverse;
            traverse=traverse->right;
        }
        else
           printf("Invalid choice\n");
    }
    newnode=(TNODE*)malloc(sizeof(TNODE));
    if(newnode)
    {
        newnode->dp=datain;
        newnode->left=NULL;
        newnode->right=NULL;
    }
    else
       return false;
    if(ch==1)
       parent->left=newnode;
    else if(ch==2)
       parent->right=newnode;
    else
       bt->root=newnode;
    bt->count++;
    return true;
}

void preorder(BTREE *bt,TNODE *root)
{
    if(root)
    {
        bt->print(root->dp);
        preorder(bt,root->left);
        preorder(bt,root->right);
    }
}

void inorder(BTREE *bt,TNODE *root)
{
    if(root)
    {
        inorder(bt,root->left);
        bt->print(root->dp);
        inorder(bt,root->right);
    }
}

void postorder(BTREE *bt,TNODE *root)
{
    if(root)
    {
        postorder(bt,root->left);
        postorder(bt,root->right);
        bt->print(root->dp);
    }
}

void breadth_first(BTREE *bt)
{
    TNODE *currentnode;
    QHEAD *q;
    q=createq();
    currentnode=bt->root;
    while(currentnode)
    {
        bt->print(currentnode->dp);
        if(currentnode->left)
           enqueue(q,currentnode->left);
        if(currentnode->right)
           enqueue(q,currentnode->right);
        if(!qempty(q))
           currentnode=(TNODE*)dequeue(q);
        else
           currentnode=NULL;
    }
    destroyqueue(q);
    return;
}

void deletenode(BTREE *bt,TNODE *t)
{
    if(t)
    {
        deletenode(bt,t->left);
        deletenode(bt,t->right);
        printf("Node to be deleted:");
        bt->print(t->dp);
        printf("\n");
        bt->count--;
        free(t);
    }
}

void find_key_parent(BTREE *bt,TNODE *t,TNODE **p,void *key)
{
    if(t)
    {
        if(bt->compare(t->dp,key))
           return;
        if(t->left)
        {
            if(bt->compare(t->left->dp,key))
            {
                *p=t;
                return;
            }
            find_key_parent(bt,t->left,p,key);
        }
        if(t->right)
        {
            if(bt->compare(t->right->dp,key))
            {
                *p=t;
                return;
            }
            find_key_parent(bt,t->right,p,key);
        }
    }
}

bool deletekeynode(BTREE *bt,void *key)
{
    TNODE *parent=NULL,*t;
    int ch;
    find_key_parent(bt,bt->root,&parent,key);
    if(!parent&&bt->compare(bt->root->dp,key))
    {
        printf("Node to be deleted is the root of htet tree\n");
        printf("Still do you want tto delete?\n");
        printf("press 1 to delete\n2-stop\n");
        scanf("%d",&ch);
        if(ch==1)
        {
            deletenode(bt,bt->root);
        }
        else
        {
            return false;
        }
    }
    else if(!parent)
       return false;
    else
    {
        if(bt->compare(parent->left->dp,key))
        {
            t=parent->left;
            parent->left=NULL;
        }
        else
        {
            t=parent->right;
            parent->right=NULL;
        }
        deletenode(bt,t);
        return true;
    }
}

void find_keyfrequency(BTREE *bt,TNODE *root,int *freq,void *key)
{
    if(root)
    {
        if(bt->compare(root->dp,key))
           (*freq)++;
        if(root->left)
           find_keyfrequency(bt,root->left,freq,key);
        if(root->right)
           find_keyfrequency(bt,root->right,freq,key);
    }
}

void noofleaves(TNODE *root,int *leaves)
{
    if(root)
    {
        if(root->left==NULL&&root->right==NULL)
        {
            (*leaves)++;
            return;
        }
        if(root->left)
           noofleaves(root->left,leaves);
        if(root->right)
           noofleaves(root->right,leaves);
    }
}

int find_tree_height(TNODE *t)
{
    int hl,hr;
    if(t)
    {
        hl=find_tree_height(t->left);
        hr=find_tree_height(t->right);
        if(hl>=hr)
           return(1+hl);
        return(1+hr);
    }
}

bool balanced_tree(BTREE *bt)
{
    TNODE *root;
    int bf,hleft,hright;
    root=bt->root;
    if(root)
    {
        hleft=find_tree_height(root->left);
        hright=find_tree_height(root->right);
        bf=abs(hleft-hright);
        if(bf<=1)
           return true;
        return false;
    }
    return true;
}

TNODE* search_node(BTREE *bt,TNODE *root,void *key)
{
    if(root)
    {
        if(bt->compare(root->dp,key))
           return(root);
        if(root->left)
           return(search_node(bt,root->left,key));
        if(root->right)
           return(search_node(bt,root->right,key));
    }
    return NULL;
}

TNODE* createnode(TNODE *t)
{
    TNODE *newnode;
    if(t)
    {
        newnode=(TNODE*)malloc(sizeof(TNODE));
        newnode->dp=t->dp;
        newnode->left=createnode(t->left);
        newnode->right=createnode(t->right);
        return(newnode);
    }
    return NULL;
}

void destroy(BTREE *bt)
{
    if(bt)
    {
        deletenode(bt,bt->root);
        free(bt);
    }
}

bool copy_tree(BTREE *b1,BTREE *b2)
{
    if(b1->root)
    {
        deletenode(b2,b2->root);
        b2->root=createnode(b1->root);
        b2->count=b1->count;
        b2->compare=b1->compare;
        b2->print=b1->print;
        return true;
    }
    return false;
}
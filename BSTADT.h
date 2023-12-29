#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdbool.h>
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
    int (*compare)(void*,void*);
    void (*print)(void*);
}BST;

BST* createtree(int (*comp)(void*,void*),void (*prt)(void*))
{
    BST *bst;
    bst=(BST*)malloc(sizeof(BST));
    if(bst)
    {
        bst->count=0;
        bst->root=NULL;
        bst->compare=comp;
        bst->print=prt;
    }
    return(bst);
}
 
void* findsmallestnode(TNODE *root)
{
    if(root)
    {
        if(root->left==NULL)
           return(root->dp);
        return(findsmallestnode(root->left));
    }
    return NULL;
}

void* findlargestnode(TNODE *root)
{
    if(root)
    {
        if(root->right==NULL)
           return(root->dp);
        return(findlargestnode(root->right));
    }
    return NULL;
}

bool searchkey(BST *bst,TNODE *root,void *key)
{
    static int res;
    if(!root)
       return false;
    res=bst->compare(root->dp,key);
    if(res==0)
       return true;
    else if(res>0)
       return(searchkey(bst,root->right,key));
    else
       return(searchkey(bst,root->left,key));
}

bool insert_BST(BST *bst,void *datain)
{
    TNODE *newnode,*root;
    int res;
    newnode=(TNODE*)malloc(sizeof(TNODE));
    if(!newnode)
       return false;
    newnode->dp=datain;
    newnode->left=NULL;
    newnode->right=NULL;
    if(!bst->root)
    {
        bst->root=newnode;
        bst->count++;
        return true;
    }
    root=bst->root;
    do
    {
        res=bst->compare(root->dp,datain);
        if(res>=0)
        {
            if(root->right)
               root=root->right;
            else
               break;
        }
        else
        {
            if(root->left)
               root=root->left;
            else
               break;
        }
    }while(root);
    if(res>=0)
       root->right=newnode;
    else
       root->left=newnode;
    bst->count++;
    return true;
}

bool delete_bst_node(BST *bst,void *key)
{
    TNODE *curnode,*parent=NULL;
    int res;
    curnode=bst->root;
    while(curnode)
    {
        res=bst->compare(curnode->dp,key);
        if(res==0)
        {
           break;
        }
        else if(res>0)
        {
            parent=curnode;
            curnode=curnode->right;
        }
        else
        {
            parent=curnode;
            curnode=curnode->left;
        }
    }
    if(curnode==NULL)
       return false;
    if(curnode->left==NULL&&curnode->right==NULL)
    {
        if(parent)
        {
            if(parent->left==curnode)
               parent->left=NULL;
            else
               parent->right=NULL;
        }
        else
        {
            bst->root=NULL;
        }
    }
    else if(curnode->left==NULL)
    {
        if(parent)
        {
            if(parent->left==curnode)
               parent->left=curnode->right;
            else  
               parent->right=curnode->right;
        }
        else
        {
            bst->root=curnode->right;
        }
    }
    else if(curnode->right=NULL)
    {
        if(parent)
        {
            if(parent->left==curnode)
               parent->left=curnode->left;
            else
               parent->right=curnode->left;
        }
        else
        {
            bst->root=curnode->left;
        }
    }
    else
    {
        TNODE *s,*ps;
        s=curnode->right;
        ps=curnode;
        while(s->left)
        {
            ps=s;
            s=s->left;
        }
        if(ps==curnode)
        {
            if(parent)
            {
                if(parent->left==curnode)
                {
                    s->left=curnode->left;
                    parent->left=s;
                }
                else
                {
                    s->left=curnode->left;
                    parent->right=s;
                }
            }
            else
            {
               s->left=curnode->left;
               bst->root=s;
            }
        }
        else
        {
           if(s->right)
           {
               ps->left=s->right;
           }
           else
               ps->left=NULL;
           s->left=curnode->left;
           s->right=curnode->right;
           if(parent)
           {
               if(parent->left==curnode)
                  parent->left=s;
               else
                   parent->right=s;
           }
           else
           {
               bst->root=s;
           }
        }
    }
    printf("The node to be deleted:");
    bst->print(curnode->dp);
    printf("\n");
    free(curnode->dp);
    free(curnode);
    return true;
}

void preorder(BST *bst,TNODE *root)
{
    if(root)
    {
        bst->print(root->dp);
        preorder(bst,root->left);
        preorder(bst,root->right);
    }
}

void inorder(BST *bst,TNODE *root)
{
    if(root)
    {
        inorder(bst,root->left);
        bst->print(root->dp);
        inorder(bst,root->right);
    }
}

void postorder(BST *bst,TNODE *root)
{
    if(root)
    {
        postorder(bst,root->left);
        postorder(bst,root->right);
        bst->print(root->dp);
    }
}

void breadth_first(BST *bst)
{
    TNODE *currentnode;
    QHEAD *q;
    q=createq();
    currentnode=bst->root;
    while(currentnode)
    {
        bst->print(currentnode->dp);
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

void find_key_parent(BST *bst,TNODE *t,TNODE **p,void *key)
{
    if(t)
    {
        if(!bst->compare(t->dp,key))                                     //bst->compare---->!bst->compare
           return;
        if(t->left)
        {
            if(!bst->compare(t->left->dp,key))                            //bst->compare----->!bst->compare
            {
                *p=t;
                return;
            }
            find_key_parent(bst,t->left,p,key);
        }
        if(t->right)
        {
            if(!bst->compare(t->right->dp,key))                          //bst->compare---->!bst->compare
            {
                *p=t;
                return;
            }
            find_key_parent(bst,t->right,p,key);
        }
    }
}

void find_keyfrequency(BST *bst,TNODE *root,int *freq,void *key)
{
    if(root)
    {
        if(!bst->compare(root->dp,key))                              //bst->compare------->!bst->compare
           (*freq)++;
        if(root->left)
           find_keyfrequency(bst,root->left,freq,key);
        if(root->right)
           find_keyfrequency(bst,root->right,freq,key);
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

bool balanced_tree(BST *bst)
{
    TNODE *root;
    int bf,hleft,hright;
    root=bst->root;
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

void deletenode(BST *bst,TNODE *t)
{
    if(t)
    {
        deletenode(bst,t->left);
        deletenode(bst,t->right);
        printf("Node to be deleted:");
        bst->print(t->dp);
        printf("\n");
        bst->count--;
        free(t);
    }
}

void destroy(BST *bst)
{
    if(bst)
    {
        deletenode(bst,bst->root);
        free(bst);
    }
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

bool copy_tree(BST *b1,BST *b2)
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


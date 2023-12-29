#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"BSTADT.h"

int compare(void *d1,void *d2)
{
    if((*(int*)d1)==(*(int*)d2))
       return 0;
    else if((*(int*)d1)<(*(int*)d2))
       return 1;
    else
       return -1;
}

void printnode(void *d)
{
    printf("%d",*(int*)d);
}

void tree_search(BST *bst)
{
    int c,freq;
    int *key;
    TNODE *parent,*keynode;
    while(1)
    {
        printf("1.Find key element\n2.find occurance of key element\n3.find parent of key element\n4.Return back to main menu\n");
        scanf("%d",&c);
        if(c<4)
        {
            key=(int*)malloc(sizeof(int));
            printf("Enter key string\n");
            scanf("%d",key);
        }
        switch(c)
        {
            case 1:if(searchkey(bst,bst->root,key))
                      printf("Search is successful\n");
                   else
                      printf("Key not found\n");
                   break;
            case 2:freq=0;
                   find_keyfrequency(bst,bst->root,&freq,key);
                   printf("Key string has occured %d times in tree\n",freq);
                   break;
            case 3:parent=NULL;
                   find_key_parent(bst,bst->root,&parent,key);
                   if(!parent&&(!bst->compare(bst->root->dp,key)))                            //bst->compare----->1bst->compare
                      printf("Root itself is the key.\nhence it does not have parent\n");
                   else if(!parent)
                      printf("Key string has not found in the tree\n");
                   else
                      printf("Parent of key string %d=%d\n",*(int*)key,*(int*)parent->dp);            //(int*)----->*(int*)
                   break;
            case 4:return;
            default:printf("Invalid choice\n");
        }
    }
}

void traverse(BST *t)
{
    int c;
    while(1)
    {
        printf("1.Pre order\n2.In order\n3.Post order\n4.Breadth first traversal\n5.To return to main menu\n");
        scanf("%d",&c);
        switch(c)
        {
            case 1:printf("Pre-order travesal of the tree\n");
                   preorder(t,t->root);
                   break;
            case 2:printf("In-order traversal of the tree\n");
                   inorder(t,t->root);
                   break;
            case 3:printf("Post-order traversal of the tree\n");
                   postorder(t,t->root);
                   break;
            case 4:printf("Breadth first traversal of hte tree\n");
                   breadth_first(t);
                   break;
            case 5:return;
            default:printf("Invlaid choice\n");
        }
    }
}

int main()
{
    int ch,height;
    BST *bst,*temp;
    int *tdata;
    bst=createtree(compare,printnode);
    if(!bst)
    {
        printf("Binary tree creation failed\n");
        printf("Program is terminating\n");
        return 1;
    }
    while(1)
    {
        printf("1.insert\n2.delete an element\n3.check whether the tree is balanced or not\n4.height of the tree\n5.tree search(frequency,find......)\n6.tree nodes\n7.tree traversals\n8.copy tree\n9.Destroy\n");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("-----------------------------\n");
                   printf("Enter string to insert\n");
                   tdata=(int*)malloc(sizeof(int));
                   scanf("%d",tdata);
                   if(insert_BST(bst,tdata))
                      printf("String insertion successful\n");
                   else
                      printf("Insertion failed\n");
                   printf("--------------------------------\n");
                   break;
            case 2:printf("----------------------------\n");
                   tdata=(int*)malloc(sizeof(int));
                   printf("Enter key string to delete\n");
                   scanf("%d",tdata);
                   if(delete_bst_node(bst,tdata))
                      printf("Deletion successful\n");
                   else
                      printf("Deletion failed\n");
                   printf("-----------------------------\n");
                   break;
            case 3:if(balanced_tree(bst))
                      printf("Tree is balanced\n");
                   else 
                      printf("Tree is not balanced\n");
                   break;
            case 4:height=find_tree_height(bst->root);
                   printf("Heigth of the tree=%d\n",height);
                   break;
            case 5:tree_search(bst);
                   break;
            case 6:height=0;
                   noofleaves(bst->root,&height);
                   printf("No of leaf nodes=%d\n",height);
                   printf("No of internal nodes=%d\n",bst->count-height);
                   printf("Total nodes=%d\n",bst->count);
                   break;
            case 7:printf("----------------------------\n");
                   traverse(bst);
                   break;
            case 8:temp=createtree(compare,printnode);
                   if(copy_tree(bst,temp))
                   {
                       traverse(temp);
                       destroy(temp);
                   }
                   else
                   {
                       printf("Copy tree operatio failed\n");
                       free(temp);  
                   }
                   break;
            case 9:destroy(bst);
                   printf("Program terminating\n");
                   exit(0);
                   break;
            default:printf("Invalid choice\n");
        }
    }
    return 1;
}
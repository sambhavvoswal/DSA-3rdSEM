#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"BinarytreeADT.h"

bool compare(void *d1,void *d2)
{
    if(!strcmp((char*)d1,(char*)d2))
       return true;
    return false;
}

void printnode(void *d)
{
    printf("%s",(char*)d);
}

void tree_search(BTREE *t)
{
    int c,freq;
    char key[20];
    TNODE *parent,*keynode;
    while(1)
    {
        printf("1.Find key element\n2.find occurance of key element\n3.find parent of key element\n4.Return back to main menu\n");
        scanf("%d",&c);
        if(c<4)
        {
            printf("Enter key string\n");
            scanf("%s",key);
        }
        switch(c)
        {
            case 1:keynode=search_node(t,t->root,key);
                   if(keynode)
                      printf("Search is successful\n");
                   else
                      printf("Key not found\n");
                   break;
            case 2:freq=0;
                   find_keyfrequency(t,t->root,&freq,key);
                   printf("Key string has occured %d times in tree\n",freq);
                   break;
            case 3:parent=NULL;
                   find_key_parent(t,t->root,&parent,key);
                   if(!parent&&t->compare(t->root->dp,key))
                      printf("Root itself is the key.\nhence it does not have parent\n");
                   else if(!parent)
                      printf("Key string has not found in the tree\n");
                   else
                      printf("Parent of key string %s=%s\n",key,(char*)parent->dp);
                   break;
            case 4:return;
            default:printf("Invalid choice\n");
        }
    }
}

void traverse(BTREE *t)
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
    BTREE *bt,*temp;
    char *tdata;
    bt=createtree(compare,printnode);
    if(!bt)
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
                   tdata=(char*)calloc(20,sizeof(char));
                   scanf("%s",tdata);
                   if(insert_node(bt,tdata))
                      printf("String insertion successful\n");
                   else
                      printf("Insertion failed\n");
                   printf("--------------------------------\n");
                   break;
            case 2:printf("----------------------------\n");
                   tdata=(char*)calloc(20,sizeof(char));
                   printf("Enter key string to delete\n");
                   scanf("%s",tdata);
                   if(deletekeynode(bt,tdata))
                      printf("Deletion successful\n");
                   else
                      printf("Deletion failed\n");
                   printf("-----------------------------\n");
                   break;
            case 3:if(balanced_tree(bt))
                      printf("Tree is balanced\n");
                   else 
                      printf("Tree is not balanced\n");
                   break;
            case 4:height=find_tree_height(bt->root);
                   printf("Heigth of the tree=%d\n",height);
                   break;
            case 5:tree_search(bt);
                   break;
            case 6:height=0;
                   noofleaves(bt->root,&height);
                   printf("No of leaf nodes=%d\n",height);
                   printf("No of internal nodes=%d\n",bt->count-height);
                   printf("Total nodes=%d\n",bt->count);
                   break;
            case 7:printf("----------------------------\n");
                   traverse(bt);
                   break;
            case 8:temp=createtree(compare,printnode);
                   if(copy_tree(bt,temp))
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
            case 9:destroy(bt);
                   printf("Program terminating\n");
                   exit(0);
                   break;
            default:printf("Invalid choice\n");
        }
    }
    return 1;
}

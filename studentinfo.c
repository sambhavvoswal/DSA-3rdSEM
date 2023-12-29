#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"pdLLLinkedListADT.h"

typedef struct 
{
    char name[30];
    char usn[15];
    char branch[10];
    int sem;
}student;

bool compusn(void *pd,void *key)
{
   student *pdata;
   pdata=(student*)pd;
   if(!strcmp(pdata->usn,(char*)key))
      return true;
   return false;
}

bool compname(void *pd,void *key)
{
   student *pdata;
   pdata=(student*)pd;
   if(!strcmp(pdata->name,(char*)key))
      return true;
   return false;
}

void printnode(void *pd)
{
   student *pnode;
   if(!pd)
      return;
   pnode=(student*)pd;
   printf("Student details are:\n");
   printf("Name:%s\n",pnode->name);
   printf("Student USN:%s\n",pnode->usn);
   printf("Branch:%s\n",pnode->branch);
   printf("Sem:%d\n",pnode->sem);
}

int main()
{
    LHEADER *list;
    LNODE *t;
    //void *pdata;
    student *pdata;
    int choice;
    char sname[30];
    char susn[15];
    list=createlist();
    if(!list)
       return 1;
    printf("Application to create list of students\n");
    while(1)
    {
        printf("1.insert\n2.delete\n3.search\n4.display\n5.list empty\n6.list full\n7.destroy\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("Enter student details\n");
                   pdata=(student*)malloc(sizeof(student));
                   printf("Enter name of the student\n");
                   scanf("%s",pdata->name);
                   printf("Enter student USN\n");
                   scanf("%s",pdata->usn);
                   printf("Enter branch\n");
                   scanf("%s",pdata->branch);
                   printf("Enter sem\n");
                   scanf("%d",&pdata->sem);
                   printf("Enter the position to insert\n");
                   printf("1.beginning\n2.middle\n3.end\n");
                   scanf("%d",&choice);
                   switch(choice)
                   {
                       case 1:if(insert_beginning(list,pdata))
                                 printf("Insertion successful\n");
                              else
                                 printf("Insertion failed\n");
                              break;
                       case 2:printf("Enter the student name after which the entered details should be inserted\n");
                              scanf("%s",sname); 
                              if(insert_middle(list,sname,pdata,compname))
                                 printf("Insertion successful\n");
                              else
                                 printf("Insertion failed\n");
                              break;
                       case 3:if(insert_end(list,pdata))
                                 printf("Insertion successful\n");
                              else
                                 printf("Insertion failed\n");
                              break;
                       default:printf("Invalid choice\n");
                   }
                   break;
            case 2:printf("enter hte position to delete\n");
                   printf("1.beginning\n2.middle\n3.end\n");
                   scanf("%d",&choice);
                   switch(choice)
                   {
                       case 1:pdata=(student*)delete_beginning(list);
                              break;
                       case 2:printf("Enter the name of the student whose details are to be deleted\n");
                              scanf("%s",sname);
                              pdata=(student*)delete_middle(list,sname,compname);
                              break;
                       case 3:pdata=(student*)delete_end(list);
                              break;
                       default:printf("Invalid choice\n");
                    }
                    if(pdata)
                    {
                        printf("Node to be deleted:\n");
                        printf("Student name:%s\n",pdata->name);
                        printf("USN:%s\n",pdata->usn);
                        printf("Branch:%s\n",pdata->branch);
                        printf("Sem:%d\n",pdata->sem);
                        free(pdata);
                    }
                    else
                    {
                        printf("Delete operation has failed\n");
                    }
                    break;
            case 3:printf("To search\n1.By student name\n2.By USN\n");
                   scanf("%d",&choice);
                   switch(choice)
                   {
                       case 1:printf("Enter student name\n");
                              scanf("%s",sname);
                              if(searchlist(list,sname,compname))
                                 printf("Search is successful\n");
                              else
                                 printf("student details not found\n");
                              break;
                       case 2:printf("Enter student USN\n");
                              scanf("%s",susn);
                              if(searchlist(list,susn,compusn))
                                 printf("Search is successful\n");
                              else
                                 printf("Student details not found\n");
                              break;
                       default:printf("Invalid choice\n");
                   }
                   break;
            case 4:displaylist(list,printnode);
                   break;
            default:printf("Invalid choice\n");
        }
    }
    return 0;   
}
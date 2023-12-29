
#include<stdio.h>
#include<string.h>
#include"arraystackADT.h"

int priority(char token)
{
	if(token=='*'||token=='/')
	  return 2;
	if(token=='+'||token=='-')
	  return 1;
    return 0;
}
bool isoperator(char token)
{
	if(token=='*'||token=='/'||token=='+'||token=='-')
	   return true;
	return false;
}

int main()
{
	char p[80]={0};
	char temp[2]={0};
	char token;
	char *data;
	STACK *s;
	s=stackcreate(20);
	printf("Infix To Postfix Expression\n");
	printf("Enter an Infix formula: ");
	while((token=getchar())!='\n')
	{
		if(token=='(')
		{
			data=(char*)malloc(sizeof(char));
			*data=token;
			pushstack(s,data);
		}
		else if(token==')')
		{
			data=(char*)popstack(s);
			while(*data!='(')
			{
				temp[0]=*data;
				strcat(p,temp);
				data=(char*)popstack(s);
			}
		}
		else if(isoperator(token))
		{
			data=(char*)stacktop(s);
			while(!emptystack(s)&&priority(token)<=priority(*data))
			{
				data=(char*)popstack(s);
				temp[0]=*data;
				strcat(p,temp);
				data=(char*)stacktop(s);
			}
			data=(char*)malloc(sizeof(char));
			*data=token;
			pushstack(s,data);
		}
		else
		{
			temp[0]=token;
			strcat(p,temp);
		}
	}
	while(!emptystack(s))
	{
		data=(char*)popstack(s);
		temp[0]=*data;
		strcat(p,temp);
	}
	printf("postfix formula is: ");
	puts(p);
	destroystack(s);
	return 0;
}

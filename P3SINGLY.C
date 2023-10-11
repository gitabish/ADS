#include<stdio.h>
#include<stdlib.h>
struct Node
{
  int data;
  struct Node*next;
};
struct Node*top=NULL;
int count=0;
struct Node*temp;
void display()
{
  struct Node*temp=top;
  if(count==0)
  {
    printf("\n Stack is empty!\n");
    return;
  }
  else
  {
    printf("\n There are currently %d items:\n",count);
    while(temp!=NULL)
    {
      printf("%d ",temp->data);
      temp=temp->next;
    }
    printf("\n");
  }
}
void push(int el)
{
  struct Node*temp=(struct Node*)malloc(sizeof(struct Node));
  if(temp==NULL)
  {
    printf("Memory allocation failed.\n");
    return;
  }
  temp->data=el;
  temp->next=top;
  top=temp;
  count++;
  display();
}
void pop()
{
  if(count==0)
  {
    printf("\n Stack is empty!\n");
    return;
  }
  temp=top;
  top=top->next;
  printf("\n Item to be removed is %d.\n",temp->data);
  free(temp);
  count--;
  display();
}
void search()
{
  int item,flag=0,position=1;
  printf("Enter search element:");
  scanf("%d",&item);
  if(top==NULL)
  {
    printf("stack underflow\n");
    return;
  }
  temp=top;
  while(temp!=NULL)
  {
    if(temp->data==item)
    {
      flag=1;
      printf("\n Element %d found at position %d\n",item,position);
      break;
    }
    else
    {
      temp=temp->next;
      position++;
    }
  }
  if(flag==0)
  {
    printf("\n element %d not found \n",item);
  }
}
void main()
{
  int choice,element;
  clrscr();
  while(1)
  {
    printf("\n Stack operations:\n");
    printf(" 1.Push\n 2.Pop\n 3.Display\n 4.Search\n 5.Exit\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:
	     printf("Enter element to push:");
	     scanf("%d",&element);
	     push(element);
	     break;
      case 2:
	     pop();
	     break;
      case 3:
	     display();
	     break;
      case 4:
	     search();
	     break;
      case 5:
	     exit(0);
	     break;
      default:
	      printf("Invalid choices please try again.\n");
    }
  }
}
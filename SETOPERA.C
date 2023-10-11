#include<stdio.h>
#include<conio.h>
void input();
void output();
void setunion();
void intersection();
void difference();
int a[]={0,0,0,0,0,0,0,0,0},b[]={0,0,0,0,0,0,0,0,0},c[]={0,0,0,0,0,0,0,0,0,0};
void main()
{
  int ch,wish;
  clrscr();
  do
  {
    printf("\n MENU\n");
    printf("\n 1.Input\n 2.Union\n 3.Intersection\n 4.Difference\n");
    printf("\n Enter your choice:");
    scanf("%d",&ch);
    switch(ch)
    {
      case 1:
	     input();
	     break;
      case 2:
	     setunion();
	     break;
      case 3:
	     intersection();
	     break;
      case 4:
	     difference();
	     break;
      default:
	      printf("wrong choice");
    }
    printf("\nDo you wish to continue(1/0) \n");
    scanf("%d",&wish);
  }
  while(wish==1);
  getch();
}
void input()
{
  int n,ele,i;
  printf("Enter the size of first set:");
  scanf("%d",&n);
  printf("Enter the elements:\n");
  for(i=1;i<=n;i++)
  {
    scanf(" %d",&ele);
    a[ele]=1;
  }
  printf("ENter the size of second set:");
  scanf("%d",&n);
  printf("Enter the elements:\n");
  for(i=1;i<=n;i++)
  {
    scanf(" %d",&ele);
    b[ele]=1;
  }
  printf("\n The first set:");
  for(i=1;i<=9;i++)
  {
    printf("%d\t",a[i]);
  }
  printf("\n The second set:");
  for(i=1;i<=9;i++)
  {
    printf("%d\t",b[i]);
  }
}
void output(int c[])
{
  int i;
  printf("\n Set is:");
  for(i=1;i<=9;i++)
  {
    if(c[i]!=0)
    {
      printf("%d\t",i);
    }
  }
}
void setunion()
{
  int i,c[10];
  for(i=1;i<=9;i++)
  {
    if(a[i]!=b[i])
    {
      c[i]=1;
    }
    else
    {
      c[i]=a[i];
    }
  }
  for(i=1;i<=9;i++)
  {
    printf("%d\t",c[i]);
  }
  output(c);
}
void intersection()
{
  int i,c[10];
  for(i=1;i<=9;i++)
  {
    if(a[i]==b[i])
	c[i]=a[i];
    else
	c[i]=0;
  }
  for(i=1;i<=9;i++)
  {
    printf("%d\t",c[i]);
  }
  output(c);
}
void difference()
{
  int i,c[10];
  for(i=1;i<=9;i++)
  {
    if(a[i]==1&&b[i]==0)
	 c[i]=1;
    else
	 c[i]=0;
  }
  for(i=1;i<=9;i++)
  {
    printf("%d\t",c[i]);
  }
  output(c);
}

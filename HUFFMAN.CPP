#include <stdio.h>
#include <string.h>
#include<conio.h>
#include<malloc.h>
#define NULL 0

struct node
{
  int f ;
  struct node *left, *right, *father ;
  int leftson ; // leftson will be 1 for left son and 0 for right son
};

struct node1
{
  struct node *data ;
  struct node1 *next ;
};

struct  node1  *front =NULL, *rear=NULL;
int count = 0 ; // counts the number of elements in PQ

void insert(struct node* x)
{
  struct  node1  *pnode ;
  pnode=(struct node1*)malloc(sizeof(struct node1)) ;
  pnode->data=x ;
  pnode->next=NULL;   /* New node is always last node */
  if(front==NULL)
  {
    front=rear=pnode ;
  }
  else
  {
      rear->next=pnode ;
      rear=pnode ;
  }
  ++count ;
}

struct node* removes()
{
  int  min ;
  struct  node1  *follow , *follow1 , *p , *p1 ;

  /* finding the node with minimum value in the APQ.*/

  p=p1=front ;
  follow=follow1=NULL ;
  min=front->data->f ;
  while(p!=NULL)
  {
    if(p->data->f < min)
    {
	 min=p->data->f ;
	 follow1=follow ;
	 p1=p ;
    }
    follow=p ;
    p=p->next ;
  }

  /* Deleting the node with min value */

  if(p1==front)  /* deleting first node.*/
  {
    front=front->next ;
    if(front==NULL) /* Deleting the only one node */
     {
       rear=NULL ;
     }
  }
  else
  {
    if(p1==rear)  /* Deleting last node */
    {
      rear=follow1 ;
      rear->next=NULL ;
    }
    else
    { 			/* deleting any other node.*/
      follow1->next=p1->next ;
    }
  }
  --count ;
  return  p1->data ;
}

struct node *root = NULL;

int  frequency[100];

struct node*  position[100];

void main()
{
  clrscr();
  struct node *p1, *p2, *p, *pnode ;
  int  i , j , n, k, l, s;
  char input[100],text[100];
  printf("Enter text: ");
  gets(input);
  n=strlen(input);
  for(i=0;i<n;i++)       //setting text as NULL string
  {
   text[i]='\0';
  }
  text[0]=input[0];
  l=0;
  for(i=0;i<n;i++)       // counting the entered letters
  {
    for(k=0;k<=i;k++)
    {
      if(input[i]!=text[k] && text[k+1]=='\0')
      {
       l++;
       text[l]=input[i];
      }
      else if(input[i]==text[k])
      {
       k=i;
      }
    }
  }

  s=strlen(text);
  printf("Entered characters are : ");
  for(k=0;k<s;k++)           // display entered letters once
  {
   printf("%c ",text[k]);
  }
  printf("\n");

  for(k=0;k<s;k++)           //count frequency of each letter
  {
    frequency[k]=0;
    for(i=0;i<n;i++)
    {
     if(text[k]==input[i])
     {
      frequency[k]++;
     }
    }
  }

  printf("\n");

  for(k=0;k<s;k++)        //print frequency of each letter
  {
   printf("Frequency of %c is %d\n",text[k],frequency[k]) ;
  }

  for(k=0;k<s;k++)
  {
   pnode=(struct node*)malloc(sizeof(struct node)) ;
   pnode->f=frequency[k] ;
   position[k] = pnode;
   insert(pnode);
  }

// Constructing the Huffman tree

  while(count>1)
  {
   p1=removes();
   p2=removes();
   p=(struct node*)malloc(sizeof(struct node)) ;
   p->f = p1->f + p2->f ;
   p->left=p1;
   p->right=p2;
   p1->father=p;
   p1->leftson=1;
   p2->father=p;
   p2->leftson=0;
   insert(p);
  }

// Use the constructed tree to find codes

  root=removes();
  for(k=0;k<s;k++)
  {
    p=(struct node*)malloc(sizeof(struct node)) ;
    p=position[k];
    char  code[20]="\0";

    // Travel up the tree

    while(p!=root)
    {
	if(p->leftson==1)
	{
	  strcat(code,"0") ;
	}
	else
	{
	 strcat(code,"1") ;
	}
	p=p->father;
    }
    printf("\nCode of symbol %c is: ",text[k]) ;
    for(j=strlen(code)-1;j>=0;j--)
    {
     printf("%c",code[j]) ;
    }
  }
getch();
}
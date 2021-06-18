#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
struct node{
	char book_name[50];
	char author_name[50];
	int book_id;
	char book_genre[50];
	struct node* link;
	
};
typedef struct node *Node;

Node getnode()
{
	Node x;
	x = (Node)malloc(sizeof(struct node));
	
	if(x == NULL)
	{
	
		printf("out of memory\n");
		
	}
	return x;
}

void swap(Node a, Node b)
{
	Node temp=getnode();
	strcpy(temp->book_name, a->book_name);
	strcpy(temp->author_name, a->author_name);
	strcpy(temp->book_genre, a->book_genre);
	temp->book_id = a->book_id;
	
	a->book_id = b->book_id;
	strcpy(a->book_name, b->book_name);
	strcpy(a->author_name, b->author_name);
	strcpy(a->book_genre, b->book_genre);
	
	b->book_id = temp->book_id;
	strcpy(b->book_name, temp->book_name);
	strcpy(b->author_name, temp->author_name);
	strcpy(b->book_genre, temp->book_genre);
	free(temp);
}

void bubble_sort(Node first)
{
	Node cur, prev;
	int swapped = 0;
	if (first == NULL)
	{
		printf("empty list\n");
		return;
	}
	prev=NULL;
	do
	{	
		cur = first;
		swapped = 0;
		while(cur->link != prev)
		{
			
			if(cur->book_id > cur->link->book_id)
			{
				swap(cur, cur->link);
			}
			cur= cur->link;
			swapped=1;
		}
		prev = cur;
	}while(swapped);
}


Node insert(char book_name[], char author_name[], int book_id, char book_genre[], Node first)
{
	Node temp;
	Node cur;
	temp = getnode();
	strcpy(temp->book_name, book_name);
	strcpy(temp->author_name, author_name);
	strcpy(temp->book_genre, book_genre);
	temp->book_id = book_id;
	temp->link = NULL;
	if(first == NULL)
		return temp;
	cur = first;
	while(cur->link != NULL)
		cur = cur->link;
	cur->link = temp;
	return first;	
}

void display(Node first)
{
	Node temp;
	if (first==NULL)
	{
		printf("nothing to display\n");
		return;
	}
	bubble_sort(first);
	printf("Book Name\t|Authors Name\t|Genre\t|Book id number\n");
	printf("_________\t|____________\t|_____\t|______________\n");
	for(temp=first; temp!= NULL; temp = temp->link)
	{
		printf("%s\t\t|%s\t|%s\t|%d\n", temp->book_name, temp->author_name, temp->book_genre, temp->book_id);
	}
}

Node remove_book(Node first, int id)
{
	Node temp, cur, prev;
	if(first == NULL)
	{
		printf("no books found\n");
		return first;	
	}	
	if(first->book_id== id)
	{
		temp= first;
		first = first->link;
		printf("removed book is %s with book id %d", temp->book_name, temp->book_id);
		free(temp);
		return first;
	}
	prev = NULL;
	cur = first;
	while(cur != NULL && id != cur->book_id)
	{
		prev = cur;
		cur = cur->link;
	}
	if(cur == NULL)
	{
		printf("book not found\n");
		return first;
	}
	printf("removed book is %s with book id %d", cur->book_name, cur->book_id);
	prev->link = cur->link;
	free(cur);
	return first;
}

Node search(int id, Node first)
{
	Node cur;
	cur = first;
	if(first== NULL)
	{
		printf("no books found\n");
		return first;
	}
	while(cur!= NULL && cur->book_id != id)
	{
		cur = cur->link;
	}
	if(cur==NULL)
	{
		printf("scan completed, no books found with this id \n");
	}
	else
	{
		printf("scan completed...\n Book found with id %d is %s by %s", cur->book_id, cur->book_name, cur->author_name);
	}
	return first;
	
}

int main()
{
	int book_id, ch, i, j;
	char book_name[50], author_name[50], book_genre[50];
	
	Node first = NULL;
	for(;;)
	{
		printf("\n1. Insert 2. Search 3. Display 4. Remove 5. exit\n");
		printf("enter your choice \n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("enter: \n1. book id\n2. Book name\n3. author name\n4. Book genre \n");
					scanf("%d", &book_id); 
					gets(book_name);
					gets(book_name); 
					gets(author_name);
					gets(book_genre);
					first = insert(book_name, author_name, book_id, book_genre, first);
					break;	
			case 2: printf("enter book id\n");
					scanf("%d", &book_id);
					first = search(book_id, first);
					break;
			case 3: display(first);
					break;
			case 4: printf("enter book id\n");
					scanf("%d", &book_id);
					first = remove_book(first,book_id );
					break;
			default: printf("exit code....\n");
					exit(0);
		}
	}
	getch();
}

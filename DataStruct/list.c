/**
* list.c
* 2012-08-09 tusion@163.com
*/

/**
* thsi is practice data struct of list
*/
#include <fcntl.h>		//open();
#include <unistd.h> 	//read();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#define MAX 20		//the max length of name string
#define BUFFSIZE 100	//the max length of read data per cloumn
#define	TRUE 1		//BOOL
#define FALSE 0

struct list
{
	int number;
	char name[MAX];
	//	long int hash;
	struct list* next;
};

typedef struct list node;
typedef node	*my_link;
/**
* in put the data file name( list_demo.data ), and creat a list data struct
*/
my_link CreateList( char *datafile )
{

	char 	*buf;
	FILE    *data_fp;
	my_link  start;
	my_link  head;
	my_link	 new;
	int 	 initial=TRUE;
	printf("===================================================\n");
	printf("creat a new list struct, datafile is %s\n",datafile);
	printf(" size of struct list:%d,  node:%d, my_link:%d", \
			sizeof(struct list), sizeof(node), sizeof(my_link));
	data_fp = NULL;
	if( (buf = malloc(sizeof(char) * BUFFSIZE )) == NULL )
	{
		printf("memory allocate error! \n");
		exit(1);
	}

	
	printf("Input the data from datafile %s\n",datafile);
	if( ( data_fp = fopen( datafile, "r")) == NULL )
	{
		printf("open data file error!\n" );
		exit(1);
	}

	/**
	*Add data item to the my_link list
	*/
	fgets( buf, BUFFSIZE, data_fp ); 			//clear the first cloumn
	int i = 0;
	while( ( fgets( buf, BUFFSIZE, data_fp )) != NULL )
	{	
		//printf("Start to create lsit node %d",++i);
		/**
		*Initial the new node.
		*/
		new = (my_link) malloc( sizeof( node ) );
		if( !new)
		{
			printf("memory allocate error!\n");
			exit(0);
		}
		new->next = NULL;
		if( initial )
		{
			start = new;
			initial = FALSE;
		}
		else
		{
			head->next = new;
		}

		/**
		*this get rid of space in a name string,cool!
		*eg:	sscanf("1,Tu Can", "%d,%[A-Za-z, ]", \
		*				&head->number, head->name );
		*/
		//sscanf( buf, "%d,%s", &head->number, head->name );
		sscanf( buf, "%d,%[A-Za-z, ]", &new->number, new->name );
		/*
		printf("read the head->num:%d, head->name:%s\n", \
				new->number, new->name );
		*/
		head = new;
	}
	if( ferror( data_fp ) )
	{
		printf(" data file read error\n");
		exit(0);
	}
	fclose( data_fp );
	head->next = NULL;
	return start;
	}

/**
*Go through and print all items in the my_link list
*/
void PrintList( my_link head )
{
	my_link temp;
	temp = head;
	printf("==================================================\n");
	printf("print all items in my_link list\n");
	for( temp=head; temp != NULL; temp=temp->next)
	{
		printf(" Num =%2d | name=%20s | node add:0x%x | next add:0x%x\n",\
				temp->number, temp->name, temp, temp->next);
	}
}

/**
*free the every list item
*/
void FreeList( my_link head )
{
	int i = 0;

	printf("====================================================\n");
	while( head != NULL )
	{
		printf("free list: %d node add:%x\n", ++i, head);
		head = head->next;
		free( head );
	}
	printf("success free the list\n");
}

/**
* searche a intem in the list by key
* return: success:1, fail:0.
*/
int ListKeySearch( int key, my_link head )
{
	my_link temp;
	printf("====================================================\n");
	if( head != NULL )
	{
		for( temp=head; temp!= NULL; temp=temp->next)
		{
			if( temp->number == key )
			{
				printf(" searched key:%d, the item is %s\n",\
						key, temp->name );
				return 1;
			}
		}	
	}
	printf("failed to search the key's item\n");
	return 0;
}

/**
* searche a intem in the list by name
* return: success:1, fail:0.
*/
int ListNameSearch( char *name, my_link head )
{
	my_link temp;
	printf("====================================================\n");
	if( head != NULL )
	{
		for( temp=head; temp != NULL; temp = temp->next )
		{
			if( ( strcmp(& temp->name, name ) == 0 ))
			{
				printf(" success searched item name %s, key is num:%d\n",\
						temp->name, temp->number );
				return 1;
			}
		}
	}
	printf(" failed to search the item's name\n" );
	return 0;
}

/**
*Insert any item at any where in a list
*/
my_link InsertList( my_link head, node *new, int key )
{
	my_link temp;
	printf("==========================================================\n");
	for( temp=head; temp !=NULL; temp = temp->next )
	{
		if( temp->number == key-1 )
		{
			printf("insert a node at num:%d\n", key);
			new->next = temp->next;
			temp->next = new;
			/**
			* after add new node, sort the node number
			*/
			int i = key-1;
			my_link midtemp;
			for( midtemp=temp; midtemp!=NULL; midtemp=midtemp->next)
				midtemp->number = i++; 
			
			break;
		}
	}
	return head;
}	

/**
*delete any item in the list
*/
my_link DeleteList( my_link head, int key)
{
	my_link temp1, temp2;
	printf(" delete the node number:%d\n", key );
	for( temp1=head; temp1!=NULL; temp1=temp1->next)
	{
		if( temp1->number == key-1 )
		{
			temp2 = temp1->next;
			temp1->next =  temp2->next;
			for(temp1=temp1->next; temp1 !=NULL; temp1=temp1->next )
				temp1->number -= 1;
			free( temp2 );
			break;
		}
	}
	return head;
}	

/**
*invert all item in the list
* this is the most diffcult function in the list structure
*/
my_link InvertList( my_link head )
{
	my_link old, mid, new;
	my_link temp;

	printf("================================================\n");
	printf("Invert all items in the list\n");
	old = head;
	mid = head->next;
	new = mid->next;
	head->next = NULL;

	while( mid->next != NULL )
	{
		mid->next = old;
		old = mid;
		mid = new;
		new = mid->next;
	}
	mid->next = old;
	return mid;
}


/**
*connecte two list 
*/
my_link ConcatenateList( my_link head1, my_link head2 )
{
	my_link node;
	int t;
	printf("=========================================================\n");
	if( head1!=NULL && head2!=NULL )
	{
		for( node=head1; node->next!=NULL; node=node->next )
			printf(">");
		printf("\ngo through list1 until  address:%x\n", node);
		node->next = head2;
		t = node->number;
		for( node=head2; node!=NULL; node=node->next )
			node->number = ++t;
		printf("success concatenate two list\n");
	}
	return head1;
}

/**
* Below is used the list struct in practice.
* as strack, queue.
*/

#define STACK_MAX_SIZE 10

int stack[STACK_MAX_SIZE];
int top = -1;

/**
*stack use array struct
*/
void stack_array_push( int value )
{
	int t;

	printf("\n=================================================\n");
	if( top < STACK_MAX_SIZE )
	{
		stack[++top] = value;
		printf("push stack[%d]=%d.\n", top, stack[top]);
	}
	else
	{
		printf("stack is full\n");
	}
	printf(" the stack is:\n");
	for(t=0; t<=top; t++ )
		printf("[%d]:%d	",t, stack[t]);
	printf("\n");
}

/**
* stack pop use array strcut
*/
int stack_array_pop( void )
{
	int t;

	printf("\n=================================================\n");
	//for( ; top>-1; top-- )
	if( top >-1 )
	{
		printf(" pop stack[%d]=%d\n", top, stack[top] );
		top--;
		return stack[top+1];
	}
	else
		printf(" stack now is empty\n");
}

/**
* stack push used list struct
*/
my_link link_stack = NULL;

void stack_list_push( int value )
{
	my_link new,t;
	
	if( link_stack == NULL )
	{
		link_stack = (my_link) malloc( sizeof( node ) );
		if( link_stack  == NULL )
		{
			printf("memory allocate error\n");
			exit(0);
		}
		link_stack->number = value;
		link_stack->next = NULL;
	}
	else
	{
		new = (my_link) malloc( sizeof( node ) );
		if( new == NULL )
		{
			printf("memory allocate error\n");
			exit(0);
		}
		new->number= value;
		new->next = NULL;

		for( t=link_stack; t->next!=NULL; t=t->next )
			;
		t->next = new;
	}
}

/**
* stack pop used list struct
*/
int stack_list_pop( void )
{
	my_link t;
	int value;
	if( link_stack != NULL )
	{
		value = link_stack->number;
		printf(" pop stack item:%d\n", value );
		t = link_stack;
		link_stack = link_stack->next;
		free( t );
		return value;
	}
	else
		printf("stack is empty\n");
}

/**
*main program to test the sub functions.
*/
void main( void )
{
	my_link my_list, my_list2;
	char *datafile = "list_demo.data";
	node *new;
	new = (node *) malloc( sizeof( node ) );
	if( new != NULL )
	{
		strcpy( new->name, "Zhou Peng");
		new->next = NULL;
	}
	else
		printf(" allocate memory to node new error!\n");

	my_list = CreateList( datafile);
	PrintList( my_list );
	ListKeySearch( 4, my_list );
	ListNameSearch("An DongDong", my_list );

	printf("\n***** already insert a new node ihe list *********\n");
	my_list = InsertList( my_list, new, 7 );
	PrintList( my_list ); 

	printf("\n**********  delete a item in the list ***********\n");
	my_list = DeleteList( my_list, 5 );
	PrintList( my_list );
	
	my_list = InvertList( my_list );
	PrintList( my_list );

	my_list2 = CreateList( datafile );
	my_list = ConcatenateList( my_list, my_list2 );
	PrintList( my_list );

	FreeList( my_list );
	FreeList( my_list2 );

	/**
	* stack operation;
	*/
	stack_array_push( 11 );
	stack_array_push( 12 );
	stack_array_push( 13 );
	stack_array_push( 14 );
	stack_array_push( 15 );
	printf(" pop:%d \n", stack_array_pop( ));
	
	stack_list_push( 11 );
	stack_list_push( 12 );
	stack_list_push( 13 );
	stack_list_push( 14 );
	stack_list_push( 15 );
	stack_list_push( 16 );
	PrintList( link_stack );
	printf(" pop %d\n",stack_list_pop());
	PrintList( link_stack );
}

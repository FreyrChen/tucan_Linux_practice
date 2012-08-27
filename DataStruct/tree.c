/**
*tree.c
*Bsic tree data struct practice
*tusion@163.com	2012/08/16
*/
#include <fcntl.h>		//open()
#include <unistd.h>		//read()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100;		//get data number every line in the data file.


struct tree
{
	struct tree *left;
	int 		data;
	struct tree *right;
};
typedef struct tree treenode;
typedef treenode *binary_tree;

/**
* create a binary tree from a data file
*/
binary_tree CreateBinaryTree( char * datafile )
{
	FILE *data_fp;
	char *buf;
	char *number;
	int temp[20];

	printf("\n Create binary tree based on the data file %s", datafile );
/*	
	if( ( data_fp = fopen( datafile, "r" ) ) == NULL )
	{
		printf(" open input data file error\n");
		exit(0);
	}

	buf = malloc( sizeof(char) * BUF_SIZE );
	number = (char * )malloc( sizeof(char) * BUF_SIZE );
	if( buf == NULL || number == NULL )
	{
		prinft(" allocate memory to char buffer error\n");
		exit(0);
	}
	fgets( buf, BUF_SIZE, data_fp );
	while( ( fgets( buf, BUF_SIZE, data_fp ) ) != NULL )
	{
		printf(" before sscanf, buf=%s\n", buf );
		sscanf( buf, ":%[0-9,0]", number );
		printf(" after sscanf, number=%s\n", number );
	}
*/
	int i;
	binary_tree b_tree, new_tree;
	temp={6,9,7,4,5,2,1,8,12,0};
	b_tree =( binary_tree )malloc( sizeof( treenode ) );
	b_tree->data = temp[0];
	b_tree->left = NULL;
	b_tree->right = NULL;
	for( i=1; temp[i]==NULL; i++ )
	{	

			new_tree =( binary_tree )malloc( sizeof( treenode ) );
			new_tree->data = temp[i];
			new_tree->left = NULL;
			new_tree->right = NULL;
		if( temp[i] < b_tree->data )
			b_tree->left = new_tree;
		else
			b_tree->right = new_tree;

		b_tree = new_tree;
}

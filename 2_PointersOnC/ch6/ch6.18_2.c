//删除一个字符串的一部分
#include <stdio.h>

#define MAX 30

int del_substr( char *str, char *substr );

int main( void )
{
	char in_str[ MAX ] ;
	char in_substr[ MAX ];

	printf("=========================================================\n");
	printf("======We will delet the substr of the input sting.=======\n");
	printf("=========================================================\n");
	printf("Please input the string :");
	scanf("%s", in_str);
	printf("\nPlease intput the substring :");
	scanf("%s", in_substr);
	printf("string is : %s\n substr is : %s\n", in_str, in_substr);
	if( del_substr( in_str, in_substr) )
	{
		printf("The del_str is : %s \n", in_str );
		printf("The sub_str is : %s (all right???） \n", in_substr );
	}
		//return 1;
	else 
		return 0;
}

int del_substr( char *str, char *substr )
{
	char *strs;
	char *substrs;
	int flag;
	flag = 0;
	while( ( ( strs = str ) != NULL) && ( ( substrs = substr ) != NULL ) )
	{
		while( *strs != '\0' )
		{
			while( *strs == *substrs )
			{
				flag++;
				strs++;
				substrs++;
				//while( ( *strs != '\0' ) && ( *substrs != '\0' ) )
				if( *substrs == '\0' )
				{

					for( strs; *strs != '\0'; strs++)
						*( strs - flag ) = *strs;
					*( strs - flag ) = '\0';
					return 1;
				}
			}
			strs++;
		}
	return 0;
	}
}
	


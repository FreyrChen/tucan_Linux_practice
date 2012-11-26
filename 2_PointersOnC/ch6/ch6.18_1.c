//通过比较两个字符串的第一个像同字母
#include <stdio.h>
//#define TRUE     1
//#define FALSE    0
	
char *find_char( char const *source, char const *chars );

int main( void )
{
	char  const chars[10]	= {"ABCDE"};
	char  const source[10]   = {"dEdDCAB"};
	char  *pointer;

	//pointer = source;
	pointer = find_char( source, chars );
	printf("the pointer is : %c \n", *pointer );
	return 1;
}


char *find_char( char const *source, char const *chars )
{
	char *source_str, *chars_str;
	source_str = source;
    while( source_str != NULL )
//			&&(( chars_str = chars ) != NULL ) )
	{
		while( *source_str != '\0')
		{
			chars_str = chars;
			while( ( *chars_str != '\0' ) )// &&(( chars_str++ ) != NULL ) )
			{
				if( *source_str == *chars_str )
				{
				//	printf(" the num is : %c \n", *source_str);
					return source_str ;
				}
				chars_str++;
			}
			source_str++;
		}
	}
	return NULL;
}					   

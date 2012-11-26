//************************************************************************
//
// 3FILEoP.C
//DATE;2012/4/26
//*************************************************************************

#include <fcntl.h> //open();
#include <unistd.h> //read(); getcwd();
#include <sys/stat.h> // S_isdir();
#include <sys/times.h> // timer();


#define BUFFSIZE	4096	//4096


#define DEBUG_FIEL_MODE 	1	// is detect the file's mode
#define DEBUG_READ_FILE		1


void FileModeDetect( int filefd );
void FileKindDetect( char *file_name );

char * GetDir( void );
static void Measure_times( clock_t start, clock_t end, struct tms *tmsstart, struct tms *tmsend );
char* MakeDir( char* path_name , char * dir_name);


void main( int argc, char *argv[])
{
	int 	source_fd;
	int	dest_fd;
	int 	n;
	int 	temp;
//	int 	open_mode;
	char 	buf[BUFFSIZE];
	char*	pathname;

	struct tms  tmsstart, tmsend;
	clock_t		start, end;
	int	status;

	temp = 0;

	printf("--------- open file and write it to another file ---------\n");
	printf(" usege: sduo time - p fileOP <source> <desnation> \n");
	// to meaasure time , stamp start time.	
	if( ( start = times( &tmsstart ) ) == -1 )
		printf("start time measure error! \n");
	else
		printf("start time measure ok! \n");
	
	//if( ( fd = open( "sensor_data.txt", O_RDONLY) )<0 )
	if( argc  != 3 )
	{	
		printf("argc= %d, usege: sduo time - p fileOP <source> <desnation> \n",argc);
		for( temp=1; temp < argc ; temp++ )
		{	// the argc[0] is the function itsel
			printf( "argc[%d]:%s \n", temp,argv[temp]);
			FileKindDetect( argv[temp] );
		}
	}
	else 
	{
		
		printf(" This is to open the datafile \n");

		if( ( source_fd = open( argv[1], O_RDONLY   ))<0 )
			printf(" file:%s creat erro ! \n",argv[1]);
		else
		{
			#ifdef DEBUG_FILE_MODE
			printf(" file:[ %s ] is opened  ! \n",argv[1]);
			FileModeDetect( source_fd );
			#endif
		}	


		#ifdef DEBUG_READ_FILE

		pathname = GetDir();
		printf(" get the current path is %s \n", pathname);

		pathname = MakeDir( pathname,"copy_dir");
	
		chdir( pathname );
		
		if( ( dest_fd = open( argv[2], O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH ))<0 )
			printf(" file:%s creat erro ! \n",argv[2]);
		else
		{
			printf( " new file:[ %s ] is created, the file descroptor is %d \n",
				argv[2], dest_fd ); 
			#ifdef DEBUG_FILE_MODE
			FileModeDetect( dest_fd );
			#endif
		}

		printf(" write [%s] to [%s] ... \n", argv[1],argv[2]);
		while( ( n = read( source_fd, buf, BUFFSIZE ) ) > 0 )
		{
			if( write( dest_fd, buf, n) != n )
				printf(" write file error! \n");
			//else
			//	printf(">>>");
			temp ++;
		//	printf("[%2d] n=%4d : %s\n" ,temp,n,buf);
			//if( temp > 10 )
			//	exit(0);
		}
		if( n < 0 )
			printf( " read the end! \n");
		#endif
	}
	
	// to test Measuer_time() 
	sleep(1);
	// to meaasure time , stamp end time.	
	if( ( end = times( &tmsend ) ) == -1 )
		printf(" end time measure error \n" );
	else
		printf( " end time measure Ok! \n" );
	
	Measure_times( start, end, &tmsstart, &tmsend );
	
	exit(0);
		
}
	
void FileModeDetect( int filefd )
{	
		int open_mode;
		//determint the opened file's properity
		if( (open_mode = fcntl( filefd,F_GETFL, 0) ) < 0 )
			printf( "fcntl error for fd %d", filefd);
		printf( " the file's open mode is: ");
		switch( open_mode & O_ACCMODE )
		{
		case O_RDONLY:
			printf(" read only\n");
			break;
		case O_WRONLY:
			printf(" write only \n");
			break;
		case O_RDWR:
			printf("read and write \n");
			break;
		default:
			printf(" Unknown access open mode \n");
		}
}

//******************************************************************************
//file kind detect 
// in apue chapter 4 P73
//*****************************************************************************
void FileKindDetect( char *file_name )
{
	struct stat buf;
	char * 	ptr;
	if( ! strlen( file_name ) )
		printf( " FileKindDetect() input file name is invalid! \n");
	else
	{
		printf(" Detect the kind of file:[ %s ]: ", file_name );
		if( lstat( file_name, &buf ) < 0 )
			printf( " lstat to get file's info struct error! \n");
		else
		{
			if( S_ISREG( buf.st_mode ) )
				ptr = "regular";
			else if( S_ISDIR( buf.st_mode) )
				ptr = " directory ";
			else if( S_ISCHR( buf.st_mode ) )
				ptr = " character special";
			else if( S_ISBLK( buf.st_mode ) )
				ptr = " block special ";
			else if( S_ISFIFO( buf.st_mode ) )
				ptr = "fifo";
			else if( S_ISLNK( buf.st_mode ))
				ptr = " symbolic link ";
			else if( S_ISSOCK( buf.st_mode ))
				ptr = " socket ";
			else
				ptr = " Unkowm kind of file. \n ";
			printf(" %s \n ", ptr);
		}
	}
}		

// get the current directory 
char * GetDir( void )
{
	/*
	#ifdef PATH_MAX
	static int pathmax = PATH_MAX;
	#else
	static int pathmax = 0;
	#endif
	*/
	static int pathmax = 1024;
	char * pathname;

	printf(" pathmax: %d \n", pathmax );
	if( (pathname = malloc( pathmax) ) == NULL )
		printf(" cannot malloc for pathname string \n");
	else
	{
		if( getcwd( pathname, pathmax ) == NULL )
			printf(" getcwd error \n" );
		else
			printf(" cwd = %s\n", pathname );
		return pathname;
	}
}
				 
//out put the directory path
char* MakeDir( char* path_name, char* dir_name )
{
	char* old_path;
	char* new_path;
	
	static int pathmax = 1024;
	if( ( old_path = malloc( pathmax) ) == NULL )
		printf("MakeDir: cannot malloc for old_path string \n");
	if( ( new_path = malloc( pathmax) ) == NULL )
		printf("MakeDir: cannot malloc for new_path string \n");
	strcpy( old_path, path_name );
	printf(" MakeDir: old_path is: %s \n", old_path );
	new_path = strcat( new_path, old_path );
	new_path = strcat( new_path, "/");
	new_path = strcat( new_path, dir_name );
	
	printf(" MakeDir: new_path is: %s \n", new_path );
	// detect the directory is alredy exsit???	
	if( access( new_path , F_OK ) ==  0 )
	{
		return new_path;
		printf(" MakeDir:  director [%s] is already exsit ! \n",dir_name);
	}
	else 
	{
		printf(" MakeDir:  director [%s] is not exsit, so we creat ... \n",dir_name);
		// remenber all directory should have the excute permision for all users.
		if( mkdir( new_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH )<0 )
			printf("MakeDir: can not mkdir %s \n", new_path );
		else
			return new_path;
	}
}
//measure the time used.
//nedd at start and end use time stamp
static void Measure_times( clock_t start,clock_t end, struct tms *tmsstart, struct tms *tmsend )
{
	static long	clktck = 0;
	clock_t		real;
	
	real = ( end - start );
	printf(">> Get the time: \n");
	if( clktck == 0 )
		if( (clktck = sysconf( _SC_CLK_TCK ))  < 0 )
			printf(" sysconf( _SC_CLK_TCK)  error \n");
	printf(" clktck: %f, so it determined the time measure  resolution  \n", (double)clktck );
	printf(" end is %f, start is %f  \n",(double) end,(double) start );
	printf(" real:	%7.3f\n", real/ (double) clktck);
	printf(" user:	%7.3f\n", (tmsend->tms_utime - tmsstart->tms_utime ) / (double) clktck );
	printf(" sys:	%7.3f\n", (tmsend->tms_stime - tmsstart->tms_stime ) / (double) clktck );
	printf(" child user:	%7.3f\n", (tmsend->tms_cutime - tmsstart->tms_cutime ) / (double) clktck );
	printf(" child sys:	%7.3f\n", (tmsend->tms_cstime - tmsstart->tms_cstime ) / (double) clktck );
}

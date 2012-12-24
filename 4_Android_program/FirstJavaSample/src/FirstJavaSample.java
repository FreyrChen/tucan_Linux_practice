import java.io.File;	//File();
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;


public class FirstJavaSample {
	public static void main( String[] args ) throws FileNotFoundException
	{
		Scanner in = new Scanner( System.in );
		
		System.out.println("we will not use 'Hello World!' ");
		
		/*test input from console */
		/*
		System.out.print("what is your name?");
		String name = in.nextLine();
		System.out.print("how old are you?");
		int age = in.nextInt();
		System.out.println("Hello" + name + ", next year,you'll be "+(age+1));
		*/
		
		/* write data to a file */
		//PrintWriter file_out = new PrintWriter("test.txt");
		//file_out.print("hahha");
		
		//test input from a file
		String dir = System.getProperty( "user.dir" );
		System.out.println("the default dir path is: " + dir );
		Scanner input_data = new Scanner( new File("test.txt"));
		System.out.println("read first line: " + input_data.nextLine() );
		
		int[] numbers = new int[10];
		for( int i=0; i<numbers.length; i++ )
			numbers[i] = i+1;
		for( int i=0; i<numbers.length; i++ )
			System.out.printf( "n[%d]: %d, ", i, numbers[i] );
		System.out.printf( "\n");
		for( int i=0; i<numbers.length; i++ )
			numbers[i] = (int) ( Math.random() * 100 );
		for( int i=0; i<numbers.length; i++ )
			System.out.printf( "n[%d]:%d, ", i, numbers[i] );
		System.out.printf( "\n after sort: \n");
		Arrays.sort( numbers );
		for( int i=0; i<numbers.length; i++ )
			System.out.printf( "n[%d]:%d, ", i, numbers[i] );
		System.out.printf( "\n ");
		
	}

	//catch exception
	

}

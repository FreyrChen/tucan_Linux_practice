import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;


public class StreamTest {
	
	private short audio_data [];

	public StreamTest() {
		// TODO Auto-generated constructor stub
		audio_data = new short[1024];
		for( int i=0; i<audio_data.length; i++)
			audio_data[i] = (short) ( i * Math.pow(2, 8));
		
		System.out.println("initial audio_data:");
		for( int i=0; i<10; i++)
			System.out.printf("audio_data[%d] = %d\n", i, audio_data[i]);
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println( System.getProperty("user.dir") );
		
	
		
		StreamTest tester = new StreamTest();
	
	
	
	
		
		
	}
	
	
	public void fromShortarryToBytestream( short data[] ){
		FileOutputStream fout = null;
		try {
			fout= new FileOutputStream("data.dat");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		for( int i=0; i<data.length; i++)
			fout.write(data);
	}

}

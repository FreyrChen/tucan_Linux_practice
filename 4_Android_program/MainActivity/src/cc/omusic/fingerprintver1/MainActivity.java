package cc.omusic.fingerprintver1;

import java.io.File;
import java.util.Random;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;
import cc.omusic.fingerprintver1.SDRecord;
import cc.omusic.musicidentify.Fingerprint;
import cc.omusic.musicidentify.Fingerprint.*;




public class MainActivity extends Activity {

	
	private SDRecord SDRecorder;
	//private File RecordMusicFile;
	private File RecordMusicDir;
	private File WavFile;
	private TextView infoText;
	private MusicRecorder musicRecorder = null;
	private String TAG = "main";
	private long fingerprint_time=0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		infoText = (TextView) findViewById( R.id.info_text);
		
		SDRecorder = new SDRecord();
		RecordMusicDir = SDRecorder.createSDDir( "omusic" );
		WavFile = new File(RecordMusicDir.getAbsolutePath()
							+ File.separator 
							+ "test.wav");
		
		
		//initial audio recorder
		musicRecorder =  new MusicRecorder();
		String text = "";
		
		fingerprint_time = System.currentTimeMillis();
//		int data_len = 44100*2*120;		//21.168Mb
		int data_len = 100;	
		float data[] = new float[ data_len ];
		
		//data = musicRecorder.readWavFileToFloatArray( WavFile , 6553 );

		Random ran = new Random();
		
		for( int i=0; i<data_len;  i++ )
		{
			
			data[i] = ran.nextFloat();	//[0-1]
		}
		infoText.setText( text);
		
		fingerprint_time = System.currentTimeMillis() - fingerprint_time;
		Log.i(TAG,"array generate time: " + fingerprint_time + "ms" );
		Log.i(TAG,"Array size " + data.length);
		

		//fingerprint_time = System.currentTimeMillis();
		
		Log.d(TAG,"ready to generate fingerprint");
		Log.d(TAG,"audioData length: " + data.length );
		//audioData.length == read_size
		
		if( data.length != 0 ) {
			Log.d(TAG,"new Fingerprint()" );
			
			Fingerprint fingerprinter = new Fingerprint();
			String fingerprint = fingerprinter.generate( data, data.length );
			Log.i(TAG,"fingerprint: " + fingerprint );
			//String fingerprint = fingerprinter.fingerprint(data, data.length );
			fingerprint_time = System.currentTimeMillis() - fingerprint_time;
			Log.i(TAG,"fingerprint generate time: " + fingerprint_time + "ms" );
			
			if( fingerprint == null ){
				infoText.setText( "fingerprint is null ");
			}else{
				infoText.setText( fingerprint);
			}
			
		}
		
		
		
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}

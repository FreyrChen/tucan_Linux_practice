package cc.omusic.fingerprintdemover1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

import cc.omusic.fingerprintjni.FingerprintWraper;
import cc.omusic.decorder.*;
import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckedTextView;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;


public class MainActivity extends Activity {

	private ProgressBar  autoProgressBar;
	private Button testButton;
	private Button playButton;
	private TextView infoText;
	private ListView musicList;
	
	private ArrayList<String> recordFiles;
	private ArrayAdapter<String> adapter;
	
	private SDRecord SDRecorder;
	private File RecordMusicDir;
	private File SelectedFile;
	
	private String TAG = "main";
	private long fingerprint_time=0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		
		autoProgressBar = (ProgressBar) findViewById(R.id.progress_bar);
		autoProgressBar.setIndeterminate(false);
		playButton = (Button) findViewById( R.id.play_button);
		testButton = (Button) findViewById( R.id.test_button);
		infoText = (TextView) findViewById( R.id.info_text);
		musicList = (ListView) findViewById( R.id.music_List);
		
		SDRecorder = new SDRecord();
		RecordMusicDir = SDRecorder.createSDDir( "omusic" );
		//list all  media (.amr) files
		getRecordFiles();
		// use a ArrarAdapter to contain a ListView
		adapter = new ArrayAdapter<String>(this, R.layout.my_simple_list_item, recordFiles );
		musicList.setAdapter(adapter);
		
		testButton.setOnClickListener( new testButtonListener() );
		playButton.setOnClickListener( new playButtonListener() );
		musicList.setOnItemClickListener(new musicListClickListener());
		
		
	
	}

	
	
	
	public class playButtonListener  implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Log.d(TAG,"play a music");
			try 
			{			
				//start audio record thread to write data to sd file.
				//new Thread( new AutoTestThread()).start();
				
				playMusicFile( SelectedFile );
				
			}catch( Exception e ){
				e.printStackTrace();
			}
		
		}
	}
	

	public boolean playMusicFile( File mp3file ){
		if( mp3file == null && !mp3file.exists())
			return false;
		Intent intent = new Intent();
		intent.addFlags( Intent.FLAG_ACTIVITY_NEW_TASK);
		intent.setAction( android.content.Intent.ACTION_VIEW);
		String type = SDRecorder.getMIMEType( mp3file );
		intent.setDataAndType(Uri.fromFile( mp3file ), type);
		startActivity( intent );	
		return true;
	}
	

	
	public class testButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Log.d(TAG,"start test");
			//calculateFP();	
			String music_end = SelectedFile.getName().substring( SelectedFile.getName().lastIndexOf(".") + 1,
					SelectedFile.getName().length()).toLowerCase();
			if( music_end.equals("mp3"))
				playMp3File( SelectedFile );
			else if( music_end.equals("ogg") )
				playOggFile(SelectedFile);
			else if( music_end.equals("wav"))
			{
				playWavFile(SelectedFile);
				calculateFP();
			}

			else
			{
				Log.e(TAG,"music file is not mp3/ogg/wav, can not support!");
			}
			
		
		}
	}
	
	public boolean playMp3File( File mp3file ){
		if( mp3file == null && !mp3file.exists())
			return false;
		String file_end = mp3file.getName().substring( mp3file.getName().lastIndexOf(".") + 1,
				     mp3file.getName().length()).toLowerCase();
		if( file_end.equals("mp3") )
		{
			Log.d(TAG, "select music file:" + mp3file.getAbsolutePath());
			Mpg123Decoder mp3 = new Mpg123Decoder( mp3file );
			Log.d( TAG, "channels:" + mp3.getChannels() );
			Log.d( TAG, "rate:" + mp3.getRate() );
			Log.d( TAG, "length:" + mp3.getLength() );
			mp3.dispose();
			return true;
		}
		else
		{
			Log.e( TAG, "select music file is not a mp3 format");
			return false;
		}
	}
	
	public boolean playOggFile( File Oggfile ){
		if( Oggfile == null && !(Oggfile.exists()))
			return false;
		String file_end = Oggfile.getName().substring( Oggfile.getName().lastIndexOf(".") + 1,
				Oggfile.getName().length()).toLowerCase();
		if( file_end.equals("ogg") )
		{
			Log.d(TAG, "select music file:" + Oggfile.getAbsolutePath());
			VorbisDecoder oog_music = new VorbisDecoder( Oggfile );
			Log.d( TAG, "channels:" + oog_music.getChannels() );
			Log.d( TAG, "rate:" + oog_music.getRate() );
			Log.d( TAG, "length:" + oog_music.getLength() );
			oog_music.dispose();
			return true;
		}
		else
		{
			Log.e( TAG, "select music file is not a ogg format");
			return false;
		}
	}
	
	public boolean playWavFile( File Wavfile ){
		if( Wavfile == null && !(Wavfile.exists()))
			return false;
		String file_end = Wavfile.getName().substring( Wavfile.getName().lastIndexOf(".") + 1,
				Wavfile.getName().length()).toLowerCase();
		if( file_end.equals("wav") )
		{
			Log.d(TAG, "select music file:" + Wavfile.getAbsolutePath());
			WavDecoder wav_music = new WavDecoder( Wavfile );
			Log.d( TAG, "channels:" + wav_music.getChannels() );
			Log.d( TAG, "rate:" + wav_music.getRate() );
			Log.d( TAG, "length:" + wav_music.getLength() );
			wav_music.dispose();
			return true;
		}
		else
		{
			Log.e( TAG, "select music file is not a wav format");
			return false;
		}
	}
	
	public void calculateFP( ){
		Log.d(TAG,"ready to generate fingerprint");
		fingerprint_time = System.currentTimeMillis();
		FingerprintWraper fp = new FingerprintWraper();

		String music_file_path = SelectedFile.getAbsolutePath();
		infoText.setText( "calculate music file's fingerprint:" + music_file_path);
		Log.d(TAG, "calculate music file's fingerprint:" + music_file_path);
		byte []fp_byte = new byte[424];
		fp_byte = fp.generate(  SelectedFile  );	
		fingerprint_time = System.currentTimeMillis() - fingerprint_time;
		Log.i(TAG,"fingerprint generate time: " + fingerprint_time + "ms" );

		if( fp_byte == null ){
			infoText.setText( "fingerprint is null ");
		}else{
			infoText.setText("fingerprint : \n"
							+ "cost time:"+ fingerprint_time + "ms \n"
							+ "fingerprint: \n" + byteArrayToHexString( fp_byte ) );
			Log.e(TAG,"fp_str: " + byteArrayToHexString(fp_byte));
		}	
	}
	
	//select a music file from list
	class musicListClickListener implements OnItemClickListener{
		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
			// TODO Auto-generated method stub
			
			playButton.setEnabled(true);
			testButton.setEnabled(true);
			
			SelectedFile = new File( RecordMusicDir.getAbsolutePath()
									+ File.separator 
									+ ( (CheckedTextView) arg1).getText());
			infoText.setText(( (CheckedTextView) arg1).getText() );
			Log.d(TAG,"select: " + ( (CheckedTextView) arg1).getText());
		}
		
	}
	
	//play a music that selected

	
	public String byteArrayToHexString( byte[] array)
	{
		StringBuilder sb =new StringBuilder();
		for( byte b: array ){
			sb.append(String.format("%02x", b & 0xff));
		}
		return sb.toString();
	}
	
	
	

	private void getRecordFiles( ){
		recordFiles = new ArrayList<String>();
		 if( SDRecorder.checkSD() ){
			 File files[] = RecordMusicDir.listFiles();
			 if(files != null ){
				 //Log.d("tusion"," get files!");
				 for( int i=0; i<files.length; i++ ){
					 if( files[i].getName().indexOf(".") >= 0 )
					 {
						 //read all .amr files
						 String file_str = files[i].getName().substring(
								 	files[i].getName().indexOf("."));
						 //if( file_str.toLowerCase().equals(".wav"))
							 recordFiles.add( files[i].getName());
					 }
				 }
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

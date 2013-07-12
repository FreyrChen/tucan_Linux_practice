package cc.omusic.musicidentify;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

import cc.omusic.musicidentify.MusicRecorder.AutolAudioRecorderThread;
import cc.omusic.musicidentify.MusicRecorder.ManualAudioRecorderThread;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckedTextView;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;




public class MainActivity extends Activity {
	
	private ProgressBar  autoProgressBar;
	private ToggleButton startAutoButton;
	private Button testButton;
	private ToggleButton startManualButton;
	private Button queryButton;
	private Button playButton;
	private Button deleteButton;
	private TextView infoText;
	private ListView musicList;
	private ArrayList<String> recordFiles;
	private ArrayAdapter<String> adapter;
	
	//private File RecordMusicFile;
	private File RecordMusicDir;
	private File SelectedFile;
//	private MediaRecorder mMediaRecorder;
	private boolean isStopRecord;
	private boolean isGetJson;
	private SDRecord SDRecorder;
	private Handler handler = new Handler();
	private int  count = 0;
	private MusicRecorder musicRecorder = null;
	private final String TAG = "Main";
	private int PROGRESS_MAX = 30; //define process time for process bar
	private final String TEST_SERVER_IP = "192.168.4.205";
	private final int TEST_SERVER_PORT = 6000;
	private PrintWriter out = null;
	private BufferedReader in = null;
	private Socket socket = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		autoProgressBar = (ProgressBar) findViewById(R.id.auto_progress);
		autoProgressBar.setIndeterminate(false);
		
		startAutoButton = (ToggleButton) findViewById( R.id.auto_record_button);
		testButton = (Button) findViewById( R.id.test_button);
		startManualButton = (ToggleButton) findViewById( R.id.manual_record_button);
		queryButton = (Button) findViewById( R.id.query_button);
		playButton = (Button) findViewById( R.id.play_button);
		deleteButton = (Button) findViewById( R.id.delete_button);
		
		infoText = (TextView) findViewById( R.id.info_text);
		musicList = (ListView) findViewById( R.id.music_List);
		
		SDRecorder = new SDRecord();
		RecordMusicDir = SDRecorder.createSDDir( "omusic" );
		//list all  media (.amr) files
		getRecordFiles();
		// use a ArrarAdapter to contain a ListView
		adapter = new ArrayAdapter<String>(this, R.layout.my_simple_list_item, recordFiles );
		musicList.setAdapter(adapter);
		
		//set every button's click event
		startAutoButton.setOnCheckedChangeListener( new startAutoButtonListener()); 
		startManualButton.setOnCheckedChangeListener( new startManualButtonListener()); 
		testButton.setOnClickListener( new testButtonListener() );
		playButton.setOnClickListener( new playButtonListener() );
		deleteButton.setOnClickListener( new deleteButtonListener() );
		musicList.setOnItemClickListener(new musicListClickListener());
		queryButton.setOnClickListener(new queryButtonListener());
		
		//initial audio recorder
		musicRecorder =  new MusicRecorder();
		musicRecorder.creatRecorder();
		//wait recording thread stop to send  a message.
		musicRecorder.setHandler(myHandler);
	}
	
	// 1 s conte timer 
	Runnable timer_runnable = new Runnable(){
		public void run(){
			count++;
			infoText.setText("record time: " + count + "s");
			autoProgressBar.setProgress( count );
			handler.postDelayed(this, 1000);
		}
	};
	
	private Handler myHandler = new Handler(){
		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			//auto record process
			if(msg.what == 0){
				// complete record 20s automatic stop recorder
				isStopRecord = true;
				//stop timer and reverse count
				handler.removeCallbacks(timer_runnable);
				autoProgressBar.setProgress( PROGRESS_MAX );
				infoText.setText("generate finger print and query on server");
			}else if( msg.what == 1){
				autoProgressBar.setVisibility(View.GONE);
				count =  0;
				infoText.setText( "[f-time]:" + musicRecorder.getFingerprintTime() + "ms;   "
					    + "[q-time]:" + musicRecorder.getQueryTime() + "ms"
						+ "\n" + musicRecorder.getQueryResult());
				startAutoButton.setChecked(false);
			} 
			//manual record process
			else if( msg.what == 2){
				//manual stop recorder,wait creat new wav file
				adapter.add(musicRecorder.getRecordMusicWavFile().getName());
				SelectedFile = musicRecorder.getRecordMusicWavFile();
				infoText.setText("new wav file:"+
									musicRecorder.getRecordMusicWavFile().getName());
			}else if( msg.what == 3){
				//get query server's respoense.
				infoText.setText( musicRecorder.getQueryResult());	
			}
			// server to client auto test complete
			else if( msg.what == 4){
				musicRecorder.stopRecorder();
				// step4: wait for recorder complete , in the message handler process.
				//out.println(" {{test json}}");
				out.println( musicRecorder.getQueryResult() );
				Log.i(TAG,"android send json to server");
			}
					
		}
		
	};
	
	
	
	public class testButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Log.d(TAG,"start continu test");
			try 
			{			
				//start audio record thread to write data to sd file.
				new Thread( new AutoTestThread()).start();
				Log.d(TAG,"start a thread for auto audio recorder");
				
			}catch( Exception e ){
				e.printStackTrace();
			}
		
		}
	}

	// new thread for auto
	// can not add any UI set in the thread
	class AutoTestThread implements Runnable{
		@Override
		public void run() {	
			String msg = null;
			//startAutoButton.setChecked( true);
			try{
				//create socket
				socket = new Socket( TEST_SERVER_IP, TEST_SERVER_PORT );
				//send message to server
				out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
				//receive message from server
				in = new BufferedReader( new InputStreamReader(socket.getInputStream()));
				//wait sever's welcome message
				msg = in.readLine();
				Log.i(TAG,"from server: " + msg);
			}catch( Exception e ){
				e.printStackTrace();
			}

			int times = 610;
			while( times > 0){
				times --;
				
				//1. send server ready to new song
				out.println("android ready to next song");
				Log.i(TAG,"send to server: android ready to next song");
				
				//2. waitting server replay, receive new song id
				do{
					try {
						msg = null;
						msg = in.readLine();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}while( msg == null );
				Log.i(TAG,"from server: " + msg);
				
				//3.start to record and query the music
				//startAutoButton.setChecked(true);
				Log.i(TAG,"start recorder");

				musicRecorder.startAutoRecorder();
				//start timer after 1 second, count record time
				handler.postDelayed(timer_runnable, 1000);
				
				//4. wait for recorder complete , in the message handler process.
				//....
				
				//5. waitting server replay, complete the song
				do{
					try {
						msg = null;
						msg = in.readLine();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}while( msg == null );
				Log.e(TAG,"complete this cycle, from server: " + msg);
			}
			
			try{
				//close connection
				out.close();
				in.close();
				socket.close();
			}catch( Exception e ){
				e.printStackTrace();
			}
		}
		
}
	
	// automatic record 20s,  gernerate fingerprint, query server. 
	public class startAutoButtonListener implements OnCheckedChangeListener{
		@Override
		public void onCheckedChanged(CompoundButton buttonView,
				boolean isChecked) {
			// TODO Auto-generated method stub
			if(isChecked){ 
				Toast.makeText(MainActivity.this, "Start to recognise music.", Toast.LENGTH_LONG).show(); 
				queryButton.setEnabled(false);
				playButton.setEnabled(false);
				deleteButton.setEnabled(false);
				startManualButton.setEnabled(false);
				
				autoProgressBar.setVisibility(View.VISIBLE);
				//set 20s
				autoProgressBar.setMax( PROGRESS_MAX ); 
				
				isStopRecord = false;
				
				musicRecorder.startAutoRecorder();
				
				//Display info
				infoText.setText("recording ...");
				//start timer after 1 second, count record time
				handler.postDelayed(timer_runnable, 1000);
				
			}
			//press to stop record
			else{	

				musicRecorder.stopRecorder();
				
				Toast.makeText(MainActivity.this, 
					"record voice stopped.", Toast.LENGTH_SHORT).show();
				Log.d(TAG,"press to stop");
				queryButton.setEnabled(true);
				playButton.setEnabled(true);
				deleteButton.setEnabled(true);
				startManualButton.setEnabled(true);
				Log.d(TAG,"in close process");		
			}
		}
		
	}


	//start manual record button
	public class startManualButtonListener implements OnCheckedChangeListener{
		public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {
			// TODO Auto-generated method stub
			// press to start record
			if(isChecked){ 
	
				if( !SDRecorder.checkSD() ){
					Toast.makeText(MainActivity.this, "please check SD card", Toast.LENGTH_SHORT).show();
					infoText.setText("SD card is not insert.");
					return;
				}
				else{
					Toast.makeText(MainActivity.this, "Start to record voice.", Toast.LENGTH_LONG).show(); 
					queryButton.setEnabled(false);
					playButton.setEnabled(false);
					deleteButton.setEnabled(false);
					startAutoButton.setEnabled(false);
					isStopRecord = false;
					
					musicRecorder.startManualRecorder();
					
					//Display info
					infoText.setText("recording ...");
					//start timer after 1 second, count record time
					handler.postDelayed(timer_runnable, 1000);
					
					//while( musicRecorder.getQueryStatus() == false )
					//	; //wait record and query
					
				}
			}
			//press to stop record
			else{	

				musicRecorder.stopRecorder();
				
				Toast.makeText(MainActivity.this, 
					"record voice stopped.", Toast.LENGTH_SHORT).show();
				Log.d(TAG,"press to stop");
				queryButton.setEnabled(true);
				playButton.setEnabled(true);
				deleteButton.setEnabled(true);
				startAutoButton.setEnabled(true);
				Log.d(TAG,"in close process");
				
				isStopRecord = true;
				//stop timer and reverse count
				handler.removeCallbacks(timer_runnable);
				count =  0;				
			}
		}
	}
	
	
	//query a wav file in sd card
	//input a stream -> short[] audio data -> String fingerprint -> query server 
	class queryButtonListener implements OnClickListener{
		@Override
		public void onClick(View arg0) {
			// TODO Auto-generated method stub
			//infoText.setText("want to query? it's not ready.");
			infoText.setText("query ...");
			if( SelectedFile.isFile() && SelectedFile.exists() ){
				genFingerprintQueryServer query = new genFingerprintQueryServer();
				//infoText.setText("query ...\n server:" + query.getServerUrl());
				String fingerprint = query.generateMusicFp( 
										musicRecorder.readWavFileToShortArray(
												SelectedFile) );
				String jsonstr = query.getJSONStr(fingerprint);
				infoText.setText( "[f-time]:" + query.getFingerprintTime() + "ms;   "
								    + "[q-time]:" + query.getQueryTime() + "ms"
									+ "\n" + jsonstr);
			}
			else{
				infoText.setText("Error! SelectedFile: " + SelectedFile.toString());
				Log.e(TAG, "Error! SelectedFile: " + SelectedFile.toString());
			}
			
		}
	}
	
	
	//select a music file from list
	class musicListClickListener implements OnItemClickListener{
		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
			// TODO Auto-generated method stub
			playButton.setEnabled(true);
			deleteButton.setEnabled(true);
			queryButton.setEnabled(true);
			
			SelectedFile = new File( RecordMusicDir.getAbsolutePath()
									+ File.separator 
									+ ( (CheckedTextView) arg1).getText());
			infoText.setText("music time: " + musicRecorder.getWavFileTime(SelectedFile)
							+ "\n" + ( (CheckedTextView) arg1).getText() );
		}
		
	}
	
	//play a music that selected
	class playButtonListener implements OnClickListener{
		@Override
		public void onClick(View arg0) {
			// TODO Auto-generated method stub
			
			if( SelectedFile != null && SelectedFile.exists() ){
				//openFile( SelectedFile );
				Intent intent = new Intent();
				intent.addFlags( Intent.FLAG_ACTIVITY_NEW_TASK);
				intent.setAction( android.content.Intent.ACTION_VIEW);
				String type = SDRecorder.getMIMEType( SelectedFile );
				intent.setDataAndType(Uri.fromFile( SelectedFile ), type);
				startActivity( intent );	
			}
		}
		
	}

	
	//delete the selected music file
	class deleteButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			if( SelectedFile != null){
				//remove file name from adapter
				Log.d("tusion","success remove file name"+SelectedFile.getName());
				adapter.remove(SelectedFile.getName());
				//delete file data in sd card
				if( SelectedFile.exists() )
					SelectedFile.delete();
				infoText.setText("success delete. ");		
			}
		}
		
	}
	

	
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
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
    

	
}
	

	

		
	

	



		

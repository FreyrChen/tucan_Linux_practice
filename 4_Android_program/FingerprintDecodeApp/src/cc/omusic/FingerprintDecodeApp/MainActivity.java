package cc.omusic.FingerprintDecodeApp;

import cc.omusic.FingerprintDecodeJin.FingerprintWraper;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	private TextView infoText;
	private String TAG = "main";
	
	private long fingerprint_time=0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		infoText = (TextView) findViewById( R.id.info_text);
		
		infoText.setText( "wating for decorder's version ...");
		
		fingerprint_time = System.currentTimeMillis();
		byte []fp_byte = new byte[424];
		
		FingerprintWraper fp = new FingerprintWraper();
		fp_byte = fp.generate();
		
		fingerprint_time = System.currentTimeMillis() - fingerprint_time;
		Log.i(TAG,"fingerprint generate time: " + fingerprint_time + "ms" );
		
		if( fp_byte == null ){
			infoText.setText( "fingerprint is null ");
		}else{
			infoText.setText("fingerprint : \n"
							+ "cost time:"+ fingerprint_time + "ms \n"
							+ "fingerprint: \n" + byteArrayToHexString( fp_byte ) );
			//Log.d(TAG, "file name: " + music_file.getName());
			Log.d(TAG,"fp_str: " + byteArrayToHexString(fp_byte));
			
			Log.d(TAG, "fp_version: " + byteArray2ToShort(fp_byte,0 ) );
			Log.d(TAG, "fp_length: " + byteArray4ToInt(fp_byte, 2));
			Log.d(TAG, "fp_avg_fit: " + byteArray2ToShort(fp_byte,6 ));
			Log.d(TAG, "fp_avg_dom: " + byteArray2ToShort(fp_byte,8 ) );
			
			byte[] fp_fit = new byte[348];
			for( int i=10; i<358; i++ ){
				fp_fit[i-10] = fp_byte[i];
			}
			Log.d(TAG, "fp_fit:" + byteArrayToHexString( fp_fit));
			
			byte[] fp_dom = new byte[66];
			for( int i =358; i<424; i++){
				fp_dom[i-358] = fp_byte[i];
			}
			Log.d(TAG, "fp_dom:" + byteArrayToHexString( fp_dom));
		}	
		
	}
	
	
	public String byteArrayToHexString( byte[] array)
	{
		StringBuilder sb =new StringBuilder();
		for( byte b: array ){
			sb.append(String.format("%02x", b & 0xff));
		}
		return sb.toString();
	}
	
	
	private  int byteArray4ToInt(byte[] byteValue, int index){   
        if(byteValue.length   <   4)   
           return   0;   
        int   intValue =   0;
        intValue   =   byteValue[index+ 3]; 
        intValue   =   (intValue   <<  8)   +   byteValue[index+2];   
        intValue   =   (intValue   <<  8)   +   byteValue[index+1]; 
        intValue   =   (intValue   <<  8)   +   byteValue[index+0]; 
        return   intValue;   
	}   
	
	
	private  int byteArray2ToShort(byte[] byteValue, int index){   
        if(byteValue.length   <  2)   
                return   0;   
        short   shortValue   =   0;    
        shortValue   =   byteValue[index+ 1];   
        shortValue   =   (short) ( (shortValue << 8) + byteValue[index+0] );   
 
        return   shortValue;   
	} 

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	

}

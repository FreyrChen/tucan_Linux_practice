package TestSensor.tusion;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Date;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.List;


import TestSensor.tusion.SDRecord;

import android.R.bool;
import android.app.Activity;
import android.app.ListActivity;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Environment;
import android.text.format.Time;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

public class TestSensorActivity extends Activity implements  SensorEventListener {
    /** Called when the activity is first created. */
	final String tag = "tusion sensor";
	
	//����SD���ɼ��ı�־����
	public boolean SDRecordState = false;
    private PrintWriter captureFile;
	public String[]sensordata=new String[10];
    //private float timestamp;
	//final float NS2S = 1.0f / 1000000000.0f;
	//private float[] angle = new float[3];
	
	SensorManager sensorManager = null;
    Sensor ourSensor = null;
	  	
	    TextView tvTopinfo = null;
	    TextView tvAccelerometer = null;
	    TextView tvGyro = null;
	    TextView tvMagentic = null;
	    TextView tvOrientation= null;
	    TextView tvLight = null;
	    TextView tvTemperature  = null;
	    
	    Button testallsensorbutton = null;
	    EditText  serverip =null;
	    ToggleButton  ServerConnection = null;
	    ToggleButton  SDRecord = null;
	    
	
    	
	    private WifiManager wifimanager = null;
	    
	    
    	private String SDPath = Environment.getExternalStorageDirectory() +"/SensorRecordData/";
    	DecimalFormat df = new DecimalFormat("###.00");  
    	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON); 
  
        tvTopinfo = (TextView) findViewById(R.id.topinfo);
  
        tvAccelerometer = (TextView) findViewById(R.id.Acce);
        tvGyro = (TextView) findViewById(R.id.Gyro);
        tvMagentic  = (TextView) findViewById(R.id.zViewO);
        tvOrientation = (TextView) findViewById(R.id.xViewO_raw);
         
        tvLight= (TextView) findViewById(R.id.Light);
        tvTemperature = (TextView) findViewById(R.id.Temperature);
        
        // get reference to SensorManager
        sensorManager  = (SensorManager) getSystemService(SENSOR_SERVICE);
        
        /*List<Sensor> sensors = sensorManager.getSensorList( Sensor.TYPE_ALL );
           for(Sensor sensor:sensors)  
        	{  
            	//  �����ǰ������������  
        	   xViewA.append(sensor.getName() + "\n");  
        	} 
    	*/
         
        serverip = (EditText)findViewById(R.id.ServerIP);
        
        //��һ���µ�Activity�л�ȡ����ʾ�ֻ����еĴ�����
        testallsensorbutton = (Button)findViewById(R.id.TestAllSensors);
        testallsensorbutton.setOnClickListener( new TestAllSensorsListener());
        
        //ͨ��wifi���ӷ�������׼��������
        ServerConnection=(ToggleButton)findViewById(R.id.ServerConnection);
        ServerConnection.setOnCheckedChangeListener( new ServerConnectionsListener());   
        
        //�ɼ����ݴ浽SD����
        SDRecord = (ToggleButton)findViewById(R.id.SDRecord);
        SDRecord.setOnCheckedChangeListener(new SDRecordListener());
        

    }
   
    class TestAllSensorsListener implements OnClickListener{

 		public void onClick(View arg0) {
 			// TODO Auto-generated method stub

 			Intent intent = new Intent();
 			intent.setClass( TestSensorActivity.this, TestAllSensorsActivity.class);
 			TestSensorActivity.this.startActivity(intent);
 		}
 	}
    
    
    public void onSensorChanged(SensorEvent event){ 

    	String SensorChangedTag = "SensorChanged";
    	
    	 //  ͨ��getType������õ�ǰ�������ݵĴ��������� 
        switch (event.sensor.getType())  
        {  
            case Sensor.TYPE_ACCELEROMETER:            //  ������ٶȴ��������ص�����  
                String accelerometer = "�����ٶȡ� " + " X��" +  df.format(event.values[0])+ ";  "  
                        + "Y:" + df.format(event.values[1]) + "  " + "  Z:" + df.format(event.values[2]) ;  
                tvAccelerometer.setText(accelerometer);  
                sensordata[0]=GetTimeNow();
                sensordata[1]=String.valueOf(event.values[0]);
                sensordata[2]=String.valueOf(event.values[1]);
                sensordata[3]=String.valueOf(event.values[2]);
                break;  
           case Sensor.TYPE_GYROSCOPE:            //  �������ݴ��ص�����  
                String gyro = "�����ٶȡ� " + " X��" + df.format(event.values[0]) + ";  "  
                        + "Y:" + df.format(event.values[1]) + ";  " + "Z:" + df.format(event.values[2]);  
               tvGyro.setText(gyro); 
                /*
                if (event.accuracy == SensorManager.SENSOR_STATUS_UNRELIABLE)   
                {   
                return;   
                }
             
                if (timestamp != 0) {
                final float dT = (event.timestamp - timestamp) * NS2S;
                angle[0] += event.values[0] * dT * 100;
                angle[1] += event.values[1] * dT * 100;
                angle[2] += event.values[2] * dT * 100;
                }
                timestamp = event.timestamp;
                //String angle=  
                tvGyro.setText( "time:"+timestamp );
                */
                break;                   
           case Sensor.TYPE_MAGNETIC_FIELD:            //  ����ų����������ص�����  
                String magentic = "�� �� �� ��   " + "X��" + df.format(event.values[0]) + ";  " + "Y:"  
                        +df.format(event.values[1]) + ";  " + "Z:" +df.format(event.values[2]);  
                tvMagentic.setText(magentic);  
                sensordata[0]=GetTimeNow();
                sensordata[4]=String.valueOf(event.values[0]);
                sensordata[5]=String.valueOf(event.values[1]);
                sensordata[6]=String.valueOf(event.values[2]);
                break;  
            case Sensor.TYPE_ORIENTATION:                //  �����򴫸������ص�����  
                String orientation = "�� �� �� ��   " + "H��" + df.format(event.values[0]) + ";   "  
                        + "P:" + df.format(event.values[1])+ ";  " + "R:" + df.format(event.values[2]) ;  
                tvOrientation.setText(orientation); 
                sensordata[0]=GetTimeNow();
                sensordata[7]=String.valueOf(event.values[0]);
                sensordata[8]=String.valueOf(event.values[1]);
                sensordata[9]=String.valueOf(event.values[2]);
                break;  
            case Sensor.TYPE_LIGHT:                    //  ������ߴ��������ص�����  
                tvLight.setText("�� �� �� ��           " + df.format(event.values[0]));  
                break;  
            case Sensor.TYPE_TEMPERATURE:                    //  �����¶ȴ��������ص�����  
            	tvTemperature.setText("�� �¶� ��      " + df.format(event.values[0]));  
                break;       
        }  
        
      	StringBuilder b = new StringBuilder();
        for( int i = 0 ; i < sensordata.length ; ++i ) {
            if( i > 0 )
                b.append( " , " );
            b.append( sensordata[i]  );
        }

        Log.d( SensorChangedTag, "onSensorChanged: ["+b+"]" );
        
        if( captureFile != null ) {
            for( int i = 0 ; i < sensordata.length ; ++i ) {
                if( i > 0 )
                   captureFile.print( "," );
                captureFile.print( sensordata[i]  );
            }
            captureFile.println();
        }
    } 
    
    
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    	Log.d(tag,"onAccuracyChanged: " + sensor + ", accuracy: " + accuracy);
    }

    @Override
    protected void onResume() {
        super.onResume();
       // register this class as a listener for the orientation and accelerometer sensors
        
        //  ע����ٶȴ�����  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),  
                SensorManager.SENSOR_DELAY_NORMAL);  
  
        //  ע��ų�������  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),  
                SensorManager.SENSOR_DELAY_NORMAL); 
        //  ע�����ݴ�����  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE),  
                SensorManager.SENSOR_DELAY_NORMAL); 
 
        //  ע����ߴ�����  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT),  
                SensorManager.SENSOR_DELAY_NORMAL);  
  
        //  ע�᷽�򴫸���  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION),  
                SensorManager.SENSOR_DELAY_NORMAL);  
        //  ע���¶ȴ�����  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_TEMPERATURE),  
                SensorManager.SENSOR_DELAY_NORMAL);  
        
    }
    
    @Override
    protected void onStop() {
        // unregister listener
    	sensorManager.unregisterListener(this);
        super.onStop();
    }   
    
    //WIFI�ͷ��������ӵİ�ť����
    class ServerConnectionsListener implements OnCheckedChangeListener{
    	private String wifitag = "wifi tag";
		public void onCheckedChanged(CompoundButton buttonView,
				boolean isChecked) {
			// TODO Auto-generated method stub
			if(isChecked){ 
    			wifimanager = (WifiManager)TestSensorActivity.this.getSystemService(Context.WIFI_SERVICE);
    	        //�ж�wifi�Ƿ���
    	        if (!wifimanager.isWifiEnabled()) {
    	        wifimanager.setWifiEnabled(true);  
    	        }
    	        
    			//��һ������wifi
    			// getWifiState() return:
    			//WIFI_STATE_DISABLED, WIFI_STATE_DISABLING, WIFI_STATE_ENABLED, WIFI_STATE_ENABLING, WIFI_STATE_UNKNOWN
    			Log.d(wifitag,"wifi state ----->"+wifimanager.getWifiState());
    			Toast.makeText(TestSensorActivity.this, "��ǰWIFI״̬"+wifimanager.getWifiState(), Toast.LENGTH_SHORT).show();
    			
    			/*
    			Context context = listActivity.getApplicationContext();//��ȡӦ��������  
    			ConnectivityManager connectivityManager = (ConnectivityManager) Context.getSystemService(Context.CONNECTIVITY_SERVICE);//��ȡϵͳ�����ӷ���  
    	        NetworkInfo activeNetInfo = connectivityManager.getActiveNetworkInfo();//��ȡ������������  
    	        if(activeNetInfo.getType()==ConnectivityManager.TYPE_WIFI){  
    	            //�ж�WIFI��  
    	        }else if(activeNetInfo.getType()==ConnectivityManager.TYPE_MOBILE) {  
    	            //�ж�3G��  
    	        }
    	        */
    			
    			if(wifimanager.getWifiState()== 3){
        	        WifiInfo wifiInfo = wifimanager.getConnectionInfo();     
        	        int ipAddress = wifiInfo.getIpAddress();
        	        serverip.setText("����IPΪ:"+ipAddress );	
    			}

    			//�ڶ�����������������
    			
    			
            }
    		else{  
    			wifimanager = (WifiManager)TestSensorActivity.this.getSystemService(Context.WIFI_SERVICE);
    			wifimanager.setWifiEnabled(false);
    			//System.out.println("wifi state ----->"+wifimanager.getWifiState());
    			Log.d(wifitag,"wifi state ----->"+wifimanager.getWifiState());
    			Toast.makeText(TestSensorActivity.this, "��ǰWIFI״̬"+wifimanager.getWifiState(),  Toast.LENGTH_SHORT).show();
            }  	
		}
    }

    class SDRecordListener implements OnCheckedChangeListener{
    	
    	private String sdtag = "SD tag";
    	String captureStateText = null;
    	File captureFileName = null;
    	private String FileName;
    	
		public void onCheckedChanged(CompoundButton buttonView,
				boolean isChecked) {
			// TODO Auto-generated method stub
			if(isChecked){ 
		    	// timetag.setToNow(); // ȡ��ϵͳʱ�䡣
		    	 //FileName="SensorData" +timetag.toString();

				FileName= GetTimeNow() +".csv";
				//FileName= "fffff.csv";
				Log.d(sdtag,"SD state ----->start record the sensor data");
    			Toast.makeText(TestSensorActivity.this, "�����ļ�." + FileName+"\n��ʼ�ɼ�...", Toast.LENGTH_LONG).show();
    			//serverip.setText("��ǰSD״̬,FileName=" + FileName);
    			SDRecordState = true;
    			
    	        if( SDRecordState ) {
					try {
						 creatSDDir(SDPath);
						 captureFileName = creatSDFile( SDPath + FileName);
						 
						captureFileName = creatSDFile( FileName );
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
    	            Log.d(sdtag,"SD captureFileName ----->"+ captureFileName);
    	            try {
    	                captureFile = new PrintWriter( new FileWriter( captureFileName, false ) );
    	            } catch( IOException ex ) {
    	                Log.e( sdtag, ex.getMessage(), ex );
    	                captureStateText = "Capture: "+ex.getMessage();
    	            }
    	        } 
    	        
			}
			//�ɼ����ʱ�����°�ť
			else{
				Log.d(sdtag,"SD state ----->Stop record sensor data");
    			Toast.makeText(TestSensorActivity.this, "�ɼ���ϣ����ݱ�����SD����.\n�ļ���"+ captureFileName, Toast.LENGTH_LONG).show();
    			//WriteToSDCard("SensorData",FileName,"test");
    			SDRecordState = false;
    			
    	        if( captureFile != null ) {
    	            captureFile.close();
    	        }
			}
	}
    
 }
    //��ȡʵʱʱ��
	public String GetTimeNow() {
		SimpleDateFormat    formatter    =   new    SimpleDateFormat    ("yyyyMMdd_HHmmss_SS");
    	Date    curDate    =   new    Date(System.currentTimeMillis());//��ȡ��ǰʱ��       
    	String TimerStr    =    formatter.format(curDate);   
    	return TimerStr;
		
	}

	 //��SD�������ļ�
	 public File creatSDFile( String DirName) throws IOException{
		 File file = new File( SDPath + DirName);
		 if(!file.exists()){
			 try{
				 file.createNewFile();
			 }
			 catch(Exception e){
				 e.printStackTrace();
			 }
		 }
		
		 return file;
	 }
	 
		//��SD������Ŀ¼
	 public File creatSDDir( String DirName){
		 File dir = new File( SDPath + DirName);
		 if(!dir.exists()){
			 try{
				 // mkdirs() ��ʾ�������Ҫ�����ȴ����ϲ�Ŀ¼.
				 dir.mkdirs();
			 }
			 catch(Exception e){
				 e.printStackTrace();
			 }
		 }
		 
		 return dir;
	 }




	 
	 
	 
}
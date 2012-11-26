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
	
	//按下SD卡采集的标志变量
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
            	//  输出当前传感器的名称  
        	   xViewA.append(sensor.getName() + "\n");  
        	} 
    	*/
         
        serverip = (EditText)findViewById(R.id.ServerIP);
        
        //在一个新的Activity中获取并显示手机所有的传感器
        testallsensorbutton = (Button)findViewById(R.id.TestAllSensors);
        testallsensorbutton.setOnClickListener( new TestAllSensorsListener());
        
        //通过wifi连接服务器，准备传数据
        ServerConnection=(ToggleButton)findViewById(R.id.ServerConnection);
        ServerConnection.setOnCheckedChangeListener( new ServerConnectionsListener());   
        
        //采集数据存到SD卡中
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
    	
    	 //  通过getType方法获得当前传回数据的传感器类型 
        switch (event.sensor.getType())  
        {  
            case Sensor.TYPE_ACCELEROMETER:            //  处理加速度传感器传回的数据  
                String accelerometer = "【加速度】 " + " X：" +  df.format(event.values[0])+ ";  "  
                        + "Y:" + df.format(event.values[1]) + "  " + "  Z:" + df.format(event.values[2]) ;  
                tvAccelerometer.setText(accelerometer);  
                sensordata[0]=GetTimeNow();
                sensordata[1]=String.valueOf(event.values[0]);
                sensordata[2]=String.valueOf(event.values[1]);
                sensordata[3]=String.valueOf(event.values[2]);
                break;  
           case Sensor.TYPE_GYROSCOPE:            //  处理陀螺传回的数据  
                String gyro = "【角速度】 " + " X：" + df.format(event.values[0]) + ";  "  
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
           case Sensor.TYPE_MAGNETIC_FIELD:            //  处理磁场传感器传回的数据  
                String magentic = "【 磁 场 】   " + "X：" + df.format(event.values[0]) + ";  " + "Y:"  
                        +df.format(event.values[1]) + ";  " + "Z:" +df.format(event.values[2]);  
                tvMagentic.setText(magentic);  
                sensordata[0]=GetTimeNow();
                sensordata[4]=String.valueOf(event.values[0]);
                sensordata[5]=String.valueOf(event.values[1]);
                sensordata[6]=String.valueOf(event.values[2]);
                break;  
            case Sensor.TYPE_ORIENTATION:                //  处理方向传感器传回的数据  
                String orientation = "【 方 向 】   " + "H：" + df.format(event.values[0]) + ";   "  
                        + "P:" + df.format(event.values[1])+ ";  " + "R:" + df.format(event.values[2]) ;  
                tvOrientation.setText(orientation); 
                sensordata[0]=GetTimeNow();
                sensordata[7]=String.valueOf(event.values[0]);
                sensordata[8]=String.valueOf(event.values[1]);
                sensordata[9]=String.valueOf(event.values[2]);
                break;  
            case Sensor.TYPE_LIGHT:                    //  处理光线传感器传回的数据  
                tvLight.setText("【 亮 度 】           " + df.format(event.values[0]));  
                break;  
            case Sensor.TYPE_TEMPERATURE:                    //  处理温度传感器传回的数据  
            	tvTemperature.setText("【 温度 】      " + df.format(event.values[0]));  
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
        
        //  注册加速度传感器  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),  
                SensorManager.SENSOR_DELAY_NORMAL);  
  
        //  注册磁场传感器  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),  
                SensorManager.SENSOR_DELAY_NORMAL); 
        //  注册陀螺传感器  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE),  
                SensorManager.SENSOR_DELAY_NORMAL); 
 
        //  注册光线传感器  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT),  
                SensorManager.SENSOR_DELAY_NORMAL);  
  
        //  注册方向传感器  
        sensorManager.registerListener(this,  
                sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION),  
                SensorManager.SENSOR_DELAY_NORMAL);  
        //  注册温度传感器  
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
    
    //WIFI和服务器连接的按钮动作
    class ServerConnectionsListener implements OnCheckedChangeListener{
    	private String wifitag = "wifi tag";
		public void onCheckedChanged(CompoundButton buttonView,
				boolean isChecked) {
			// TODO Auto-generated method stub
			if(isChecked){ 
    			wifimanager = (WifiManager)TestSensorActivity.this.getSystemService(Context.WIFI_SERVICE);
    	        //判断wifi是否开启
    	        if (!wifimanager.isWifiEnabled()) {
    	        wifimanager.setWifiEnabled(true);  
    	        }
    	        
    			//第一步，打开wifi
    			// getWifiState() return:
    			//WIFI_STATE_DISABLED, WIFI_STATE_DISABLING, WIFI_STATE_ENABLED, WIFI_STATE_ENABLING, WIFI_STATE_UNKNOWN
    			Log.d(wifitag,"wifi state ----->"+wifimanager.getWifiState());
    			Toast.makeText(TestSensorActivity.this, "当前WIFI状态"+wifimanager.getWifiState(), Toast.LENGTH_SHORT).show();
    			
    			/*
    			Context context = listActivity.getApplicationContext();//获取应用上下文  
    			ConnectivityManager connectivityManager = (ConnectivityManager) Context.getSystemService(Context.CONNECTIVITY_SERVICE);//获取系统的连接服务  
    	        NetworkInfo activeNetInfo = connectivityManager.getActiveNetworkInfo();//获取网络的连接情况  
    	        if(activeNetInfo.getType()==ConnectivityManager.TYPE_WIFI){  
    	            //判断WIFI网  
    	        }else if(activeNetInfo.getType()==ConnectivityManager.TYPE_MOBILE) {  
    	            //判断3G网  
    	        }
    	        */
    			
    			if(wifimanager.getWifiState()== 3){
        	        WifiInfo wifiInfo = wifimanager.getConnectionInfo();     
        	        int ipAddress = wifiInfo.getIpAddress();
        	        serverip.setText("本机IP为:"+ipAddress );	
    			}

    			//第二步，建立网络连接
    			
    			
            }
    		else{  
    			wifimanager = (WifiManager)TestSensorActivity.this.getSystemService(Context.WIFI_SERVICE);
    			wifimanager.setWifiEnabled(false);
    			//System.out.println("wifi state ----->"+wifimanager.getWifiState());
    			Log.d(wifitag,"wifi state ----->"+wifimanager.getWifiState());
    			Toast.makeText(TestSensorActivity.this, "当前WIFI状态"+wifimanager.getWifiState(),  Toast.LENGTH_SHORT).show();
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
		    	// timetag.setToNow(); // 取得系统时间。
		    	 //FileName="SensorData" +timetag.toString();

				FileName= GetTimeNow() +".csv";
				//FileName= "fffff.csv";
				Log.d(sdtag,"SD state ----->start record the sensor data");
    			Toast.makeText(TestSensorActivity.this, "数据文件." + FileName+"\n开始采集...", Toast.LENGTH_LONG).show();
    			//serverip.setText("当前SD状态,FileName=" + FileName);
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
			//采集完毕时，按下按钮
			else{
				Log.d(sdtag,"SD state ----->Stop record sensor data");
    			Toast.makeText(TestSensorActivity.this, "采集完毕，数据保存在SD卡中.\n文件名"+ captureFileName, Toast.LENGTH_LONG).show();
    			//WriteToSDCard("SensorData",FileName,"test");
    			SDRecordState = false;
    			
    	        if( captureFile != null ) {
    	            captureFile.close();
    	        }
			}
	}
    
 }
    //获取实时时间
	public String GetTimeNow() {
		SimpleDateFormat    formatter    =   new    SimpleDateFormat    ("yyyyMMdd_HHmmss_SS");
    	Date    curDate    =   new    Date(System.currentTimeMillis());//获取当前时间       
    	String TimerStr    =    formatter.format(curDate);   
    	return TimerStr;
		
	}

	 //在SD卡创建文件
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
	 
		//在SD卡创建目录
	 public File creatSDDir( String DirName){
		 File dir = new File( SDPath + DirName);
		 if(!dir.exists()){
			 try{
				 // mkdirs() 表示，如果需要，会先创建上层目录.
				 dir.mkdirs();
			 }
			 catch(Exception e){
				 e.printStackTrace();
			 }
		 }
		 
		 return dir;
	 }




	 
	 
	 
}
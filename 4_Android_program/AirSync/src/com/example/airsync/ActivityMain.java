package com.example.airsync;


import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.view.Menu;
import android.view.View;

/* TextView �ؼ���Ҫ�Ŀ�*/
import android.widget.TextView;
import android.widget.Toast;
/*��ť�ؼ���Ҫ��*/
import android.widget.Button;
import android.util.DisplayMetrics;
import android.util.Log;
/*��ť������*/
import android.view.View.OnClickListener;
/*���Activity��Ҫ�½�intent���� */
import android.content.DialogInterface;
import android.content.Intent;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;



public class ActivityMain extends Activity {
	/*���ڸ��û���ʾ�����������ǰ��Ҫ�ı�ҪӲ������ */
	private TextView tvTopinfo;
	private TextView tvMetrics;
	private Button   btPicture;
	private Button   btHttp;
	private Button 	 btImageSwithcer;
	
	//��Ҫ���ص�ͼƬ��ַ
	//String ImageWeb = "http://image.baidu.com/i?tn=list&word=liulan#%E6%91%84%E5%BD%B1|%E5%85%A8%E9%83%A8|0";
	String ImageWeb = "http://www.huxiu.com/";

	//log �ļ��ı��
	String Tag = "tusion";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		/*����������ĸ����ؼ���ʽ*/
		setContentView(R.layout.activity_main);
		
		/*�жϵ�ǰ�豸��android�汾��
		 * APK֧�ֵ���Ͱ汾��projec.properties target=android-8
		 */
		if( getApplicationInfo().targetSdkVersion <=  Build.VERSION_CODES.FROYO )
		{
			//����һ����ʾ��
			;
		}
		
		/*���ڸ��û���ʾ�����������ǰ��Ҫ�ı�ҪӲ��������Ϣ��Ҫ��֤������һ���������� */
		tvTopinfo = (TextView) findViewById(R.id.MainTextView1);
		tvMetrics = (TextView) findViewById(R.id.MainTextView2);
		btPicture = (Button) findViewById(R.id.show_picture_button);
		btHttp =    (Button) findViewById(R.id.http_button);
		btImageSwithcer = (Button) findViewById( R.id.image_switcher_button );
				
		CharSequence info_str = getString( R.string.start_info );
		tvTopinfo.setText( info_str );
	
		/*��ʾ�û��豸�ķֱ���,Ϊ��ʵ��Ƭ��׼����Ҳ����Ƭ����ѹ��Ϊ����ֱ�������ʾ*/
		DisplayMetrics dm = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dm); 
		String metrics_str ="����豸�ķֱ���Ϊ�� "+ dm.widthPixels +
							" * " + dm.heightPixels;
		tvMetrics.setText( metrics_str );
		
		/*Ϊ��ť����������*/
		btPicture.setOnClickListener( new PictureButtonListener() );
		btHttp.setOnClickListener(new HttpButtonListener() );
		btImageSwithcer.setOnClickListener( new SwitcherListener() );

	}
	

	/*Ϊ��ʾ��Ƭ��activity��ť����������*/
    class PictureButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
 			Intent intent = new Intent();
 			intent.setClass( ActivityMain.this, ActivitySurface.class);
 			/*�����µ�Activity*/
 			ActivityMain.this.startActivity(intent);
 			/*�ر��������Activity�������ذ�ťʱ���˲�������*/
 			//Main.this.finish();
			
		}
 	}
    
    /*Ϊ���������̵߳İ�ť����������*/
    class HttpButtonListener implements OnClickListener
    {	//Ϊ�˷������磬��Ҫ��manifest�ļ������������Ȩ��
    	NetConnection mNet = new NetConnection();
    	List<String> ImageStrings=new ArrayList<String>();
    	String ImageUrl ;
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			try{
					
				ImageStrings =  mNet.HttpPraseImage( ImageWeb );
				tvTopinfo.setText(ImageWeb);
				tvMetrics.setText(ImageStrings.toString() );
				
			}
			catch ( Exception e )
			{
				Toast.makeText( ActivityMain.this, "������ʱ", Toast.LENGTH_LONG).show(); 
				Log.e(Tag, "Error in network call",e);
			}
			
			try
			{
				for(String ImageUrl: ImageStrings)
				{
					mNet.saveImageFromUrl( ImageUrl );
				}
			}
			catch ( Exception e )
			{
				Toast.makeText( ActivityMain.this, "������Ƭ����", Toast.LENGTH_LONG).show(); 
				Log.e(Tag, "Error in save picture to SD card",e);
			}
			
		}		
    }
    
    class SwitcherListener implements OnClickListener
    {

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
 			Intent intent = new Intent();
 			intent.setClass( ActivityMain.this, ActivityImageSwitcher.class);
 			/*�����µ�Activity*/
 			ActivityMain.this.startActivity(intent);			
		}
    	
    }
    

    
	/*��ʾ�û�WIFIҪ����aircard */
	// ��������ʾ����򣬲�̫ˬ~~
	//ShowAlertDialog( );
     
	/*��������ʱ������һ�������
	 *���ڸ��û���ʾ�����������ǰ��Ҫ�ı�ҪӲ��������Ϣ��Ҫ��֤������һ���������� 
	 *�����������豸��ת��activity���»�������������ٴγ��֣������Ҫ���ơ�
	 */
   private void ShowAlertDialog(  )
    {
	    new AlertDialog.Builder( ActivityMain.this )
		.setTitle(R.string.alert_title)
		.setMessage(R.string.alert_message)
		//���ȷ�������ˣ���һ��������
		.setPositiveButton(
							R.string.alert_ok,
							new DialogInterface.OnClickListener() {
								
								@Override
								public void onClick(DialogInterface dialog, int which) {
									// TODO Auto-generated method stub
									
								}
							}
							)
		//���û�������أ�
		.setNegativeButton(
							R.string.alert_exit,
							new DialogInterface.OnClickListener() {
								
								@Override
								public void onClick(DialogInterface dialog, int which) {
									// TODO Auto-generated method stub
									
								}
							}
							)
		.show();
    }
    
    /*menu�˵��µ�һЩѡ��*/
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	


}
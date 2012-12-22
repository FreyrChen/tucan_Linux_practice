package com.example.airsync;


import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
/* TextView �ؼ���Ҫ�Ŀ�*/
import android.widget.TextView;
/*��ť�ؼ���Ҫ��*/
import android.widget.Button;
/*̽���豸�ķֱ���ʱ��Ҫ*/
import android.util.DisplayMetrics;
/*��ť������*/
import android.view.View.OnClickListener;
/*���Activity��Ҫ�½�intent���� */
import android.content.Intent;



public class Main extends Activity {
	/*���ڸ��û���ʾ�����������ǰ��Ҫ�ı�ҪӲ������ */
	private TextView tvTopinfo;
	private TextView tvMetrics;
	private Button   btPicture;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		/*����������ĸ����ؼ���ʽ*/
		setContentView(R.layout.activity_main);
		
		/*���ڸ��û���ʾ�����������ǰ��Ҫ�ı�ҪӲ��������Ϣ��Ҫ��֤������һ���������� */
		tvTopinfo = (TextView) findViewById(R.id.MainTextView1);
		tvMetrics = (TextView) findViewById(R.id.MainTextView2);
		btPicture = (Button) findViewById(R.id.show_picture_button);
				
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
	}
	

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
    class PictureButtonListener implements OnClickListener{
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
 			tvMetrics.setText( "���ˣ����Ǳ���������ˣ�̫��~");
 			Intent intent = new Intent();
 			intent.setClass( Main.this, ShowPicture.class);
 			/*�����µ�Activity*/
 			Main.this.startActivity(intent);
			
		}
 	}

	


}
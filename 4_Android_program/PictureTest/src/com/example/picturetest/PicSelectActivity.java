package com.example.picturetest;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.Gallery;
import android.widget.ImageView;

public class PicSelectActivity extends Activity {
	
	private final int PICKER = 1;
	//���浱ǰѡ���զ��Ƭ�ǵڼ���
	private int CurrentPicture = 0;
	private Gallery PictureGallery;
	//��ʵ��ͼ�õ�imageview�ؼ�
	private ImageView PictureView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_pic_select);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_pic_select, menu);
		return true;
	}

}


//��manifest.xml�м����������䣬��ֹ�����л�ʱ����activity
//android:configChanges="orientation|keyboardHidden"
package com.example.picturetest;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.Gallery;
import android.widget.ImageView;

public class PicSelectActivity extends Activity {
	
	private final int PICKER = 1;
	//保存当前选择的咋破片是第几张
	private int CurrentPicture = 0;
	private Gallery PictureGallery;
	//现实大图用的imageview控件
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


//在manifest.xml中加入下面的语句，防止横竖切换时重启activity
//android:configChanges="orientation|keyboardHidden"
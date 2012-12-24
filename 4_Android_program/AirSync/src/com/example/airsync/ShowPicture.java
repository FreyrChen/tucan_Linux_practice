package com.example.airsync;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import com.example.airsync.Main.PictureButtonListener;


import android.app.Activity;
import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
/* 建立一个gallery显示SD卡里的照片*/
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;


public class ShowPicture extends Activity 
{
	private TextView tvShowPicture;
	private String file_path="/mnt/extsd/TestPhoto/photo6.png";
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		/*载入主界面的各个控件格式*/
		setContentView(R.layout.activity_showpicture);
		
		/*第一行的字，显示信息用*/
		tvShowPicture = (TextView) findViewById(R.id.show_picture_text);
		tvShowPicture.setText("好吧，我饿了，就做到这里了");
		
		/* 建立一个gallery显示内存里的照片*/
		/* 建立一个gallery显示SD卡里的照片*/
		Gallery gallery = (Gallery)findViewById( R.id.my_gallery);
		//gallery.setAdapter( new ImageAdapter( this));
		gallery.setAdapter( new ImageAdapter( this, GetSDPicture()));
		//gallery.setOnItemClickListener( new GalleryClickListener())
		//gallery.setOnItemClickListener(   new  PictureClickListener() );

		/* 建立一个ImageView显示SD卡里的照片*/	
		/*
		ImageView mImageView = (ImageView)findViewById(R.id.mImageView);
		File file = new File( file_path );
		if(file.exists() )
		{
			Bitmap bm = BitmapFactory.decodeFile( file_path );
			mImageView.setImageBitmap(bm);
		}
		*/
	
		

		
	}

	
	/*将SD卡指定文件夹的照片路径存在一个List中，好让相册控件显示
	 * 这个照片目录是从aircard穿过来的照片存储的地方
	 * 现在实验的时候我放在：/mnt/extsd/TestPhoto
	 */
	private List<String> GetSDPicture()
	{
		List<String> it=new ArrayList<String>();
		/*这里存放的照片不要太大，不然内存不够存放*/
		//File file_path = new File("/mnt/extsd/TestPhoto/");
		File file_path = new File("/mnt/sdcard/Pictures/Screenshots/");
		File[] files = file_path.listFiles();
		
		for( int i=0; i<files.length; i++ )
		{
			File file = files[i];
			if( getImageFile( file.getPath()))
				it.add( file.getPath());
		}
		return it;
	}
	
	/*判断取道的图片文件的文件名是不是支持的类型 */
	private boolean getImageFile( String Name )
	{
		boolean re;
		/*去的扩展名*/
		String end = Name.substring( Name.lastIndexOf(".")+1,
									 Name.length()).toLowerCase();
		if( end.equals("jpg") || end.equals("gif") || end.equals("png") ||
				end.equals("bmp") || end.equals("jpeg") )
		{
			re = true;
		}
		else
		{
			re = false;
		}
		return re;
	}

}

class PictureClickListener implements OnItemClickListener{

	private String picture_tag = "picture_tag";
	
	public void onItemClick
	( AdapterView<?> parent, View v, int position, long id )
	{
		// TODO Auto-generated method stub
		Log.d( picture_tag, "this picture is"+ position, null );
		//Toast.makeText( ShowPicture.this, "有图片了", Toast.LENGTH_SHORT).show();
		
		
	}
	
}


class ImageAdapter extends BaseAdapter
{
	int mGalleryItemBackground;
	private Context mContext;
	private List<String> lis;
	
	/*构建一个Iteger array，去的预先需要加载的Drawable文件夹内的图片ID */
	/*
	private Integer[] myImageIds = 
		{ 
				R.drawable.photo1,
				R.drawable.photo2, 
				R.drawable.photo3, 
				R.drawable.photo4, 
				R.drawable.photo5, 
				R.drawable.photo6, 
		};
	private String file_name="/mnt/extsd/TestPhoto/DSCF0359.JPG";
	private Bitmap bm = BitmapFactory.decodeFile( file_name );
	*/
	
	public ImageAdapter( Context c , List<String> li)
	{
		mContext = c;
		lis = li;
		
		TypedArray a = mContext.obtainStyledAttributes(R.styleable.Gallery);
		mGalleryItemBackground = a.getResourceId(R.styleable.Gallery_android_galleryItemBackground, 0);
		a.recycle();
	}
	
	/*返回照片数目*/
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return lis.size();
	}
	/*返回图像数组的id*/
	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		return position;
	}
	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return position;
	}
	
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		ImageView i = new ImageView( mContext );
		
		//设置图片给image对象
		//i.setImageResource( myImageIds[position]);//决定图片文件的位置:内存		
		//i.setImageBitmap(bm);						//决定图片文件的位置:sd卡
		
		Bitmap bm = BitmapFactory.decodeFile( lis.get(position).toString() );
		i.setImageBitmap(bm);//决定图片文件的位置:sd卡
		
		//设置图片的高和宽
		i.setScaleType( ImageView.ScaleType.FIT_XY );
		//设置Layout的高和宽
		i.setLayoutParams( new Gallery.LayoutParams( 240, 180));
		//i.setLayoutParams( new Gallery.LayoutParams( 1024, 768));
		//设置gallery的背景
		i.setBackgroundResource( mGalleryItemBackground );
		
		return i;
	}
	
		

/*为按钮创建监听器*/
/*
class GalleryClickListener implements OnClickListener{

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		
	}
}
*/


}


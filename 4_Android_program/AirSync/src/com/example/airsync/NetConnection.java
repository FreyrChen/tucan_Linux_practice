package com.example.airsync;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.util.Log;

import com.example.airsync.SDCard;

public class NetConnection {
	
	
	private String Tag = "Netconnection";
	private StringBuffer sff = new StringBuffer();
	private String myString = null;
	
	
	public List<String>  HttpPraseImage( String HttpWeb) throws Exception
	{
		List<String> ImageStrings=new ArrayList<String>();
		Document doc = Jsoup.connect( HttpWeb ).get();
		//<img src="http://www.baidu.com/img/baidu_sylogo1.gif" width="270" height="129">
		Elements media = doc.select("[src]");
		Log.i(Tag,"get html's tag select");
		Log.i(Tag,"get media size:"+media.size());
		
		for( Element link: media )
		{
			if (link.tagName().equals("img"))
			{
				Log.i(Tag,link.text());
				sff.append(link.attr("abs:src")).append("\n");
				ImageStrings.add(link.attr("abs:src"));
			}
		}
		myString = sff.toString();
		Log.i(Tag,"parse image link: " + myString );
		return ImageStrings;
	}
	
	
    /*
     * ���ƶ���ַ����ҳԴ�ļ�HTML���أ��Ա����
     */
    public String getHtmlFromUrl( String ImagePath ) throws Exception
	{

		URL url = new URL(ImagePath);
		String html="";
		// ��·������---�õ�HttpURLConnection����
		HttpURLConnection connection = (HttpURLConnection ) url.openConnection();
		Log.i(Tag,"URL:" + url.toString());
		// �������ӳ�ʱ
		connection.setReadTimeout(5*1000);
		// ͨ��HTTPЭ����������HTML---��������ʽ��get/post 
		connection.setRequestMethod("GET");
		Log.i(Tag,"response code:"+ connection.getResponseCode());
		//�ж���վ���ӵĳɹ�Ŷ�������
		if( connection.getResponseCode() == 200 )
		{
			Log.i(Tag,"http connection response success!");
			// ��������ֻ�Ӧ���ڴ�������----ͨ����������ȡHTML���� 
			InputStream input_stream = connection.getInputStream();
			// ���������л�ȡHTML�Ķ���������----readInputStream() 
			byte[] data = readHttpStream(input_stream );
			html = new String(data);
			Log.i(Tag,"data length=" + data.length);	
		}
		Log.i(Tag,"data=" + html);
		return html;
	}
   //��������������һ��������
	public byte[] readHttpStream( InputStream in_stream ) throws Exception 
	{
		ByteArrayOutputStream out_stream = new ByteArrayOutputStream();
		  // ����һ�������� 
		byte[] buffer = new byte[1024];
		int length = 1;
	    // ���ϵĴ������ȡ����---in_stream.read(buffer)��ʾ�������ȡ���ݵ������� 
	    // ��ȡ��ĩβʱ������ֵ��-1��
		while( (length = in_stream.read( buffer ) )!=-1 )
		{
			out_stream.write( buffer, 0, length );
		}
		out_stream.close();
		in_stream.close();
		return out_stream.toByteArray();
		
	}
	
	
	/*
	 * ���������ϵ�ͼƬ�ļ�,������������ʾ
	 */
	public Bitmap getURLToBitmap( String pic_url )
	{
	
		String test_url = "http://www.baidu.com/img/baidu_sylogo1.gif";
		
		URL image_Url = null;
		Bitmap bit_map = null;
		
		try 
		{
			//image_Url = new URL( pic_url );
			image_Url = new URL( test_url );
		}
		catch ( MalformedURLException e )
		{
			e.printStackTrace();
		}
		
		try
		{
			//
			HttpURLConnection connection = (HttpURLConnection) image_Url.openConnection();
			connection.connect();
		
			InputStream input_stream = connection.getInputStream();
			bit_map = BitmapFactory.decodeStream( input_stream );
			input_stream.close();
		}
		catch ( IOException e )
		{
			e.printStackTrace();
		}
		return bit_map;
	}
	
	
	

	/*
	 * ���������ϵ�ͼƬ�ļ�,����ΪSD���ϵ��ļ���
	 */
	
	public void saveImageFromUrl( String ImagePath ) throws Exception
	{
		//��Ҫ���ص�ͼƬ��ַ
		//String ImagePath = "";
		URL url = new URL(ImagePath);
		//�ļ�����ʲô����Ҫ���ǰ�������������������������
		String FileName = ImagePath;
		 File  file = null;
		
		SDCard sd = new SDCard();
		
		//�½�HTTP���Ӷ���
		HttpURLConnection connection = (HttpURLConnection ) url.openConnection();
		Log.i(Tag, "URL:" + url.toString());
		connection.setReadTimeout(6*1000);
		connection.setRequestMethod("GET");
		Log.i(Tag, "response code:"+ connection.getResponseCode());
		//�ж���վ���ӵĳɹ�Ŷ�������
		if( connection.getResponseCode() == 200 )
		{
			Log.i(Tag, "http connection response success!");

			//�½�������
			InputStream input_stream = connection.getInputStream();
			byte[] data = readStream(input_stream );
			
			//String FileName = GetTimeNow() +".csv";
			String SDPath = Environment.getExternalStorageDirectory().toString() +"/tusion_image/";
			Log.i(Tag, "creat SD dirsdpath is "+SDPath);
			
			try 
			{
				 sd.creatSDDir(SDPath);
			
			} catch (IOException e) {
				// TODO Auto-generated catch block
				Log.e(Tag, "creat SD dir error",e);
				e.printStackTrace();
			}
			
			try 
			{
				//��ͼƬ���ڱ����ļ���
				file = sd.creatSDFile( SDPath + FileName);
				 //file = sd.creatSDFile( FileName);
			
			} catch (IOException e) {
				// TODO Auto-generated catch block
				Log.e(Tag, "creat SD dir error",e);
				e.printStackTrace();
			}
	

			//�����ܵ�����д���ļ�������
			FileOutputStream output_stream = new FileOutputStream( file); 
			output_stream.write( data );
			output_stream.close();
		}
	}


	//
	public byte[] readStream( InputStream in_stream ) throws Exception 
	{
		ByteArrayOutputStream out_stream = new ByteArrayOutputStream();
		byte[] buffer = new byte[1024];
		int length = 1;
		while( (length = in_stream.read( buffer ) )!=-1 )
		{
			out_stream.write( buffer, 0, length );
		}
		out_stream.close();
		in_stream.close();
		return out_stream.toByteArray();
		
	}
	
		

}
/**
 * AudioFingerprinter.java
 * EchoprintLib
 * 
 * Created by Alex Restrepo on 1/22/12.
 * Copyright (C) 2012 Grand Valley State University (http://masl.cis.gvsu.edu/)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package edu.gvsu.masl.echoprint;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Hashtable;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONObject;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

/**
 * Main fingerprinting class<br>
 * This class will record audio from the microphone, generate the fingerprint code using a native library and query the data server for a match
 * 
 * @author Alex Restrepo (MASL)
 *
 */
public class AudioFingerprinter implements Runnable 
{
	public final static String META_SCORE_KEY = "meta_score";
	public final static String SCORE_KEY = "score";
	public final static String ALBUM_KEY = "release";
	public final static String TITLE_KEY = "track";
	public final static String TRACK_ID_KEY = "track_id";
	public final static String ARTIST_KEY = "artist_name";
	
	public final static String RESPONSE_KEY = "response";
	public final static String SONGS_KEY = "songs";
	public final static String ARTIST_NAME_KEY = "artist_name";
	
	
	
	//private final String SERVER_URL = "<your server address here>/query?fp_code=";
	//private final String SERVER_URL = "http://developer.echonest.com/api/v4/song/identify?api_key=AV6AWC8NL7IJPZ5QO&code=";
	//private final String SERVER_URL = "http://developer.echonest.com/api/v4/song/identify?api_key=J4XWDUE9WJATUMXXS&code=";
	//private final String SERVER_URL = "http://223.202.52.148/query?fp_code=";
	private final String SERVER_URL = "http://music.api.omusic.cc/api/innerapi/testfingerprint2.0.php?fp_code=";
	//http://music.api.omusic.cc/api/innerapi/testfingerprint2.0.php?fp_code=AV6AWC8NL7IJPZ5QO&code=eJzNV1mOHTkMu5Ity1qOI0v2_Y8wrBogL3hAnI8gmPlhd7sWyxRJVbfWiNsFpt_gtAv0vm4w9AaTb-DjAn90oswbbLlAn3QDyRuY3iD8Ar9pA40b3NmQukGcC_ym-zJvcGdj1QX-p-ed_Qb3855xgT_qPl_hzpVe4cpVK7vAH3EVcYFG6wZ_kY1-g1wX-I2ulC_QOt3gzsb9vGY3iH2DPS_wF53ycP1r-CM25Ab_VW48I-vXcPiXQDy3bC2t6ZOC5igTMqa1d2pxl7022xijXKf3dRbFXF1jhrZV3RpZpakVTVWV3rnc3JJm7YryfdrM3WMs6qkWFG07s2gOGzmIasytxtzGdDZ8E-yqMbTTbIOzfOaizT9B6Rzfax8wb1W19WSFbMktyj3osArG75hU1JJRJRWWhp04KEomWbgbMUn4TmNDdZ1RQZyhtvfxY7rirLWxhY51ZqlsZI0IaKo5RosYZzOvEAkq0zOXsRrhhtmnevcsaQO-0XZ8W4uVG4Qok57obmiJc--N1_oAuVl8rX0gyqol3LbHQD-YT87uy2dbq2yo1yiNvoQcTTyBg67TcmwfYpx8JKn2ke7sKFHYi6NAHM-0PbDLNJhVUvTJuECrtx2FJFYrsbTVZnPHKUbP7nvkWZAKS5SaTTSE8bF2as33FvUcbUlq87X7QQPUt240birpRG065KSraZrtTqcKix943_e19oGWOM_CqVAQiFmVyyj36H06Oi7oKg5zSknOyUzx4a6MOJq2oQmGdnfg6LFCw6fBXrqYC3QNykopiCMUT56S7TRJOtJbWlBOcBTvLXMeeKkmrRjRIRso7r36PvteFWjN36tfbz5hqO0HvG_-WvsA9PUcYgUhgM52iIqRFxmt_PQO7wlk10iFxkg63igWJgLDAXPiQRdvHdKhA-mpTJn7nE50NprkwbXa2jHZ9xqbTsCtYzkax0geYYVBIKgFz7SKLRw7_XhuGHAmLZG1cEpGdMxYTkYTnDHRgtcEpuKx9dFw2uCdOREwCmPo2fQ8Id2Gi0DE0iU2uiYMPU_NcBvgNXGgH9AGmvK19oGFfxlg5xhZ-PqYh0Egp_RENsHP1ZgmtqDYj28gesHCUfaufW10Oynp2WMNi0MYvAdo7iyVfce2wvv6Xk-GoeKDQ5NajkzHwZCsxcVr6pToHRu-n26eaMEhJUIUoU7CrygDG2I72AxZCiM5igBfC2X_BBNT9nvtA6MPMoGnEv7UAdadjzXUgQptdqhWQT9iUtvWIAT0MYFlqBbmgqHVyDZHNtYjnBQ0B6MIugvEGQxR1fFDpSqh9uwIXgwcsFM-wgMRgcrZeBBIXETgPt1AGiOIx0bMUDtS0d-rYtjo69kF3vp739JHMs-zE2ai96rwGvIBdFC_1z7giEJZiuEUaEAD41Gn-2MIlF8zG6I48Xfx01lMMPg0rIFKOLwaJK6ODDkYd94Z4yJyIyHoTOoKf2OQYIYabLzQXpwDtPT1bIDPc0H5MpzGHtAIBCMnRhuBUaXoLgZepSK0CWJ_b56-HlmNAblMfNJawdjP1YCl6X1VR7A1iCL-3QPZ0uOzUSCgdMGMZ2-DK-E7-8C779faB_4Bx0T9fg
	private final int FREQUENCY = 11025;
	private final int CHANNEL = AudioFormat.CHANNEL_IN_MONO;
	private final int ENCODING = AudioFormat.ENCODING_PCM_16BIT;	
	
	private Thread thread;
	private volatile boolean isRunning = false;
	AudioRecord mRecordInstance = null;
	
	private short audioData[];
	private int bufferSize;	
	private int secondsToRecord;
	private volatile boolean continuous;
	
	private AudioFingerprinterListener listener;
	
	private String JsonStr="";
	private String SearchTime;
	
	/**
	 * Constructor for the class
	 * 
	 * @param listener is the AudioFingerprinterListener that will receive the callbacks
	 */
	public AudioFingerprinter(AudioFingerprinterListener listener)
	{
		this.listener = listener;
	}
	
	/**
	 * Starts the listening / fingerprinting process using the default parameters:<br>
	 * A single listening pass of 20 seconds 
	 */
	public void fingerprint()
	{
		// set dafault listening time to 20 seconds
		this.fingerprint(20);
	}
	
	/**
	 * Starts a single listening / fingerprinting pass
	 * 
	 * @param seconds the seconds of audio to record.
	 */
	public void fingerprint(int seconds)
	{
		// no continuous listening
		this.fingerprint(seconds, false);
	}
	
	/**
	 * Starts the listening / fingerprinting process
	 * 
	 * @param seconds the number of seconds to record per pass
	 * @param continuous if true, the class will start a new fingerprinting pass after each pass
	 */
	public void fingerprint(int seconds, boolean continuous)
	{
		if(this.isRunning)
			return;
				
		this.continuous = continuous;
//-------test for debug the json
		
		// cap to 30 seconds max, 10 seconds min.
		this.secondsToRecord = Math.max(Math.min(seconds, 30), 10);
		//this.secondsToRecord = Math.max(Math.min(seconds, 1), 2);
		
		// start the recording thread
		thread = new Thread(this);
		thread.start();
	}
	
	/**
	 * stops the listening / fingerprinting process if there's one in process
	 */
	public void stop() 
	{
		this.continuous = false;
		if(mRecordInstance != null)
			mRecordInstance.stop();
	}
	
	/**
	 * The main thread<br>
	 * Records audio and generates the audio fingerprint, then it queries the server for a match and forwards the results to the listener.
	 */
	public void run() 
	{
		this.isRunning = true;
		try 
		{			
			// create the audio buffer
			// get the minimum buffer size
			int minBufferSize = AudioRecord.getMinBufferSize(FREQUENCY, CHANNEL, ENCODING);
			
			// and the actual buffer size for the audio to record
			// frequency * seconds to record.
			bufferSize = Math.max(minBufferSize, this.FREQUENCY * this.secondsToRecord);
						
			audioData = new short[bufferSize];
						
			// start recorder
			mRecordInstance = new AudioRecord(
								MediaRecorder.AudioSource.MIC,
								FREQUENCY, CHANNEL, 
								ENCODING, minBufferSize);
						
			willStartListening();
			
			mRecordInstance.startRecording();
			boolean firstRun = true;
			do 
			{		
				try
				{
					willStartListeningPass();
					
					long time = System.currentTimeMillis();
					// fill audio buffer with mic data.
					int samplesIn = 0;
					do 
					{					
						samplesIn += mRecordInstance.read(audioData, samplesIn, bufferSize - samplesIn);
						
						if(mRecordInstance.getRecordingState() == AudioRecord.RECORDSTATE_STOPPED)
							break;
					} 
					while (samplesIn < bufferSize);				
					Log.d("Fingerprinter", "Audio recorded: " + (System.currentTimeMillis() - time) + " millis");
										
					// see if the process was stopped.
					if(mRecordInstance.getRecordingState() == AudioRecord.RECORDSTATE_STOPPED || (!firstRun && !this.continuous))
						break;
					
					// create an echoprint codegen wrapper and get the code
					time = System.currentTimeMillis();
					Codegen codegen = new Codegen();
	    			String code = codegen.generate(audioData, samplesIn);
	    			SearchTime= "Codegen created in: " + (System.currentTimeMillis() - time) + " millis.\n";
	    			Log.d("Fingerprinter", "Codegen created in: " + (System.currentTimeMillis() - time) + " millis");
	    			
	    			didGenerateFingerprintCode(code);
	   //======================================================================== 			
	    			// fetch data from echonest
	    			time = System.currentTimeMillis();

	    			
	    /*			
	    			String urlstr = SERVER_URL + code;
	    			//String urlstr="http://developer.echonest.com/api/v4/song/identify?api_key=AV6AWC8NL7IJPZ5QO&code=eJzNV1mOHTkMu5Ity1qOI0v2_Y8wrBogL3hAnI8gmPlhd7sWyxRJVbfWiNsFpt_gtAv0vm4w9AaTb-DjAn90oswbbLlAn3QDyRuY3iD8Ar9pA40b3NmQukGcC_ym-zJvcGdj1QX-p-ed_Qb3855xgT_qPl_hzpVe4cpVK7vAH3EVcYFG6wZ_kY1-g1wX-I2ulC_QOt3gzsb9vGY3iH2DPS_wF53ycP1r-CM25Ab_VW48I-vXcPiXQDy3bC2t6ZOC5igTMqa1d2pxl7022xijXKf3dRbFXF1jhrZV3RpZpakVTVWV3rnc3JJm7YryfdrM3WMs6qkWFG07s2gOGzmIasytxtzGdDZ8E-yqMbTTbIOzfOaizT9B6Rzfax8wb1W19WSFbMktyj3osArG75hU1JJRJRWWhp04KEomWbgbMUn4TmNDdZ1RQZyhtvfxY7rirLWxhY51ZqlsZI0IaKo5RosYZzOvEAkq0zOXsRrhhtmnevcsaQO-0XZ8W4uVG4Qok57obmiJc--N1_oAuVl8rX0gyqol3LbHQD-YT87uy2dbq2yo1yiNvoQcTTyBg67TcmwfYpx8JKn2ke7sKFHYi6NAHM-0PbDLNJhVUvTJuECrtx2FJFYrsbTVZnPHKUbP7nvkWZAKS5SaTTSE8bF2as33FvUcbUlq87X7QQPUt240birpRG065KSraZrtTqcKix943_e19oGWOM_CqVAQiFmVyyj36H06Oi7oKg5zSknOyUzx4a6MOJq2oQmGdnfg6LFCw6fBXrqYC3QNykopiCMUT56S7TRJOtJbWlBOcBTvLXMeeKkmrRjRIRso7r36PvteFWjN36tfbz5hqO0HvG_-WvsA9PUcYgUhgM52iIqRFxmt_PQO7wlk10iFxkg63igWJgLDAXPiQRdvHdKhA-mpTJn7nE50NprkwbXa2jHZ9xqbTsCtYzkax0geYYVBIKgFz7SKLRw7_XhuGHAmLZG1cEpGdMxYTkYTnDHRgtcEpuKx9dFw2uCdOREwCmPo2fQ8Id2Gi0DE0iU2uiYMPU_NcBvgNXGgH9AGmvK19oGFfxlg5xhZ-PqYh0Egp_RENsHP1ZgmtqDYj28gesHCUfaufW10Oynp2WMNi0MYvAdo7iyVfce2wvv6Xk-GoeKDQ5NajkzHwZCsxcVr6pToHRu-n26eaMEhJUIUoU7CrygDG2I72AxZCiM5igBfC2X_BBNT9nvtA6MPMoGnEv7UAdadjzXUgQptdqhWQT9iUtvWIAT0MYFlqBbmgqHVyDZHNtYjnBQ0B6MIugvEGQxR1fFDpSqh9uwIXgwcsFM-wgMRgcrZeBBIXETgPt1AGiOIx0bMUDtS0d-rYtjo69kF3vp739JHMs-zE2ai96rwGvIBdFC_1z7giEJZiuEUaEAD41Gn-2MIlF8zG6I48Xfx01lMMPg0rIFKOLwaJK6ODDkYd94Z4yJyIyHoTOoKf2OQYIYabLzQXpwDtPT1bIDPc0H5MpzGHtAIBCMnRhuBUaXoLgZepSK0CWJ_b56-HlmNAblMfNJawdjP1YCl6X1VR7A1iCL-3QPZ0uOzUSCgdMGMZ2-DK-E7-8C779faB_4Bx0T9fg==&version=4.12";
	    			Log.d("tusion", urlstr );
	    			Log.d("1", "String: " + (System.currentTimeMillis() - time) + " millis");
			
	    			
	    				//String httpUrl = "http://192.168.1.110:8080/httpget.jsp";  
	    	        //��õ�����  
	    				// String resultData = "";  
	    	        URL url = null;  
	    	        try 
	    	        {  
	    	            //����һ��URL����  
	    	            url = new URL(urlstr);   
	    	        }  
	    	        catch (MalformedURLException e)  
	    	        {  
	    	            Log.e("URL", "MalformedURLException");  
	    	        }  
	    	        if (url != null)  
	    	        {  
	    	                // ʹ��HttpURLConnection������  
	    	                HttpURLConnection urlConn = (HttpURLConnection) url.openConnection();  
	    	               Log.d("2-1", "open connection: " + (System.currentTimeMillis() - time) + " millis");
	    	    			
	    	                //��Ϊ�����post����,������Ҫ����Ϊtrue  
	    	                urlConn.setDoOutput(true);  
	    	                urlConn.setDoInput(true);  
	    	                // ������POST��ʽ  
	    	                urlConn.setRequestMethod("POST");  
	    	                // Post ������ʹ�û���  
	    	                urlConn.setUseCaches(false);  
	    	                urlConn.setInstanceFollowRedirects(true);  
	    	                // ���ñ������ӵ�Content-type������Ϊapplication/x-www-form-urlencoded��  
	    	                urlConn.setRequestProperty("Content-Type","application/x-www-form-urlencoded");  
	    	                // ���ӣ���postUrl.openConnection()���˵����ñ���Ҫ��connect֮ǰ��ɣ�  
	    	                // Ҫע�����connection.getOutputStream�������Ľ���connect��  
	    	                urlConn.connect();  
	    	                Log.d("2-2", "open connection: " + (System.currentTimeMillis() - time) + " millis");
	    	    	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
	    	                InputStream instream =  urlConn.getInputStream();
	    	                
	    	                Log.d("3", "wait input stream: " + (System.currentTimeMillis() - time) + " millis");
		    	            JsonStr= convertStreamToString(instream);
		    	            Log.d("4", "convert to string: " + (System.currentTimeMillis() - time) + " millis");
			    	        SearchTime += "Search time: " + (System.currentTimeMillis() - time) + " millis";
			     			Log.d("Fingerprinter", "Results fetched in: " + (System.currentTimeMillis() - time) + " millis");
			     			Log.d("result", JsonStr);
			 
			     			didFindMatchForCode(JsonStr, SearchTime);
			     			
		    	            // now you have the string representation of the HTML request
		    	            instream.close();

		    	            Log.d("5", "close: " + (System.currentTimeMillis() - time) + " millis");
	    	                

	    	        }
	    	*/        
	//--------------------------------------
	 
	    			
	    			
	    			
					//String urlstr = SERVER_URL + code +"&version=4.12";
	    			String urlstr = SERVER_URL + code;
	    			//String urlstr="http://developer.echonest.com/api/v4/song/identify?api_key=AV6AWC8NL7IJPZ5QO&code=eJzNV1mOHTkMu5Ity1qOI0v2_Y8wrBogL3hAnI8gmPlhd7sWyxRJVbfWiNsFpt_gtAv0vm4w9AaTb-DjAn90oswbbLlAn3QDyRuY3iD8Ar9pA40b3NmQukGcC_ym-zJvcGdj1QX-p-ed_Qb3855xgT_qPl_hzpVe4cpVK7vAH3EVcYFG6wZ_kY1-g1wX-I2ulC_QOt3gzsb9vGY3iH2DPS_wF53ycP1r-CM25Ab_VW48I-vXcPiXQDy3bC2t6ZOC5igTMqa1d2pxl7022xijXKf3dRbFXF1jhrZV3RpZpakVTVWV3rnc3JJm7YryfdrM3WMs6qkWFG07s2gOGzmIasytxtzGdDZ8E-yqMbTTbIOzfOaizT9B6Rzfax8wb1W19WSFbMktyj3osArG75hU1JJRJRWWhp04KEomWbgbMUn4TmNDdZ1RQZyhtvfxY7rirLWxhY51ZqlsZI0IaKo5RosYZzOvEAkq0zOXsRrhhtmnevcsaQO-0XZ8W4uVG4Qok57obmiJc--N1_oAuVl8rX0gyqol3LbHQD-YT87uy2dbq2yo1yiNvoQcTTyBg67TcmwfYpx8JKn2ke7sKFHYi6NAHM-0PbDLNJhVUvTJuECrtx2FJFYrsbTVZnPHKUbP7nvkWZAKS5SaTTSE8bF2as33FvUcbUlq87X7QQPUt240birpRG065KSraZrtTqcKix943_e19oGWOM_CqVAQiFmVyyj36H06Oi7oKg5zSknOyUzx4a6MOJq2oQmGdnfg6LFCw6fBXrqYC3QNykopiCMUT56S7TRJOtJbWlBOcBTvLXMeeKkmrRjRIRso7r36PvteFWjN36tfbz5hqO0HvG_-WvsA9PUcYgUhgM52iIqRFxmt_PQO7wlk10iFxkg63igWJgLDAXPiQRdvHdKhA-mpTJn7nE50NprkwbXa2jHZ9xqbTsCtYzkax0geYYVBIKgFz7SKLRw7_XhuGHAmLZG1cEpGdMxYTkYTnDHRgtcEpuKx9dFw2uCdOREwCmPo2fQ8Id2Gi0DE0iU2uiYMPU_NcBvgNXGgH9AGmvK19oGFfxlg5xhZ-PqYh0Egp_RENsHP1ZgmtqDYj28gesHCUfaufW10Oynp2WMNi0MYvAdo7iyVfce2wvv6Xk-GoeKDQ5NajkzHwZCsxcVr6pToHRu-n26eaMEhJUIUoU7CrygDG2I72AxZCiM5igBfC2X_BBNT9nvtA6MPMoGnEv7UAdadjzXUgQptdqhWQT9iUtvWIAT0MYFlqBbmgqHVyDZHNtYjnBQ0B6MIugvEGQxR1fFDpSqh9uwIXgwcsFM-wgMRgcrZeBBIXETgPt1AGiOIx0bMUDtS0d-rYtjo69kF3vp739JHMs-zE2ai96rwGvIBdFC_1z7giEJZiuEUaEAD41Gn-2MIlF8zG6I48Xfx01lMMPg0rIFKOLwaJK6ODDkYd94Z4yJyIyHoTOoKf2OQYIYabLzQXpwDtPT1bIDPc0H5MpzGHtAIBCMnRhuBUaXoLgZepSK0CWJ_b56-HlmNAblMfNJawdjP1YCl6X1VR7A1iCL-3QPZ0uOzUSCgdMGMZ2-DK-E7-8C779faB_4Bx0T9fg==&version=4.12";
	    			Log.d("tusion", urlstr );
	    			Log.d("1", "String: " + (System.currentTimeMillis() - time) + " millis");
					
	    			HttpClient client = new DefaultHttpClient();
	    			HttpGet get = new HttpGet(urlstr);
	    			Log.d("2-1", "new httpget " + (System.currentTimeMillis() - time) + " millis");
		    	        
	    			// get response
	    			HttpResponse response = client.execute(get);                
	    			// Examine the response status
	    	        Log.d("Fingerprinter",response.getStatusLine().toString());
	    	        Log.d("2-2", "http response " + (System.currentTimeMillis() - time) + " millis");
	    	        
	    	        // Get hold of the response entity
	    	        HttpEntity entity = response.getEntity();
	    	        // If the response does not enclose an entity, there is no need
	    	        // to worry about connection release
	    	        Log.d("2-3", "http entity " + (System.currentTimeMillis() - time) + " millis");
	    	        
	    	        if (entity != null) 
	    	        {
	    	            // A Simple JSON Response Read
	    	            InputStream instream = entity.getContent();
	    	            Log.d("3", "stream: " + (System.currentTimeMillis() - time) + " millis");
	    	            JsonStr= convertStreamToString(instream);
	    	            Log.d("4", "convert to string: " + (System.currentTimeMillis() - time) + " millis");
		    	        SearchTime += "Search time: " + (System.currentTimeMillis() - time) + " millis";
		     			Log.d("Fingerprinter", "Results fetched in: " + (System.currentTimeMillis() - time) + " millis");
		     			Log.d("result", JsonStr);
		 
		     			didFindMatchForCode(JsonStr, SearchTime);
		     			
	    	            // now you have the string representation of the HTML request
	    	            instream.close();
	    	            
	    	            Log.d("5", "close: " + (System.currentTimeMillis() - time) + " millis");
	    	        }
	    	       

	     	/*		
	     			//======================================================================== 			
	    			// parse JSON
		    		JSONObject jobj = new JSONObject(JsonStr);
		    		
					JSONObject jresp  = jobj.getJSONObject( "response" );
					JSONArray jsonarray = jresp.getJSONArray("songs");
	
					Hashtable<String, String> match = new Hashtable<String, String>();
					//match.put(SCORE_KEY, jobj.getDouble(SCORE_KEY) + "");
					JSONObject jmes = null;
					Log.d("1","ok");
					for( int i = 0; i< jsonarray.length(); i++){
						JSONObject c = jsonarray.getJSONObject(i);
						//String title  = c.getString("title");
						//String artist = c.getString("artist_name");
						match.put(TITLE_KEY, c.getString(TITLE_KEY));
						jmes = c.getJSONObject("message");	
		    		}
					if( jmes.has("OK")){
						Log.d("tusion", "success get message from echoprint server ");
						//didFindMatchForCode(match, code);
					}
					else{
			    		didNotFindMatchForCode(code);	
					}
					//didFailWithException(new Exception("Unknown error"));
		    		firstRun = false;
		    		didFinishListeningPass();
		    	*/	
			}
			catch(Exception e)
			{
				e.printStackTrace();
				Log.e("json process", e.getLocalizedMessage());
				didFailWithException(e);
			}
		}
		while (this.continuous);
		}
		catch (Exception e) 
		{
			e.printStackTrace();
			Log.e("get process", e.getLocalizedMessage());
			
			didFailWithException(e);
		}
		
		if(mRecordInstance != null)
		{
			mRecordInstance.stop();
			mRecordInstance.release();
			mRecordInstance = null;
		}
		this.isRunning = false;
		
		didFinishListening();
	}
	
	private static String convertStreamToString(InputStream is) 
	{
	    /*
	     * To convert the InputStream to String we use the BufferedReader.readLine()
	     * method. We iterate until the BufferedReader return null which means
	     * there's no more data to read. Each line will appended to a StringBuilder
	     * and returned as String.
	     */
	    BufferedReader reader = new BufferedReader(new InputStreamReader(is));
	    StringBuilder sb = new StringBuilder();

	    String line = null;
	    try {
	        while ((line = reader.readLine()) != null) {
	            sb.append(line + "\n");
	        }
	    } catch (IOException e) {
	        e.printStackTrace();
	    } finally {
	        try {
	            is.close();
	        } catch (IOException e) {
	            e.printStackTrace();
	        }
	    }
	    return sb.toString();
	}
		
	private String messageForCode(int code)
	{
		try{
			String codes[] = {
					"NOT_ENOUGH_CODE", "CANNOT_DECODE", "SINGLE_BAD_MATCH", 
					"SINGLE_GOOD_MATCH", "NO_RESULTS", "MULTIPLE_GOOD_MATCH_HISTOGRAM_INCREASED",
					"MULTIPLE_GOOD_MATCH_HISTOGRAM_DECREASED", "MULTIPLE_BAD_HISTOGRAM_MATCH", "MULTIPLE_GOOD_MATCH"
					}; 
	
			return codes[code];
		}
		catch(ArrayIndexOutOfBoundsException e)
		{
			return "UNKNOWN";
		}
	}
	
	private void didFinishListening()
	{
		if(listener == null)
			return;
		
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.didFinishListening();
				}
			});
		}
		else
			listener.didFinishListening();
	}
	
	private void didFinishListeningPass()
	{
		if(listener == null)
			return;
		
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.didFinishListeningPass();
				}
			});
		}
		else
			listener.didFinishListeningPass();
	}
	
	private void willStartListening()
	{
		if(listener == null)
			return;
		
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.willStartListening();
				}
			});
		}
		else	
			listener.willStartListening();
	}
	
	private void willStartListeningPass()
	{
		if(listener == null)
			return;
			
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.willStartListeningPass();
				}
			});
		}
		else
			listener.willStartListeningPass();
	}
	
	private void didGenerateFingerprintCode(final String code)
	{
		if(listener == null)
			return;
		
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.didGenerateFingerprintCode(code);
				}
			});
		}
		else
			listener.didGenerateFingerprintCode(code);
	}
	
	//private void didFindMatchForCode(final Hashtable<String, String> table, final String code)
	private void   didFindMatchForCode( final String JsonStr, final String SearchTime) {
		if(listener == null)
			return;
			
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					//listener.didFindMatchForCode(table, code);
					listener.didFindMatchForCode(JsonStr, SearchTime);
				}
			});
		}
		else
			//listener.didFindMatchForCode(table, code);
			listener.didFindMatchForCode(JsonStr, SearchTime);
	}
	
	private void didNotFindMatchForCode(final String code)
	{
		if(listener == null)
			return;
		
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.didNotFindMatchForCode(code);
				}
			});
		}
		else
			listener.didNotFindMatchForCode(code);
	}
	
	private void didFailWithException(final Exception e)
	{
		if(listener == null)
			return;
			
		if(listener instanceof Activity)
		{
			Activity activity = (Activity) listener;
			activity.runOnUiThread(new Runnable() 
			{		
				public void run() 
				{
					listener.didFailWithException(e);
				}
			});
		}
		else
			listener.didFailWithException(e);
	}
		
	/**
	 * Interface for the fingerprinter listener<br>
	 * Contains the different delegate methods for the fingerprinting process
	 * @author Alex Restrepo
	 *
	 */
	public interface AudioFingerprinterListener
	{		
		/**
		 * Called when the fingerprinter process loop has finished
		 */
		public void didFinishListening();
		
		/**
		 * Called when a single fingerprinter pass has finished
		 */
		public void didFinishListeningPass();
		
		/**
		 * Called when the fingerprinter is about to start
		 */
		public void willStartListening();
		
		/**
		 * Called when a single listening pass is about to start
		 */
		public void willStartListeningPass();
		
		/**
		 * Called when the codegen libary generates a fingerprint code
		 * @param code the generated fingerprint as a zcompressed, base64 string
		 */
		public void didGenerateFingerprintCode(String code);
		
		/**
		 * Called if the server finds a match for the submitted fingerprint code 
		 * @param table a hashtable with the metadata returned from the server
		 * @param code the submited fingerprint code
		 */
		//public void didFindMatchForCode(Hashtable<String, String> table, String code);
		public void didFindMatchForCode(String JsonStr, String code);
		
		/**
		 * Called if the server DOES NOT find a match for the submitted fingerprint code
		 * @param code the submited fingerprint code
		 */
		public void didNotFindMatchForCode(String code);
		
		/**
		 * Called if there is an error / exception in the fingerprinting process
		 * @param e an exception with the error
		 */
		public void didFailWithException(Exception e);
	}
}
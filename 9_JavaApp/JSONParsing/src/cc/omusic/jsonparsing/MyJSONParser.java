package cc.omusic.jsonparsing;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONException;
import org.json.JSONObject;

public class MyJSONParser {
	
	static InputStream is = null;
	static JSONObject jsonobj = null;
	static String jsonstr = "";
	//constructor
	public MyJSONParser(){
	}
	
	public JSONObject getJSONFromUrl( String url ){
		try {
			DefaultHttpClient httpClient = new DefaultHttpClient();
			HttpGet httpGet = new HttpGet(url);
			
			HttpResponse httpResponse = httpClient.execute( httpGet );
			HttpEntity httpEntity = httpResponse.getEntity();
			is = httpEntity.getContent();
		}catch ( UnsupportedEncodingException e ){
			e.printStackTrace();
		}catch( ClientProtocolException e){
			e.printStackTrace();
		}catch(IOException e){
			e.printStackTrace();
		}
		
		try{
			BufferedReader reader = new BufferedReader( new InputStreamReader(is) );
			StringBuilder sb = new StringBuilder();
			String line = null;
			while( (line=reader.readLine()) != null ){
				sb.append( line + "\n");
			}
			is.close();
			jsonstr = sb.toString();
			System.out.println( "print jsonstr: " );
			System.out.println( jsonstr );
		}catch ( Exception e){
			System.out.println("Buffer Error"+ "Error converting result"+ e.toString());
		}
		
		try{
			jsonobj = new JSONObject( jsonstr);
		}catch (JSONException e){
			System.out.println("JSON Parsing"+"Error parsing data" + e.toString());
		}
		return jsonobj;
	}
	
	private static final String title = "";
	private static final String artist_name="";
	

}


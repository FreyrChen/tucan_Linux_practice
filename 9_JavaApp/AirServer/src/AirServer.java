import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;


public class AirServer 
{
	public static void main(String[] args) throws Exception 
	{
		HttpImage test = new HttpImage();
		test.getImage();
	}
	
	
	
	
}


class HttpImage
{
	public HttpImage()
	{
		;
	}
	
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
	
	public void getImage() throws Exception
	{
		//��Ҫ���ص�ͼƬ��ַ
		String ImagePath = "http://imgsrc.baidu.com/forum/pic/item/7318deaa8992a8730ff4778e.jpg";
		URL url = new URL(ImagePath);
		//�½�HTTP���Ӷ���
		HttpURLConnection connection = (HttpURLConnection ) url.openConnection();
		System.out.println("URL:" + url.toString());
		connection.setReadTimeout(6*1000);
		connection.setRequestMethod("GET");
		System.out.println("response code:"+ connection.getResponseCode());
		//�ж���վ���ӵĳɹ�Ŷ�������
		if( connection.getResponseCode() == 200 )
		{
			System.out.println("http connection response success!");
			//�½�������
			InputStream input_stream = connection.getInputStream();
			byte[] data = readStream(input_stream );
			//��ͼƬ���ڱ����ļ���
			File file = new File("haha.jpg"); 
			//�����ܵ�����д���ļ�������
			FileOutputStream output_stream = new FileOutputStream( file); 
			output_stream.write( data );
			output_stream.close();
			
		}
	}
	
}




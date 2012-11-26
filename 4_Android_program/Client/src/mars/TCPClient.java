package mars;

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.Socket;

public class TCPClient {
	public static void main(String[] args) {
		try {
			//创建一个Socket对象，指定服务器端的IP地址和端口号
			Socket socket = new Socket("192.168.2.109",4567);
			//使用InputStream读取硬盘上的文件
			InputStream inputStream = new FileInputStream("c://words.txt");
			//从Socket当中得到OutputStream
			OutputStream outputStream = socket.getOutputStream();
			byte buffer [] = new byte[4*1024];
			int temp = 0 ;
			//将InputStream当中的数据取出，并写入到OutputStream当中
			while((temp = inputStream.read(buffer)) != -1){
				outputStream.write(buffer, 0, temp);
			}
			outputStream.flush();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

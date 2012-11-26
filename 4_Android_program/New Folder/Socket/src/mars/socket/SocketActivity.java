package mars.socket;

import java.io.IOException;
import java.io.InputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class SocketActivity extends Activity {
    /** Called when the activity is first created. */
	private Button startButton = null;
	private TextView textview =null;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        startButton = (Button)findViewById(R.id.startListener);
        startButton.setOnClickListener(new StartSocketListener());
        
        textview =(TextView)findViewById(R.id.textview);
        Log.e("mydebug","start creat..");
    }
    
    class StartSocketListener implements OnClickListener{

		public void onClick(View v) {
			new ServerThread().start();
		}
    	
    }
    
    class ServerThread extends Thread{
    /*	
    	public void run(){
    		//����һ��ServerSocket����
    		ServerSocket serverSocket = null;
    		try {
    			//����һ��ServerSocket���󣬲������Socket��4567�˿ڼ���
				serverSocket = new ServerSocket(4567);
				//����ServerSocket��accept()���������ܿͻ��������͵�����
				Socket socket = serverSocket.accept();
				//��Socket���еõ�InputStream����
				InputStream inputStream = socket.getInputStream();
				byte buffer [] = new byte[1024*4];
				int temp = 0;
				//��InputStream���ж�ȡ�ͻ��������͵�����
				while((temp = inputStream.read(buffer)) != -1){
					//System.out.println(new String(buffer,0,temp));
					Log.e("mydebug",new String(buffer,0,temp));
					//textview.setText("OK!!!!!!!!");
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			finally{
				try {
					serverSocket.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		
    	}
    	
    	*/
    	public void run(){
    		/*try {
    			//����һ��DatagramSocket���󣬲�ָ�������Ķ˿ں�
				DatagramSocket socket = new DatagramSocket(4567);
				byte data [] = new byte[1024];
				//����һ���յ�DatagramPacket����
				DatagramPacket packet = new DatagramPacket(data,data.length);
				//ʹ��receive�������տͻ��������͵�����
				socket.receive(packet);
				String result = new String(packet.getData(),packet.getOffset(),packet.getLength());
				System.out.println("result--->" + result);
		        textview.setText("received "+result);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/
    		
    		try {
			//���ȴ���һ��DatagramSocket����
			DatagramSocket socket = new DatagramSocket(4567);
			//����һ��InetAddree
			InetAddress serverAddress = InetAddress.getByName("192.168.1.2");
			String str = "131321";
			byte data [] = str.getBytes();
			//����һ��DatagramPacket���󣬲�ָ��Ҫ��������ݰ����͵����統�е��ĸ���ַ���Լ��˿ں�
			DatagramPacket packet = new DatagramPacket(data,data.length,serverAddress,4567);
			//����socket�����send��������������
			socket.send(packet);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	}
    	
    }
}
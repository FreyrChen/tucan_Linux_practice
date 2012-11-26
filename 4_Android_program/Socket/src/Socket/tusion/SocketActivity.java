package Socket.tusion;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class SocketActivity extends Activity {
    /** Called when the activity is first created. */
	
	private Button startsocketbutton = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        startsocketbutton = (Button) findViewById(R.id.startsocketbutton);
        startsocketbutton.setOnClickListener(new StartSocketButtonListener());
    }
    
    class StartSocketButtonListener implements OnClickListener{

		public void onClick(View arg0) {
			// TODO Auto-generated method stub
			//new ServerThread().start();
			System.out.println("onclick-----------> is good");
			ServerSocket serversocket = null;
    		try{
    			serversocket = new ServerSocket(4567);
    			Socket socket = serversocket.accept();
    			InputStream inputstream = socket.getInputStream();
    			byte buffer[] = new byte[1024*4];
    			int temp = 0;
    			while(( temp = inputstream.read(buffer)) !=  -1){
    				System.out.println(new String(buffer,0,temp));
    			}
    		}
    		catch(IOException e){
				e.printStackTrace();
			}
			finally{
				try{
					serversocket.close();
				}
				catch(IOException e){
					e.printStackTrace();
				}
			}
			
			
		}
    }
    /*
    class ServerThread extends Thread{
    	public void run(){
    		ServerSocket serversocket = null;
    		try{
    			serversocket = new ServerSocket(4567);
    			Socket socket = serversocket.accept();
    			InputStream inputstream = socket.getInputStream();
    			byte buffer[] = new byte[1024*4];
    			int temp = 0;
    			while(( temp = inputstream.read(buffer)) !=  -1){
    				System.out.println(new String(buffer,0,temp));
    			}
    		}
    		catch(IOException e){
				e.printStackTrace();
			}
			finally{
				try{
					serversocket.close();
				}
				catch(IOException e){
					e.printStackTrace();
				}
			}
    	}
    }*/
}

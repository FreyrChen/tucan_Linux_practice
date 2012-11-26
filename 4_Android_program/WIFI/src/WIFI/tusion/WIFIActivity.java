package WIFI.tusion;

import android.app.Activity;
import android.content.Context;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class WIFIActivity extends Activity {
    /** Called when the activity is first created. */
	private Button startwifibutton = null;
	private Button stopwifibutton = null;
	private Button checkwifibutton = null;
	private WifiManager wifimanager = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        startwifibutton = (Button) findViewById(R.id.startwifibutton);
        stopwifibutton =  (Button) findViewById(R.id.stopwifibutton);
        checkwifibutton = (Button) findViewById(R.id.checkwifibutton);  
        
        startwifibutton.setOnClickListener( new SrartWifiListener());
        stopwifibutton.setOnClickListener( new StopWifiListener());
        checkwifibutton.setOnClickListener( new CheckWifiListener());
       
        
    }
    class SrartWifiListener implements OnClickListener{

		public void onClick(View arg0) {
			wifimanager = (WifiManager)WIFIActivity.this.getSystemService(Context.WIFI_SERVICE);
			wifimanager.setWifiEnabled(true);
			System.out.println("wifi state ----->"+wifimanager.getWifiState());
			//System.out.println("wifi state ----->");
			Toast.makeText(WIFIActivity.this, "当前WIFI状态"+wifimanager.getWifiState(), Toast.LENGTH_SHORT).show();
		}
			// TODO Auto-generated method stub		
		}
    class StopWifiListener implements OnClickListener{

		public void onClick(View arg0) {
			wifimanager = (WifiManager)WIFIActivity.this.getSystemService(Context.WIFI_SERVICE);
			wifimanager.setWifiEnabled(false);
			System.out.println("wifi state ----->"+wifimanager.getWifiState());
			Toast.makeText(WIFIActivity.this, "当前WIFI状态"+wifimanager.getWifiState(),  Toast.LENGTH_SHORT).show();
		}
			// TODO Auto-generated method stub		
		}
    class CheckWifiListener implements OnClickListener{

		public void onClick(View arg0) {
			wifimanager = (WifiManager)WIFIActivity.this.getSystemService(Context.WIFI_SERVICE);
			System.out.println("wifi state ----->"+wifimanager.getWifiState());
			Toast.makeText(WIFIActivity.this, "当前WIFI状态"+wifimanager.getWifiState(),  Toast.LENGTH_SHORT).show();
		}
			// TODO Auto-generated method stub		
		}
    
    
}
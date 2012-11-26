package tusion_activity.test;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.widget.Button;
/*
 * edit by tusion
 * 20110926
 */
public class Activity01 extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
      TextView myTextView =(TextView )(  findViewById(R.id.myTextView) );
      Button myButton = (Button) ( findViewById(R.id.myButton) );
      myTextView.setText("我的第一个TextView");
      myButton.setText("我的第一个Button"+"\n"+"wo");
      
    		  
    }
}
package Activity_02.tusion;

import android.app.Activity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;



public class Activity_02Activity extends Activity {
    /** Called when the activity is first created. */
	private Button myButton = null;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        myButton = (Button)findViewById(R.id.myButton);
        myButton.setOnClickListener( new MyButtonListener()); 
    }
    
    class MyButtonListener implements OnClickListener{
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Intent intent = new Intent();
			intent.setClass(Activity_02Activity.this, Oter_Activity.class);
			Activity_02Activity.this.startActivity(intent);
		}
     
    }

}
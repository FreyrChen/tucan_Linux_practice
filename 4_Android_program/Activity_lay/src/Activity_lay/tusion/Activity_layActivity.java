package Activity_lay.tusion;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class Activity_layActivity extends Activity {
    

	/** Called when the activity is first created. */
	
	private TextView textview = null;
	private Button startbutton = null;
	private Button endbutton = null;
	
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        System.out.println("First Activity ---> onCreate...");
        textview = (TextView)findViewById(R.id.TextView);
        textview.setText("No activity is oprate!!");
       
        startbutton = (Button)findViewById(R.id.StartButton);
        startbutton.setOnClickListener( new StartButtonListener());
       // endbutton = (Button)findViewById(R.id.EndButton);
       // endbutton.setOnClickListener( new EndButtonListener());
        
    }
    
    class StartButtonListener implements OnClickListener{

		public void onClick(View arg0) {
			// TODO Auto-generated method stub
			//textview.setText("Clcik on the Button 1 !!");
			//System.out.println("First Activity ---> pressed Button 1");
			Intent intent = new Intent();
			intent.putExtra("testintent", "123");
			intent.setClass( Activity_layActivity.this, other_Activity.class);
			Activity_layActivity.this.startActivity(intent);
		}
	}
	
	class EndButtonListener implements OnClickListener{

		public void onClick(View arg0) {
			// TODO Auto-generated method stub
			textview.setText("Clcik on the Button 2 !!");
			System.out.println("First Activity ---> pressed Button 2");
		}
		
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		System.out.println("[First Activity ]: onDestroy ...");
		super.onDestroy();
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		System.out.println("[First Activity ]: onPause ...");
		super.onPause();
	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		System.out.println("[First Activity ]: onRestart ...");
		super.onRestart();
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		System.out.println("[First Activity ]: onResume ...");
	
		super.onResume();
	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		System.out.println("[First Activity ]: onStart ...");
		super.onStart();
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		System.out.println("[First Activity ]: onStop ...");
		super.onStop();
	}
    
}





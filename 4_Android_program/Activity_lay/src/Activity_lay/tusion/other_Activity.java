package Activity_lay.tusion;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class other_Activity extends Activity{

	private Button backbutton = null;
	private TextView secondtextview = null;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		 setContentView(R.layout.other);
		 
		Intent intent = getIntent();
		String value = intent.getStringExtra("testintent");
		secondtextview = (TextView)findViewById(R.id.SecondTextView);
        //textview.setText("No activity is oprate!!");
		secondtextview.setText(value);
				
		backbutton = (Button)findViewById(R.id.myBackButton);
		backbutton.setOnClickListener( new BackButtonListener());

	}
	
    class BackButtonListener implements OnClickListener{

		public void onClick(View arg0) {
			// TODO Auto-generated method stub
			//System.out.println("First Activity ---> pressed Button 1");
			/*
			Intent intent = new Intent();
			intent.setClass( other_Activity.this, Activity_layActivity.class);
			other_Activity.this.startActivity(intent);
			*/
			
			Uri uri= Uri.parse("smsto://800");
			Intent intent = new Intent(Intent.ACTION_SENDTO,uri);
			intent.putExtra("sms_body", "the sms text in out");
			startActivity(intent);
		}
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		System.out.println("[Second Activity ]: onDestroy ...");
		super.onDestroy();
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		System.out.println("[Second Activity ]: onPause ...");
		super.onPause();
	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		System.out.println("[Second Activity ]: onRestart ...");
		super.onRestart();
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		System.out.println("[Second Activity ]: onResume ...");
	
		super.onResume();
	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		System.out.println("[Second Activity ]: onStart ...");
		super.onStart();
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		System.out.println("[Second Activity ]: onStop ...");
		super.onStop();
	}

}

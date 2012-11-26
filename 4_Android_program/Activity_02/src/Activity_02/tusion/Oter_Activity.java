package Activity_02.tusion;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class Oter_Activity extends Activity {
	
	private TextView myTextView = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.other);
		myTextView = (TextView) findViewById(R.id.myTextView); 
		myTextView.setText(R.string.display);
	}
	

}
 
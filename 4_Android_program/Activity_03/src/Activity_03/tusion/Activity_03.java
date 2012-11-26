package Activity_03.tusion;

import android.app.Activity;

import android.content.Intent;
import android.os.Bundle;

import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class Activity_03 extends Activity {
    /** Called when the activity is first created. */
	private EditText factorone;
	private EditText factortwo;
	private Button calculate;
	private TextView symbol;
	private TextView resultView;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        factorone = (EditText) findViewById(R.id.factorone);
        factortwo = (EditText) findViewById(R.id.factortwo);
        calculate = (Button) findViewById(R.id.calculate);
        symbol = (TextView) findViewById(R.id.symbol);  
        resultView = (TextView)findViewById(R.id.last);
        
        symbol.setText(R.string.symbol);
        calculate.setText(R.string.calculate);
        resultView.setText(R.string.calculate);

        calculate.setOnClickListener((android.view.View.OnClickListener) new CalculatorListener() );
    }
    
 
    class CalculatorListener implements  OnClickListener{

		public void onClick(View v) {
			// TODO Auto-generated method stub
			// get the two factors
			String factoroneStr = factorone.getText().toString();
			String factortwoStr = factortwo.getText().toString();
			int factoroneInt = Integer.parseInt(factoroneStr);
			int factortwoInt = Integer.parseInt(factortwoStr);
			int result = factoroneInt * factortwoInt;
			calculate.setText(result);
			//resultView.setText(result);	
			
		/*
			//get the value to the intent
			Intent intent = new Intent();
			intent.putExtra("one", factoroneStr);
			intent.putExtra("two", factortwoStr);
			intent.setClass(Activity_03.this, ResultActivity.class);
			Activity_03.this.startActivity(intent);
		*/
		}



    }
    
}
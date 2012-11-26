package TestSensor.tusion;

import java.util.List;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ScrollView;
import android.widget.TextView;

public class TestAllSensorsActivity extends Activity {

	TextView tx1 = null;
	ScrollView scrollview = null;
	SensorManager sm = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		 setContentView(R.layout.testallsensor);
		
		tx1= (TextView) findViewById(R.id.info);
		scrollview = (ScrollView) findViewById(R.id.infoscrollview);
		
		sm = (SensorManager) getSystemService(SENSOR_SERVICE);
	      //从传感器管理器中获得全部的传感器列表
		List<Sensor> allSensors = sm.getSensorList(Sensor.TYPE_ALL);
	
		//显示有多少个传感器
		tx1.setText("经检测该手机有" + allSensors.size() + "个传感器，他们分别是：\n");
	
		//显示每个传感器的具体信息
		for (Sensor s : allSensors) {
	
			String tempString = "\n" + "  设备名称：" + s.getName() + "\n" + "  设备版本：" + s.getVersion() + "\n" + "  供应商："
					+ s.getVendor() + "\n";
	
			switch (s.getType()) {
			case Sensor.TYPE_ACCELEROMETER:
				tx1.setText(tx1.getText().toString() + s.getType() + " 加速度传感器accelerometer" + tempString);
				break;
			case Sensor.TYPE_GYROSCOPE:
				tx1.setText(tx1.getText().toString() + s.getType() + " 陀螺仪传感器gyroscope" + tempString);
				break;
			case Sensor.TYPE_LIGHT:
				tx1.setText(tx1.getText().toString() + s.getType() + " 环境光线传感器light" + tempString);
				break;
			case Sensor.TYPE_MAGNETIC_FIELD:
				tx1.setText(tx1.getText().toString() + s.getType() + " 电磁场传感器magnetic field" + tempString);
				break;
			case Sensor.TYPE_ORIENTATION:
				tx1.setText(tx1.getText().toString() + s.getType() + " 方向传感器orientation" + tempString);
				break;
			case Sensor.TYPE_PRESSURE:
				tx1.setText(tx1.getText().toString() + s.getType() + " 压力传感器pressure" + tempString);
				break;
			case Sensor.TYPE_PROXIMITY:
				tx1.setText(tx1.getText().toString() + s.getType() + " 距离传感器proximity" + tempString);
				break;
			case Sensor.TYPE_TEMPERATURE:
				tx1.setText(tx1.getText().toString() + s.getType() + " 温度传感器temperature" + tempString);
				break;
			default:
				tx1.setText(tx1.getText().toString() + s.getType() + " 未知传感器" + tempString);
				break;
			}
		}
		//scrollview.addView(tx1);
		//setContentView(scrollview);
		
	}

}

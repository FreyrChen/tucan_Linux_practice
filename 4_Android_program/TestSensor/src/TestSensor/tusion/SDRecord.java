package TestSensor.tusion;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.os.Environment;


public class SDRecord {

	private String SDPath = Environment.getExternalStorageDirectory() +"/SensorRecordData/";
	
	//��SD������Ŀ¼
	 public File creatSDDir( String DirName){
		 File dir = new File( SDPath + DirName);
		 if(!dir.exists()){
			 try{
				 // mkdirs() ��ʾ�������Ҫ�����ȴ����ϲ�Ŀ¼.
				 dir.mkdirs();
			 }
			 catch(Exception e){
				 e.printStackTrace();
			 }
		 }
		 
		 return dir;
	 }
	 
	 //��SD�������ļ�
	 public File creatSDFile( String DirName) throws IOException{
		 File file = new File( SDPath + DirName);
		 if(!file.exists()){
			 try{
				 file.createNewFile();
			 }
			 catch(Exception e){
				 e.printStackTrace();
			 }
		 }
		
		 return file;
	 }
	 
	 public File WriteToSDCard(String Path, String FileName, InputStream data){
		 File file = null;
		 OutputStream output = null;
		 try{
			 creatSDDir(Path);
			 file = creatSDFile( Path + FileName);
			 output = new FileOutputStream( file);
			 
			 byte buffer[]= new byte[4*1024];
			 while((data.read(buffer) != -1)){
				 output.write(buffer);
			 }
			 output.flush(); 
		 }
		 catch(Exception e){
			 e.printStackTrace();
		 }
		 finally{
			 try{
				 output.close();
			 }
			 catch(Exception e){
				 e.printStackTrace();
			 }
		 }
		return file;
	 }

}
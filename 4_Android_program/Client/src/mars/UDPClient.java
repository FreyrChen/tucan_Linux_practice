package mars;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPClient {
	public static void main(String[] args) {
		
		try {
		//创建一个DatagramSocket对象，并指定监听的端口号
		DatagramSocket socket = new DatagramSocket(4567);
		byte data [] = new byte[1024];
		//创建一个空的DatagramPacket对象
		DatagramPacket packet = new DatagramPacket(data,data.length);
		//使用receive方法接收客户端所发送的数据
		socket.receive(packet);
		String result = new String(packet.getData(),packet.getOffset(),packet.getLength());
		System.out.println("result--->" + result);
        //textview.setText("received "+result);
	} catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
		
		/*try {
			//首先创建一个DatagramSocket对象
			DatagramSocket socket = new DatagramSocket(4567);
			//创建一个InetAddree
			InetAddress serverAddress = InetAddress.getByName("192.168.2.109");
			String str = "131321";
			byte data [] = str.getBytes();
			//创建一个DatagramPacket对象，并指定要讲这个数据包发送到网络当中的哪个地址，以及端口号
			DatagramPacket packet = new DatagramPacket(data,data.length,serverAddress,4567);
			//调用socket对象的send方法，发送数据
			socket.send(packet);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
	}
}

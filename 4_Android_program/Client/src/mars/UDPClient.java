package mars;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPClient {
	public static void main(String[] args) {
		
		try {
		//����һ��DatagramSocket���󣬲�ָ�������Ķ˿ں�
		DatagramSocket socket = new DatagramSocket(4567);
		byte data [] = new byte[1024];
		//����һ���յ�DatagramPacket����
		DatagramPacket packet = new DatagramPacket(data,data.length);
		//ʹ��receive�������տͻ��������͵�����
		socket.receive(packet);
		String result = new String(packet.getData(),packet.getOffset(),packet.getLength());
		System.out.println("result--->" + result);
        //textview.setText("received "+result);
	} catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
		
		/*try {
			//���ȴ���һ��DatagramSocket����
			DatagramSocket socket = new DatagramSocket(4567);
			//����һ��InetAddree
			InetAddress serverAddress = InetAddress.getByName("192.168.2.109");
			String str = "131321";
			byte data [] = str.getBytes();
			//����һ��DatagramPacket���󣬲�ָ��Ҫ��������ݰ����͵����統�е��ĸ���ַ���Լ��˿ں�
			DatagramPacket packet = new DatagramPacket(data,data.length,serverAddress,4567);
			//����socket�����send��������������
			socket.send(packet);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
	}
}

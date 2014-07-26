//for TCP connection
var net = require('net');
//for log file
var fs  = require('fs');
// for timestamp
var moment = require('moment');

var HOST = '';
//var HOST = '127.0.0.1';
var PORT = 6000;
var total_num = 0;	//total mesg number
var commander_num = 0;
var set_num = 0;
var qurey_num = 0;
var data_num = 0;
var log_data = '';
var TIME_FORMAT = 'YYYY-MM-DD_HH:mm:ss:SSS';
var LOG_FORMAT ='YYYYMMDD_HHmmss';
//var LOG_PATH = 'log_'  + '.txt';
var LOG_PATH = 'server_log_' + moment().format( LOG_FORMAT ) + '.txt';
var logWriteStream = fs.createWriteStream( LOG_PATH );

var current_client_socket = {} ; //is a object
var ConnectionInfoTable=[];
//var DeviceInfoTable = [];

// process thread OBD device data from TCP connection
// NETWORK DATA FORMAT:
// 1.from gps client node:
// 	Data, sequence_id, timestamp, client_IP:PORT, data mesg
// 	Connected, ......
// 2.from commander server.
// 	Commander, SET, timestamp, client_IP:PORT, commander_data
// 	Commander, QUERY, timestamp, client_IP:PORT, commander_data
function processThreadOBDData( data_str, socket){
	//process reveived data
	var data_array = data_str.split(",");
	switch(data_array[0].trim()){
	case 'Commander':	// if mesg is commander to setting device
		commander_num += 1;
		//console.log( data_array[1] )
		if( data_array[1].trim() == "SET" ){
			//send commader to device
			set_num += 1;
			log_data = data_str;
			console.log( data_str );
			logWriteStream.write( log_data + "\n" );	
		}else if( data_array[1].trim() == "QUERY" ){
			//qurey device's socket.
			console.log("to qurey");
		}else{
			console.log("commander error!");
		}
		
		break;
	case 'Test':
		break;
	case '$EST627':		// Thread OBD device data string
		data_num += 1;
		console.log("in data process, socket type is: " + typeof( socket ));
		log_data = 'Data, ' + data_num +', '+ moment().format( TIME_FORMAT) + ', ' + socket.remoteAddress + ':' + socket.remotePort + ', '+ data_str;
		console.log( log_data ); 
		logWriteStream.write( log_data + "\n" );

		//Server echo data to client.
		socket.write(  data_str  );
		var device_id = data_array[1];
		console.log( "device_id: " + device_id + ", add deviece in info table" );
		var list_num = addOnlineUser(  device_id );
			if( data_array[2].trim() == "01" )
			{
				ConnectionInfoTable[list_num].socket_id = socket;
				ConnectionInfoTable[list_num].name = data_array[0].trim();
				ConnectionInfoTable[list_num].msg_num = data_array[4].trim() ;
				ConnectionInfoTable[list_num].last_time = data_array[5].trim();
				
			}
				
		break;
	default:	//other is data
		log_data = 'Unknown, ' + moment().format( TIME_FORMAT ) + ', ' + data_str;
		console.log( log_data );
		logWriteStream.write( log_data + '\n' );
		 
	}
}

/*
 *
*/


/*
var ConnectInfoJSON={ server:{ ip:"114.215.238.215", port:"6000", },
			commander:[ {ip:"0.0.0.o", port:"1234"} ],
			device:[ {
					id: "000000",
					name: "Thread_OBD",
					ip:"111.111.11.1",
					port:"8888",
					msg_num:"0",
					last_time:"2014-01-01-23-11-45"
				}
				]
			}		
*/


function Device( id, is_online, socket, name, ip, port, msg_num, last_time){
	this.id = id;		 //	device_id: "000000";
	this.is_online = is_online;	//boolen, device is or not online
	this.socket = socket;	// js socket handler.
	this.name = name;	//	device_name: "Thread_OBD";
	this.ip = ip; 		//	device_IP:"111.111.11.1";
	this.prot = port;	//	device_socket:8888;
	this.msg_num = msg_num;	//	send_msg_num:0;
	this.last_time = last_time; //	last_online_time:"2014-01-01-23-11-45"
}
	


function deleteOnlineUser( SocketID ){
	for( var i=0; i<ConnectionInfoTable.length; i++ )
	{
		if( ConnectionInfoTable[i].socket_id == Socket_ID )
		{
			ConnectionInfoTable[i].is_online = 0;
			return i;
		}
	}	
}


function addOnlineUser( device_id ){	
	//var device_str = device.toJSONString();
	for( var i=0; i<ConnectionInfoTable.nh; i++ )
	{
		if( ConnectionInfoTable[i].device_id == device_id )
		{
			ConnectionInfoTable[i].is_online = 1;
			return i;
		}
	}	

	var device = new Device( device_id, {},"0","Null", "Thread_OBD", "111.111.11.1", "6200", "1", "2014-01-02-22-10-34");
	//array push is to add elements to the tail, and return new array's length.
	var num_of_devices = ConnectionInfoTable.push( device );
	return num_of_devices;
}

function queryOnlineUser( device_id ){
	var total_devices = ConnectInfoTable.length;
	var device_seq_id = 0;
	for( vari=0; i<total_devices; i++)
	{
		if( device_id == ConnectionInfoTable.device[i].id )
		{
			device_seq_id = device_id;
			var SocketID = ConnectionInfoTable.device[ device_seq_id ].socket_id;
			return SocketID;
		}
	}
	return Null;
}


var server = net.createServer( );

server.on('connection', function(sock) {
	//disable Nagle, send vevry small packet ASAP
	sock.setNoDelay( true );
	sock.setKeepAlive( true );
	current_client_socket = sock;
	//server establihed welcome message
	log_data ='Connected, ' + moment().format(TIME_FORMAT)  + 
		', ' +  sock.remoteAddress + ':' + sock.remotePort ; 
	console.log( log_data );
	logWriteStream.write( log_data + "\n");

	//add a name to object 'sock'
	sock.name = sock.remoteAddress + ":" + sock.remotePort;
	//sock.id = 
	sock.write("Hi, " + sock.name + "!\n");
	ConnctionInfoTable.push( sock );

	//received client send data
	sock.on('data', function(data){
		//console.log("data received, type of sock is: " + typeof( sock) );
		//sock type is a object.
//		processThreadOBDData( data.toString(), sock );
			
		broadCast( data, sock); //received client message, send to other clients.

		total_num += 1;
	});
	
	//client connect socket colesd.
	sock.on('close', function(data) {
		//deleteOnlineUser( SocketID );
		console.log('CLOSE: ' + sock.remoteAddress + ':' + sock.remotePort);
	
	});
	
	sock.on('error', function( err ){
		//deleteOnlineUser( SocketID );
	});
	
	
	sock.on('end', function(){
		//when client colsed connection, then remove socket in array.
		//client is not must close the connection
		ConnectionInfoTable.splice( ConnectionInfoTable.indexOf( sock ), 1);
	});
		
	//sock.end(); //end this connection.

});


server.listen( PORT, function(){
	//server listerner
	log_data = 'Server, ' + moment().format( TIME_FORMAT) + ', ' + HOST + ':' + PORT;
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );

});


function boradCast( message, socket)
{
	for (var i=0; i<ConnectionInfoTable.length; i++ )
	{
		if( socket != ConnectionInfoTable[i])
		{
			if( ConnectionInfoTable[i].writeable )
			{
				ConnectionInfoTable[i].write( "["+ConnectionInfoTable.length +"-"+i+
								"] "+ socket.name + ": " + message );
			}else{
				ConnectionNotOnlineTable[i].push( ConnectionInfoTable[i] );
			}
		}
	}
	for( var i=0; i<ConnectionNotOnlineTable.length; i++ ){
		ConnectionInfoTable[i].destroy();
		ConnectionInfoTable.splice( ConnectionInfoTable.indexOf( ConnectionNotOnlineTable[i]), 1 );
	}	
}

//logWriteStream.end();

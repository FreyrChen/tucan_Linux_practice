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
	default:	//other is data
		data_num += 1;
		log_data = 'Data, ' + data_num +', '+ moment().format( TIME_FORMAT) + ', ' + socket.remoteAddress + ':' + socket.remotePort + ', '+ data_str;
		console.log( log_data ); 
		logWriteStream.write( log_data + "\n" );

		//Server echo data to client.
		socket.write(  data_str  );
	}
}

/*
 *
*/

var ConnectInfoTable={ server:{ ip:"114.215.238.215", port:"6000", },
			commander:[ {ip:"0.0.0.o", port:"1234"} ],
			device:[ {
					device_id: "000000",
					device_name: "Thread_OBD",
					device_IP:"111.111.11.1",
					device_socket:"8888",
					send_msg_num:"0",
					last_online_time:"2014-01-01-23-11-45"
				}
				]
			}		
var client ={
	device_id: "000000";
	device_name: "Thread_OBD";
	device_IP:"111.111.11.1";
	device_socket:8888;
	send_msg_num:0;
	last_online_time:"2014-01-01-23-11-45"
};
	


function deleteOnlineUser( SocketID ){
}

function addOnlineUser( SocketID ){
	
}

function queryOnlineUser( DeviceID ){
	
	return SocketID;
}


var server = net.createServer( function(sock) {
	//disable Nagle, send vevry small packet ASAP
	sock.setNoDelay( true );
	sock.setKeepAlive( true );

	//server establihed welcome message
	log_data ='Connected, ' + moment().format(TIME_FORMAT)  +', ' +  sock.remoteAddress + ':' + sock.remotePort ; 
	console.log( log_data );
	logWriteStream.write( log_data + "\n");

		
	//new client connected
	sock.on('data', function(data){
		processThreadOBDData( data.toString(), sock );
		total_num += 1;
	});
	
	//client connect socket colesd.
	sock.on('close', function(data) {
		deleteOnlineUser( SocketID );
		console.log('CLOSE: ' + sock.remoteAddress + ':' + sock.remotePort);
	
	});
	
	sock.on('error', function( err ){
		deleteOnlineUser( SocketID );
	});

});


server.listen( PORT, function(){
	//server listerner
	log_data = 'Server, ' + moment().format( TIME_FORMAT) + ', ' + HOST + ':' + PORT;
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );

});

//logWriteStream.end();

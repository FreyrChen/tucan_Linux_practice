var net = require('net');
var fs = require('fs');
var moment = require('moment');
var util = require('util');

var SERVER_IP = '114.215.238.215';
var SERVER_PORT = 6000;
var count = 0;
var TIME_FORMAT = 'YYYY-MM-DD HH:mm:ss:SSS';
var LOG_FORMAT ='YYYYMMDD_HHmmss';


//var LOG_PATH = 'log_'  + '.txt';
var LOG_PATH = 'client_log_' + moment().format( LOG_FORMAT ) + '.txt';
var logWriteStream = fs.createWriteStream( LOG_PATH );


//wait for user input conmmander
function readCommander(){
	stdin.pause();
	console.log("");
		
	stdout.write("Eenter your commander:");
	var input_data = fs.readSync( stdin.fd, 1000, 0, "utf8");
	stdin.resume();
	var commander = input_data[0].trim();
	return commander;
}

var Commander_client = new net.Socket();

Commander_client.connect( SERVER_PORT, SERVER_IP, function(){
	/*
	log_data = 'connect to server: ' + SERVER_IP + ':' + SERVER_PORT;
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );
	//log_data = 'Commander, SET, ' + moment().format(TIME_FORMAT) + ', '  +
	//			'192.168.0.1:2222' +',  AT+SRGPS';	

	log_data = 'Commander,   QUERY , ' + moment().format(TIME_FORMAT) + ', '  +
				'192.168.0.1:2222' +',  AT+SRGPS';
	// send message to server throgh TCP
	Commander_client.write( log_data );
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );
	*/

	console.log("input message:\n");
});


Commander_client.on('data', function(data){
//	log_data = 'Data, ' + moment().format(TIME_FORMAT) + ', ' + data ;
	log_data = data + "";
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );
	
});


Commander_client.on('close', function(){
	console.log('Connection closed');
	process.exit();
});

process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('data', function( commander ){
	//console.log('Input commander:', util.inspect( commander ) );
	if( commander.trim() == 'exit' ){
		console.log('process exit. Bye!');
		Commander_client.destroy();
		process.exit();
	}else{
	//	log_data = 'Commander, SET, ' + moment().format(TIME_FORMAT) + ', '  + 
	//				'192.168.0.1:2222' + ', ' + commander;
		log_data = commander;
		Commander_client.write( log_data );
	//	console.log( log_data );
		logWriteStream.write( log_data + "\n" );

	}

});

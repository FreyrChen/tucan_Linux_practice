var net = require('net');
var fs = require('fs');
var moment = require('moment');

var SERVER_IP = '114.215.238.215';
var SERVER_PORT = 6000;
var count = 0;
var TIME_FORMAT = 'YYYY-MM-DD HH:mm:ss:SSS';
var LOG_FORMAT ='YYYYMMDD_HHmmss';


//var LOG_PATH = 'log_'  + '.txt';
var LOG_PATH = 'client_log_' + moment().format( LOG_FORMAT ) + '.txt';
var logWriteStream = fs.createWriteStream( LOG_PATH );


var Commander_client = new net.Socket();
Commander_client.connect( SERVER_PORT, SERVER_IP, function(){
	log_data = 'connect to server: ' + SERVER_IP + ':' + SERVER_PORT;
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );
	//log_data = 'Commander, SET, ' + moment().format(TIME_FORMAT) + ', '  + '192.168.0.1:2222' +',  AT+SRGPS';

	log_data = 'Commander,   QUERY , ' + moment().format(TIME_FORMAT) + ', '  + '192.168.0.1:2222' +',  AT+SRGPS';
	Commander_client.write( log_data );
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );
});

Commander_client.on('data', function(data){
	log_data = 'Data, ' + moment().format(TIME_FORMAT) + ', ' + data ;
	console.log( log_data );
	logWriteStream.write( log_data + "\n" );
	
});


Commander_client.on('close', function(){
	console.log('Connection closed');
});


//Commander_client.destroy();

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//imposto nome e password della rete a cui devo collegarmi
const char *nome_rete = "xxxxxxxxxxxx"; // Substitute X with your SSID
const char *password_rete = "xxxxxxxxxx"; // Substitute X with your wi-fi password

String ip_interfaccia;
 
// Set the http port on the module
ESP8266WebServer server (80);

// Module initializzation
void setup ( void ) {

  // Set the communication at 115200 of baudrate
  Serial.begin (115200);

  // Initialized the wi-fi connection
	WiFi.begin (nome_rete, password_rete);

  // Carriege return 
	Serial.println ("");

  // Waiting wi-fi connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay (500);
		Serial.print (".");
	}

  // Connection resume 
	Serial.println ( "" );
	Serial.print ("Connesso alla rete : ");
	Serial.println (nome_rete);
	Serial.print ("Pagina di controllo raggiungibile da : http://");
	Serial.println (WiFi.localIP());

  // Check connection complete 
	if (MDNS.begin ("esp8266")) {
	  Serial.println ("Modulo pronto!");
	}

  // Set the get commands for each function
  server.on("/", interfaccia);
	server.on("/uscita1", uscita1);
	server.on("/uscita2", uscita2);
  server.on("/uscita3", uscita3);
  server.on("/uscita4", uscita4);
  server.on("/uscita5", uscita5);


  // Start server 
	server.begin();

	Serial.println ("Server HTTP avviato!");
  
}


void loop ( void ) {
  // Keep the server waiting 
	server.handleClient();
}

void interfaccia() {
    // Web interface 
    server.send(200, "text/html", "<!DOCTYPE html><html><head><title>ESP8266 REMOTE WI-FI INTERFACE</title><style type='text/css'>#id1 {position: absolute;top: 200px; left: 720px;width: 100px; height: 100px;color:#00f; border-radius:10px; font-family:Courier; font-size:50px; padding:4px; font-weight:bold;}#id2{position: absolute;top: 400px; left: 720px;width: 100px; height: 100px;color:#00f; border-radius:10px; font-family:Courier; font-size:50px; padding:4px; font-weight:bold;}#id3{position: absolute;top: 300px; left: 720px;width: 100px; height: 100px;color:white; background-color:red; border-radius:10px; font-family:Courier; font-size:35px; padding:4px; font-weight:bold;}#id4{position: absolute;top: 300px; left: 820px;width: 100px; height: 100px;color:#00f; border-radius:10px; font-family:Courier; font-size:50px; padding:4px; font-weight:bold;}#id5{position: absolute;top: 300px; left: 620px; width: 100px; height: 100px;color:#00f; border-radius:10px; font-family:Courier; font-size:50px; padding:4px; font-weight:bold;}</style></head><body><H1 align=center>ESP8266 REMOTE WI-FI INTERFACE</h1><H3 align=center>BY</h3><H2 align=center>__THELASTENGINEER__</h2><button id = 'id1' onclick='location.href=&#39;/uscita1&#39;'>GH</button><br /><br /><button id = 'id2' onclick='location.href=&#39;/uscita2&#39;'>GB</button><br /><br /><button id = 'id3' onclick='location.href=&#39;/uscita3&#39;'>STOP</button><br /><br /><button id = 'id4' onclick='location.href=&#39;/uscita4&#39;'>TR</button><br /><br /><button id = 'id5' onclick='location.href=&#39;/uscita5&#39;'>TL</button><br /><br /></body></html>");
} 
  
void uscita1() {
  //AVANTI
Serial.println('1');
  interfaccia();
}
void uscita2() {
  //INDIETRO
Serial.println('2');
  interfaccia();
}
void uscita3() {
  //STOP
Serial.println('3');
  interfaccia();
}
void uscita4() {
  //RUOTA DX
Serial.println('4');
  interfaccia();
}
void uscita5() {
  //richiama uscita 5
Serial.println('5');
  interfaccia();
}



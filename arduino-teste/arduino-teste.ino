/*--------------------------------------------------------------
  Program:      eth_websrv_page

  Description:  Arduino web server that serves up a basic web
                page. Does not use the SD card.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                
  Software:     Developed using Arduino 1.0.3 software
                Should be compatible with Arduino 1.0 +
  
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet

  Date:         7 January 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 77); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
String readstring="";
//int teste =2 ;
void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();  // start to listen for clients
   Serial.begin(9600);
}

void loop()
{
    
    EthernetClient client = server.available();  // try to get client
    if (client) {  // got client?
        //boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {// client data available to read              
              
                char c = client.read(); // read 1 byte (character) from client
                //Serial.write (c);
                readstring += c;
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' ) {
                  //Serial.print(c);
                  Serial.print(readstring+"\n");                                  

                  if(readstring=="G#\n"){
                    Serial.print("GLS11#\n");
                    client.println("GLS11#");
                    
                    readstring=""; 
                  }
                  else if(readstring=="G\n"){
                    Serial.print("segundo envio ok");
                    client.println("segundo envio ok");
                  }
                }//fim if
            } // end if (client.available())
        } // end while (client.connected())
        
        delay(1);      // give the web browser time to receive the data
        client.stop();
        // close the connection
    } // end if (client)
    
    
}

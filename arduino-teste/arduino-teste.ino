#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 171); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80


void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();  // start to listen for clients
    Serial.begin(9600);
}

void loop()
{    
    EthernetClient client = server.available();  // try to get client
    char c;
    c=' ';
    String readstring;
    readstring="";
    if (client) { 
      while (client.connected()) {
        if (client.available()) {          
          c = client.read(); // read 1 byte (character) from client
          readstring += c;                        
          //Serial.print(readstring+"\n");
          if (c == '#' ) {
            //Serial.print(readstring+"\n");     
            if(readstring=="G#"){
              //Serial.print("GLS11#\n");
              String auxiliar;
              auxiliar = "GLS11#";
              client.print(auxiliar);  
              auxiliar = "";                  
              readstring=""; 
              
            }c=' ';
          }
        } // end if (client.available())
      } // end while (client.connected())
        
        delay(1);      // give the web browser time to receive the data
        client.stop();
        // close the connection
    } // end if (client)
    
    
}

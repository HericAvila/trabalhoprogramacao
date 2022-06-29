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
    int quant_leituras,valor_atuacao;    
    String readstring,valor_atuacao_vet;
    c=' ';
    quant_leituras=0; 
    valor_atuacao=0;      
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
              Serial.print("GLS11#\n");
              String auxiliar;
              auxiliar = "GLS11#";
              client.print(auxiliar);  
              auxiliar = "";                  
              readstring="";               
            }
            else if(readstring[0]=='L'){
              if(readstring[1]=='0'){        
                quant_leituras=(readstring[4]-'0');
                
                if(0<quant_leituras<5){
                  Serial.print(quant_leituras);
                  client.print(quant_leituras);                  
                }
                else{
                  Serial.print("Entrada não é valida, digite um valor até 4 repeticoes;");
                  client.print("Entrada não é valida, digite um valor até 4 repeticoes;"); 
                }
                
              }
              else if(readstring[1]=='1'){
                
                valor_atuacao_vet+=readstring[2];
                valor_atuacao_vet+=readstring[3];
                valor_atuacao_vet+=readstring[4]; 
                
                             
                Serial.print(valor_atuacao_vet);
                char str[10]="122" ;
                strcpy (str ,valor_atuacao_vet.c_str());
                int x = atoi(str);
                client.print(x); 
              }
            }
                              
            readstring="";
            c=' ';
          }
        } // end if (client.available())
      } // end while (client.connected())
        
        delay(1);      // give the web browser time to receive the data
        client.stop();
        // close the connection
    } // end if (client)
    
    
}

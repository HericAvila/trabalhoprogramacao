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
            else if(readstring[0]=='L'){ // se a msg esta no formato L0001# o "L" está na posição readstring[5], não?
              if(readstring[1]=='0'){        
                quant_leituras=(readstring[4]-'0');
                
                if(quant_leituras<5){  // e qtde leitura posição quant_leituras[1]?
                    //open_cleidson
                    int a=1;
                    //definir leituras, um bit por posição no vetor
                    string leitura_sensor, sensor_unidade, sensor_dezena, sensor_centena;
                    for (int i=0, i<quant_leituras), i++)
                    {
                        leitura_sensor[a+1]=sensor_unidade;
                        a=a+1;
                        leitura_sensor[a+1]=sensor_dezena;
                         a=a+1;
                        leitura_sensor[a+1]=sensor_centena;
                        a=a+1
                    }
                    
                    leitura_sensor[0]="#";
                    leitura_sensor[1]="P";
                    leitura_sensor[a+1]="0";
                    leitura_sensor[a+2]="L";
                    
                    //deve enviar o vetor leitura sensor completo.
                    
                    //close_cleidson
                    
                  Serial.print(quant_leituras);
                  client.print(quant_leituras);                  
                }
                else{
                  Serial.print("Entrada nao eh valida, digite um valor ateh 4 repeticoes;");
                  client.print("Entrada nao eh valida, digite um valor ateh 4 repeticoes;"); 
                }
                
              }
              else if(readstring[1]=='1'){
                
                for(int i=2;i<5;i++){
                valor_atuacao_vet+=readstring[i];                 
                }                             
                char str[10]="";
                strcpy (str ,valor_atuacao_vet.c_str());
                valor_atuacao = atoi(str);

                ////////////////////////////
                //tem que mandar valor_atuacao para o servo
                //////////////////////////
                client.print("Servo setado para : "+valor_atuacao_vet); 
              }
            }
            else if(readstring[0]=='A'){
              
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

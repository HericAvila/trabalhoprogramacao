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
    char c,valor_sensor_vet[20];
    int quant_leituras,valor_atuacao, valor_sensor;    
    String readstring,valor_atuacao_str,resposta;
    c=' ';
    quant_leituras=0; 
    valor_atuacao=0;      
    readstring="";
    resposta="";
    
    if (client) { 
      while (client.connected()) {
        if (client.available()) {          
          c = client.read(); // read 1 byte (character) from client
          readstring += c;                        
          //Serial.print(readstring+"\n");
          if (c == '#' ) {
            //Serial.print(readstring+"\n");     
            if(readstring=="G#"){
              String auxiliar;              
              client.print("GLS11#");  
              auxiliar = "";                  
              readstring="";               
            }
            else if(readstring[0]=='L'){
              if(readstring[1]=='0'){        
                quant_leituras=(readstring[4]-'0');
                valor_sensor = 100;                
                
                if(quant_leituras<5){
                  //Serial.print(quant_leituras+"\n");
                  resposta+='L';
                  for(int i=0;i<quant_leituras;i++){
                    resposta+= '0'; ; //aqui deve receber o sinal do sensor(0 se positivo)(1 se negativo) // nesse caso só rebece valores positivos do sensor;
                    itoa(valor_sensor,valor_sensor_vet,10);
                    if(valor_sensor<100){
                      resposta+= '0';
                    }
                    resposta+= valor_sensor_vet[0];
                    resposta+= valor_sensor_vet[1];
                    if(valor_sensor==100){
                      resposta+= valor_sensor_vet[2];
                    }
                    
                  }
                  resposta+='P';
                  resposta+='#';                  
                  Serial.print(resposta);
                  client.print(resposta);  
                  quant_leituras=6;  
                  resposta="";
              
                }
                else{
                  Serial.print("Entrada nao eh valida, digite um valor ateh 4 repeticoes;");
                  client.print("Entrada nao eh valida, digite um valor ateh 4 repeticoes;"); 
                }
                
                
              }
              else if(readstring[1]=='1'){
                
                for(int i=2;i<5;i++){
                valor_atuacao_str+=readstring[i];                 
                }                             
                char str[10]="";
                strcpy (str ,valor_atuacao_str.c_str());
                valor_atuacao = atoi(str);

                ////////////////////////////
                //tem que mandar valor_atuacao para o servo
                //////////////////////////
                client.print("Servo setado para : "+valor_atuacao_str); 
              }
            }
            else if(readstring[0]=='A'){
              
            }
            else{
              Serial.print("ERRO#");
              client.print("ERRO#"); 
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

#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include<stdbool.h>
#pragma comment(lib,"ws2_32.lib")

int primeiro_acesso =0;
bool cliente = true;

void loop();

int main(int argc , char *argv[])
{
    #pragma region Conexão com o socket
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message , server_reply[2000],*auxiliar;
    int recv_size;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n\n");
    #pragma endregion
    #pragma region Obtenção do IP
    
    
    
    char EnderecoIP[13];
    printf("Digite o Endereco de IP do intrumento que deseja conectar com pontos: ");
    gets (EnderecoIP);
    server.sin_addr.s_addr = inet_addr(EnderecoIP);

    
    //server.sin_addr.s_addr = inet_addr("192.168.4.50");
    //server.sin_addr.s_addr = inet_addr(ipdestino);
    printf("\n\n");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
    puts("Connected");
    #pragma endregion
    
      
    
    while ( strcmp(message,"EXIT#"))
    {   
        printf("Digite o codigo: ");
        scanf("%s", message);
        
        puts(message);
        if( send(s , message , strlen(message) , 0) < 0)
        {
        puts("Send failed");
        return 1;
        }
        puts("Dado enviado");
        if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
        {
         puts("recv failed");
        }

        puts("Resposta recebida:\n");    
        server_reply[recv_size] = '\0';
        puts(server_reply);       
    }
    
    system("pause");
   // return 0;
}

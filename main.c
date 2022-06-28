#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main(int argc , char *argv[])
{
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

    //printf("Digite o IP que voce deseja se conectar:\n");
    //char ipdestino[13];
    //scanf("%s", &ipdestino);

    server.sin_addr.s_addr = inet_addr("192.168.0.171");
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

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////  
    for(int i=0;i<6;i++){
    message = "G#";    
    puts(message);
    
    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    printf("Data Send\n");

    //Receive a reply from the server
    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        printf("recv failed");
    } 
    
    //printf("Recebeu o %i envio \n",i);  
    server_reply[recv_size] = '\0'; 
    /*     
    printf("%d ", server_reply[0]);
    printf("%d ", server_reply[1]);
    printf("%d ",  server_reply[2]);
    printf("%d ",  server_reply[3]);    
    printf("%d ",  server_reply[4]);
    printf("%d ",  server_reply[5]);
    printf("%d ",  server_reply[6]);
    printf("%s ",server_reply);  */
    puts(server_reply);
    
    } 

    system("pause");
   // return 0;
}

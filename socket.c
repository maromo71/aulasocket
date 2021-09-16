#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main(){
    //Buffer para armazenar a mensagem
    char buff[128];

    //Padrão para estrutura WSADATA
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 0), &wsa);


    //definindo a estrutura cliente/servidor, usando
    //sockets
    struct sockaddr_in caddr;
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(5000)    
    };

    int server = socket(AF_INET, SOCK_STREAM, 0);

    //variaveis para controle
    //client = cliente do soquete
    //x = mensagem a ser recebida pelo server
    //enviada pelo cliente. 
    //csize = tamanho da estrutura do soquete cliente
    int client, x;
    int csize = sizeof caddr;

    //Associar o soque a um endereco na rede bind
    bind(server, (struct sockaddr *) &saddr, sizeof saddr);

    //especificar o numero de conexoes que ficam em espera
    listen(server, 5);

    while(1){
        fflush(stdout);
        //o servidor aceitar um pedido de conexao de um cliente
        client = accept(server, (struct sockaddr *) &caddr, &csize);

        //ler da conexao
        x = recv(client, buff, sizeof buff, 0);

        //escrever para conexao
        send(client, buff, x, 0);

        fflush(stdout);
        //imprimir
        puts(buff);

        closesocket(client);
    }
    return 0;
}
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

int main(){

    //Master socket é o servidor, client_0 e client_1 são os sockets das aplicações que iram se comunicar, client_sockets é o vetor que os sockets das aplicações seram armazenados.
    int master_socket, client_0, client_1, client_sockets[2], activity;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    //Buffer de leitura  e str_final string que será enviada para as aplicações.
    char buffer[4097], str_final[5050];

    //Criamos o socket tcp.
    master_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(master_socket == 0){
        printf("Socket creation failed.");
        exit(EXIT_SUCCESS);
    }

    address.sin_family = AF_INET;   //IPV4
    address.sin_addr.s_addr = INADDR_ANY;   //Se liga a todos os IPs disponíveis.
    address.sin_port = htons(PORT); //porta 8080.

    //Amarramos o servidor ao endereço e porta especificadas.
    int bind_return = bind(master_socket, (struct sockaddr*)&address, sizeof(address));

    if(bind_return < 0){
        printf("Binding socket to address failed.");
        exit(EXIT_SUCCESS);
    }

    int listen_return = listen(master_socket, 2);

    if(listen_return < 0){
        printf("Listening failed.");
        exit(EXIT_SUCCESS);
    }


    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;

    //Pegamos o nome do host.
    gethostname(hostbuffer, sizeof(hostbuffer));

    //Com o nome do host recuperamos informações sobre o mesmo.
    host_entry = gethostbyname(hostbuffer);

    //Com as informações do host pegamos seu IP local (com o qual você usará na parte do cliente para se conectar ao servidor).
    IPbuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

    //Informamos ao usuário o nome do host e seu ip local.
    printf("Hostname: %s\n", hostbuffer);
    printf("Host IP: %s\n", IPbuffer);

    //Conectamos a primeira aplicação ao socket.
    client_0 = accept(master_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    //Verificamos se a aplicação se conectou ao servidor.
    if(client_0 >= 0){
        printf("Client 1 connected!\n");
    }else{
        printf("Client 1 not connected!");
        exit(EXIT_SUCCESS);
    }

    //Conectamos a segunda aplicação ao socket.
    client_1 = accept(master_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    //Verificamos se a aplicação se conectou ao servidor.
    if(client_1 >= 0){
        printf("Client 2 connected!\n");
    }else{
        printf("Client 2 not connected!");
        exit(EXIT_SUCCESS);
    }

    //Estrutura de dados usada para o select.
    fd_set readfds;

    int cmdExit = 0;

    //Enquanto nenhuma das aplicações tenha digitado o comando exit, o servidor continua trocando mensagens entre as duas.
    while(cmdExit == 0){

        //Limpa o fd_set
        FD_ZERO(&readfds);
        //Adiciona o socket master ao fd_set.
        FD_SET(master_socket, &readfds);

        //Adiciona os sockets das suas aplicações no vetor client_sockets.
        client_sockets[0] = client_0;
        client_sockets[1] = client_1;

        int max_sd = master_socket;

        //Procura o socket de maior valor (essa parte serve para o select).
        for(int i = 0; i < 2; i++){
            FD_SET(client_sockets[i], &readfds);

            if(client_sockets[i] > max_sd){
                max_sd = client_sockets[i];
            }
        }

        //Espera por uma atividade em algum dos sockets indefinidamente.
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if((activity < 0) && (errno!=EINTR)){
            printf("select error");
        }

        for(int i = 0; i < 2; i++){
            int sd = client_sockets[i];

            //Se algo aconteceu em algum dos sockets é uma mensagem chegando.
            if (FD_ISSET( sd , &readfds)){
                memset(buffer, '\0', sizeof (buffer));

                int client_recv, client_prod;

                //Verifica qual cliente é o produtor e qual cliente é o receptor da mensagem.
                if(i == 0){
                    client_prod = 0;
                    client_recv = 1;
                }else{
                    client_prod = 1;
                    client_recv = 0;
                }

                //Lê a mensagem vinda do socket.
                recv(sd, buffer, 4096, 0);
                printf("Message from client %d received.\n%s\n", client_prod,buffer);

                //Se a mensagem for o comando exit o servidor manda o comando para o cliente receptor e sai do loop.
                if(strcmp(buffer, "exit") == 0){
                    send(client_sockets[client_recv], buffer, strlen(buffer)+1, 0);
                    cmdExit = 1;
                    break;
                }

                //Caso contrário mandamos uma mensagem formatada para o cliente receptor.
                sprintf(str_final, "Client %d: %s", client_prod, buffer);
                send(client_sockets[client_recv], str_final, strlen(str_final)+1, 0);
                printf("Message from client %d sent to client %d.\n", client_prod, client_recv);
            }

        }

    }

    //Fechamos todos os sockets.
    close(master_socket);
    close(client_0);
    close(client_1);
    printf("Chat ended.\n");

    return 0;
}

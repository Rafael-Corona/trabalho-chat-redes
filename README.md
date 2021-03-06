# Trabalho Chat - SSC0142 - Redes de Computadores
Trabalho de Redes de Computadores - ICMC - 1 semestre - 2022



## Sumário
* [Grupo](#grupo)
* [Requisitos](#requisitos)
* [Descrição do Projeto](#descrição-do-projeto)
* [Tutorial da Instalação e Utilização da Aplicação](#tutorial-da-instalação-e-utilização-da-aplicação)
* [Problemas encontrados](#problemas-encontrados)
* [Comentários adicionais](#comentários-adicionais)  

## Grupo
 - Rafael Corona | Número USP: 4769989
 - Leonardo Gabriel Fusineli Silva |  Número USP: 11218841
 - Luccas Stroppa Saliba Barizon | Número USP: 11275022

## Requisitos
- O projeto está sendo desenvolvido em sistema operacional Linux, portanto recomenda-se que seja executado em Linux.

## Descrição do Projeto
- Neste projeto, vamos implementar as diversas partes que compõe um cliente e servidor IRC, ou Internet Relay Chat. Até o momento, a aplicação conta com uma implementação de Sockets.


## Tutorial da Instalação e Utilização da Aplicação
A aplicação é dividida entre cliente e servidor. A primeira etapa é fazer o download das pastas [server](/server) e [client](/client).  
Para que dois clientes possam se conectar, é necessário primeiro configurar o servidor.

### Instruções para iniciar o servidor:
Dentro da pasta [server](/server), é necessário abrir um terminal e compilar o código, utilizando o comando abaixo:
```
$ Make
```
Após a compilação, para rodar o código, basta digitar:
```
$ Make run
```
Caso tudo tenha funcionado como deveria, a aplicação servidor vai mostrar o IP local do host. Esse IP será necessário para que os clientes possam se conectar ao servidor.

### Instruções para Conectar o Cliente:
Dentro da pasta [client](/client), é necessário abrir um terminal e compilar o código, utilizando o comando abaixo:
```
$ Make
```
Após a compilação, para rodar o código, basta digitar:
```
$ Make run
```
Caso tudo tenha funcionado como deveria, a aplicação irá perguntar o IP local do host onde o servidor se encontra. Esse IP será necessário para que os clientes possam se conectar ao servidor.  
Repita essas etapas em uma nova janela do terminal mais uma vez, pois o chat funciona somente com dois clientes conectados no mesmo servidor.

### Instruções Para Usar o Chat:

Com tudo funcionando, o chat está pronto para ser usado. Em qualquer um dos dois clientes digite uma mensagem em sua respectiva aba do terminal e aperte enter, após isso verifique a aba do outro cliente, a mensagem digitada aparecerá lá e vice-versa.
Para finalizar a aplicação, digite ``exit``

## Problemas encontrados  
Caso tente rodar o servidor de novo pouco tempo depois de tê-lo rodado a primeira vez é possível que haja um erro de binding, nessa situação espere alguns minutos para o IP e porta ficarem disponíveis novamente e execute o código mais uma vez
## Comentários adicionais  

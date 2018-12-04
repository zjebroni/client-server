/*
 **********************************************************
 *
 *  Programme : client.c
 *
 *
 *  resumé :    envoi une chaine de caractères a un programme serveur
 *              dont l'adresse intrenet et le numéro de port son lu
 *              au clavier.
 *
 *
 ***********************************************************
 */

/* includes generaux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* includes socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


main(int argc, char *argv[])
{

  char chaine[100];
  int sock,                /* descipteur de la socket locale */
      err;                 /* code d'erreur */
  struct hostent*    host; /* description de la machine serveur (host) */
  struct sockaddr_in sockaddrServeur;  /* adresse de la socket du serveur */


  /*
   * Commentaire
   */
  if ( argc != 3 ) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }

  /* 
   * Commentaire
   */
  printf("client : Se connecter a %s, %d\n", argv[1], atoi( argv[2]));
  
  /* 
   * Commentaire
   */
  sock = socket( AF_INET, SOCK_STREAM, 0);
  if (sock<0) {

    printf("Client : erreur sur la creation de socket");
    exit(2);
  }

  /*
  * Commentaire
   */
  sockaddrServeur.sin_family = AF_INET;
  bzero(sockaddrServeur.sin_zero, 8);
  sockaddrServeur.sin_port = htons( atoi( argv[2]) );

  /* 
   * Commentaire
   */
  host = gethostbyname( argv[1] );
  if ( host == NULL ) {
    
    printf("Client : erreur gethostbyname\n");
    exit(2);
  }

  /*
   * Commentaire
   */
  sockaddrServeur.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
  
  /* 
   * Commentaire 
   */
  err = connect ( sock, (struct sockaddr *)&sockaddrServeur, sizeof(struct sockaddr_in) );
  if ( err<0 ) {
    perror("Client : erreur a la connection du socket\n");
    exit(3);
  }
  
  /* 
   * Commentaire
   */
  printf("client : donner une chaine : ");
  scanf("%s", chaine );
  printf("client : envoi de - %s - \n", chaine);
 
  
  /*
   * Commentaire
   */
  err = send( sock, (void*)chaine, (strlen(chaine) + 1), 0);
  if ( err != (strlen(chaine)+1) ) {
    
    perror("client : erreur sur le send");
    shutdown(sock, 2);
    exit(4);
  }
  printf("Cient : envoi realise\n");

  /* 
   * Commentaire
   */
  shutdown(sock, 2);
  close(sock);
}
 


/*
 **********************************************************
 *
 *  Programme : client.c
 *
 *
 *  resume :    envoi une chaine de caracteres a un programme serveur
 *              dont l'adresse intrenet et le numero de port son lu
 *              au clavier.
 *
 *
 ***********************************************************
 */

/* include generaux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* includes socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


main(int argc, char **argv)
{

  char chaine[100];
  int sock,                /* descipteur de la socket locale */
      err;                 /* code d'erreur */
  struct hostent*    host; /* description de la machine serveur */
  struct sockaddr_in nom;  /* adresse de la socket du serveur */

  socklen_t size_addr_in = sizeof(struct sockaddr_in);


  /*
   * Verification des arguments
   */
  if ( argc != 3 ) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }

  /* 
   * Creation d'une socket, domaine AF_INET, protocole TCP 
   */
  printf("client : connect to %s, %d\n", argv[1], atoi( argv[2]));
  
  /* 
   * Creation d'une socket, domaine AF_INET, protocole TCP 
   */
  sock = socket( AF_INET, SOCK_STREAM, 0);
  if (sock<0) {

    perror("fonctionClient : erreur sur la creation de socket");
    exit(2);
  }

  /* Initialisation de l'adresse de la socket */
  nom.sin_family = AF_INET;
  bzero(nom.sin_zero, 8);
  nom.sin_port = htons( atoi( argv[2]) );

  /* 
   * Recherche de l'adresse de la machine
   */
  host = gethostbyname ( argv[1] );
  if ( host == NULL ) {
    
    printf("fonctionClient : erreur gethostbyname %d\n", h_errno );
    exit(2);
  }

  /*
   * Recopie de l'adresse IP
   */
  nom.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
  
  /* 
   * Connection au serveur 
   */
  err = connect ( sock, (struct sockaddr *)&nom, size_addr_in );
  if ( err<0 ) {
    perror("fonctionClient : erreur a la connection de socket\n");
    exit(3);
  }
  
  /* 
   * Saisie de la chaine 
   */
  printf("client : donner une chaine : ");
  scanf("%s", chaine );
  printf("client : envoi de - %s - \n", chaine);
 
  
  /*
   * Envoi de la chaine
   */
  err = send( sock, (void*)chaine, (strlen(chaine) + 1), 0);
  if ( err!= (strlen(chaine)+1) ) {
    
    perror("client : erreur sur le send");
    shutdown(sock, 2);
    exit(4);
  }
  printf("client : envoi realise\n");

  /* 
   * Fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);
}
 


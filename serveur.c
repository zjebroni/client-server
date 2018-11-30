/*
 **********************************************************
 *
 *  Programme : serveur.c
  *
 *  resume :    recoit une chaine de caracteres du programme client
 * *
 ***********************************************************
 */

/* include generaux */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* includes socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* taille du buffeur de reception */
#define TAIL_BUF 100


main(int argc, char** argv)
{
    int             sock_cont, 
                    sock_trans,	        /* descipteurs des sockets locales */
                    err;	        /* code d'erreur */

    struct sockaddr_in nom;	      /* adresse de la socket */
    struct sockaddr_in nom_transmis;  /* adresse de la socket client */

    char            buffer[TAIL_BUF],	/* buffer de reception */
                    reponse[2];         /* pour le test de fin */

    socklen_t      size_addr;  	/* taille de l'adresse d'une socket */



    /*
     * Verification des arguments
     */
    if ( argc != 2 ) {

      printf ( "usage : serveur no_port\n" );
      exit( 1 );
    }

    // calcul taille structure d'adresse
    size_addr = sizeof(struct sockaddr_in);

    /* Creation de la socket, protocole TCP */
    sock_cont = socket( AF_INET, SOCK_STREAM, 0);
    if (sock_cont < 0) {
      
      perror("serveur: erreur de socket\n");
      exit( 2 );
    }
    
    /* 
     * Initialisation de l'adresse de la socket 
     */
    nom.sin_family = AF_INET;
    nom.sin_port = htons( atoi( argv[1] ));
    nom.sin_addr.s_addr = INADDR_ANY;
    bzero(nom.sin_zero, 8);
    
    /* 
     * Attribution de l'adresse a la socket
     */
    err = bind( sock_cont, (struct sockaddr *)&nom, size_addr);
    if (err < 0) {
      
      perror("serveur: erreur sur le bind");
      exit( 3 );
    }
    
    /* 
     * Utilisation en socket de controle, puis attente de demandes de 
     * connexion.
     */
    err = listen( sock_cont, 1);
    if (err < 0) {
      
      perror("serveur: erreur dans listen");
      exit( 4 );
    }
    
    /*
     * Attente de connexion
     */
    sock_trans = accept(sock_cont, 
                        (struct sockaddr *)&nom_transmis, 
                        &size_addr );
    if (sock_trans < 0) {
	perror("serveur :  erreur sur accept");
	exit( 5 );
    }

    /*
     * Reception et affichage du message en provenance du client
     */
    err = recv( sock_trans, (void*)buffer, TAIL_BUF, 0);
    if (err < 0) {
      
      perror("serveur : erreur dans la reception");
      shutdown(sock_trans, 2);
      exit( 6 );
    }
    printf("serveur : voila le message recu: %s\n", buffer);
    
    /* 
     * arret de la connexion et fermeture
     */
    shutdown(sock_trans, 2);
    close(sock_cont);
}

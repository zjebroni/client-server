/*
 **********************************************************
 *
 *  Programme : serveur.c
  *
 *  resume :    recevoir une chaine de caractères du programme client
 * *
 ***********************************************************
 */

/* includes generaux */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* includes socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* taille du buffer de reception */
#define TAIL_BUF 100


main(int argc, char** argv)
{
    int             sock_cont, 
                    sock_trans,	        /* descipteurs des sockets locales */
                    err;	        /* code d'erreur */

    struct sockaddr_in sockaddrCont;	      /* adresse de la socket */
    struct sockaddr_in sockaddTrans;  /* adresse de la socket client */

    char    		buffer[TAIL_BUF];	/* buffer de reception */

    /*
     * Commentaire
     */
    if ( argc != 2 ) {

      printf ( "usage : serveur no_port\n" );
      exit( 1 );
    }


    /* Commentaire */
    sock_cont = socket( AF_INET, SOCK_STREAM, 0);
    if (sock_cont < 0) {
      
      perror("serveur: erreur de socket\n");
      exit( 2 );
    }
    
    /* 
     * Commentaire 
     */
    sockaddrCont.sin_family = AF_INET;
    sockaddrCont.sin_port = htons( atoi( argv[1] ));
    sockaddrCont.sin_addr.s_addr = INADDR_ANY;
    bzero(sockaddrCont.sin_zero, 8);
    
    /* 
     * Commentaire
     */
    err = bind( sock_cont, (struct sockaddr *)&sockaddrCont, sizeof(struct sockaddr_in));
    if (err < 0) {
      
      perror("serveur: erreur sur le bind");
      exit( 3 );
    }
    
    /* 
     * Commentaire
     */
    err = listen( sock_cont, 1);
    if (err < 0) {
      
      perror("serveur: erreur dans listen");
      exit( 4 );
    }
    
    /*
     * Commentaire
     */
    socklen_t addrlen = sizeof(struct sockaddr_in);
    sock_trans = accept(sock_cont, (struct sockaddr *)&sockaddTrans, &addrlen);
    if (sock_trans < 0) {
	perror("serveur :  erreur sur accept");
	exit( 5 );
    }

    /*
     * Commentaire
     */
    err = recv( sock_trans, (void*)buffer, TAIL_BUF, 0);
    if (err < 0) {
      
      perror("serveur : erreur dans la reception");
      shutdown(sock_trans, 2);
      exit( 6 );
    }
    printf("serveur : voila le message recu: %s\n", buffer);
    
    /* 
     * Commentaire
     */
    shutdown(sock_trans, 2);
    close(sock_cont);
}

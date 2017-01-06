/* servidor
 * File:   main.c
 * Laura Carolina Sánchez Cardoso
 * 4.532.196-2
 * Created on 24 de octubre de 2011, 21:14
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include <errno.h>
#define BUFF_LEN 4
#define FILAS 7
#define COLUMNAS 7
#define CLIENTE 'X'
#define SERVIDOR 'O'
#define VACIO ' '
#include <ctype.h>

void inicializotablero(char tablero[FILAS][COLUMNAS]) 
{
    int fila, columna;

    for (fila = 0; fila < FILAS; fila++)
        for (columna = 0; columna < COLUMNAS; columna++)
            tablero[fila][columna] = VACIO; /*inicializa el tablero en vacio*/


}

char imprimirtablero(char tablero[FILAS][COLUMNAS]) 
{
    int fila, columna;

    for (columna = 0; columna < COLUMNAS; columna++)
        printf("  %d ", columna + 1);
    printf("\n");
    for (fila = 0; fila < FILAS; ++fila) 
    {
        for (columna = 0; columna < COLUMNAS; ++columna) 
        {
            printf("| %c ", tablero[fila][columna]);

        }/*impimo el tablero poniendo 
           * lo que encuentre en el lugar de fila fila y columna columna*/
        printf("|\n");
    }
}

char jugada(int turno, int jugada_j1, int jugada_j2, char tablero [FILAS][COLUMNAS]) 
{
    int fila = FILAS - 1; /*esta es mi variable de control*/

    if ((turno % 2) == 1) 
    {
        while (fila >= 0) 
        { /*recorro las filas de abajo para arriba*/
            if ((tablero [fila][jugada_j1 - 1] == VACIO))/*si encuentra un lugar vacio coloca la ficha*/ 
            {
                tablero [fila][jugada_j1 - 1] = CLIENTE;
                /*en el lugar fila(vacia) jugada_j1 -1 */
                printf("\nla ultima jugada realizada por el jugador 1 es [%d][%d]\n\n", fila + 1, jugada_j1);
                fila = -9;
                /*para salir del bucle una vez encuentre donde poner la ficha*/

            }


            fila--;
        }

    } 
    else 
    {

        while (fila >= 0) 
        {/*recorro las filas de abajo para arriba*/


            if ((tablero [fila][jugada_j2 - 1] == VACIO)) 
            {/*si encuentra un lugar vacio coloca la ficha*/
                tablero [fila][jugada_j2 - 1] = SERVIDOR; /*en el lugar fila(vacia) columna jugada_j2-1 */

                printf("la ultima jugada realizada por el jugador 2 es [%d][%d]\n\n", fila + 1, jugada_j2);
                fila = -9;
                /*para salir del bucle una vez encuentre donde poner la fila*/

            }
            --fila;
        }


    }
}

int ganador(char tablero1[FILAS][COLUMNAS]) 
{
    int fila, columna;

    for (fila = 6; fila >= 0; fila--) 
    {/*ganador horizontal*/
        for (columna = 0; columna <= COLUMNAS - 4; columna++) 
        {
            if (((tablero1[fila][columna] == CLIENTE) &&
                    (tablero1[fila][columna + 1] == CLIENTE) &&
                    (tablero1[fila][columna + 2] == CLIENTE) &&
                    (tablero1[fila][columna + 3] == CLIENTE))) 
            {
                printf("\nFelicidades jugador 1! ha vencido a jugador 2\n");
                return 1;
            } 
            else if (
                    ((tablero1[fila][columna] == SERVIDOR) &&
                    (tablero1[fila][columna + 1] == SERVIDOR) &&
                    (tablero1[fila][columna + 2] == SERVIDOR) &&
                    (tablero1[fila][columna + 3] == SERVIDOR)
                    )) 
            {
                printf("\nFelicidades jugador 2! ha vencido ha jugador 1\n");
                return 2;
            }

        }
    }
    for (fila = 0; fila <= FILAS - 4; fila++) 
    {/*ganador vertical*/
        for (columna = 0; columna <= COLUMNAS - 1; columna++) 
        {
            if (((tablero1[fila][columna] == CLIENTE) &&
                    (tablero1[fila + 1][columna] == CLIENTE) &&
                    (tablero1[fila + 2][columna] == CLIENTE) &&
                    (tablero1[fila + 3][columna] == CLIENTE)
                    )) 
            {
                printf("\nFelicidades jugador 1! ha vencido a jugador 2\n");
                return 1;
            } 
            else if ((tablero1[fila][columna] == SERVIDOR) &&
                    (tablero1[fila + 1][columna] == SERVIDOR) &&
                    (tablero1[fila + 2][columna] == SERVIDOR) &&
                    (tablero1[fila + 3][columna] == SERVIDOR)) 
            {
                printf("\nFelicidades jugador 2! ha vencido ha jugador 1\n");
                return 2;
            } 
            else if ((tablero1[0][0] != VACIO) && (tablero1[0][1] != VACIO)
                    && (tablero1[0][2] != VACIO) && (tablero1[0][3] != VACIO)
                    && (tablero1[0][4] != VACIO) && (tablero1[0][5] != VACIO)
                    && (tablero1[0][6] != VACIO)) 
            {            
                printf("\ntablero lleno\n");
                return 3;
                /*empate*/
            }

        }
    }
    for (fila = 0; fila <= FILAS - 4; fila++) 
    {/*diagonal descendiente*/
        for (columna = 0; columna <= COLUMNAS - 4; columna++) 
        {
            if ((tablero1[fila][columna] == CLIENTE) &&
                    (tablero1[fila + 1][columna + 1] == CLIENTE) &&
                    (tablero1[fila + 2][columna + 2] == CLIENTE) &&
                    (tablero1[fila + 3][columna + 3] == CLIENTE)) 
            {
                printf("\nFelicidades jugador 1! ha vencido a jugador 2\n");
                return 1;
            }
            else if ((tablero1[fila][columna] == SERVIDOR) &&
                    (tablero1[fila + 1][columna + 1] == SERVIDOR) &&
                    (tablero1[fila + 2][columna + 2] == SERVIDOR) &&
                    (tablero1[fila + 3][columna + 3] == SERVIDOR)) 
            {
                printf("\nFelicidades jugador 2! ha vencido ha jugador 1\n");
                return 2;
            }
        }
    }

    for (fila = FILAS - 1; fila >= FILAS - 4; fila--) 
    { /*diagonal ascendente*/
        for (columna = 0; columna <= COLUMNAS - 4; columna++) 
        {
            if ((tablero1[fila][columna] == CLIENTE) &&
                    (tablero1[fila - 1][columna + 1] == CLIENTE) &&
                    (tablero1[fila - 2][columna + 2] == CLIENTE) &&
                    (tablero1[fila - 3][columna + 3] == CLIENTE)) 
            {
                printf("\nFelicidades jugador 1! ha vencido a jugador 2\n");
                return 1;
            }
            else if ((tablero1[fila][columna] == SERVIDOR) &&
                    (tablero1[fila - 1][columna + 1] == SERVIDOR) &&
                    (tablero1[fila - 2][columna + 2] == SERVIDOR) &&
                    (tablero1[fila - 3][columna + 3] == SERVIDOR)) 
            {
                printf("\nFelicidades jugador 2! ha vencido ha jugador 1\n");
                return 2;
            }
        }
    }
    return 0;
}

void error(char *msg) 
{
    perror(msg);
    exit(-1);
}

int main(int argc, char *argv[]) 
{
    /*inicializo variables*/
    char jugada_J1;
    char jugada_J2;    
    char tablero[FILAS][COLUMNAS];
    
    int jugada_j1 = 0;
    int jugada_j2 = 0;
    int gana = 0;
    int turno = 0;
    int n;
    int buffer[BUFF_LEN];
    
    unsigned int newsockfd, clilen;
    unsigned int sockfd, portno;
    
    struct sockaddr_in serv_addr, cli_addr;
    struct hostent *server;
    
    if (strcmp(argv[1], "servidor")) 
    {
        if (argc < 3) 
        {
            fprintf(stderr, "Uso: %s <nombre_host> <puerto>\n", argv[0]);
            exit(0);
        }

        portno = atoi(argv[3]);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) 
        {
            error("ERROR al abrir el socket.");
        }

        server = gethostbyname(argv[2]);
        if (server == NULL) 
        {
            fprintf(stderr, "ERROR, host desconocido\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof (serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr,
                (char *) &serv_addr.sin_addr.s_addr,
                server->h_length);
        serv_addr.sin_port = htons(portno);

        if (connect(sockfd, &serv_addr, sizeof (serv_addr)) < 0) 
        {
            error("ERROR durante la conexión.");
        }
	printf("\nBienvenido a 4 en Linea\n");
        inicializotablero(tablero); /*empiezo inicializando el tablero*/
        imprimirtablero(tablero);
        printf("\n¿quien juega primero?\n1-Jugador 1\n2-Jugador 2\n");
        scanf("%d", &turno); /*escaneo el numero de turno*/

        buffer[0] = turno; /*guardo turno en el buffer*/

        n = write(sockfd, buffer, 4);
        if (n < 0) 
        {
            error("Error escribiendo al socket");
        }; /*mando buffer*/

        n = read(sockfd, buffer, BUFF_LEN);

        while (gana == 0) 
        {
            if ((turno % 2) == 1) 
            {

                printf("\ningrese su jugada\n");
                fflush(stdin);
                scanf("%c", &jugada_J1);
                scanf("%c", &jugada_J1);
                jugada_j1 = (int) jugada_J1 - 48;

                while (((jugada_j1 < 1) || (jugada_j1 > 7)) || (tablero[0][jugada_j1 - 1] != VACIO)) 
                {/*me aseguro de que el numero este dentro del rango valido, 
                     * y en el caso de ser valido me fijo si la columna no esta llena*/
                    if (tablero[0][jugada_j1 - 1] != VACIO) 
                    {
                        printf("\nla columna  esta llena. Ingrese otra\n");
                    } else printf("\nnumero de columna no valido. Ingrese otro\n");

                    scanf("%c", &jugada_J1);
                    jugada_j1 = (int) jugada_J1 - 48;
                }
                jugada(turno, jugada_j1, jugada_j2, tablero);
                imprimirtablero(tablero);
                buffer[0] = jugada_j1; /*guardo la jugada para mandarsela al otro jugador*/
                n = write(sockfd, buffer, 4);
                if (n < 0) 
                {
                    error("Error escribiendo al socket");
                };
                gana = ganador(tablero);
                
                    turno++;

            }
            else 
            {
                printf("\nEspere mientras el jugador 2 realiza su jugada\n");

                n = read(sockfd, buffer, BUFF_LEN);
                jugada_j2 = buffer[0];
                jugada(turno, jugada_j1, jugada_j2, tablero);
                imprimirtablero(tablero);
                gana = ganador(tablero);
              
                    turno++;
            }
        }
        if (gana == 1) 
        {
            printf("\nFelicidades!! ha vencido al jugador 2\n");
        }
        else if (gana == 2) 
        {
            printf("\nmal asunto, ha sido vencido por el jugador 2\n");
        }
        else if (gana == 3)
        {
            printf("\nwow, ha habido un empate\n");
        }
        close(newsockfd);
        close(sockfd);
        return 0;
    }
    else 
    {
    if (argc < 2) 
        {
            fprintf(stderr, "ERROR, faltó indicar el número de puerto.\n");
            exit(-1);
         }
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
        {
            error("ERROR abriendo el socket.\n");
        }

        bzero((char *) &serv_addr, sizeof (serv_addr));

        portno = atoi(argv[2]);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) 
        {
            error("ERROR haciendo el binding");
        }

        listen(sockfd, 0);
        clilen = sizeof (cli_addr);

        printf("Esperando conexiones remotas...\n");

        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) 
        {
            error("ERROR en el accept.\n");
        }

        printf("Escuchando...\n");
        inicializotablero(tablero);
        imprimirtablero(tablero);
        n = read(newsockfd, buffer, BUFF_LEN);
        if (n < 0) 
        {
            error("error leyendo el socket");
        }
        turno = buffer[0];

        n = write(newsockfd, buffer, n);
        if (n < 0) 
        {
            error("Error escribiendo al socket");
        }

        while (gana == 0) 
        {

            if ((turno % 2) == 1) 
            {

                printf("\nEspere mientras el jugador 1 realiza su jugada\n");
                n = read(newsockfd, buffer, BUFF_LEN);
                if (n < 0) 
                {
                    error("error leyendo el socket");
                }
                jugada_j1 = buffer[0]; /*extrae la jugada del contrario*/
                jugada(turno, jugada_j1, jugada_j2, tablero);
                imprimirtablero(tablero);
                gana = ganador(tablero);

          
                    turno++;

            }
            else 
            {
                printf("\ningrese su jugada\n");
                fflush(stdin);
                scanf("%c", &jugada_J2);
                jugada_j2 = (int) jugada_J2 - 48;
                while (((jugada_j2 < 1) || (jugada_j2 > 7)) || (tablero[0][jugada_j2 - 1] != VACIO)) 
                {/*me aseguro de que el numero este dentro del rango valido, 
                     * y en el caso de ser valido me fijo si la columna no esta llena*/
                    if (tablero[0][jugada_j2 - 1] != VACIO) 
                    {
                        printf("\nla columna  esta llena. Ingrese otra\n");
                    }
                    else printf("\nnumero de columna no valido. Ingrese otro\n");
                    scanf("%c", &jugada_J2);
                    jugada_j2 = (int) jugada_J2 - 48;
                }
                jugada(turno, jugada_j1, jugada_j2, tablero);
                imprimirtablero(tablero);

                buffer[0] = jugada_j2;
                n = write(newsockfd, buffer, n);
                if (n < 0) 
                {
                    error("Error escribiendo al socket");
                }

                gana = ganador(tablero);
            
                    turno++;
            }
            
       
        }

        if (gana == 1) 
        {
            printf("\nmal asunto, ha sido vencido por el jugador 1\n");
        }
        else if (gana == 2) 
        {
            printf("\nfelicidades!!! ha vencido al jugador 1\n");
        } else if (gana == 3) 
        {
            printf("\nwow, ha habido un empate\n");
        }
        close(newsockfd);
        close(sockfd);
        return 0;
    }
}

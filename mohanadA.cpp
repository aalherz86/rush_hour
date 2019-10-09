// Mohanad Algoraibi
//First Modification: Display My name on screen when pressing (c) which is the Credit.
//Second Modification on the main file (car.cpp): Display the Highest scores on screen.
//Third Modification: adding the fuction from lab3 and call it in hussainJ file 
/* The Debug steps:
1-Identify (checking) is to find the debugging.
2-Isolate is to separate the buggy code with other healthy code
3-Fix is to correct the buggy code.
4-Review is to ensure the bug you fixed are working correctly now.
*/

#include "fonts.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void showMcredit() 
{
	Rect n;
	n.bot = 360;
	n.left = 280;
	n.center = 0;
	ggprint8b(&n, 16, 0x00fffff00, "Mohanad Algoraibi");


}

void set_to_non_blocking(const int sock)
{
    //Set a socket to be non-blocking.
    int opts;
    opts = fcntl(sock, F_GETFL);
    if (opts < 0) {
        perror("ERROR: fcntl(F_GETFL)");
        exit(EXIT_FAILURE);
    }
    opts = (opts | O_NONBLOCK);
    if (fcntl(sock, F_SETFL, opts) < 0) {
        perror("ERROR: fcntl(O_NONBLOCK)");
        exit(EXIT_FAILURE);
    }
}







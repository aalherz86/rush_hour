// Mohanad Algoraibi
//First Modification: Display My name on screen when pressing (c) which is the Credit.
//Second Modification on the main file (car.cpp): Display the Highest scores on screen.
//Third Modification: adding the function from lab3 and call it in hussainJ file
//Fourth Modification: created a function called displayHighscores to get 5 scores on screen.
//Fifth Modification: Moving and fixing all my functions to a new framework.
/* The Debug steps:
   1-Identify (checking) is to find the debugging.
   2-Isolate is to separate the buggy code with other healthy code
   3-Fix is to correct the buggy code.
   4-Review is to ensure the bug you fixed are working correctly now.
   */
// Sixth Modification: This is Friday code.
// seventh Modification: creating mohanadA Header.

#include "fonts.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "mohanadA.h"

using namespace std;

extern vector<int> getHighscore ();

void showMcredit() 
{
	Rect n;
	n.bot = 580;
	n.left = 820;
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

void displayHighscores()
{
	vector<int> scores;
	scores = getHighscore();
	Rect n[6];

	n[0].bot = 720;
	n[0].left = 820;
	n[0].center = 0;
	ggprint8b(&n[0], 16, 0x00ffffff, "Highscores");
	n[1].bot = 700;
	n[1].left = 820;
	n[1].center = 0;

	n[2].bot = 700;
	n[2].left = 800;
	n[2].center = 0;	

	for (size_t i = 0; i < 5; i++) {
		ggprint8b(&n[1], 16, 0x00ffffff, " %i", scores[i]);
	}
	for (size_t i = 1; i < 6; i++) {
		ggprint8b(&n[2], 16, 0x00ffffff, " %i - ", i);
	}
}

// This is my Friday code.





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
#include <GL/glu.h>
#include "Image.h"



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
void drawVehicle(int vehicleX, int vehicleY)
{
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    glVertex2f(vehicleX - 25, vehicleY + 16);
    glVertex2f(vehicleX + 25, vehicleY + 16);
    glVertex2f(vehicleX - 25, vehicleY - 16);
    glVertex2f(vehicleX + 25, vehicleY - 16);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex2f(vehicleX - 25, vehicleY + 20);
    glVertex2f(vehicleX - 25, vehicleY - 20);
    glVertex2f(vehicleX + 25, vehicleY - 20);
    glVertex2f(vehicleX + 25, vehicleY + 20);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex2f(vehicleX - 23, vehicleY + 20);
    glVertex2f(vehicleX - 19, vehicleY + 40);
    glVertex2f(vehicleX + 19, vehicleY + 40);
    glVertex2f(vehicleX + 23, vehicleY + 20);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex2f(vehicleX - 23, vehicleY - 20);
    glVertex2f(vehicleX - 19, vehicleY - 35);
    glVertex2f(vehicleX + 19, vehicleY - 35);
    glVertex2f(vehicleX + 23, vehicleY - 20);
    glEnd();
}

// credit screen
Image * title;
GLuint titleTex;
void initCreditScreen()
{

    title = new Image("images/credit.png");
    glGenTextures( 1, &titleTex);
    glBindTexture( GL_TEXTURE_2D, titleTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, title->width, title->height, 0, GL_RGB,
                  GL_UNSIGNED_BYTE, title->data);
    glBindTexture( GL_TEXTURE_2D, 0);

}

void drawCredit(int xres, int yres) {

    float w;
    float h;

    glPushMatrix();
    w = 250;
    h = 150;
    glTranslatef(xres/2, yres/2 + 200, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, titleTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);glVertex2f(-w, -h);
    glTexCoord2f(0.00, 0.00);glVertex2f(-w,  h);
    glTexCoord2f(1.00, 0.00);glVertex2f( w,  h);
    glTexCoord2f(1.00, 1);glVertex2f( w, -h);
    glEnd();
}






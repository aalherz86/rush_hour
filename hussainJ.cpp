// Hussain Jafri
/*
 * Quiz
 * Date: 10/09/2019
 * 
 * Debugging steps or Get a Debug Report:
 * 1. Reduce the bugs.
 * 2. Locate the bad codes.
 * 3. Fix the peice of bad codes.
 * 4. Test the bad codes. And test the whole program as well.
 */
#include "fonts.h"
#include <GL/glu.h>

// New Libs
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

//void set_to_non_blocking(const int sock);
// Global Area
#define PORT 443
#define USERAGENT "CMPS-3350"
const int MAX_READ_ERRORS = 100;

void displayName() {
	Rect n;
	n.bot = 560;
	n.left = 820;
	n.center = 0;
	ggprint8b(&n, 16, 0x00fffff, "Hussain Jafri");
}

// Adding drawImage function here with its full contents.
void drawImage(GLuint texture, int xres, int yres)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();
}

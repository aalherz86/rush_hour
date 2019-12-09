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
#include <iostream>
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
#include "aliA.h"
#include <GL/gl.h>
#include <GL/glx.h>


using namespace std;

extern vector<int> getHighscore ();
void credits();
Play pl;

void showMcredit() 
{
	Rect n;
	n.bot = 580;
	n.left = 820;
	n.center = 0;
	ggprint8b(&n, 16, 0x00ffffff, "Mohanad Algoraibi");


}
Button btn[MAXBUTTONS];
void backBtn_init(void)
{

    btn[0].r.width = BUTTON_WIDTH +30;
    btn[0].r.height = BUTTON_HEIGHT;
    btn[0].r.left = 1050 - btn[0].r.width/2;
    btn[0].r.bot = BUTTON_B -280;
    btn[0].r.right =
            btn[0].r.left + btn[0].r.width;
    btn[0].r.top =
            btn[0].r.bot + btn[0].r.height;
    btn[0].r.centerx =
            (btn[0].r.left + btn[0].r.right) / 2;
    btn[0].r.centery =
            (btn[0].r.bot + btn[0].r.top) / 2;
    strcpy(btn[0].text, "BACK");
    btn[0].down = 0;
    btn[0].click = 0;
    btn[0].color[0] = 0.0f;
    btn[0].color[1] = 0.0f;
    btn[0].color[2] = 0.0f;
    btn[0].dcolor[0] = btn[0].color[0] * 0.5f;
    btn[0].dcolor[1] = btn[0].color[1] * 0.5f;
    btn[0].dcolor[2] = btn[0].color[2] * 0.5f;
    btn[0].text_color = 0x00ffffff;

}

void btnRender(void)
{

    //add render function to render button
    for (int i = 0; i < MAXBUTTONS; i++) {
        if (btn[i].over) {
            //create the highlight color of button
            glColor3f(1.0f, 1.0f, 1.0f);
            //draw a highlight around the button
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
            glVertex2i(btn[i].r.left-2,  btn[i].r.bot-2);
            glVertex2i(btn[i].r.left-2,  btn[i].r.top+2);
            glVertex2i(btn[i].r.right+2, btn[i].r.top+2);
            glVertex2i(btn[i].r.right+2, btn[i].r.bot-2);
            glVertex2i(btn[i].r.left-2,  btn[i].r.bot-2);
            glEnd();
            glLineWidth(2);
            btn[i].text_color = 0x00fff333;

        }
        if (btn[MAXBUTTONS - 1].over)
            btn[i].text_color = 0x00ff0000;

        glBegin(GL_QUADS);
        if (btn[i].down) {
            glColor3fv(btn[i].dcolor);
        } else {
            glColor3fv(btn[i].color);
        }
        glVertex2i(btn[i].r.left,  btn[i].r.bot);
        glVertex2i(btn[i].r.left,  btn[i].r.top);
        glVertex2i(btn[i].r.right, btn[i].r.top);
        glVertex2i(btn[i].r.right, btn[i].r.bot);
        glEnd();
        Rect r;
        r.left = btn[i].r.centerx;
        r.bot  = btn[i].r.centery-8;
        r.center = 1;
        if (btn[i].down) {
            ggprint16(&r, 0, btn[i].text_color, "Pressed!");
        } else {
            ggprint16(&r, 0, btn[i].text_color, btn[i].text);
        }
    }
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

	n[1].bot = 600;
	n[1].left = 660;
	n[1].center = 0;

	n[2].bot = 600;
	n[2].left = 610;
	n[2].center = 0;	

	for (size_t i = 0; i < 5; i++) {
		ggprint16(&n[1], 16, 0x00ffffff, " %i", scores[i]);
	}
	for (size_t i = 1; i < 6; i++) {
		ggprint16(&n[2], 16, 0x00ffffff, " %i - ", i);
	}
}

// This is my Friday code
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
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D( GL_TEXTURE_2D, 0, 3, title->width, title->height, 0, GL_RGB,
                  GL_UNSIGNED_BYTE, title->data);
}

void drawCredit(int xres, int yres)
{

    glPushMatrix();
    drawImage(titleTex, xres, yres);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    backBtn_init();
    btnRender();
    credits();

}

void checkMouse(int action, Play& p)
{
    if (p.gameState == CREDITS) {
        if (action == 1) {
            for (int i=0; i<MAXBUTTONS; i++) {
                if (btn[i].over) {
                    btn[i].down = 1;
                    btn[i].click = 1;
                    if (i == 0) {
                        p.gameState = MENU ;
                        break;
                    }
                }
            }
        }
    }
}

void checkBtn(XEvent *e, Play& p)
{
    static int savex = 0;
    static int savey = 0;
    int x,y,i;
    int lbutton=0;
    int rbutton=0;
    //when mouse button is release
    if (e->type == ButtonRelease) {
        checkMouse(2, p);
        return;
    }
    if (e->type == ButtonPress) {
        //when mouse left button is pressed
        if (e->xbutton.button == 1) {
            lbutton = 1;
        }
        //when mouse right button is pressed
        if (e->xbutton.button == 3) {
            rbutton = 1;
        }
    }
    x = e->xbutton.x;
    y = e->xbutton.y;
    y = 1000-y;
    //check to see if mouse move either in x or y direction
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
        savex=e->xbutton.x;
        savey=e->xbutton.y;

    }
    if (x == savex && y == savey)
        return;

    savex=x;
    savey=y;
    for (i=0; i<MAXBUTTONS; i++) {
        btn[i].over=0;
        btn[i].down=0;

        if (x >= btn[i].r.left &&
            x <= btn[i].r.right &&
            y >= btn[i].r.bot &&
            y <= btn[i].r.top) {
            btn[i].over=1;
            break;
        }
    }
    if (lbutton)
        checkMouse(1, p);
    if (rbutton)
        checkMouse(2, p);

}

void creditInit(GLuint tex, Image& img)
{
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 img.width, img.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);

}

void showName(Rect& r, int bot, int left, const char* txt)
{
    r.bot = bot;
    r.left = left;
    r.center = 0;
    ggprint16(&r, 0, 0x00ffffff, txt);
}

void credits()
{
    Rect r[12];
    r[0].bot = 650;
    r[0].left = 660;
    r[0].center = 0;
    ggprint16(&r[0], 0, 0x00fff222, "Menu by: ");
    showName(r[6], r[0].bot -40 , 660, "Hussain Jafri");

    r[1].bot = 570;
    r[1].left = 660;
    r[1].center = 0;
    ggprint16(&r[1], 0, 0x00fff222, "Credit by: ");
    showName(r[7], r[1].bot -40 , 660, "Mohanad Algoraibi");

    r[2].bot = 490;
    r[2].left = 660;
    r[2].center = 0;
    ggprint16(&r[2], 0, 0x00fff222, "Tiles System by: ");
    showName(r[8], r[2].bot -40 , 660, "Ali Alherz");


    r[3].bot = 410;
    r[3].left = 660;
    r[3].center = 0;
    ggprint16(&r[3], 0, 0x00fff222, "Graphics by: ");
    showName(r[9], r[3].bot -40 , 660, "Mohanad Algoraibi");


    r[5].bot = 330;
    r[5].left = 660;
    r[5].center = 0;
    ggprint16(&r[5], 0, 0x00fff222, "High score system by: ");
    showName(r[10], r[5].bot -40 , 660, "Ali Alherz");


    r[4].bot = 250;
    r[4].left = 660;
    r[4].center = 0;
    ggprint16(&r[4], 0, 0x00fff222, "Physics by: ");
    showName(r[11], r[4].bot -40 , 660, "Hussain Jafri");


}






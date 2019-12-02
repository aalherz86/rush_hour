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
// Added new Library for the game timer
#include <GL/gl.h>
#include <GL/glx.h>
#include "aliA.h"

//-------------------------------------------------
#define BUTTON_WIDTH 50
#define BUTTON_HEIGHT 50
#define BUTTON_B 400
// Defining 4 buttons
#define MAXBUTTONS 4
//------------------------------------------------

//void set_to_non_blocking(const int sock);
// Global Area
#define PORT 443
#define USERAGENT "CMPS-3350"
const int MAX_READ_ERRORS = 100;
// This function to display my name on the screen.
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


void drawImage(GLuint, int, int);
void check_Button(XEvent, Play& );

typedef struct t_button {
    Rect r;
    char text[32];
    int over;
    int down;
    int click;
    float color[3];
    float dcolor[3];
    unsigned int text_color;
    t_button() { over = false; }
}Button;

Button button[MAXBUTTONS];

void button_init(void)
{
    //add button function to initiate
    //Play button
    button[0].r.width = BUTTON_WIDTH +30;
    button[0].r.height = BUTTON_HEIGHT;
    button[0].r.left = 700 - button[0].r.width/2;
    button[0].r.bot = (BUTTON_B + 300);
    button[0].r.right =
            button[0].r.left + button[0].r.width;
    button[0].r.top =
            button[0].r.bot + button[0].r.height;
    button[0].r.centerx =
            (button[0].r.left + button[0].r.right) / 2;
    button[0].r.centery =
            (button[0].r.bot + button[0].r.top) / 2;
    strcpy(button[0].text, "PLAY");
    button[0].down = 0;
    button[0].click = 0;
    button[0].color[0] = 0.0f;
    button[0].color[1] = 0.0f;
    button[0].color[2] = 0.0f;
    button[0].dcolor[0] = button[0].color[0] * 0.5f;
    button[0].dcolor[1] = button[0].color[1] * 0.5f;
    button[0].dcolor[2] = button[0].color[2] * 0.5f;
    button[0].text_color = 0x00ffffff;
    //High Score button
    button[1].r.width = BUTTON_WIDTH + 100;
    button[1].r.height = BUTTON_HEIGHT;
    button[1].r.left = 700 - button[1].r.width/2;
    button[1].r.bot = (BUTTON_B + 200);
    button[1].r.right =
            button[1].r.left + button[1].r.width;
    button[1].r.top =
            button[1].r.bot + button[1].r.height;
    button[1].r.centerx =
            (button[1].r.left + button[1].r.right) / 2;
    button[1].r.centery =
            (button[1].r.bot + button[1].r.top) / 2;
    strcpy(button[1].text, "HIGH SCORES");
    button[1].down = 0;
    button[1].click = 0;
    button[1].color[0] = 0.0f;
    button[1].color[1] = 0.0f;
    button[1].color[2] = 0.0f;
    button[1].dcolor[0] = button[1].color[0] * 1.5f;
    button[1].dcolor[1] = button[1].color[1] * 1.5f;
    button[1].dcolor[2] = button[1].color[2] * 1.5f;
    button[1].text_color = 0x00ffffff;
    //Credits button
    button[2].r.width = (BUTTON_WIDTH + 50);
    button[2].r.height = BUTTON_HEIGHT;
    button[2].r.left = 700 - button[2].r.width/2;
    button[2].r.bot = (BUTTON_B + 100);
    button[2].r.right =
            button[2].r.left + button[2].r.width;
    button[2].r.top =
            button[2].r.bot + button[2].r.height;
    button[2].r.centerx =
            (button[2].r.left + button[2].r.right) / 2;
    button[2].r.centery =
            (button[2].r.bot + button[2].r.top) / 2;
    strcpy(button[2].text, "Credits");
    button[2].down = 0;
    button[2].click = 0;
    button[2].color[0] = 0.0f;
    button[2].color[1] = 0.0f;
    button[2].color[2] = 0.0f;
    button[2].dcolor[0] = button[2].color[0] * 0.5f;
    button[2].dcolor[1] = button[2].color[1] * 0.5f;
    button[2].dcolor[2] = button[2].color[2] * 0.5f;
    button[2].text_color = 0x00ffffff;
    //Quit button
    button[3].r.width = BUTTON_WIDTH;
    button[3].r.height = BUTTON_HEIGHT;
    button[3].r.left = 700 - button[3].r.width/2;
    button[3].r.bot = BUTTON_B;
    button[3].r.right =
            button[3].r.left + button[3].r.width;
    button[3].r.top =
            button[3].r.bot + button[3].r.height;
    button[3].r.centerx =
            (button[3].r.left + button[3].r.right) / 2;
    button[3].r.centery =
            (button[3].r.bot + button[3].r.top) / 2;
    strcpy(button[3].text, "Exit");
    button[3].down = 0;
    button[3].click = 0;
    button[3].color[0] = 0.0f;
    button[3].color[1] = 0.0f;
    button[3].color[2] = 0.0f;
    button[3].dcolor[0] = button[3].color[0] * 0.5f;
    button[3].dcolor[1] = button[3].color[1] * 0.5f;
    button[3].dcolor[2] = button[3].color[2] * 0.5f;
    button[3].text_color = 0x00ffffff;
}

void button_render(void)
{
    //add render function to render button
    for (int i = 0; i < MAXBUTTONS; i++) {
        if (button[i].over) {
            //create the highlight color of button
            glColor3f(1.0f, 1.0f, 1.0f);
            //draw a highlight around the button
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
            glVertex2i(button[i].r.left-2,  button[i].r.bot-2);
            glVertex2i(button[i].r.left-2,  button[i].r.top+2);
            glVertex2i(button[i].r.right+2, button[i].r.top+2);
            glVertex2i(button[i].r.right+2, button[i].r.bot-2);
            glVertex2i(button[i].r.left-2,  button[i].r.bot-2);
            glEnd();
            glLineWidth(2);
            button[i].text_color = 0x00fff333;

        }
        if (button[MAXBUTTONS - 1].over)
            button[i].text_color = 0x00ff0000;

        glBegin(GL_QUADS);
        if (button[i].down) {
            glColor3fv(button[i].dcolor);
        } else {
            glColor3fv(button[i].color);
        }
        glVertex2i(button[i].r.left,  button[i].r.bot);
        glVertex2i(button[i].r.left,  button[i].r.top);
        glVertex2i(button[i].r.right, button[i].r.top);
        glVertex2i(button[i].r.right, button[i].r.bot);
        glEnd();
        Rect r;
        r.left = button[i].r.centerx;
        r.bot  = button[i].r.centery-8;
        r.center = 1;
        if (button[i].down) {
            ggprint16(&r, 0, button[i].text_color, "Pressed!");
        } else {
            ggprint16(&r, 0, button[i].text_color, button[i].text);
        }
    }
}

void gameMenu(int x, int y, GLuint mTexture)
{
    glPushMatrix();
    drawImage(mTexture, x, y);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    button_init();
    button_render();
}

void mouse_click(int action, Play& p)
{
    if (p.gameState == MENU) {
        if (action == 1) {
            //center of menu
            for (int i=0; i<MAXBUTTONS; i++) {
                if (button[i].over) {
                    button[i].down = 1;
                    button[i].click = 1;
                    if (i == 0) {
                        p.gameState = PLAY ;
                        break;
                    }
                    if (i == 1) {
                        p.gameState = HIGHSCORES;
                        break;
                    }
                    if (i == 2) {
                        p.gameState = CREDITS;
                        break;
                    }
                    if (i == 3) {
                        exit(0);
                    }
                }
            }
        }
    }
}

void check_Button(XEvent *e, Play& p)
{
    static int savex = 0;
    static int savey = 0;
    int x,y,i;
    int lbutton=0;
    int rbutton=0;
    //when mouse button is release
    if (e->type == ButtonRelease) {
        mouse_click(2, p);
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
        button[i].over=0;
        button[i].down=0;

        if (x >= button[i].r.left &&
            x <= button[i].r.right &&
            y >= button[i].r.bot &&
            y <= button[i].r.top) {
            button[i].over=1;
            break;
        }
    }
    if (lbutton)
        mouse_click(1, p);
    if (rbutton)
        mouse_click(2, p);

}



/*
// This is my Fridday code.
// I have added a functoin that to display a timer by seconds and store the Game timer for the user on the screen
//
void GameTimer() {
    time_t sec;
    // To store the timing in the score file:
    time(&sec);
    cout << ("Timer Seconds: ", sec);
}
// Display seconds on the screen to let the user see their timing on the game.
// Domentoin needs to be updated
void displaySeconds() {
    Rect n;
    n.bot = 500;
    n.left = 460;
    n.center = 0;
    ggprint8b(&n, 10, 0x00fffff, "Timer: ");
}
*/

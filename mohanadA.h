// Date: 11/17/2019

#ifndef MOHANAD_H
#define MOHANAD_H

#include "fonts.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include "mohanadA.h"
#include <GL/glu.h>
#include "Image.h"
#include "aliA.h"
#include <GL/gl.h>
#include <GL/glx.h>
//-------------------------------------------------
#define BUTTON_WIDTH 50
#define BUTTON_HEIGHT 50
#define BUTTON_B 400
// Defining 4 buttons
#define MAXBUTTONS 4
//------------------------

extern void drawImage(GLuint, int, int);

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

#endif

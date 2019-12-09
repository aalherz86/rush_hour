//
//program: asteroids.cpp
//author:  Gordon Griesel
//date:    2014 - 2018
//mod spring 2015: added constructors
//This program is a game starting point for a 3350 project.
//
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl->h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include <fstream>
#include <string>
#include "Image.h"
#include "aliA.h"
using namespace std;

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
						(c)[1]=(a)[1]-(b)[1]; \
						(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
const int MAX_BULLETS = 11;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------

/**************** External functions *****************************/
extern void showCredit();
extern void showMcredit();
extern void displayName();
extern void highscore (int, int*);
extern void writeScores(int, vector<int>);
extern vector<int> getHighscore ();
extern void displayHighscores();
extern void drawImage(GLuint, int, int);
extern int updatedScores (int, char[]);
extern void gameMenu(int, int, GLuint);
extern void check_Button(XEvent* , Play& );
extern void drawVehicle(int, int);
extern void initCreditScreen();
extern void drawCredit(int, int );
extern void initTiles(void);
extern void renderLevel(int);
extern void checkBtn(XEvent* , Play& );
extern void imgInit(GLuint, Image&);


/****************************************************************/


/**************** Declaration of classes' objects *****************************/
Image img[4] = {
"./images/highscore.png",
"./images/menu.png",
"./images/credit.png",
"./images/gameover.png"
};
Play play;



/******************************************************************************/

class Global {
public:
int showCredit;
	int displayscores;

	GLuint highscoreTexture;
	GLuint creditTex;
	GLuint gOverTex;
	int showScores;
	int xres, yres;
	char keys[65536];
    GLuint menuTexture;
    int vehicleX = 0, vehicleY = 0;

    static Global * GetInstance()
    {
        if (!instance)
            instance = new Global();
        return instance;
    }
private:
    static Global * instance;
	Global() {

		xres = 1400;
		yres = 1000;
		memset(keys, 0, 65536);
	}
    Global(Global const& copy);
    Global & operator=(Global const& copy);
};
Global* Global::instance = 0;
Global * gl = Global::GetInstance();

class Car {
public:
	Vec dir;
	Vec pos;
	Vec vel;
	float angle;
	float color[3];
public:
	Car() {
		VecZero(dir);
		pos[0] = (Flt)(gl->xres/2)+575;
		pos[1] = (Flt)(gl->yres/2);
		pos[2] = 0.0f;
		VecZero(vel);
		angle = 0.0;
		color[0] = color[1] = color[2] = 1.0;
	}
};




class Game {
public:
	Car car;
    vector<int> highscores;
    int score,lives;
	int nasteroids;
	int nbullets;
	struct timespec bulletTimer;
	struct timespec mouseThrustTimer;
	bool mouseThrustOn;
public:
	Game() {
        highscores = getHighscore();
        lives = 3;
		clock_gettime(CLOCK_REALTIME, &bulletTimer);
	}
	~Game() {

	}
} g;

//X Windows variables
class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() { }
	X11_wrapper(int w, int h) {
		GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		XSetWindowAttributes swa;
		setup_screen_res(gl->xres, gl->yres);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			std::cout << "\n\tcannot connect to X server" << std::endl;
			exit(EXIT_FAILURE);
		}
		Window root = DefaultRootWindow(dpy);
		XWindowAttributes getWinAttr;
		XGetWindowAttributes(dpy, root, &getWinAttr);
		int fullscreen=0;
		gl->xres = w;
		gl->yres = h;
		if (!w && !h) {
			//Go to fullscreen.
			gl->xres = getWinAttr.width;
			gl->yres = getWinAttr.height;
			//When window is fullscreen, there is no client window
			//so keystrokes are linked to the root window.
			XGrabKeyboard(dpy, root, False,
				GrabModeAsync, GrabModeAsync, CurrentTime);
			fullscreen=1;
		}
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			std::cout << "\n\tno appropriate visual found\n" << std::endl;
			exit(EXIT_FAILURE);
		} 
		Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
			PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
			StructureNotifyMask | SubstructureNotifyMask;
		unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
		if (fullscreen) {
			winops |= CWOverrideRedirect;
			swa.override_redirect = True;
		}
		win = XCreateWindow(dpy, root, 0, 0, gl->xres, gl->yres, 0,
			vi->depth, InputOutput, vi->visual, winops, &swa);
		//win = XCreateWindow(dpy, root, 0, 0, gl->xres, gl->yres, 0,
		//vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		set_title();
		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
		show_mouse_cursor(1);
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void set_title() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		XStoreName(dpy, win, "Asteroids template");
	}
	void check_resize(XEvent *e) {
		//The ConfigureNotify is sent by the
		//server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;
		if (xce.width != gl->xres || xce.height != gl->yres) {
			//Window size did change.
			reshape_window(xce.width, xce.height);
		}
	}
	void reshape_window(int width, int height) {
		//window has been resized.
		setup_screen_res(width, height);
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, gl->xres, 0, gl->yres, -1, 1);
		set_title();
	}
	void setup_screen_res(const int w, const int h) {
		gl->xres = w;
		gl->yres = h;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void set_mouse_position(int x, int y) {
		XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
	}
	void show_mouse_cursor(const int onoff) {
		if (onoff) {
			//this removes our own blank cursor.
			XUndefineCursor(dpy, win);
			return;
		}
		//vars to make blank cursor
		Pixmap blank;
		XColor dummy;
		char data[1] = {0};
		Cursor cursor;
		//make a blank cursor
		blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
		if (blank == None)
			std::cout << "error: out of memory." << std::endl;
		cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
		XFreePixmap(dpy, blank);
		//this makes you the cursor. then set it using this function
		XDefineCursor(dpy, win, cursor);
		//after you do not need the cursor anymore use this function.
		//it will undo the last change done by XDefineCursor
		//(thus do only use ONCE XDefineCursor and then XUndefineCursor):
	}
} x11(1400, 1000);

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void render();


//==========================================================================
// M A I N
//==========================================================================
int main()
{
	logOpen();
	init_opengl();
	srand(time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	x11.set_mouse_position(100,100);
	int done=0;
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			check_mouse(&e);
			done = check_keys(&e);
		}
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		timeCopy(&timeStart, &timeCurrent);
		physicsCountdown += timeSpan;
		while (physicsCountdown >= physicsRate) {
			physics();
			physicsCountdown -= physicsRate;
		}
		render();
		x11.swapBuffers();
	}
	cleanup_fonts();
	logClose();
	return 0;
}

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, gl->xres, gl->yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, gl->xres, 0, gl->yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen to black
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	// initiate texture
	
	glGenTextures(1, &gl->highscoreTexture);
	glBindTexture(GL_TEXTURE_2D, gl->highscoreTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		img[0].width, img[0].height,
		0, GL_RGB, GL_UNSIGNED_BYTE, img[0].data);
	//

    // menu init
    glGenTextures(1, &gl->menuTexture);
    glBindTexture(GL_TEXTURE_2D, gl->menuTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 img[1].width, img[1].height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, img[1].data);

// menu init
    glGenTextures(1, &gl->creditTex);
    glBindTexture(GL_TEXTURE_2D, gl->creditTex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 img[1].width, img[2].height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, img[2].data);

// menu init
    glGenTextures(1, &gl->gOverTex);
    glBindTexture(GL_TEXTURE_2D, gl->gOverTex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 img[1].width, img[3].height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, img[3].data);



    //imgInit(gl->creditTex, img[1]);
    // init tiles
    initTiles();
    initCreditScreen();


}

void normalize2d(Vec v)
{
	Flt len = v[0]*v[0] + v[1]*v[1];
	if (len == 0.0f) {
		v[0] = 1.0;
		v[1] = 0.0;
		return;
	}
	len = 1.0f / sqrt(len);
	v[0] *= len;
	v[1] *= len;
}

void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;

	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {

		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	//keys[XK_Up] = 0;
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
        savex = e->xbutton.x;
        savey = e->xbutton.y;
	}
    if (play.gameState == MENU) {
        check_Button(e, play);
    }
    if (play.gameState == CREDITS) {
        checkBtn(e, play);
    }
}

int check_keys(XEvent *e)
{
	//keyboard input?
	static int shift=0;
	int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
	//Log("key: %i\n", key);
	if (e->type == KeyRelease) {
		gl->keys[key]=0;
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return 0;
	}
	if (e->type == KeyPress) {
		gl->keys[key]=1;
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift=1;
			return 0;
		}
	} else {
		return 0;
	}
	if (shift){}
	switch (key) {
		case XK_Escape:
			writeScores(g.score, g.highscores);
			return 1;
		case XK_c:
		gl->showCredit ^= 1;
            play.gameState ^= CREDITS;
			break;
		case XK_h:
		gl->showScores ^= 1;
			gl->displayscores ^= 1;
            play.gameState ^= HIGHSCORES;
			break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
	}
	return 0;
}



void physics()
{

	//Update ship position
	g.car.pos[0] += g.car.vel[0];
	g.car.pos[1] += g.car.vel[1];
	//Check for collision with window edges
	if (g.car.pos[0] < 0.0) {
		g.car.pos[0] = 15.0;
		g.lives--;
	}
	else if (g.car.pos[0] > (float)gl->xres) {
		g.car.pos[0] = (float)gl->xres -15;
        g.lives--;
	}
	else if (g.car.pos[1] < 0.0) {
		g.car.pos[1] =  15;
        g.lives--;
	}
	else if (g.car.pos[1] > (float)gl->yres) {
		g.car.pos[1] = (float)gl->yres - 15;
        g.lives--;
	}

	/*else if(g.car.pos[0] > 200 && g.car.pos[0] > 0 && g.car.pos[1] < 300 && g.car.pos[1] < 400   ) {
	    g.car.pos[0] = 159;
	}*/





	//---------------------------------------------------
	//check keys pressed now
	if (gl->keys[XK_Left]) {
		g.car.angle += 4.0;
		if (g.car.angle >= 360.0f)
			g.car.angle -= 360.0f;
	}
	if (gl->keys[XK_Right]) {
		g.car.angle -= 4.0;
		if (g.car.angle < 0.0f)
			g.car.angle += 360.0f;
	}
    //convert ship angle to radians
    Flt rad = ((g.car.angle+90.0) / 360.0f) * PI * 2.0;
    //convert angle to a vector
    Flt xdir = cos(rad);
    Flt ydir = sin(rad);
    Flt speed = sqrt(g.car.vel[0]*g.car.vel[0]+
                     g.car.vel[1]*g.car.vel[1]);
	if (gl->keys[XK_Up]) {
		g.car.vel[0] += xdir*4.2f;
		g.car.vel[1] += ydir*4.2f;
		g.score++;

		if (speed > 10.0f) {
			speed = 10.0f;
			normalize2d(g.car.vel);
			g.car.vel[0] *= speed;
			g.car.vel[1] *= speed;
		}
        if (speed >0) {
            g.car.vel[0] += xdir * 0.3f;
            g.car.vel[1] += ydir * 0.3f;
            // speed =0;
            normalize2d(g.car.vel);
            g.car.vel[0] *= speed;
            g.car.vel[1] *= speed;
        }
	} else {
	    if (speed >0) {
            g.car.vel[0] += xdir * 0.2f;
            g.car.vel[1] += ydir * 0.2f;
           // speed =0;
            normalize2d(g.car.vel);
            g.car.vel[0] *= speed;
            g.car.vel[1] *= speed;
        }

	}

	if (gl->keys[XK_Down]) {
        g.car.vel[0] -= xdir*0.02f;
        g.car.vel[1] -= ydir*0.02f;

        if (speed > 10.0f) {
            speed = 10.0f;
            normalize2d(g.car.vel);
            g.car.vel[0] *= speed;
            g.car.vel[1] *= speed;
        }
	}

	if (gl->keys[XK_space]) {

	}
	if (g.mouseThrustOn) {

	}
}

void render()
{
    switch (play.gameState) {
        case MENU:
            gameMenu(gl->xres,gl->yres,gl->menuTexture);
            break;
        case CREDITS:
            //glClear(GL_COLOR_BUFFER_BIT);
            drawCredit(gl->xres, gl->yres);
/*
            showCredit();
            showMcredit();
            displayName();
*/

            break;
        case PLAY:

            Rect r;
            glClear(GL_COLOR_BUFFER_BIT);
            renderLevel(gl->yres);
            //
            r.bot = gl->yres - 20;
            r.left = 10;
            r.center = 0;
            ggprint8b(&r, 16, 0x00ff0000, "Score: %i", g.score);
            ggprint8b(&r, 16, 0x00ff0000, "lives: %i", g.lives);
            ggprint8b(&r, 16, 0x00ffff00, "H -- High Scores: ");
            ggprint8b(&r, 16, 0x00ffff00, "C -- credit");
            //ggprint8b(&r, 16, 0x00ffff00, "Down --- Slow");
            //-------------------------------------------------------------------------



            //Draw the car
            glColor3fv(g.car.color);
            glPushMatrix();
            glTranslatef(g.car.pos[0], g.car.pos[1], g.car.pos[2]);
            //float angle = atan2(car.dir[1], car.dir[0]);
            glRotatef(g.car.angle, 0.0f, 0.0f, 1.0f);
            drawVehicle(gl->vehicleX, gl->vehicleY);
            glEnd();
            glPopMatrix();
            if (g.lives == 0) {
                //play.gameState = GAMEOVER;
            }


            break;
        case HIGHSCORES:
            drawImage(gl->highscoreTexture, gl->xres, gl->yres);
            displayHighscores();
            break;
        case GAMEOVER:
           // drawImage(gl->gOverTex, gl->xres, gl->yres);

            break;


    }

}




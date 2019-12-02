// Ali Alherz
/* the debugging steps:
 * 1. recognize that a bug exists.
 * 2. isolate the bad code.
 * 3. fix bad codes.
 * 4. test the source code.
 */

#include "fonts.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <GL/glu.h>
#include <string.h>
#include "aliA.h"
#include "Image.h"
using namespace std;

class aliGlobal {
public:
    Image * tree;
    GLuint treeTex;
    Image * turn1;
    GLuint turn1Tex;
    Image * turn2;
    GLuint turn2Tex;
    Image * turn3;
    GLuint turn3Tex;
    Image * roadHor;
    GLuint roadHorTex;
    Image * roadHor1;
    GLuint roadHor1Tex;
    Image * roadVer;
    GLuint roadVerTex;
    Image * turn4;
    GLuint turn4Tex;
    Image * roadVer1;
    GLuint roadVer1Tex;
    Image * turn5;
    GLuint turn5Tex;
    Image * turn6;
    GLuint turn6Tex;
    Image * turn7;
    GLuint turn7Tex;
    Image * turn8;
    GLuint turn8Tex;
    Image * grass;
    GLuint grassTex;

    static aliGlobal * GetInstance()
    {
        if (!instance)
            instance = new aliGlobal();
        return instance;
    }
private:
    static aliGlobal * instance;
    aliGlobal() {
    }
    aliGlobal(aliGlobal const& copy);
    aliGlobal & operator=(aliGlobal const& copy);

};
aliGlobal* aliGlobal::instance = 0;
aliGlobal * agl = aliGlobal::GetInstance();

Image aImg[15] = {
        "./images/track/tree.png",
        "./images/track/road_asphalt-turn.png",
        "./images/track/road_asphalt-hor.png",
        "./images/track/road_asphalt-turn1.png",
        "./images/track/road_asphalt-turn2.png",
        "./images/track/road_asphalt-turn3.png",
        "./images/track/road_asphalt-ver.png",
        "./images/track/road_asphalt-hor1.png",
        "./images/track/turn4.png",
        "./images/track/roadVer1.png",
        "./images/track/turn5.png",
        "./images/track/turn6.png",
        "./images/track/turn7.png",
        "./images/track/turn8.png",
        "./images/track/grass.png",

};

class Level {
public:
    unsigned char arr[22][22];
    int nrows, ncols;
    int tilesize[2];
    Level() {
        //Log("Level constructor\n");
        tilesize[0] = 64;
        tilesize[1] = 64;
        //read level
        FILE *fpi = fopen("level1.txt","r");
        if (fpi) {
            nrows=0;
            char line[100];
            while (fgets(line, 100, fpi) != NULL) {
                removeCrLf(line);
                int slen = strlen(line);
                ncols = slen;
                //Log("line: %s\n", line);
                for (int j=0; j<slen; j++) {
                    arr[nrows][j] = line[j];
                }
                ++nrows;
            }
            fclose(fpi);
            //printf("nrows of backtree data: %i\n", nrows);
        }
        for (int i=0; i<nrows; i++) {
            for (int j=0; j<ncols; j++) {
                printf("%c", arr[i][j]);
            }
            printf("\n");
        }
    }
    void removeCrLf(char *str) {
        //remove carriage return and linefeed from a Cstring
        char *p = str;
        while (*p) {
            if (*p == 10 || *p == 13) {
                *p = '\0';
                break;
            }
            ++p;
        }
    }
} lev;


void initTiles ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);

    glBindTexture(GL_TEXTURE_2D, 0);
    //load the images file into a ppm structure.
    /***************************tree************************************/
    int w = aImg[0].width;
    int h = aImg[0].height;
    agl->tree = &aImg[0];
    glGenTextures(1, &agl->treeTex);
    glBindTexture(GL_TEXTURE_2D, agl->treeTex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->tree->data);

    /***************************road-hor*********************************/
    w = aImg[2].width;
    h = aImg[2].height;
    agl->roadHor = &aImg[2];
    glGenTextures(1, &agl->roadHorTex);
    glBindTexture(GL_TEXTURE_2D, agl->roadHorTex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->roadHor->data);
    /***************************road-turn1***************************/
     w = aImg[3].width;
    h = aImg[3].height;
    agl->turn1 = &aImg[3];
    glGenTextures(1, &agl->turn1Tex);
glBindTexture(GL_TEXTURE_2D, agl->turn1Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn1->data);
    /***************************road-turn2***************************/
    w = aImg[4].width;
    h = aImg[4].height;
    agl->turn2 = &aImg[4];
    glGenTextures(1, &agl->turn2Tex);
glBindTexture(GL_TEXTURE_2D, agl->turn2Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn2->data);
    /***************************road-turn3***************************/
   w = aImg[5].width;
    h = aImg[5].height;
    agl->turn3 = &aImg[5];
    glGenTextures(1, &agl->turn3Tex);
glBindTexture(GL_TEXTURE_2D, agl->turn3Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn3->data);
    /***************************road-ver*********************************/
    w = aImg[6].width;
    h = aImg[6].height;
    agl->roadVer = &aImg[6];
    glGenTextures(1, &agl->roadVerTex);
glBindTexture(GL_TEXTURE_2D, agl->roadVerTex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->roadVer->data);
    /***************************road-hor*********************************/
    w = aImg[7].width;
    h = aImg[7].height;
    agl->roadHor1 = &aImg[7];
    glGenTextures(1, &agl->roadHor1Tex);
glBindTexture(GL_TEXTURE_2D, agl->roadHor1Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->roadHor1->data);
    /***************************road-turn4*********************************/
    w = aImg[8].width;
    h = aImg[8].height;
    agl->turn4 = &aImg[8];
    glGenTextures(1, &agl->turn4Tex);
glBindTexture(GL_TEXTURE_2D, agl->turn4Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn4->data);
    /***************************road-roadVer1*********************************/
    w = aImg[9].width;
    h = aImg[9].height;
    agl->roadVer1 = &aImg[9];
    glGenTextures(1, &agl->roadVer1Tex);
    glBindTexture(GL_TEXTURE_2D, agl->roadVer1Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->roadVer1->data);
/***************************road-turn5Tex*********************************/
    w = aImg[10].width;
    h = aImg[10].height;
    agl->turn5 = &aImg[10];
    glGenTextures(1, &agl->turn5Tex);
    glBindTexture(GL_TEXTURE_2D, agl->turn5Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn5->data);
/***************************road-turn6Tex*********************************/
    w = aImg[11].width;
    h = aImg[11].height;
    agl->turn6 = &aImg[11];
    glGenTextures(1, &agl->turn6Tex);
    glBindTexture(GL_TEXTURE_2D, agl->turn6Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn6->data);
/***************************road-turn7Tex*********************************/
    w = aImg[12].width;
    h = aImg[12].height;
    agl->turn7 = &aImg[12];
    glGenTextures(1, &agl->turn7Tex);
    glBindTexture(GL_TEXTURE_2D, agl->turn7Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn7->data);
/***************************road-turn8Tex*********************************/
    w = aImg[13].width;
    h = aImg[13].height;
    agl->turn8 = &aImg[13];
    glGenTextures(1, &agl->turn8Tex);
    glBindTexture(GL_TEXTURE_2D, agl->turn8Tex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->turn8->data);
/***************************road-grass*********************************/
    w = aImg[14].width;
    h = aImg[14].height;
    agl->grass = &aImg[14];
    glGenTextures(1, &agl->grassTex);
    glBindTexture(GL_TEXTURE_2D, agl->grassTex);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, agl->grass->data);



}




void tileCenter(const int i, const int j, int center[2])
{
    int size0 = 64;
    int size1 = 64;

    center[0] = size0;
    center[1] = size1;
    center[0] *= j;
    center[1] *= i;
}

void renderLevel(int yres)
{
    int tileSize = 64;
    int center[2];

    for (int i = 0; i < 22 ; i++) {
        for (int j = 0; j < 22 ; j++) {

            switch (lev.arr[i][j]) {
                case ('b'):
                    glColor3f(1.0, 1.0, 1.0);
                    glBindTexture(GL_TEXTURE_2D, agl->treeTex);
                    tileCenter(i,j,center);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('h'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->roadHorTex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('v'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->roadVerTex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('s'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn1Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('t'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn2Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);
                    glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);
                    glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);
                    glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('u'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn3Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('1'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->roadHor1Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('2'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn4Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('3'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->roadVer1Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('4'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn5Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('5'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn6Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('6'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn7Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('7'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->turn8Tex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;
                case ('8'):
                    glColor3f(1.0, 1.0, 1.0);
                    //put tile in its place
                    tileCenter(i,j,center);
                    glBindTexture(GL_TEXTURE_2D, agl->grassTex);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);glVertex2i(center[0],yres-center[1]-tileSize);
                    glTexCoord2f(0.0f, 1.0f);glVertex2i(center[0],yres-center[1]);
                    glTexCoord2f(1.0f, 1.0f);glVertex2i(center[0]+tileSize,yres-center[1]);
                    glTexCoord2f(1.0f, 0.0f);glVertex2i(center[0]+tileSize,yres-center[1]-tileSize);
                    glEnd();
                    break;

            }
        }
    }
}


// My friday code
Play::Play() {
    gameState = MENU;
}




// getting current highscores
vector<int> getHighscore ()
{
	ifstream myfile("highscores.txt");
	vector<int> scores (5);

	for (int i = 0; i < 5; i++)
	{
		myfile >> scores[i];
	}
	return scores;
}

// finding the minimum score
int findMin(vector<int> myVector) 
{     
	int min = myVector[0]; 
	for (size_t i = 1; i < myVector.size(); i++) 
		if (myVector[i] < min) 
			min = myVector[i]; 
	return min; 
} 

// save scores to txt file
void writeScores(int score, vector<int> scores)
{
	int last = findMin(scores); 

	if (score > last)
		scores.push_back (score);

	// sorting in descending order
	sort(scores.begin(), scores.end(), greater<int>());

	// open txt file 
	ofstream myfile ("highscores.txt");

	if (myfile.is_open()) {
		for (auto x : scores) {
			myfile << x <<"\n";
		}
		myfile.close();
	}
}

void showCredit() 
{
	Rect n;

	n.bot = 600;
	n.left = 820;
	n.center = 0;
	ggprint8b(&n, 16, 0x00ffffff, "Ali Alherz");
}


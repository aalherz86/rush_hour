
/*
Created By: Nickolas Larson
Date: 10/28/2019


*/

#ifndef MAP_H
#define MAP_H

#include <string>
#include "Image.h"

struct Tile {
    GLuint texture;
    bool walkable;
    Tile(){}
    void initTile(const char * _imgSrc, bool _walkable);
};

class Map {
  
    private:

     //holds all possible textures in the map
    Tile tiles[16];
     
    //2d array that makes up the map
    //each element is an index to the tiles array
    int map[][102];

    public:

    Map();

    void drawMap(int xres, int yres, int xpos, int ypos);
    //checks to see if the player is allowed to walk on a requested tile
    bool isWalkable(int x, int y);

};


#endif

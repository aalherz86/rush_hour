//
// Created by aalherz on 11/17/19.
//

#ifndef RUSH_HOUR_ALIA_H
#define RUSH_HOUR_ALIA_H

#include <GL/gl.h>
#include <GL/glu.h>


class Image {
public:
    int width, height;
    unsigned char *data;
    Image() {}
    ~Image();
    Image(const char *fname);
    void GenerateGLTexture(GLuint & texture);
    static void GenerateGLTextureALPHA(GLuint & texture, const char * img);


}; // end of image class


#endif //RUSH_HOUR_ALIA_H

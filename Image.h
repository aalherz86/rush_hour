//Author: Gordon Griesel
//Modified by: Ali Alherz

#ifndef RUSH_HOUR_IMAGE_H
#define RUSH_HOUR_IMAGE_H

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

		
};



#endif
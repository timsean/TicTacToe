//
//  texture.cpp
//  OpenGL2
//
//  Created by Tim on 12/29/14.
//  Copyright (c) 2014 Tim. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "texture.h"

using namespace std;

GLuint loadBmp(const char* imagePath) {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    
    // Actual RGB data
    unsigned char * data;
    
    // Open file
    FILE* imageFile = fopen(imagePath, "rb");
    if(!imageFile) {
        throw runtime_error((string)"Cannot open file: " + (string)imagePath + (string)"\n");
        return 0;
    }
    
    // Make sure file is BMP file
    if (fread(header, 1, 54, imageFile)!=54 || header[0]!='B' || header[1]!='M') {
        throw runtime_error((string)"Not a correct BMP file\n");
        return 0;
    }
    
    // Read ints from the byte array
    dataPos    = *(int*)&(header[10]);
    width      = *(int*)&(header[18]);
    height     = *(int*)&(header[22]);
    imageSize  = *(int*)&(header[34]);
    
    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way
    
    // Get image data
    data = new unsigned char [imageSize];
    fread(data, 1, imageSize, imageFile);
    
    // Close file
    fclose(imageFile);
    
    // Create texture
    GLuint textureId;
    glGenTextures(1, &textureId);
    
    // Load texture
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return textureId;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
GLuint loadDDS(const char* imagePath) {
    // Data read from the header of the BMP file
    unsigned char header[124]; // Each BMP file begins by a 54-bytes header
    unsigned int height;
    unsigned int width;
    unsigned int linearSize;
    unsigned int mipMapCount;
    unsigned int fourCC;
    
    // Open file
    FILE* imageFile = fopen(imagePath, "rb");
    if(!imageFile) {
        throw runtime_error((string)"Cannot open file: " + (string)imagePath + (string)"\n");
        return 0;
    }
    
    // Make sure file is DDS file
    char filecode[4];
    fread(filecode, 1, 4, imageFile);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(imageFile);
        return 0;
    }
    
    // Get surface description
    fread(&header, 124, 1, imageFile);
    
    height = *(unsigned int*)&(header[8]);
    width = *(unsigned int*)&(header[12]);
    linearSize = *(unsigned int*)&(header[16]);
    mipMapCount = *(unsigned int*)&(header[24]);
    fourCC = *(unsigned int*)&(header[80]);
    
    unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, imageFile);
	/* close the file pointer */
	fclose(imageFile);
    
	//unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch(fourCC)
	{
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break; 
        default: 
            free(buffer); 
            return 0; 
	}
    
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;
    
	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); level++)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);
        
		offset += size;
		width  /= 2;
		height /= 2;
        
		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;
        
	} 
    
	free(buffer);
    
    return textureId;
}
#pragma once

#include <GL/gl.h>

class bitmap
{
public:
	int nx;
	int ny;
	short planes;
	short bpp;
	GLubyte *data;
	GLubyte *LoadBMP(const char* fname);
	bitmap();
	~bitmap();
};
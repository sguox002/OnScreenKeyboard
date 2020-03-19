#include "StdAfx.h"
#include "bitmap.h"

bitmap::bitmap()
{
	nx=ny=0;
	data=0;
	planes=0;
	bpp=0;
}

bitmap::~bitmap()
{
	delete []data;
}

GLubyte* bitmap::LoadBMP(const char*fname)
{
	int total_bytes;
	int i;
	FILE* pFile = fopen(fname, "rb");
	if( pFile == 0 ) return 0;

	fseek(pFile, 18, SEEK_CUR);
	i = fread(&nx, 4, 1, pFile);
	i = fread(&ny, 4, 1, pFile);
	i = fread(&planes, 2, 1, pFile);
	i = fread(&bpp, 2, 1, pFile);
	fseek(pFile, 24, SEEK_CUR);
	total_bytes = nx*ny * (bpp/8);
	if(bpp!=32 && bpp!=24)
	{
		//MyMessageBox("bitmap format not supported");
		fclose(pFile);
        return 0;
	}
	if(data) {delete []data;data=0;}
	data=new GLubyte[total_bytes];
	if( fread(data, total_bytes, 1, pFile) <= 0 )
	{
		delete []data;
		data=0;
		fclose(pFile);
		return 0;
	}
	fclose(pFile);
	return data;
}
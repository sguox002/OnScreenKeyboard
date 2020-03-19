#ifndef OPENGL_H
#define OPENGL_H
//#include "stdafx.h"
#include "windows.h"

#include "gl/gl.h"
#include "gl/glu.h"
#include "glext.h"

namespace opengl
{
	typedef void (APIENTRY *PFNWGLEXTSWAPCONTROLPROC) (int);
	typedef int (*PFNWGLEXTGETSWAPINTERVALPROC) (void);
	extern PFNGLGENBUFFERSARBPROC pglGenBuffersARB ;                     // VBO Name Generation Procedure
	extern PFNGLBINDBUFFERARBPROC pglBindBufferARB ;                     // VBO Bind Procedure
	extern PFNGLBUFFERDATAARBPROC pglBufferDataARB ;                     // VBO Data Loading Procedure
	extern PFNGLBUFFERSUBDATAARBPROC pglBufferSubDataARB ;               // VBO Sub Data Loading Procedure
	extern PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB ;               // VBO Deletion Procedure
	extern PFNGLGETBUFFERPARAMETERIVARBPROC pglGetBufferParameterivARB ; // return various parameters of VBO
	extern PFNGLMAPBUFFERARBPROC pglMapBufferARB ;                       // map VBO procedure
	extern PFNGLUNMAPBUFFERARBPROC pglUnmapBufferARB ;                   // unmap VBO procedure
	extern PFNGLGENERATEMIPMAPPROC pglGenerateMipmap;
	#define glGenBuffersARB           pglGenBuffersARB
	#define glBindBufferARB           pglBindBufferARB
	#define glBufferDataARB           pglBufferDataARB
	#define glBufferSubDataARB        pglBufferSubDataARB
	#define glDeleteBuffersARB        pglDeleteBuffersARB
	#define glGetBufferParameterivARB pglGetBufferParameterivARB
	#define glMapBufferARB            pglMapBufferARB
	#define glUnmapBufferARB          pglUnmapBufferARB
	#define glGenerateMipmap		  pglGenerateMipmap
	
	extern PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT ;
	extern PFNWGLEXTGETSWAPINTERVALPROC wglGetSwapIntervalEXT ;
	
	//function pointer typdefs
	bool InitVSync();
	bool VSyncEnabled();
	void SetVSyncState(bool enable); //this is the only interface to user.
	bool is_vbo_supported();
	void GlBlender(bool enable);
	void GlText(float x, float y, const char *pStr);
	void GlTextInit(HDC hDC);
	BOOL SetupPixelFormat(HDC hDC, int mode);
	BOOL SetupPixelFormat(HDC hDC);
}
#endif
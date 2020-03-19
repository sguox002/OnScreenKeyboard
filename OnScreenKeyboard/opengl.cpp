#include "stdafx.h"
#include "afxwin.h"
#include "stdio.h"
#include "opengl.h"
#pragma comment(lib,"opengl32.lib")

namespace opengl
{
#ifdef _WIN32
	//VBO supporting & PBO uses the same stuff
	PFNGLGENBUFFERSARBPROC pglGenBuffersARB = 0;                     // VBO Name Generation Procedure
	PFNGLBINDBUFFERARBPROC pglBindBufferARB = 0;                     // VBO Bind Procedure
	PFNGLBUFFERDATAARBPROC pglBufferDataARB = 0;                     // VBO Data Loading Procedure
	PFNGLBUFFERSUBDATAARBPROC pglBufferSubDataARB = 0;               // VBO Sub Data Loading Procedure
	PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB = 0;               // VBO Deletion Procedure
	PFNGLGETBUFFERPARAMETERIVARBPROC pglGetBufferParameterivARB = 0; // return various parameters of VBO
	PFNGLMAPBUFFERARBPROC pglMapBufferARB = 0;                       // map VBO procedure
	PFNGLUNMAPBUFFERARBPROC pglUnmapBufferARB = 0;                   // unmap VBO procedure
	
	#define glGenBuffersARB           pglGenBuffersARB
	#define glBindBufferARB           pglBindBufferARB
	#define glBufferDataARB           pglBufferDataARB
	#define glBufferSubDataARB        pglBufferSubDataARB
	#define glDeleteBuffersARB        pglDeleteBuffersARB
	#define glGetBufferParameterivARB pglGetBufferParameterivARB
	#define glMapBufferARB            pglMapBufferARB
	#define glUnmapBufferARB          pglUnmapBufferARB

	// Framebuffer object
	PFNGLGENFRAMEBUFFERSPROC                     pglGenFramebuffers = 0;                      // FBO name generation procedure
	PFNGLDELETEFRAMEBUFFERSPROC                  pglDeleteFramebuffers = 0;                   // FBO deletion procedure
	PFNGLBINDFRAMEBUFFERPROC                     pglBindFramebuffer = 0;                      // FBO bind procedure
	PFNGLCHECKFRAMEBUFFERSTATUSPROC              pglCheckFramebufferStatus = 0;               // FBO completeness test procedure
	PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pglGetFramebufferAttachmentParameteriv = 0;  // return various FBO parameters
	PFNGLGENERATEMIPMAPPROC                      pglGenerateMipmap = 0;                       // FBO automatic mipmap generation procedure
	PFNGLFRAMEBUFFERTEXTURE2DPROC                pglFramebufferTexture2D = 0;                 // FBO texdture attachement procedure
	PFNGLFRAMEBUFFERRENDERBUFFERPROC             pglFramebufferRenderbuffer = 0;              // FBO renderbuffer attachement procedure
	// Renderbuffer object
	PFNGLGENRENDERBUFFERSPROC                    pglGenRenderbuffers = 0;                     // renderbuffer generation procedure
	PFNGLDELETERENDERBUFFERSPROC                 pglDeleteRenderbuffers = 0;                  // renderbuffer deletion procedure
	PFNGLBINDRENDERBUFFERPROC                    pglBindRenderbuffer = 0;                     // renderbuffer bind procedure
	PFNGLRENDERBUFFERSTORAGEPROC                 pglRenderbufferStorage = 0;                  // renderbuffer memory allocation procedure
	PFNGLGETRENDERBUFFERPARAMETERIVPROC          pglGetRenderbufferParameteriv = 0;           // return various renderbuffer parameters
	PFNGLISRENDERBUFFERPROC                      pglIsRenderbuffer = 0;                       // determine renderbuffer object type

	#define glGenFramebuffers                        pglGenFramebuffers
	#define glDeleteFramebuffers                     pglDeleteFramebuffers
	#define glBindFramebuffer                        pglBindFramebuffer
	#define glCheckFramebufferStatus                 pglCheckFramebufferStatus
	#define glGetFramebufferAttachmentParameteriv    pglGetFramebufferAttachmentParameteriv
	#define glGenerateMipmap                         pglGenerateMipmap
	#define glFramebufferTexture2D                   pglFramebufferTexture2D
	#define glFramebufferRenderbuffer                pglFramebufferRenderbuffer

	#define glGenRenderbuffers                       pglGenRenderbuffers
	#define glDeleteRenderbuffers                    pglDeleteRenderbuffers
	#define glBindRenderbuffer                       pglBindRenderbuffer
	#define glRenderbufferStorage                    pglRenderbufferStorage
	#define glGetRenderbufferParameteriv             pglGetRenderbufferParameteriv
	#define glIsRenderbuffer                         pglIsRenderbuffer


#endif
	PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT = NULL;
	PFNWGLEXTGETSWAPINTERVALPROC wglGetSwapIntervalEXT = NULL;
	
	//init VSync func
	bool InitVSync()
	{
		//get extensions of graphics card
		char* extensions = (char*)glGetString(GL_EXTENSIONS);
		
		//is WGL_EXT_swap_control in the string? VSync switch possible?
		if (strstr(extensions,"WGL_EXT_swap_control"))
		{
			//get address's of both functions and save them
			wglSwapIntervalEXT = (PFNWGLEXTSWAPCONTROLPROC)
				wglGetProcAddress("wglSwapIntervalEXT");
			wglGetSwapIntervalEXT = (PFNWGLEXTGETSWAPINTERVALPROC)
				wglGetProcAddress("wglGetSwapIntervalEXT");
			return true;
		}
		else
			return false;	
	}
	
	bool VSyncEnabled()
	{
		//if interval is positive, it is not 0 so enabled ;)
		return (wglGetSwapIntervalEXT()> 0);
	}
	
	void SetVSyncState(bool enable) //this is the only interface to user.
	{
		if(InitVSync())
		{
			if (enable)	wglSwapIntervalEXT(1); //set interval to 1 -&gt; enable
			else wglSwapIntervalEXT(0); //disable
		}
	}
	
	bool is_vbo_supported()
	{
		glGenBuffersARB = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferDataARB");
		glBufferSubDataARB = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubDataARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffersARB");
		glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetBufferParameterivARB");
		glMapBufferARB = (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBufferARB");
		glUnmapBufferARB = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBufferARB");
		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
		// check once again VBO extension
		if(glGenBuffersARB && glBindBufferARB && glBufferDataARB && glBufferSubDataARB &&
			glMapBufferARB && glUnmapBufferARB && glDeleteBuffersARB && glGetBufferParameterivARB)
		{
			//vboSupported = vboUsed = true;
			//cout << "Video card supports GL__vertex_buffer_object." << endl;
			printf("VBO is supported\n");
			return true;
		}
		else
		{
			//vboSupported = vboUsed = false;
			//cout << "Video card does NOT support GL__vertex_buffer_object." << endl;
			printf("VBO not supported\n");
			return false;
		}
	}

	void GlBlender(bool enable)
	{
		if(enable)
		{
			glEnable(GL_BLEND);
			glEnable(GL_POINT_SMOOTH);
			glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
		//	glEnable(GL_LINE_SMOOTH);
		//	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
			glEnable(GL_POLYGON_SMOOTH);
			glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
		}
		else
		{
			glDisable(GL_BLEND);
			glDisable(GL_POINT_SMOOTH);
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
		}
	}

	void GlText(float x, float y, const char *pStr)
	{
		if(strlen(pStr)!=0)
		{
			//glPushAttrib();
			//glPushMatrix();
			glListBase(1000);
			//glColor3f(1,1,0);
			glRasterPos2f(x, y); // Position
			glCallLists(strlen(pStr), GL_UNSIGNED_BYTE, pStr);   //Display
			//glPopAttrib();
			//glPopMatrix();
		}
	}

	void GlTextInit(HDC hDC)
	{
		wglUseFontBitmaps(hDC, 0, 128, 1000); // hDC = wglGetCurrentDC()
	}

	BOOL SetupPixelFormat(HDC hDC)
	{
		PIXELFORMATDESCRIPTOR pixelDesc=
		{
			sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
				PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				24,
				0,0,0,0,0,0,
				0,
				0,
				0,
				0,0,0,0,
				32,
				0,
				0,
				PFD_MAIN_PLANE,
				0,
				0,0,0
		};
		
		int pixelformat;
		
		if ( (pixelformat = ChoosePixelFormat(hDC, &pixelDesc)) == 0 )
		{
 			MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
			return FALSE;
		}
		
		if (SetPixelFormat(hDC, pixelformat, &pixelDesc) == FALSE)
		//if (SetPixelFormat(hDC, 6, &pixelDesc) == FALSE)
		//if (SetPixelFormat(hDC, 9, &pixelDesc) == FALSE)
		{
			MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
			return FALSE;
		}
		return TRUE;
	}

	BOOL SetupPixelFormat(HDC hDC, int mode)
	{
		PIXELFORMATDESCRIPTOR pixelDesc=
		{
			sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
				PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				24,
				0,0,0,0,0,0,
				0,
				0,
				0,
				0,0,0,0,
				32,
				0,
				0,
				PFD_MAIN_PLANE,
				0,
				0,0,0
		};
		
		int pixelformat;
		
		if ( (pixelformat = ChoosePixelFormat(hDC, &pixelDesc)) == 0 )
		{
			MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
			return FALSE;
		}
		
		if (SetPixelFormat(hDC, mode, &pixelDesc) == FALSE)
		{
			MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
			return FALSE;
		}
		return TRUE;
	}

}
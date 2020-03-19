#include "StdAfx.h"

#include <afxwin.h>
#include "opengl.h"
#include "glwin.h"
#include "bitmap.h"
#include "resource.h"

using namespace opengl;

#pragma warning(disable:4244)
//#pragma comment(lib,"glaux.lib")
 
//#define IDC_EDIT_ANNOTATION 0x2000

void glWin::clear()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void glWin::clear(float r,float g,float b)
{
	glClearColor(r, g, b, 1.0f);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void glWin::setup_ogl(HGLRC rcshare)
{
	hDC=::GetDC(m_hWnd);

	PIXELFORMATDESCRIPTOR pixelDesc =
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
			32,//
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
	};	

#ifdef AMD_GRAPHIC_CARD
	int n_PixelFormat = 14;
#else
	int n_PixelFormat = ::ChoosePixelFormat(hDC,&pixelDesc);
#endif	
	SetPixelFormat(hDC,n_PixelFormat,&pixelDesc);

	if(rcshare) hRC=rcshare;
	else hRC = wglCreateContext(hDC);


	wglMakeCurrent(hDC,hRC);
	opengl::is_vbo_supported();
	opengl::SetVSyncState(0);
	switch(font_selected)
	{
	case BitmapFont:
		SelectObject(hDC,GetStockObject(DEFAULT_GUI_FONT)); //choose different font here!
		wglUseFontBitmaps(hDC,0,256,1000); //256 characters with listbase 1000
		break;
	case TextureFont:
		LoadGLTextures();
		BuildFont();
		break;
	case OutlineFont:
		if(!pDC && !pText) //for repeatedly call setup_RC memory leak
		{
			pDC=new CDC();
			pDC->Attach(hDC);
			pText=new COutlineFont(pDC,"Tahoma Bold");
		}
		break;
	}
	/*
	if(!use_outlinefont)
	{
		SelectObject(hDC,GetStockObject(DEFAULT_GUI_FONT)); //choose different font here!
		wglUseFontBitmaps(hDC,0,256,1000); //256 characters with listbase 1000
		//glText=glText;
	}
	else
	{
	//use outline font!
		if(!pDC && !pText) //for repeatedly call setup_RC memory leak
		{
			pDC=new CDC();
			pDC->Attach(hDC);
			//pText=new COutlineFont(pDC,"Tahoma");
			//pText=new COutlineFont(pDC,"Helvetica");
			pText=new COutlineFont(pDC,"Arial");
		}
		//glText=COutlineFont::Text;
	}
	*/
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	wglMakeCurrent(NULL, NULL); 
}

glWin::glWin()
{
	pDC=0;
	pText=0;
	keep_same_fontsize=1;
	font_selected = OutlineFont;//BitmapFont;//OutlineFont;
	base=0;
	aspectRatio=0.0f;
	bNeedGenGLRC=1;
}

glWin::~glWin()
{
	release();
}

void glWin::release()
{
	delete pDC;pDC=0;
	delete pText;pText=0;
	if(base) 
	{
		KillFont();
		base=0;
	}
}
void glWin::glText(float x,float y,const char *s,float scalex,float scaley, float scale,float shx,float shy)
{
/*	if(use_outlinefont)
	{
		float sc=1.0;
		if(keep_same_fontsize)
		{
			sc=16*0.75/num_pixel_per_ogl;
		}
		pText->Text(x,y,s,sc*scale/(scalex*0.75),sc*scale/(scaley*0.75));
	}
	else
	{
		opengl::GlText(x,y,s);
	}
	*/
	float sc=1.0;
	if(keep_same_fontsize)
	{
		sc=16*0.75/num_pixel_per_ogl;
	}

	switch(font_selected)
	{
	case OutlineFont:
		pText->Text(x,y,s,sc*scale/(scalex*0.75),sc*scale/(scaley*0.75));
		break;
	case BitmapFont:
		//glPushMatrix();
		//glLoadIdentity();
		//glScalef(scalex, scaley, 1.0);
		opengl::GlText(x,y,s);
		//glPopMatrix();
		break;
	case TextureFont:
		//glPrint(x,y,s,0,sc*scale/(scalex*0.75),sc*scale/(scaley*0.75),shx,shy);
		glPrint(x,y,s,0,scalex,scaley,shx,shy);
		break;
	}
}

void glWin::setup_RC(int left_off,int right_off)
{
	float w,h;
	//float xmin,xmax,ymin,ymax;

	wglMakeCurrent(hDC,hRC);

	GetClientRect(&client_area);	
	glWinRect=client_area;
	glWinRect.left+=left_off;
	glWinRect.right-=right_off;
	w = glWinRect.right  - glWinRect.left;//-left_off-right_off;
	h = glWinRect.bottom - glWinRect.top;
	
	glViewport(glWinRect.top,glWinRect.left+left_off,w,h);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	aspectRatio = (GLfloat)w / (GLfloat)h;
	
	//make the origin in the center is good for flip!
	if (w <= h) 
	{
		ogl_xmin=-25;
		ogl_xmax=25;
		ogl_ymin=-25.0 / aspectRatio;
		ogl_ymax=25.0 / aspectRatio;
		num_pixel_per_ogl=w/50.0;
		glOrtho(ogl_xmin,ogl_xmax,ogl_ymin,ogl_ymax,-1,1);
	}
	else
	{
		ogl_xmin=-25.0 * aspectRatio;
		ogl_xmax=25.0 * aspectRatio;
		ogl_ymin=-25.0;
		ogl_ymax=25;
		num_pixel_per_ogl=h/50.0;
		//glOrtho (-25.0 * aspectRatio, 25.0 * aspectRatio, -50.0, 0.0, -50.0, 50.0);
		glOrtho(ogl_xmin,ogl_xmax,ogl_ymin,ogl_ymax,-1,1);
	}

	font_scale=16.0/num_pixel_per_ogl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		
	

	wglMakeCurrent(NULL,NULL);
}

void glWin::DoDataExchange(CDataExchange* pDX)
{
	CWnd::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(glWin)
//	DDX_Control(pDX, IDC_EDIT_ANNOTATION, m_Edit_Annotation);
	//}}AFX_DATA_MAP

}

void glWin::get_ogl_rgn(float *rgn)
{
	rgn[0]=ogl_xmin;
	rgn[1]=ogl_xmax;
	rgn[2]=ogl_ymin;
	rgn[3]=ogl_ymax;
}

float glWin::get_resol_x()
{
	return resol_x=(ogl_xmax-ogl_xmin)/(glWinRect.right-glWinRect.left)/scalex;
}

float glWin::get_resol_y()
{
	return resol_y=(ogl_ymax-ogl_ymin)/(glWinRect.bottom-glWinRect.top)/scaley;
}

BEGIN_MESSAGE_MAP(glWin, CWnd)
//{{AFX_MSG_MAP(glWin)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


int glWin::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    /*int Status=FALSE;                               // Status Indicator
    AUX_RGBImageRec *TextureImage;               // Create Storage Space For The Textures

    if (TextureImage=LoadBMP("Font.bmp"))
    {
		Status=TRUE;
        glGenTextures(1, &texture_font);          // Create Two Texture

	    glBindTexture(GL_TEXTURE_2D, texture_font);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
    }
	if (TextureImage)							// If Texture Exists
	{
		if (TextureImage->data)			// If Texture Image Exists
		{
			free(TextureImage->data);	// Free The Texture Image Memory
		}
		free(TextureImage);				// Free The Image Structure
	}
    return Status;                                  // Return The Status
	*/
	return LoadGLTextures("font.bmp",texture_font);
}

int glWin::LoadGLTextures(const char* bmpfname, GLuint& texture)                                    // Load Bitmaps And Convert To Textures
{
    int Status=FALSE;                               // Status Indicator
    //AUX_RGBImageRec *TextureImage;               // Create Storage Space For The Textures
	bitmap *TextureImage=new bitmap();
    //if (TextureImage=LoadBMP(bmpfname))
	if(TextureImage->LoadBMP(bmpfname))
    {
		Status=TRUE;
        glGenTextures(1, &texture);          // Create Two Texture
		
	    glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->nx, TextureImage->ny, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
    }
	delete TextureImage;
    return Status;                                  // Return The Status
}

int glWin::LoadGlTextureswAlpha( const char *bmpfname, GLuint& texture )
{
	int Status = FALSE;                               // Status Indicator
    //AUX_RGBImageRec *TextureImage;               // Create Storage Space For The Textures
	bitmap *TextureImage=new bitmap();
    //if (TextureImage = LoadBMP(bmpfname))
	if(TextureImage->LoadBMP(bmpfname))
    {
		Status = TRUE;

		unsigned char* TextureImageAlpha = new unsigned char[TextureImage->nx * TextureImage->ny * 4];
		int i = 0;
		while (i < TextureImage->nx * TextureImage->ny)
		{
			TextureImageAlpha[i*4] = TextureImage->data[i*3];
			TextureImageAlpha[i*4+1] = TextureImage->data[i*3+1];
			TextureImageAlpha[i*4+2] = TextureImage->data[i*3+2];
			if (TextureImageAlpha[i*4] + TextureImageAlpha[i*4+1] + TextureImageAlpha[i*4+2] == 0)
				TextureImageAlpha[i*4+3] = 0;
			else
				TextureImageAlpha[i*4+3] = 255;
			i++;
		}

        glGenTextures(1, &texture);          // Create Two Texture		
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->nx, TextureImage->ny, 0, GL_BGRA, GL_UNSIGNED_BYTE, TextureImageAlpha);

		delete[] TextureImageAlpha;
		
    }
	delete TextureImage;
	return Status;                      // Return The Status
}

GLvoid glWin::BuildFont(GLvoid)								// Build Our Font Display List
{
	float	cx;											// Holds Our X Character Coord
	float	cy;											// Holds Our Y Character Coord

	base=glGenLists(256);								// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, texture_font);			// Select Our Font Texture
	for (int loop=0; loop<256; loop++)						// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;						// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);				// Start Building A List
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(cx,1-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(14,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1-cy);			// Texture Coord (Top Right)
				glVertex2i(14,14);						// Vertex Coord (Top Right)
				glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
				glVertex2i(0,14);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(12,0,0);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
}

GLvoid glWin::KillFont(GLvoid)									// Delete The Font From Memory
{
	glDeleteLists(base,256);							// Delete All 256 Display Lists
}

//set=0: non-italic font, set=1: italic font
//note x,y coordinate is in physical coordinate & opengl mixed
GLvoid glWin::glPrint(float glx, float gly, const char *string, int set,float sx,float sy,float shx,float shy)	// Where The Printing Happens
{
	if (set>1)
	{
		set=1;
	}

	int x,y;
	
	gl2win(glx,gly,&x,&y,sx,sy,shx,shy);
	//y=glWinRect.bottom-y; //note opengl is up coordinate
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_font);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,glWinRect.right,0,glWinRect.bottom,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	
	glTranslated(x,glWinRect.bottom-y,0);								// Position The Text (0,0 - Bottom Left)
	//glRasterPos2f(x, glWinRect.bottom-y);
	//glScalef(scalex, scaley, 1.0);
	glListBase(base-32+(128*set));						// Choose The Font Set (0 or 1) 32 is the char space
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDisable(GL_TEXTURE_2D);
}

void glWin::gl2win(float glx,float gly,int *x,int *y,float sx,float sy,float shx,float shy)
{
	glx+=shx;//shiftx+img_shiftx;
	gly+=shy;//shifty;
	glx*=sx;
	gly*=sy;
	//ogl_ymin is the glwinRect.bottom, ogl_ymax is the glWinRect.top
	*x=(glx-ogl_xmin)*(glWinRect.right-glWinRect.left)/(ogl_xmax-ogl_xmin);
	*y=-(gly-ogl_ymax)*(glWinRect.bottom-glWinRect.top)/(ogl_ymax-ogl_ymin);
}

void glWin::win2gl(int winx, int winy, float *glx, float *gly)
{
	*glx = winx*(ogl_xmax-ogl_xmin)/(glWinRect.right-glWinRect.left) + ogl_xmin;
	*gly = -winy*(ogl_ymax-ogl_ymin)/(glWinRect.bottom-glWinRect.top) + ogl_ymax;
}

int glWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

void glWin::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CPoint scrPoint = point;
	ClientToScreen(&scrPoint);
	//CursorPos = scrPoint;
	//TRACE("glWin Mousemove %d %d\n",scrPoint.x,scrPoint.y);

	CWnd::OnMouseMove(nFlags, point);
}




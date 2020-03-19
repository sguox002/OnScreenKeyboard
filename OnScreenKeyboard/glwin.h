#pragma once
//this is a type of window rendered by opengl
//#include "gl\glaux.h"		// Header File For The Glaux Library
//glaux.lib deprecated, replaced it with my own code
#include "outlinefont.h"
#include <list>

class glWin:public CWnd
{
public:
	enum ogl_font {BitmapFont,TextureFont,OutlineFont};

protected:
	HGLRC hRC;
	HDC hDC;
	RECT client_area;

	COutlineFont *pText;
	CDC *pDC;
	bool use_outlinefont;
	ogl_font font_selected;
	GLuint texture_font;
	GLuint	base; //display list base for texture

	RECT glWinRect;

	float shiftx,shifty;
	float scalex,scaley;
	float resol_x,resol_y;
	float aspectRatio;

	float ogl_xmin,ogl_xmax,ogl_ymin,ogl_ymax;
	float num_pixel_per_ogl;
	bool keep_same_fontsize;
	float font_scale; //to use the font to scale some elements' coordinate
	int flip_lr,flip_ud;
	//float max_ogl_range; //maximum size of opengl range

	bool bNeedGenGLRC;
public:
	glWin();
	virtual ~glWin(); //need to be virtual to call derivative

	void clear();
	void clear(float r, float g, float b);
	virtual void update_data(int data_type)=0; //may have different implementation
	void setup_ogl(HGLRC rcshare=0);
	virtual void RenderScene()=0; //may have different implementation
	void glText(float x,float y,const char *s,float scalex=1.0,float scaley=1.0, float scale = 1.0f,float shx=0,float shy=0);
	void setup_RC(int left_off=0,int right_off=0);
	void set_shift(float dx,float dy) {shiftx=dx;shifty=dy;}
	void set_scale(float sx,float sy) {scalex=sx;scaley=sy;}
	void set_shiftx(float dx) {shiftx=dx;}
	void set_shifty(float dy) {shifty=dy;}
	void set_scalex(float sx) {scalex=sx;}
	void set_scaley(float sy) {scaley=sy;}
	void get_ogl_rgn(float *rgn); 
	float get_shiftx() const {return shiftx;}
	float get_shifty() const {return shifty;}
	float get_scalex() const {return scalex;}
	float get_scaley() const {return scaley;}
	RECT get_glWinRect() const {return glWinRect;}
	HGLRC get_rc() const {return hRC;}
	//zoom operation
	void shift(float dx,float dy) {shiftx+=dx;shifty+=dy;}
	void scale(float sx,float sy) {scalex*=sx;scaley*=sy;}
	float get_pixel_per_ogl() const {return num_pixel_per_ogl;}

	float get_resol_x(); //calculate the pixel length in mm
	float get_resol_y();
	COutlineFont* get_ptext() {return pText;}
	void gl2win(float glx,float gly,int *x,int *y,float sx,float sy,float shx,float shy);	
	void win2gl(int winx, int winy, float *glx, float *gly);
	void choose_font(ogl_font fnt) {if(fnt>=BitmapFont &&fnt<=OutlineFont) font_selected=fnt;}
	void release();
protected:
	int LoadGLTextures(const char *bmpfname,GLuint& texture);
	int LoadGlTextureswAlpha(const char *bmpfname,GLuint& texture);

	//these are for 2D texture fonts
	//AUX_RGBImageRec *LoadBMP(const char *Filename);                // Loads A Bitmap Image
	int LoadGLTextures();                                    // Load Bitmaps And Convert To Textures
	GLvoid BuildFont(GLvoid);								// Build Our Font Display List
	GLvoid KillFont(GLvoid);									// Delete The Font From Memory
	GLvoid glPrint(float glx, float gly, const char *string, int set,float sx=1,float sy=1,float shx=0,float shy=0);	// Where The Printing Happens

public:
	//void set_max_ogl_range(float r) {max_ogl_range=r;}
	//const float get_ogl_range() const {return max_ogl_range;}
	//{{AFX_VIRTUAL(glWin)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL(glWin)
	
	// Generated message map functions
	//{{AFX_MSG(glWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};


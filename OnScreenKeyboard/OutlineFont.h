#ifndef _OutlineFont_h_
#define _OutlineFont_h_

#include <GL/gl.h>
#include <string.h>

// COutlineFont is a class which encapsulates the details necessary
// to draw outline font text in OpenGL on the Windows platform.


class COutlineFont 
{	
public:
	COutlineFont(
		CDC* dc, 
		char* fontname);
	virtual ~COutlineFont();
	
	void TextDisplay(POINT pt,double theta,CString text,float color_r,float color_g,float color_b, float scale);
	void TextDisplay(POINT pt,double theta,CString text,float color_r,float color_g,float color_b, float scaleX,float scaleY);
	void DrawString(char* s); 
	void Text(float x,float y,const char *str,float scalex,float scaley);
	void Text(float x,float y,float z, const char *str,float scalex,float scaley,float scalez);
private:
	GLuint m_listbase;
	CDC* m_pDC;
	
private:
	// Hide these.
	COutlineFont() { }
	COutlineFont(const COutlineFont& obj) { }
	COutlineFont& operator=(const COutlineFont& obj) { return *this; }
};

#endif

#include "StdAfx.h"
#include "afxwin.h"
#include "OutlineFont.h"

#pragma warning(disable:4244)

COutlineFont::COutlineFont(
						   CDC* dc, 
						   char* fontname)
{
	// Class constructor.
	// Stores each character in its own display list
	// for later drawing via the wglUseFontOutlines() call.

	if (dc && fontname && strlen(fontname) > 0) {

		m_pDC = dc;
		m_listbase = glGenLists(256);

		//GL_INVALID_VALUE 
		//GL_INVALID_OPERATION  

		// Setup the Font characteristics
		LOGFONT logfont;
		GLYPHMETRICSFLOAT gmf[256];
		
		logfont.lfHeight        = -12;
		logfont.lfWidth         = 0;
		logfont.lfEscapement    = 0;
		logfont.lfOrientation   = logfont.lfEscapement;
		logfont.lfWeight        = FW_THIN;
		logfont.lfItalic        = FALSE;
		logfont.lfUnderline     = FALSE;
		logfont.lfStrikeOut     = FALSE;
		logfont.lfCharSet       = ANSI_CHARSET;
		logfont.lfOutPrecision  = OUT_TT_PRECIS;
		logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logfont.lfQuality       = ANTIALIASED_QUALITY;
		logfont.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
		strcpy(logfont.lfFaceName, fontname);

		CFont font;
		CFont* oldfont;
		BOOL success = font.CreateFontIndirect(&logfont);
		oldfont = m_pDC->SelectObject(&font);
		if (!success || 
			FALSE == wglUseFontOutlines(
			m_pDC->m_hDC, 
			0, 
			256, 
			m_listbase,
			0.0f, // Deviation From The True Outlines
			0.2f, // Font Thickness In The Z Direction
			WGL_FONT_POLYGONS,
			gmf)) 
		{
			glDeleteLists(m_listbase, 256);
			m_listbase = 0;
		}
		else 
		{
			m_pDC->SelectObject(oldfont);
		}
	}
}

COutlineFont::~COutlineFont()
{
	// Class destructor.

	glDeleteLists(m_listbase, 256);
	m_listbase = 0;
}


void COutlineFont::DrawString(char* s)
{
	// Draws the given text string.

	GLsizei len = GLsizei(strlen(s));
	if (s && len > 0) {
		// Must save/restore the list base.
		glPushAttrib(GL_LIST_BIT);{
			glListBase(m_listbase);
			glCallLists(len, GL_UNSIGNED_BYTE, (const GLvoid*)s);
		} glPopAttrib();
	}
}


void COutlineFont::TextDisplay(POINT pt,double theta,CString text,float color_r,float color_g,float color_b, float scale)
{
	
	int sl = text.GetLength();
	
	glColor3f(color_r,color_g,color_b);
	
	glPushMatrix(); 
	
	glTranslatef(pt.x,pt.y, 0.0);
	glRotatef(180.0,180.0, theta, 1.0);
	//glTranslatef(-5*sl,-6, 0.0);
	glTranslatef(-5 * sl, -8, 0.0);
	glScalef(scale, scale, scale);
	
	DrawString(text.GetBuffer(sl));
	
	glPopMatrix();

}

void COutlineFont::TextDisplay(POINT pt,double theta,CString text,float color_r,float color_g,float color_b, float scaleX,float scaleY)
{
	
	int sl = text.GetLength();
	
	glColor3f(color_r,color_g,color_b);
	
	glPushMatrix(); 
	
	glTranslatef(pt.x,pt.y, 0.0);
	glRotatef(180.0,180.0, theta, 1.0);
	//glTranslatef(-5*sl,-6, 0.0);
	//glTranslatef(-5 * sl, -8, 0.0);
	glScalef(scaleX, scaleY, scaleX);
	
	DrawString(text.GetBuffer(sl));
	
	glPopMatrix();

}

void COutlineFont::Text(float x,float y,const char *str,float scalex,float scaley)
{
	int len=strlen(str);
	if(len)
	{
		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x,y,0.0);
		//glRotatef(180.0,180.0, 0, 1.0);
		glScalef(scalex, 1.0*scaley, 1.0);
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_listbase);
		glCallLists(len, GL_UNSIGNED_BYTE, (const GLvoid*)str);
		glPopAttrib();
		
		glPopMatrix();
	}
}

void COutlineFont::Text(float x,float y,float z,const char *str,float scalex,float scaley,float scalez)
{
	int len=strlen(str);
	if(len)
	{
		glPushMatrix();
		//glLoadIdentity();
		glTranslatef(x,y,z);
		//glRotatef(180.0,180.0, 0, 1.0);
		glScalef(scalex, scaley, scalez);
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_listbase);
		glCallLists(len, GL_UNSIGNED_BYTE, (const GLvoid*)str);
		glPopAttrib();
		
		glPopMatrix();
	}
}
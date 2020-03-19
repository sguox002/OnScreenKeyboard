#pragma once
//a key has a string on it, and a scanning code, virtual keycode, 
//has a rect, background color, text color, highlight color, 
#include "stdafx.h"
#include "glwin.h"
#include <string>
#include <unordered_map>

using namespace std;
typedef unsigned _int8 uint8;
//key: show text 
#define WM_SHIFT_PRESSED WM_APP+100
#define WM_CAPS_PRESSED WM_APP+101
#define WM_HIDE_APP WM_APP+102
//state modifier: shift, capslock
//shift sensitive key: `1234567890-=[];',./
//caps sensitive key: a-z
//general key: tab, enter, backspace, up,left,down,right,space
//each key has a unique virtual keycode.
//we need to maintain the keyboard display and send correct key code.
//we do not need capslock to complicate this.
void genKeymap();

class key : public glWin
{
protected:
	string text1,text2; //two string to display (if only one, two will be the same)
	int vkeycode;
	//CRect rect;
	//uint8 bgcolor[3], fgcolor[3],highlight_color[3]; //just use predefined color
	int state;
	int shift_pressed,caps_pressed;
	float bg_r, bg_g, bg_b;
public:
	key() { use_outlinefont = 0; bg_r = bg_g = bg_b = 0.25; }
	key(string s,int code) :text1(s), text2(s), vkeycode(code),state(0) {
		use_outlinefont = 1; shift_pressed = 0;	caps_pressed = 0;
		bg_r = bg_g = bg_b = 0.25;
	}
	key(string s1, string s2,int code) :text1(s1), text2(s2),vkeycode(code),state(0),shift_pressed(0),caps_pressed(0) {
		bg_r = bg_g = bg_b = 0.25;
	}
	virtual void show(); //flag is determined by shift and capslock.
	virtual void simulate_keypress();
	void set_state(int s) { state = s; }
	void set_shift(bool p) { shift_pressed = p; }
	void set_caps(bool p) { caps_pressed = p; }
	virtual void RenderScene();
	void set_bgcolor(float r, float g, float b) { bg_r = r, bg_g = g, bg_b = b; }
	void update_data(int data_type) {} //pure virtual function overload
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
protected:
	void draw_solidkey();
};

class toggle_key : public key //this only include shift and capslock
{
	bool pressed;
public:
	toggle_key(string s1,string s2,int code):key(s1,s2,code),pressed(0) {}
	bool is_selected() { return pressed; }
	void press() { pressed ^= 1; }
	virtual void simulate_keypress() {} //nothing done.
	void RenderScene();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

class shiftkey :public key
{
public:
	shiftkey(string s1, string s2,int code):key(s1,s2,code){}
	virtual void simulate_keypress();
	//virtual void RenderScene();
};

class capskey :public key //capskey affected by shift and caps
{
public:
	capskey(string s1, string s2, int code) :key(s1, s2, code) {}
	virtual void simulate_keypress();
	virtual void RenderScene();
};
//when shift is pressed: not affected by capslock

//capslock a-z affected by shift and capslock.
//keyboard is a list of keys.
class keyboard {
	unordered_map<string,key*> vkey;
	int padding;
	int height;
	bool shift_pressed,kb_created,caps_pressed;
	int layout; //for reservation of different layouts
	CWnd* pMainWnd;
public:
	keyboard(CWnd* parent, int layout = 0) :pMainWnd(parent), shift_pressed(0),kb_created(0) { padding = 0; generate_keys(); }
	
	void create_keys(int w, int h);
	void arrange_keys(int w, int h);
	bool keyboard_created() { return kb_created; }
	void show();
	//shift pressed need to notify the keyboard.
	void notify_shift_change(bool shift);
	void notify_caps_change(bool caps);
	void release();
	~keyboard() { release(); }
private:
	void generate_keys();
};
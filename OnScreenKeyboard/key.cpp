#include "stdafx.h"
#include "key.h"


#include <unordered_map>

using namespace std;


void key::show()
{
	string str = shift_pressed ? text2 : text1;
	clear(bg_r,bg_g,bg_b);

	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	float boarder_width = 1.5;
	int border_line_num = 2;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glEnd();
	/*for(int ii = 0;ii<border_line_num;ii++)
	{
	glBegin(GL_LINE_STRIP);
	boarder_width += 0.2;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glEnd();
	}*/
	

	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glEnd();
	/*for(int ii = 0;ii<border_line_num;ii++)
	{
	glBegin(GL_LINE_STRIP);
	boarder_width += 0.2;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glEnd();
	}*/
	
	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glEnd();
	/*for(int ii = 0;ii<border_line_num;ii++)
	{
	glBegin(GL_LINE_STRIP);
	boarder_width += 0.2;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glEnd();
	}*/

	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glEnd();
	/*for(int ii = 0;ii<border_line_num;ii++)
	{
	glBegin(GL_LINE_STRIP);
	boarder_width += 0.2;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glEnd();
	}*/
	//draw a boarder
	glColor3f(255, 255, 255);
	/*
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(ogl_xmin, ogl_ymax);
	glVertex2f(ogl_xmax, ogl_ymax);
	glVertex2f(ogl_xmin, ogl_ymin);
	glVertex2f(ogl_xmax, ogl_ymin);
	glEnd();
	*/

	glText(ogl_xmin*0.8, ogl_ymax*0.25, str.c_str(),1.0,1.0,2.0);
}

BEGIN_MESSAGE_MAP(key, glWin)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void key::simulate_keypress()
{
	if (text1.empty()) return;
	//if (text1 == "Hide") PostQuitMessage(0);

	if (text1 == "Hide") 
	{
		GetParent()->PostMessage(WM_HIDE_APP,0,0);
		//pMainWnd->SetWindowPos(&wndBottom,0,1024+1080-480,1920,480,SWP_HIDEWINDOW);
		return;
	}

	INPUT keyInput;
	keyInput.type = INPUT_KEYBOARD;

	KEYBDINPUT key;
	string str = text1;

	key.wVk = vkeycode;
	key.wScan = ::VkKeyScan(key.wVk);

	key.dwFlags = 0;	
	keyInput.ki = key;
	::SendInput(1, &keyInput, sizeof(INPUT));

	key.dwFlags = KEYEVENTF_KEYUP;
	keyInput.ki = key;
	::SendInput(1, &keyInput, sizeof(INPUT));
}

void shiftkey::simulate_keypress()
{
	if (text1.empty()) return;
	INPUT keyInput;
	memset(&keyInput, 0, sizeof(INPUT));
	keyInput.type = INPUT_KEYBOARD;
	//note uppercase char needs add shift!!!
	KEYBDINPUT key;
	string str = shift_pressed ==0 ? text1 : text2;

	if(shift_pressed) { //keydown shift
		key.wVk = VK_SHIFT;
		key.wScan = ::VkKeyScan(key.wVk);

		key.dwFlags = 0;
		keyInput.ki = key;
		::SendInput(1, &keyInput, sizeof(INPUT));
	}
	//key down char
	key.wVk = vkeycode;

	key.wScan = ::VkKeyScan(key.wVk);
	key.dwFlags = 0;
	keyInput.ki = key;
	::SendInput(1, &keyInput, sizeof(INPUT));

	//key up char
	key.dwFlags = KEYEVENTF_KEYUP;
	keyInput.ki = key;
	::SendInput(1, &keyInput, sizeof(INPUT));

	if (shift_pressed) {
		key.wVk = VK_SHIFT;// keycode["shift"];
		key.wScan = ::VkKeyScan(key.wVk);
		keyInput.ki = key;
		::SendInput(1, &keyInput, sizeof(INPUT));
	}
}

void capskey::simulate_keypress()
{
	if (text1.empty()) return;
	INPUT keyInput;
	memset(&keyInput, 0, sizeof(INPUT));
	keyInput.type = INPUT_KEYBOARD;
	//note uppercase char needs add shift!!!
	KEYBDINPUT key;
	string str = shift_pressed == 0 ? text1 : text2;
	//
	if (shift_pressed ^ caps_pressed) { //keydown shift
		key.wVk = VK_SHIFT;
		key.wScan = ::VkKeyScan(key.wVk);

		key.dwFlags = 0;
		keyInput.ki = key;
		::SendInput(1, &keyInput, sizeof(INPUT));
	}
	//key down char
	key.wVk = vkeycode;

	key.wScan = ::VkKeyScan(key.wVk);
	key.dwFlags = 0;
	keyInput.ki = key;
	::SendInput(1, &keyInput, sizeof(INPUT));

	//key up char
	key.dwFlags = KEYEVENTF_KEYUP;
	keyInput.ki = key;
	::SendInput(1, &keyInput, sizeof(INPUT));

	if (shift_pressed ^ caps_pressed) {
		key.wVk = VK_SHIFT;// keycode["shift"];
		key.wScan = ::VkKeyScan(key.wVk);
		keyInput.ki = key;
		::SendInput(1, &keyInput, sizeof(INPUT));
	}
}
void key::RenderScene() {
	//using opengl to draw the key
	wglMakeCurrent(hDC, hRC);

	show();
	
	SwapBuffers(hDC);
	wglMakeCurrent(NULL, NULL);
}
void toggle_key::RenderScene() {
	wglMakeCurrent(hDC, hRC);
	if(pressed)	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	else glClearColor(bg_r, bg_g, bg_b, 1.0f);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//draw_solidkey();
	string str = pressed ? text2 : text1;

	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	float boarder_width = 1.5;
	int border_line_num = 10;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glEnd();

	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glEnd();

	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glEnd();
	
	//draw a boarder
	glColor3f(1.0, 1.0, 1.0);
	/*
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(ogl_xmin, ogl_ymax);
	glVertex2f(ogl_xmax, ogl_ymax);
	glVertex2f(ogl_xmin, ogl_ymin);
	glVertex2f(ogl_xmax, ogl_ymin);
	glEnd();
	*/

	glText(ogl_xmin*0.8, ogl_ymax*0.25, str.c_str(),1.0,1.0,2.0);

	SwapBuffers(hDC);
	wglMakeCurrent(NULL, NULL);

}

void capskey::RenderScene() {
	wglMakeCurrent(hDC, hRC);
	clear(bg_r,bg_g,bg_b);
	string str = shift_pressed^caps_pressed ? text2 : text1;

	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,0);
	float boarder_width = 1.5;
	int border_line_num = 10;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glEnd();
	
	

	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymax-boarder_width);
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glEnd();
	
	
	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmin+boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glEnd();
	

	glBegin(GL_LINE_STRIP);
	boarder_width = 1.5;
	glVertex2f(ogl_xmax-boarder_width,ogl_ymin+boarder_width);
	glVertex2f(ogl_xmax-boarder_width,ogl_ymax-boarder_width);
	glEnd();
	
	//draw a boarder
	glColor3f(1.0, 1.0, 1.0);
	/*
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(ogl_xmin, ogl_ymax);
	glVertex2f(ogl_xmax, ogl_ymax);
	glVertex2f(ogl_xmin, ogl_ymin);
	glVertex2f(ogl_xmax, ogl_ymin);
	glEnd();
	*/

	glText(ogl_xmin*0.8, ogl_ymax*0.25, str.c_str(), 1.0, 1.0, 2.5);

	SwapBuffers(hDC);
	wglMakeCurrent(NULL, NULL);
}

void key::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//get shift and caps key state
	simulate_keypress();
	glWin::OnLButtonDown(nFlags, point);
}


void key::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	set_bgcolor(0, 0, 0.5);
	RenderScene();
	glWin::OnMouseHover(nFlags, point);
}


void key::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	set_bgcolor(0, 0, 0);
	RenderScene();
	glWin::OnMouseLeave();
}

void key::draw_solidkey() {
	//define the 6 surfaces
	//gluPerspective(45.0f, aspect, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	// Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity();                 // Reset the model-view matrix
	glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	   // Top face (y = 1.0f)
	   // Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
}
BEGIN_MESSAGE_MAP(toggle_key, key)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void toggle_key::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	press();
	//show();
	RenderScene();
	if(text1=="Shift")
		GetParent()->PostMessage(WM_SHIFT_PRESSED, (WPARAM)is_selected(), (LPARAM)0);
	else 
		GetParent()->PostMessage(WM_CAPS_PRESSED, (WPARAM)is_selected(), (LPARAM)0);
	//also need to notify all keys
	key::OnLButtonDown(nFlags, point);
}

void keyboard::generate_keys() {
	//genKeymap();
	//vkey[""] = new key(""); //null key.
	vkey["A"]=new capskey("a","A",'A');
	vkey["B"]=new capskey("b","B",'B');
	vkey["C"]=new capskey("c","C", 'C');
	vkey["D"]=new capskey("d","D", 'D');
	vkey["E"]=new capskey("e","E", 'E');
	vkey["F"]=new capskey("f","F", 'F');
	vkey["G"]=new capskey("g","G", 'G');
	vkey["H"]=new capskey("h","H", 'H');
	vkey["I"]=new capskey("i","I", 'I');
	vkey["J"]=new capskey("j","J", 'J');
	vkey["K"]=new capskey("k","K", 'K');
	vkey["L"]=new capskey("l","L", 'L');
	vkey["M"]=new capskey("m","M", 'M');
	vkey["N"]=new capskey("n","N", 'N');
	vkey["O"]=new capskey("o","O", 'O');
	vkey["P"]=new capskey("p","P", 'P');
	vkey["Q"]=new capskey("q","Q", 'Q');
	vkey["R"]=new capskey("r","R", 'R');
	vkey["S"]=new capskey("s","S", 'S');
	vkey["T"]=new capskey("t","T", 'T');
	vkey["U"]=new capskey("u","U", 'U');
	vkey["V"]=new capskey("v","V", 'V');
	vkey["W"]=new capskey("w","W", 'W');
	vkey["X"]=new capskey("x","X", 'X');
	vkey["Y"]=new capskey("y","Y", 'Y');
	vkey["Z"]=new capskey("z","Z", 'Z');

	vkey["`"]=new shiftkey("`", "~", VK_OEM_3);
	vkey["1"]=new shiftkey("1", "!",'1');
	vkey["2"]=new shiftkey("2", "@", '2');
	vkey["3"]=new shiftkey("3", "#", '3');
	vkey["4"]=new shiftkey("4", "$", '4');
	vkey["5"]=new shiftkey("5", "%", '5');
	vkey["6"]=new shiftkey("6", "^", '6');
	vkey["7"]=new shiftkey("7", "&", '7');
	vkey["8"]=new shiftkey("8", "*", '8');
	vkey["9"]=new shiftkey("9", "(", '9');
	vkey["0"]=new shiftkey("0", ")", '0');
	vkey["-"]=new shiftkey("-", "_", VK_OEM_MINUS);
	vkey["="]=new shiftkey("=", "+", VK_OEM_PLUS);

	vkey["backspace"] = new key("Backspace", VK_BACK);
	vkey["tab"] = new shiftkey("Tab", "Tab",VK_TAB); //shift+tab is reverse tab
	vkey["["]=new shiftkey("[", "{", VK_OEM_4);
	vkey["]"]=new shiftkey("]", "}",VK_OEM_6);
	vkey["\\"]=new shiftkey("\\", "|", VK_OEM_5);
	vkey[";"]=new shiftkey(";", ":", VK_OEM_1);
	vkey["'"]=new shiftkey("\'", "\"",VK_OEM_7);
	vkey["enter"] = new key("Enter",VK_RETURN);
	vkey[","]=new shiftkey(",", "<", VK_OEM_COMMA);
	vkey["."]=new shiftkey(".", ">",VK_OEM_PERIOD);
	vkey["/"]=new shiftkey("/", "?",VK_OEM_2);
	vkey["hide"] = new key("Hide",0);
	vkey["space"] = new key("Space",VK_SPACE);
	vkey["up"] = new key("Up",VK_UP);
	vkey["down"] = new key("Down",VK_DOWN); 
	vkey["left"] = new key("Left",VK_LEFT);
	vkey["right"] = new key("Right",VK_RIGHT);
	vkey["shift"]=new toggle_key("Shift","Shift",VK_SHIFT);
	vkey["capslock"]=new toggle_key("Caps Lock","Caps Lock",VK_CAPITAL); //do not need this.
}

void keyboard::create_keys(int w, int h) {
	int nrow = 5,nkey_row=15;
	int key_height = (h - (nrow + 1)*padding) / nrow;
	int key_width = (w - (nkey_row + 1)*padding) / nkey_row;
	CRect rect(padding, padding, padding + key_width, padding + key_height);
	DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	CString ClassName = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		NULL,
		NULL,//(HBRUSH)GetStockObject(BLACK_BRUSH),//will cause flash if use black_brush
		NULL);
	//first row
	int key_space = padding + key_width;
	int id = 100;
	key* p = vkey["`"];
	vkey["`"]->CreateEx(NULL, ClassName, "key`", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["1"]->CreateEx(NULL, ClassName, "key1", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["2"]->CreateEx(NULL, ClassName, "key2", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["3"]->CreateEx(NULL, ClassName, "key3", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["4"]->CreateEx(NULL, ClassName, "key4", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["5"]->CreateEx(NULL, ClassName, "key5", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["6"]->CreateEx(NULL, ClassName, "key6", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["7"]->CreateEx(NULL, ClassName, "key7", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["8"]->CreateEx(NULL, ClassName, "key8", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["9"]->CreateEx(NULL, ClassName, "key9", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["0"]->CreateEx(NULL, ClassName, "key0", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["-"]->CreateEx(NULL, ClassName, "key-", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["="]->CreateEx(NULL, ClassName, "key=", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding;
	vkey["backspace"]->CreateEx(NULL, ClassName, "keyback", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	//2nd row
	rect.left = padding;
	rect.top += key_height+padding;
	rect.bottom += key_height+padding;
	rect.right = padding + 1.5*key_width; //tab key
	vkey["tab"]->CreateEx(NULL, ClassName, "key_tab", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["Q"]->CreateEx(NULL, ClassName, "key_Q", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["W"]->CreateEx(NULL, ClassName, "key_W", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["E"]->CreateEx(NULL, ClassName, "key_E", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["R"]->CreateEx(NULL, ClassName, "key_R", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["T"]->CreateEx(NULL, ClassName, "key_T", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["Y"]->CreateEx(NULL, ClassName, "key_Y", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["U"]->CreateEx(NULL, ClassName, "key_U", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["I"]->CreateEx(NULL, ClassName, "key_I", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["O"]->CreateEx(NULL, ClassName, "key_O", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["P"]->CreateEx(NULL, ClassName, "key_P", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["["]->CreateEx(NULL, ClassName, "key_[", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["]"]->CreateEx(NULL, ClassName, "key_]", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding;
	vkey["\\"]->CreateEx(NULL, ClassName, "key_\\", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	//3rd row
	rect.left = padding;
	rect.top += key_height+padding;
	rect.bottom += key_height+padding;
	rect.right = padding + 1.8*key_width; //tab key

	vkey["capslock"]->CreateEx(NULL, ClassName, "key_null", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["A"]->CreateEx(NULL, ClassName, "key_A", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["S"]->CreateEx(NULL, ClassName, "key_S", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["D"]->CreateEx(NULL, ClassName, "key_D", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["F"]->CreateEx(NULL, ClassName, "key_F", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["G"]->CreateEx(NULL, ClassName, "key_G", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["H"]->CreateEx(NULL, ClassName, "key_H", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["J"]->CreateEx(NULL, ClassName, "key_J", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["K"]->CreateEx(NULL, ClassName, "key_K", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["L"]->CreateEx(NULL, ClassName, "key_L", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey[";"]->CreateEx(NULL, ClassName, "key_;", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["'"]->CreateEx(NULL, ClassName, "key_'", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding;
	vkey["enter"]->CreateEx(NULL, ClassName, "key_return", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;

	//4th row
	rect.left = padding;
	rect.top += key_height+padding;
	rect.bottom += key_height+padding;
	rect.right = padding + 2.2*key_width; //tab key

	vkey["shift"]->CreateEx(NULL, ClassName, "key_Shift", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["Z"]->CreateEx(NULL, ClassName, "key_Z", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["X"]->CreateEx(NULL, ClassName, "key_X", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["C"]->CreateEx(NULL, ClassName, "key_C", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["V"]->CreateEx(NULL, ClassName, "key_V", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["B"]->CreateEx(NULL, ClassName, "key_B", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["N"]->CreateEx(NULL, ClassName, "key_N", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["M"]->CreateEx(NULL, ClassName, "key_M", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey[","]->CreateEx(NULL, ClassName, "key_,", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["."]->CreateEx(NULL, ClassName, "key_.", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["/"]->CreateEx(NULL, ClassName, "key_/", style, rect, pMainWnd, id++);
	rect.left=rect.right-key_width, rect.right=w-padding;
	//rect.right = w - 2*padding - key_width; rect.left = rect.right - key_width;
	vkey["up"]->CreateEx(NULL, ClassName, "key_up", style, rect, pMainWnd, id++);
//	rect.left=rect.right+padding, rect.right=rect.left+key_width;

	//5th row:
	rect.left = padding;
	rect.top += key_height+padding;
	rect.bottom += key_height+padding;
	rect.right=rect.left+key_width*3;
	vkey["hide"]->CreateEx(NULL, ClassName, "key_hide", style, rect, pMainWnd, id++);
	rect.left=rect.right+padding,rect.right = w - 4 * padding-3*key_width; //tab key
	vkey["space"]->CreateEx(NULL, ClassName, "key_space", style, rect, pMainWnd, id++);
	//rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding, rect.left = rect.right - key_width;
	vkey["right"]->CreateEx(NULL, ClassName, "key_right", style, rect, pMainWnd, id++);
	rect.right = rect.left-padding, rect.left = rect.right-key_width;
	vkey["left"]->CreateEx(NULL, ClassName, "key_left", style, rect, pMainWnd, id++);
	rect.right = rect.left - padding, rect.left = rect.right - key_width;
	vkey["down"]->CreateEx(NULL, ClassName, "key_down", style, rect, pMainWnd, id++);
	for (auto it = vkey.begin(); it != vkey.end(); it++) {
		it->second->setup_ogl();
		it->second->setup_RC();
	}
	show();
	kb_created = 1;
}

void keyboard::arrange_keys(int w, int h) {
	if (keyboard_created() == 0) return;
	int nrow = 5, nkey_row = 15;
	int key_height = (h - (nrow + 1)*padding) / nrow;
	int key_width = (w - (nkey_row + 1)*padding) / nkey_row;
	CRect rect(padding, padding, padding + key_width, padding + key_height);
	int key_space = key_width + padding;

	key* p = vkey["`"];
	vkey["`"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["1"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["2"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["3"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["4"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["5"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["6"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["7"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["8"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["9"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["0"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["-"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["="]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding;
	vkey["backspace"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	//2nd row
	rect.left = padding;
	rect.top += key_height+padding;
	rect.bottom += key_height + padding;
	rect.right = padding + 1.5*key_width; //tab key
	vkey["tab"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["Q"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["W"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["E"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["R"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["T"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["Y"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["U"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["I"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["O"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["P"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["["]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["]"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding;
	vkey["\\"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	//3rd row
	rect.left = padding;
	rect.top += key_height + padding;
	rect.bottom += key_height + padding;
	rect.right = padding + 1.8*key_width; //tab key

	vkey["capslock"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["A"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["S"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["D"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["F"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["G"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["H"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["J"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["K"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["L"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey[";"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["'"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.right = w - padding;
	vkey["enter"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;

	//4th row
	rect.left = padding;
	rect.top += key_height + padding;
	rect.bottom += key_height + padding;
	rect.right = padding + 2.2*key_width; //tab key

	vkey["shift"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["Z"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["X"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["C"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["V"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["B"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["N"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["M"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey[","]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["."]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	vkey["/"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;
	rect.left=rect.right-key_width; rect.right = w - padding; 
	vkey["up"]->MoveWindow(rect);	rect.left=rect.right+padding, rect.right=rect.left+key_width;

	//5th row:
	rect.left = padding;
	rect.top += key_height + padding;
	rect.bottom += key_height + padding;
	rect.right = rect.left + key_width*3;
	vkey["hide"]->MoveWindow(rect);	rect.left = rect.right+padding, rect.right = w - 4 * padding-3*key_width; //tab key
	vkey["space"]->MoveWindow(rect);	rect.right = w - padding, rect.left = rect.right - key_width;
	vkey["right"]->MoveWindow(rect);	rect.right = rect.left - padding, rect.left = rect.right - key_width;
	vkey["down"]->MoveWindow(rect);	rect.right = rect.left - padding, rect.left = rect.right - key_width;
	vkey["left"]->MoveWindow(rect);	rect.right = rect.left - padding, rect.left = rect.right - key_width;
	
	for (auto it = vkey.begin(); it != vkey.end(); it++) {
		it->second->setup_RC();
	}
	show();
}

void keyboard::show()
{
	for (auto it = vkey.begin(); it != vkey.end();it++) {
		it->second->RenderScene();
		it->second->ShowWindow(SW_SHOW);
	}
}

void keyboard::notify_shift_change(bool shift) {
	for (auto it = vkey.begin(); it != vkey.end(); it++) {
		it->second->set_shift(shift);
	}
}

void keyboard::notify_caps_change(bool caps) {
	for (auto it = vkey.begin(); it != vkey.end(); it++) {
		it->second->set_caps(caps);
	}
}

void keyboard::release() {
	for (auto it = vkey.begin(); it != vkey.end(); it++) {
		it->second->DestroyWindow();
		delete it->second;
	}
	vkey.clear();
}


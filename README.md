# OnScreenKeyboard
using opengl and MFC

glWin: opengl CWnd to draw the key

key: the class for the key: text1,text2 and virtual key code.

shiftkey: key class which is affected by the shift key: A-Z and 0-9, []\,./;'

capskey: key class which is affected by the capslock key, A-Z

togglekey: key class which has two status, the shift and capslock.

keyboard: the container for the keys.

Window is a popup dialog window which has ex-style NOACTIVATED, so that the focus will not be taken back to the keyboard.

Simulate_keypress: 

- normal key: virtual key code with key down and key up

- shift+key: shift key down, virtual key code key down, virtual key code key up, shift key up

- caps+key: shift key down, virtual key code key down, virtual key code key up, shift key up

touchscreen friendly. To avoid non-key area touch which take away the focus, all non-key area is covered 100% by the keys.


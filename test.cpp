#include <cstdlib>
#include <iostream>
#include <math.h>
#include <fstream>
#include <Windows.h>
#include <winuser.h>
//#include <winable.h> /* Dev-C++ specific */
using namespace std;
 
/* HWND = "Window Handle" */

 
/* This is a function to simplify usage of sending keys */
void GenerateKey(int vk, BOOL bExtended) {
 
    KEYBDINPUT  kb = {0};
    INPUT       Input = {0};
 
    /* Generate a "key down" */
    if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
    kb.wVk  = vk;
    Input.type  = INPUT_KEYBOARD;
    Input.ki  = kb;
    SendInput(1, &Input, sizeof(Input));
 
    /* Generate a "key up" */
    ZeroMemory(&kb, sizeof(KEYBDINPUT));
    ZeroMemory(&Input, sizeof(INPUT));
    kb.dwFlags  =  KEYEVENTF_KEYUP;
    if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
    kb.wVk = vk;
    Input.type = INPUT_KEYBOARD;
    Input.ki = kb;
    SendInput(1, &Input, sizeof(Input));
 
    return;
}
 
int main()
{
    
	
	while (true)
	{
		HWND GameWindow = FindWindow(0, "Malinovka");
		SetForegroundWindow(GameWindow);
		GenerateKey('A', FALSE);
		Sleep(5000);
	}
 
    return 0;
}


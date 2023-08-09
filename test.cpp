#include <cstdlib>
#include <iostream>
#include <math.h>
#include <fstream>
#include <Windows.h>
#include <winuser.h>
using namespace std;
 
void GenerateKey(int vk, BOOL bExtended) {
 
    KEYBDINPUT  kb = {0};
    INPUT       Input = {0};
	
    if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
    kb.wVk  = vk;
    Input.type  = INPUT_KEYBOARD;
    Input.ki  = kb;
    SendInput(1, &Input, sizeof(Input));
	
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
		HWND GameWindow = FindWindow(0, "myWindow");
		SetForegroundWindow(GameWindow);
		GenerateKey('A', FALSE);
		Sleep(5000);
	}
 
    return 0;
}


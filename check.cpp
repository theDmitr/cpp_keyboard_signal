#include <windows.h>
#include <iostream>
#include <vector>
#include <tchar.h>

BOOL CALLBACK WorkerProc(HWND hwnd, LPARAM lParam) {
    static TCHAR buffer[50];

    GetWindowText(hwnd, buffer, 50);
    if(_tcsstr(buffer, "Malinovka Client")) {
		//ShowWindow(hwnd, SW_RESTORE);
		SetForegroundWindow(hwnd);
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = 'A';
		input.ki.dwFlags = 0;
		SendInput(1, &input, sizeof(INPUT));
        return FALSE;
    }
    return TRUE;
}

int main()
{
	while (true)
	{
		EnumWindows(WorkerProc, NULL);
	}
    return 0;
}

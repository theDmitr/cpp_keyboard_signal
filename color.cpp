#include <windows.h>
#include <iostream>
#include <tuple>
#include <map>
#include <tchar.h>

using std::cout;
using std::tuple;
using std::get;
using std::map;

typedef WINAPI COLORREF (*GETPIXEL)(HDC, int, int);
typedef tuple<int, int, int> TUPLECOLOR;
typedef tuple<int, int> TUPLEPOS;

enum keys { Q, W, E, A, S, D };
typedef map<keys, TUPLEPOS> KEYANDPOS;
typedef map<keys, char> KEYANDCHAR;

TUPLECOLOR getTupleColor(COLORREF color)
{
	return TUPLECOLOR(GetRValue(color), GetGValue(color), GetBValue(color));
}

KEYANDPOS displayKeys
{
	{Q, TUPLEPOS(1091, 916)}, {W, TUPLEPOS(1152, 913)}, {E, TUPLEPOS(1214, 912)},
	{A, TUPLEPOS(1089, 984)}, {S, TUPLEPOS(1153, 982)}, {D, TUPLEPOS(1214, 987)},
};
KEYANDCHAR requestKeys
{
	{Q, 'Q'}, {W, 'W'}, {E, 'E'},
	{A, 'A'}, {S, 'S'}, {D, 'D'},
};

char currentKey = 'A';

TUPLECOLOR demandedColor = TUPLECOLOR(242, 20, 61);

bool isColorIdentical(TUPLECOLOR color1, TUPLECOLOR color2)
{
	return get<0>(color1) == get<0>(color2) && get<1>(color1) == get<1>(color2) && get<2>(color1) == get<2>(color2);
}

BOOL CALLBACK WorkerProc(HWND hwnd, LPARAM lParam) {
    static TCHAR buffer[50];

    GetWindowText(hwnd, buffer, 50);
    if(_tcsstr(buffer, "myWindow")) {
		SetForegroundWindow(hwnd);
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = 'A';
		input.ki.dwFlags = 0;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(100);
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
		cout << 1 << "\n";
        return FALSE;
    }
    return TRUE;
}

GETPIXEL pGetPixel;
HDC _hdc;

TUPLEPOS value;
COLORREF _color;
TUPLECOLOR color;

int main(int argc, char** argv)
{
    HINSTANCE hGDI = LoadLibrary("gdi32.dll");
	
	while (true)
	{
		Sleep(3000);
		pGetPixel = (GETPIXEL)GetProcAddress(hGDI, "GetPixel");
		_hdc = GetDC(NULL);
		
		for (auto const& key : displayKeys)
		{
			value = key.second;
			_color = (*pGetPixel) (_hdc, get<0>(value), get<1>(value));
			color = getTupleColor(_color);
			
			if (isColorIdentical(demandedColor, color))
			{
				currentKey = requestKeys[key.first];
				EnumWindows(WorkerProc, NULL);
			}
		}
	}
	
    return 0;
}

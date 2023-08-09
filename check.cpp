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
		// эмулируем отпускание клавиши "A"
		//input.ki.dwFlags = KEYEVENTF_KEYUP;
		//SendInput(1, &input, sizeof(INPUT));
		
        return FALSE;
    }
    return TRUE;
}

int main()
{
    // Создаем вектор для хранения окон
    //std::vector<HWND> windows;

    // Перечисляем все окна и добавляем их в вектор
	while (true)
	{
		EnumWindows(WorkerProc, NULL);
	}

    // Выводим заголовки всех окон в консоль
    /*for (auto hwnd : EnumWindows(WorkerProc, NULL);)
    {
        char title[256];
        GetWindowText(hwnd, title, sizeof(title));
        std::cout << title << std::endl;
    }*/

    return 0;
}
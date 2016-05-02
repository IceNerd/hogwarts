#include <windows.h>
#include <stdlib.h>
#include <time.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("BERT");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc= WndProc;
	wndclass.cbClsExtra= 0;
	wndclass.cbWndExtra= 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
    if (!RegisterClass (&wndclass))
	{
        MessageBox(NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
	}
	hwnd = CreateWindow(szAppName,				// window class name
						TEXT("WinApp"),		// window caption
						WS_OVERLAPPEDWINDOW,	// window style
						CW_USEDEFAULT,			// initial x position
						CW_USEDEFAULT,			// initial y position
						CW_USEDEFAULT,			// initial x size
						CW_USEDEFAULT,			// initial y size
						NULL,					// parent window handle
						NULL,					// window menu handle
						hInstance,				// program instance handle
						NULL);					// creation parameters

	ShowWindow (hwnd, iCmdShow);
	UpdateWindow (hwnd);
    
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rect;

	switch (message)
	{
		case WM_CREATE:
			SetTimer(hwnd, 1, 10000, NULL);
			SetTimer(hwnd, 2, 30000, NULL);
		return 0;

		case WM_TIMER:
			switch(wParam)
			{
			case 1:
				Beep(1000, 250);
				return 0;

			case 2:
				MessageBox(hwnd, "Time", "Date", MB_OK);
				return 0;
			}
		return 0;

		case WM_PAINT: 
			hdc = BeginPaint (hwnd, &ps);
			GetClientRect (hwnd, &rect);
			EndPaint(hwnd, &ps);
		return 0;

		case WM_DESTROY:
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}
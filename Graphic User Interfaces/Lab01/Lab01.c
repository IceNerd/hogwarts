/*************************************************************************
*				  Author:  Alberto Martinez
*			Date Created:  October 10, 2004
* Last Modification Date:  October 13, 2004
*			  Lab Number:  CST 238
*				Filename:  Lab01.c
*
* Overview:
*	This program will create a window with text.  The text will be the
* client four-corner coordinates.  This means that the top left will
* always be (0, 0) and the bottom right will be the size of the client.
* Another line will display how many times. since the client started,
* the right mouse button was clicked.
*
* Input:
*	Mouse input will change the client as far as right-click counts and
* resizing.
*
* Output:
*	Client corner coordinates and right mouse button clicks.  Also sound
* for startup.
*
*************************************************************************/

#include <windows.h>
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
static int cur = 0;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpszCmdParam, int nCmdShow)
{
	static char szAppName[] = "Example 1";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);

	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);
	  
	hwnd = CreateWindow (szAppName, "Alberto Martinez Lab 01 - Text and Messages", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	TCHAR szBuffer[25];

	switch(message)
	{
		case WM_PAINT:
			hdc = BeginPaint (hwnd, &ps);
			GetClientRect(hwnd, &rect);

			//screen size
			TextOut(hdc, 0, 0, "Screen Size:", 12);
			TextOut(hdc, 85, 0, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetDeviceCaps(hdc, HORZRES)));
			TextOut(hdc, (lstrlen(szBuffer) * 9) + 85, 0, "X", 1);
			TextOut(hdc, ((lstrlen(szBuffer) + 1) * 9) + 85, 0, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetDeviceCaps(hdc, VERTRES)));

			//RECT
			TextOut(hdc, 0, 20, "Left:", 5);
			TextOut(hdc, 30, 20, szBuffer, wsprintf(szBuffer, TEXT("%5d"), rect.left));
			TextOut(hdc, 60, 20, "Right:", 6);
			TextOut(hdc, 100, 20, szBuffer, wsprintf(szBuffer, TEXT("%5d"), rect.right));
			TextOut(hdc, 150, 20, "Top:", 4);
			TextOut(hdc, 180, 20, szBuffer, wsprintf(szBuffer, TEXT("%5d"), rect.top));
			TextOut(hdc, 210, 20, "Bottom:", 7);
			TextOut(hdc, 260, 20, szBuffer, wsprintf(szBuffer, TEXT("%5d"), rect.bottom));

			//Mouse Button
			TextOut(hdc, 0, 40, "Right Mouse Button Clicks:", 26);
			TextOut(hdc, 180, 40, szBuffer, wsprintf(szBuffer, TEXT("%5d"), cur));

			EndPaint (hwnd, &ps);
		return 0;

		case WM_RBUTTONDOWN:
			cur = cur + 1;
			MessageBox(hwnd, "Right Mouse Button Pressed", "Event", MB_OK);
		return 0;

		case WM_CREATE:
			PlaySound(TEXT("C:\\WINDOWS\\Media\\Windows XP Startup.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;

		case WM_DESTROY:
			PostQuitMessage (0);
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}
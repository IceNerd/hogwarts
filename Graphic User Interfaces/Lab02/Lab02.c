/*************************************************************************
*				  Author:  Alberto Martinez
*			Date Created:  October 10, 2004
* Last Modification Date:  October 13, 2004
*			  Lab Number:  CST 238
*				Filename:  Lab02.c
*
* Overview:
*	This program will display text and some random ellipses.  Right-click
* and left-click will toggle WM_PAINT and WM_ERASEBKGND respectively.
*
* Input:
*	Mouse left and right-click.
*
* Output:
*	Depends on what is being drawn and erased now doesnt it?
*
*************************************************************************/

#include <windows.h>
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
static int wmpaint = 1, wmerase = 1;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpszCmdParam, int nCmdShow)
{
	static char szAppName[] = "Martinez";
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
	  
	hwnd = CreateWindow (szAppName, "Martinez Lab02 - Press LEft or Right Mouse Button", WS_OVERLAPPEDWINDOW,
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
			if(wmpaint == 1)
			{
				hdc = BeginPaint (hwnd, &ps);
				GetClientRect(hwnd, &rect);
				//B
				TextOut(hdc, 0, 0, "CHRISTMAS IS COMING", 19);

				//C
				TextOut(hdc, 0, 20, "Press Left or Right Mouse Button to Make Selection", 50);

				//D
				Ellipse(hdc, 100, 100, 200, 200);
				Ellipse(hdc, 70, 100, 100, 120);
				Ellipse(hdc, 10, 80, 20, 85);
				
				EndPaint (hwnd, &ps);
			}
		return 0;

		case WM_ERASEBKGND:
			if(wmerase == 1)
			{
				DefWindowProc (hwnd, message, wParam, lParam);
			}
		return 0;

		case WM_LBUTTONDOWN:
			if(wmpaint == 1)
			{
				wmpaint = 0;
				MessageBox(hwnd, "WM_PAINT Disabled", "Event", MB_OK);
			}
			else
			{
				wmpaint = 1;
				MessageBox(hwnd, "WM_PAINT Enabled", "Event", MB_OK);
			}
		return 0;

		case WM_RBUTTONDOWN:
			if(wmerase == 1)
			{
				wmerase = 0;
				MessageBox(hwnd, "WM_ERASEBKGND Disabled", "Event", MB_OK);
			}
			else
			{
				wmerase = 1;
				MessageBox(hwnd, "WM_ERASEBKGND Enabled", "Event", MB_OK);
			}
		return 0;

		case WM_DESTROY:
			PostQuitMessage (0);
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}
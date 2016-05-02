/*************************************************************************
*				  Author:  Alberto Martinez
*			Date Created:  October 24, 2004
* Last Modification Date:  October 24, 2004
*			  Lab Number:  CST 238
*				Filename:  WinApp.cpp
*
* Overview:
*	This program will create a window.  The window will have a menu
*  and display a 50 character long buffer that is cyclic.  The menu will
*  contain:
*        &File     &Animals     &Date Info       &Break     &Help
*		  &Erase    &Dog		 Current &Date    &Sound     &System Info
*		  E&xit     &Cat         Current &Time    S&hapes    &About
*
*  Erase will clear the text buffer.  Exit will terminate the program.
*  Dog will display a message box that says "Dog."  Cat will display
*  a message box that says "Cat."  Current Date will display a message
*  box that shows the current date.  Current time will display a message
*  box that shows the current time.  Sound will play the windows sound.
*  Shapes will draw circle on the window.  System info will display a
*  dialog box with system info on it.  Finally, about will display a
*  dialog box with some info on the program.
*
*************************************************************************/

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				                        PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Alberto Martinez - Lab 4");
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
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;

	HMENU hmenu;
	hmenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    if (!RegisterClass (&wndclass))
	{
        MessageBox(NULL, TEXT ("This program requires Windows NT!"),
			                                  szAppName, MB_ICONERROR);
        return 0;
	}
	hwnd=CreateWindow(szAppName,			// window class name
					  TEXT("WinApp"),		// window caption
					  WS_OVERLAPPEDWINDOW,	// window style
					  CW_USEDEFAULT,		// initial x position
					  CW_USEDEFAULT,		// initial y position
					  CW_USEDEFAULT,		// initial x size
					  CW_USEDEFAULT,		// initial y size
					  NULL,					// parent window handle
					  hmenu,				// window menu handle
					  hInstance,			// program instance handle
					  NULL);				// creation parameters

	ShowWindow (hwnd, iCmdShow);
	UpdateWindow (hwnd);
    
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,
						                           LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rect;
	static HINSTANCE hInstance;
	static char Buffer[51];
	static int BuffCnt;
	static bool ShapeIt;

	switch (message)
	{
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			ShapeIt = false;
			Buffer[0] = '\0';
			BuffCnt = 0;
		return 0;

		case WM_COMMAND:
			switch( LOWORD(wParam) )
			{
				case ID_FILE_ERASE:
					Buffer[0] = '\0';
					BuffCnt = 0;
					InvalidateRect(hwnd, &rect, true);
				break;

				case ID_FILE_EXIT:
					if( MessageBox(hwnd,
						"Do you really want to quit?",
						"File_Exit", MB_YESNO) == IDYES)
					{
						PostQuitMessage(0);
					}
				break;

				case ID_ANIMALS_DOG:
					MessageBox(hwnd, "Dog", "Animal", MB_OK);
				break;

				case ID_ANIMALS_CAT:
					MessageBox(hwnd, "Cat", "Animal", MB_OK);
				break;

				case ID_DATEINFO_CURRENTDATE:
					MessageBox(hwnd, "Date", "Date_Time", MB_OK);
				break;

				case ID_DATEINFO_CURRENTTIMEABOUT:
					MessageBox(hwnd, "Time", "Date_Time", MB_OK);
				break;

				case ID_BREAK_SOUND:
					PlaySound(
					TEXT("C:\\WINDOWS\\Media\\Windows XP Startup.wav"),
					                   NULL, SND_FILENAME | SND_ASYNC);
				break;

				case ID_BREAK_SHAPES:
					ShapeIt = true;
					InvalidateRect(hwnd, &rect, true);
				break;

				case ID_HELP_SYSTEMINFO:
					MessageBox(hwnd, "System Info",
						             "Sys Info", MB_OK);
				break;

				case ID_HELP_ABOUT:
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
						                 hwnd, AboutDlgProc);
				break;
			}
		return 0;

		case WM_CHAR:
			if(BuffCnt == 51)
			{
				for(int i = 0; i < 51; i++)
				{
					Buffer[i] = Buffer[i + 1];
				}
				Buffer[50] = wParam;
			}
			else
			{
				Buffer[BuffCnt] = wParam;
				BuffCnt++;
				Buffer[BuffCnt] = '\0';
			}
			InvalidateRect(hwnd, &rect, true);
		return 0;

		case WM_PAINT: 
			hdc = BeginPaint (hwnd, &ps);
			GetClientRect (hwnd, &rect);
			TextOut(hdc, 0, 0, Buffer, strlen(Buffer));
			if(ShapeIt)
			{
				for(int i = 0; i < 100; i++)
				{
					Ellipse(hdc, i*5, i*5, i*10, i*10);
				}
				ShapeIt = false;
			}
			EndPaint(hwnd, &ps);
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}


//Result of MANY attempts to get a dialog box.  However this has
//failed.  I will have questions in-lab about what I am supposed
//to do to get this to work.
BOOL CALLBACK AboutDlgProc(HWND hdlg, UINT message,
						           WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
		return true;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDCANCEL:
				case IDOK:
					EndDialog(hdlg, 0);
				return true;
			}
		break;
	}
	return false;
}
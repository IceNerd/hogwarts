/*************************************************************************** 
Alberto Martinez
vanilla.frijole@gmail.com
www.PMSoft.org
Copyright(c) 2005 PMSoft 

11/28/2004 

Main.cpp

This program does NOT abide by the PMSoft coding standards.  This program
was developed before the coding standards were applicable.
***************************************************************************/ 

/*************************************************************************** 
Comboling
Copyright(c) 2005 PMSoft 

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation; either version 2 
of the License, or (at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License 
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA." 
***************************************************************************/ 


#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <htmlhelp.h>
#include <commctrl.h>

#include "String.h"
#include "tArray.h"
#include "cField.h"
#include "cTile.h"
#include "resource.h"

#define ME_X 530
#define ME_Y 620
#define ID_BUTTON_START 0
#define ID_BUTTON_ABOUT 1
#define ID_BUTTON_OVER  2
#define ID_BUTTON_HELP  3

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

/**************************************************************
*   WinMain
*
***************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("BERT");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ID_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

    if(!RegisterClass(&wndclass))
	{
        MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
	}

	hwnd = CreateWindow(szAppName,				// window class name
						TEXT("Comboling"),		// window caption
						WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,				// window style
						CW_USEDEFAULT,			// initial x position
						CW_USEDEFAULT,			// initial y position
						ME_X,					// initial x size
						ME_Y,					// initial y size
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

/**************************************************************
*   Windows Procedure 
*
***************************************************************/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int clientX, clientY;
	static int Level(0);
	static cField field;
	static HWND Button[5];
	static RECT rect;
	static HINSTANCE hInstance;

	HDC hdc_Client;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_SIZE:
			clientX = LOWORD(lParam);
			clientY = HIWORD(lParam);
		return 0;

		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			Button[ID_BUTTON_START] = CreateWindow(	TEXT("button"),
									TEXT("Start"),
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
									ME_X - 120,
									ME_Y - 100,
									100,
									25,
									hwnd,
									(HMENU)ID_BUTTON_START,
									hInstance,
									NULL
								  );

			Button[ID_BUTTON_ABOUT] = CreateWindow(	TEXT("button"),
									TEXT("About"),
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
									0,
									ME_Y - 75,
									100,
									25,
									hwnd,
									(HMENU)ID_BUTTON_ABOUT,
									hInstance,
									NULL
								  );

			Button[ID_BUTTON_OVER] = CreateWindow(	TEXT("button"),
									TEXT("Start Over"),
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_DISABLED,
									ME_X - 120,
									ME_Y - 75,
									100,
									25,
									hwnd,
									(HMENU)ID_BUTTON_OVER,
									hInstance,
									NULL
								  );

			Button[ID_BUTTON_HELP] = CreateWindow(	TEXT("button"),
									TEXT("Help"),
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
									0,
									ME_Y - 50,
									100,
									25,
									hwnd,
									(HMENU)ID_BUTTON_HELP,
									hInstance,
									NULL
								  );
 	           
			field.Init(ME_X, ME_Y);
			field.DrawFieldOnVDC();
			field.DumpToHDC(hdc_Client);
		return 0;

		case WM_PAINT:
			hdc_Client = BeginPaint(hwnd, &ps);
			field.DumpToHDC(hdc_Client);
			EndPaint(hwnd, &ps);
		return 0;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_BUTTON_START:
					PlaySound(MAKEINTRESOURCE(SND_SELECT), NULL, SND_ASYNC | SND_RESOURCE);
					if(Level == 0)
					{
						Level = 1;
						field.MakePuzzle(Level);
						SetWindowText(Button[ID_BUTTON_START], TEXT("New Game"));
						EnableWindow(Button[ID_BUTTON_OVER], TRUE);
						InvalidateRect(hwnd, NULL, NULL);
					}
					else
					{
						if( MessageBox(hwnd, TEXT("Are you sure you want to start a new game?"), TEXT("Comboling"), MB_YESNO) == IDYES )
						{
							Level = 1;
							field.MakePuzzle(Level);
							SetWindowText(Button[ID_BUTTON_START], TEXT("New Game"));
							EnableWindow(Button[ID_BUTTON_OVER], TRUE);
							InvalidateRect(hwnd, NULL, NULL);
						}
					}
				break;

				case ID_BUTTON_OVER:
					PlaySound(MAKEINTRESOURCE(SND_SELECT), NULL, SND_ASYNC | SND_RESOURCE);
					field.ResetField();
					InvalidateRect(hwnd, NULL, NULL);
				break;

				case ID_BUTTON_ABOUT:
					DialogBox(hInstance, MAKEINTRESOURCE(ID_DIALOG_ABOUT), hwnd, AboutDlgProc);
				break;

				case ID_BUTTON_HELP:
					HtmlHelp(hwnd, TEXT("ComboHelp.chm"), HH_DISPLAY_TOPIC, 0);
				break;
			}
		return 0;

		case WM_LBUTTONUP:
			if(field.Click(lParam))
			{
				if( field.CheckWin() )
				{
					InvalidateRect(hwnd, NULL, NULL);
					SendMessage(hwnd, WM_PAINT, NULL, NULL);
					PlaySound(MAKEINTRESOURCE(SND_COMPLETE), NULL, SND_SYNC | SND_RESOURCE);
					Level++;
					field.DrawBlankFieldOnVDC();
					field.MakePuzzle(Level);
				}
				else
				{
					PlaySound(MAKEINTRESOURCE(SND_HIT), NULL, SND_ASYNC | SND_RESOURCE);
				}
				InvalidateRect(hwnd, NULL, NULL);
				SendMessage(hwnd, WM_PAINT, NULL, NULL);
			}
			else
			{
				PlaySound(MAKEINTRESOURCE(SND_WRONG), NULL, SND_ASYNC | SND_RESOURCE);
			}
		return 0;

		case WM_DESTROY:
			PlaySound(NULL, NULL, NULL);
			PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}

/**************************************************************
*   Dialog Box Procedure 
*
***************************************************************/
BOOL CALLBACK AboutDlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
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
			break;
			}
		break;
	}
	return false;
}
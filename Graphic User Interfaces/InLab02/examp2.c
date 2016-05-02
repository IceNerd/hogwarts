/*---------------------------------------------------------------
   			EXAMPLE 2 -- Getting Started & Messaging
    Displays "Hello Windows Programming Class" in client area 
    
    
    Misc Info:  Illustrates elementary Message Passing and the old way of 
 		        calling/passing (ie., Windows 3.1 - just for fun)
   	Filename:  	C:\CST238\Examp2.c
	Compiler:	Visual Studio .NET
	Author:	R. Albert
	Special Notes:   (You must get rid of the warnings too)
		1.  Notice how YOU will need to update some of the functions for 2000/XP
		2.	See help/text on CreateWindow, ShowWindow, UpdateWindow
		3.  Notice what happens when the window is created
		4.	When you resize it, move it, etc.
		5.	When you destroy it
	The MessageBox function creates, displays, and operates a message-box
	window. The message box contains an application-defined message 
	and title, plus any combination of the predefined icons and push
	buttons described in the fuStyle parameter. (From Help file). 	
-------------------------------------------------------------------*/

#include <windows.h>

long FAR PASCAL WndProc (HWND hwnd, UINT message, UINT wParam, LONG lParam) ;


int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
     {
     static char szAppName[] = "Messaging" ;
     HWND        hwnd ;
     MSG         msg ;	// Look how this struct is defined-see help/class notes NOW
     WNDCLASS    wndclass ; 

     if (!hPrevInstance)
          {
          wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
          wndclass.lpfnWndProc   = WndProc ;
          wndclass.cbClsExtra    = 0 ;
          wndclass.cbWndExtra    = 0 ;
          wndclass.hInstance     = hInstance ;
          wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
          wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
          wndclass.hbrBackground = GetStockObject (WHITE_BRUSH) ;
          wndclass.lpszMenuName  = NULL ;
          wndclass.lpszClassName = szAppName ;

          RegisterClass (&wndclass) ;
	  }

     hwnd = CreateWindow (szAppName,         // window class name
		    "Alberto Martinez",     		 // window caption
                    WS_OVERLAPPEDWINDOW,     // window style
                    CW_USEDEFAULT,           // initial x position
                    CW_USEDEFAULT,           // initial y position
                    CW_USEDEFAULT,           // initial x size
                    CW_USEDEFAULT,           // initial y size
                    NULL,                    // parent window handle
                    NULL,                    // window menu handle
                    hInstance,               // program instance handle
		    		NULL) ;		     		 // creation parameters

     ShowWindow (hwnd, nCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
          {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
          }
     return msg.wParam ;
     }

long FAR PASCAL WndProc (HWND hwnd, UINT message, UINT wParam,
                            LONG lParam)
     {
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT	 	 rect ;

     switch (message)
          {
          case WM_CREATE:
          		MessageBox(hwnd, "Inside WM_CREATE - but how??", "CHECK THIS!!", MB_OK);
          		return 0;
          	
		  case WM_SIZE:
				MessageBox(hwnd, "MESSAGE RECIEVED", "CHECK THIS!!", MB_OK);
			  return 0;

          case WM_PAINT:
	       		hdc = BeginPaint (hwnd, &ps) ;

           		GetClientRect (hwnd, &rect) ;

	       		DrawText (hdc, "Christmas is Coming", -1, &rect,
					DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;

	       		EndPaint (hwnd, &ps) ;
            	return 0 ;

          case WM_DESTROY:
            	PostQuitMessage (0) ;
               	return 0 ;

		  case WM_CLOSE:
			  MessageBox(hwnd, "WM_CLOSE RECIEVED", "CHECK THIS!!", MB_OK);
			  return 0;

		  case WM_QUIT:
			  MessageBox(hwnd, "WM_QUIT RECIEVED", "CHECK THIS!!", MB_OK);
			  return 0;
          }

     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }

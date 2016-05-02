
/*---------------------------------------------------------------
   			EXAMPLE 1 -- Getting Started & Messaging
    Displays "Hello Windows Programming Class" in client area 
    
    Misc Info:  Quick review of the .NET environment
   	Filename:  	example1.c
	Compiler:	MSVS .NET
	Author:		R. Albert
	Special Notes:   
		1.	See help/text on CreateWindow, ShowWindow, UpdateWindow
		2.  Notice what happens when the window is created, resized, etc.
		3.  Check the output
		4.  Make sure you become familiar with the use of the floating windows
		    in VS .NET AND especially the various aspects of the dynamic on-line help.

	Please print a copy of your finished lab and bring it 
	with you to the next class session.  We will be discussing it
	at that time.  (NOTE: STUDY THIS).

	MORE FUN STUFF TO DO FOR LAB:  Add a message box that pops up telling
	the class and your name when the user selects an ITEM THAT
	YOU ADD TO THE SYSTEM MENU:
	  Read about:  
		    GetSystemMenu
			AppendMenu or InsertMenuItem
		 	MessageBox / MessageBoxEx
	 NOTE:  periodically, an error or two might find it's way into the 
	        start-up code just to give you some additional excitement.
-------------------------------------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR lpszCmdParam, int nCmdShow)
     {
     static char szAppName[] = "Example 1";
     HWND			hwnd;
     MSG			msg;	// Look how this struct is defined-see help/class notes NOW
     WNDCLASSEX		wndclass; 

		  wndclass.cbSize 		 = sizeof(wndclass);
		  wndclass.style         = CS_HREDRAW | CS_VREDRAW;
          wndclass.lpfnWndProc   = WndProc;
          wndclass.cbClsExtra    = 0;
          wndclass.cbWndExtra    = 0;
          wndclass.hInstance     = hInstance;
          wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
		 
		  wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
          wndclass.hbrBackground = GetStockObject (WHITE_BRUSH);
          wndclass.lpszMenuName  = NULL;
          wndclass.lpszClassName = szAppName;
		  wndclass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION);

          RegisterClassEx (&wndclass);
	  

     hwnd = CreateWindow (szAppName,         // window class name
		    "CST 238 - Example 1",     		 // window caption
                    WS_OVERLAPPEDWINDOW,     // window style
                    CW_USEDEFAULT,           // initial x position
                    CW_USEDEFAULT,           // initial y position
                    CW_USEDEFAULT,           // initial x size
                    CW_USEDEFAULT,           // initial y size
                    NULL,                    // parent window handle
                    NULL,                    // window menu handle
                    hInstance,               // program instance handle
		    		NULL);		     		 // creation parameters

     ShowWindow (hwnd, nCmdShow);
     UpdateWindow (hwnd);

     while (GetMessage (&msg, NULL, 0, 0))
          {
          TranslateMessage (&msg);
          DispatchMessage (&msg);
          }
     return  (int) msg.wParam;  // notice I did an old style C cast because of warning
     }

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, 
						  WPARAM wParam, LPARAM lParam)
     {
     HDC         hdc;
     PAINTSTRUCT ps;
     RECT	 	 rect;

     switch (message)
         {
          case WM_PAINT:
	       		hdc = BeginPaint (hwnd, &ps);

           		GetClientRect (hwnd, &rect);

	       		DrawText (hdc, "Example 1 - Is Windows Cool or What?",
					-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	       		EndPaint (hwnd, &ps);
            	return 0;

          case WM_DESTROY:
            	PostQuitMessage (0);
               	return 0;
         }

     return DefWindowProc (hwnd, message, wParam, lParam);
     }



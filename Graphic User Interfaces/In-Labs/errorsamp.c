/*---------------------------------------------------------------
   	ERRORSAMP.C - Same as Example 1 - but with 3 or 4 (or more) errors :-)
			
			  -- Getting Started & Messaging --
    Displays "Hello Windows Programming Class" in client area 
    
    Misc Info:  Quick review/tour of MSVC 7.0 environment
   	Filename:  	errorsamp.c
	Author:		R. Albert
	Special Notes:   
		1.	See help/text on CreateWindow, ShowWindow, UpdateWindow
		2.  Notice what happens when the window is created, resize, etc.
		3.  Check the output

	Please print a copy of your finished lab and bring
	it with you to the next class session.  We will be discussing it
	at that time.  (NOTE: STUDY THIS).
	NOTE:  periodically an error or two may find it's way into some of
	       our startup code just to add some additional excitement into
		   your life!
-------------------------------------------------------------------*/

#include window.h

LRESULT CALLBACK WindProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI Winmain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR lpszCmdParam, int nCmdShow)
     {
     static char szAppName[] = "ErrorSample";
     HWND			hwnd;
     MSG			msg;	// Look how this struct is defined-see help/class notes NOW
     WNDCLASSEX		wndclass; 

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
		  wndclass.hIconSmall    = NULL;

          RegisterClass (wndclass);
	  
		  //Might be a good time to check out OutputDebugString,
		  //GetLastError, FormatMessage (see your online HELP for
		  //some good additional info, etc ;-)


     hwnd = CreateWindow (szAppName,         // window class name
		    "CST 238 - Example 0,     		 // window caption
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
     return msg.wParam;
     }

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, 
						  WPARAM wParam, LPARAM lParam)
     {
     HDC         hdc;
     PAINTSTRUCT ps;
     
     switch (message)
         {
          case WM_PAINTS:
	       		hdc = BeginPainting (hwnd, &ps);

           		GetClientRect (hwnd, &rect);

	       		DrawText (hdc, "Example 0 - Is Windows Cool or What?",
					-1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	       		EndPaints (hwnd, &ps);
            	return 0;

         }

     return DefWindowProc (hwnd, message, wParam, lParam);
     }

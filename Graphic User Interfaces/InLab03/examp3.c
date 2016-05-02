/*-----------------------------------------------------------------------
*  		EXAMPLE 3 -- Getting Started & Messaging
*               Used for IN-LAB EXERCISE #3
*         (Well, to at least get you started)
*	A few warnings and/or problems just for fun/review too - fix those
*
*            
*    Misc Info:  Keyboard and text
*    Compiler:   MSVC 7.0
*	Author:		R. Albert
*	
*   See the Help file for additional information on the 
*    new API calls NOW!  Note that some info the in this file
*	may just be included for fun.  In addition, YOU will need to
*	fix ALL the warnings when your lab is done - which should take 
*	you about 1 minute. Also, use the WNDCLASSEX vs WNDCLASS!
*   Make sure you also include an icon and your own cursor if you got time :-).  
*	Have fun AND feel free to make this a C++ file too!
-----------------------------------------------------------------------------*/


#include <windows.h>

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, UINT wParam, LONG lParam) ;


RECT rect;
unsigned int cxChar, cyChar;


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
     {
     static char szAppName[] = "Keyboarding" ;
     HWND        hwnd;
     MSG         msg; 	
     WNDCLASS    wndclass; 

     if (!hPrevInstance)
          {
          wndclass.style         = CS_HREDRAW | CS_VREDRAW;
          wndclass.lpfnWndProc   = WndProc;
          wndclass.cbClsExtra    = 0;
          wndclass.cbWndExtra    = 0;
          wndclass.hInstance     = hInstance ;
          wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
          wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
          wndclass.hbrBackground = GetStockObject (WHITE_BRUSH) ;
          wndclass.lpszMenuName  = NULL ;
          wndclass.lpszClassName = szAppName ;

          RegisterClass (&wndclass) ;
	  }

     hwnd = CreateWindow (szAppName,         // window class name
		    "In-Lab 3 Fun",   // window caption
                    WS_OVERLAPPEDWINDOW,     // window style
                    CW_USEDEFAULT,           // initial x position
                    CW_USEDEFAULT,           // initial y position
                    100, 100,                // hmmmmm???
                    NULL,                    // parent window handle
                    NULL,                    // window menu handle
                    hInstance,               // program instance handle
 	    		  NULL) ;		   	   // creation parameters

     ShowWindow (hwnd, nCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
          {
            TranslateMessage (&msg) ;
            DispatchMessage (&msg) ;
          }
     return (int) msg.wParam ;
     }

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, UINT wParam,
                            LONG lParam)
     {
     HDC         hdc ;
     PAINTSTRUCT ps ;
     TEXTMETRIC  tm;
     char MessageBoxText[16];
     static char Buffer[31];
	 static int BuffCnt;
	 static int i;
     RECT	 	 rClientRect;
     RECT	 	 rWindowRect;
     
     switch (message)
          {
          case WM_CREATE:
                hdc = GetDC(hwnd);
                
                SelectObject(hdc, GetStockObject (SYSTEM_FIXED_FONT));
                
                GetTextMetrics(hdc, &tm);
                cxChar = tm.tmAveCharWidth;
                cyChar = tm.tmHeight;
                
                Buffer[0] = '\0';  // initialize to null
				BuffCnt = 0; //initi to 0
                
                ReleaseDC (hwnd, hdc);

                return 0;
          	
          case WM_PAINT:
       			InvalidateRect(hwnd, NULL, TRUE);
                
                hdc = BeginPaint (hwnd, &ps) ;

        	    SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
                
                TextOut(hdc, cxChar, cyChar / 2, Buffer,  strlen(Buffer));
                
                EndPaint (hwnd, &ps) ;
                return 0 ;
		
		  case WM_KEYDOWN:
			  if(wParam == 46)
			  {
				  BuffCnt == 0;
				  Buffer[0] = '\0';
			  }
			  else if(wParam == 27)
			  {
				  PostQuitMessage(0);
			  }
			  return 0;
		  case WM_CHAR:
			  if(wParam == 8)
			  {
				  MessageBox(hwnd, "CTR-H Pressed", "Message", MB_OK);
			  }
			  if(BuffCnt == 31)
			  {
				  for(i = 0; i < 30; i=i+1)
				  {
					Buffer[i] = Buffer[i + 1];
				  }
				  Buffer[30] = wParam;
				  Buffer[31] = '\0';
			  }
			  else
			  {
				Buffer[BuffCnt + 1] = '\0';
				Buffer[BuffCnt] = wParam;
				BuffCnt = BuffCnt + 1;
			  }
			  InvalidateRect(hwnd, NULL, TRUE);
			  return 0;

          case WM_DESTROY:
            	PostQuitMessage (0) ;
               	return 0 ;
          }

     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }


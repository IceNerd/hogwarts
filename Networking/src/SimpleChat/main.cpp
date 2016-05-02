/*************************************************************************
Alberto Martinez
05/28/2005

main.cpp

--- Peer-to-Peer Chat ---
For a change in venue, rather than doing the Options lab, you can
  implement a peer-to-peer chat program running on top of UDP. This option
  is for those who wish to work with some application programming over the
  socket layer. The program you write will be able to do simple messaging
  between peers. Here is a list of requirements:

   1. Your system must keep track of different "chat" instances running on
        the network.
   2. When a new instance is started, your system must notice this and
        alert the user.
   3. You be able to show who is currently on-line.
   4. You must be able to send messages back and forth between different
        clients.

**************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <vector>
#include <list>

//------------------------------------------------------------------------
//-- Using PracticalSocket.  Author Unknown but was found at the URL below
//       http://cs.baylor.edu/~donahoo/practical/CSockets/practical/
#include "PracticalSocket.h"
//------------------------------------------------------------------------
#include "udpcon.h"

#define ME_X 650
#define ME_Y 570
#define BUTTON_CONNECT 0
#define BUTTON_DISCONNECT 1
#define BUTTON_SEND 2
#define TXTBOX_SEND 3
#define LSTBOX_FRIENDS 4
#define TIMER 5
#define SIZE_CHAT 38

std::vector<HWND> vctWinObj;
std::list<std::string> lstStrings;
std::list<std::string> lstMessages( SIZE_CHAT, "" );
UDPCon* Connection = 0;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void AddToChat( const std::string& );
void AddToChat( const wchar_t* );
std::string UnicodeConvert( const wchar_t* );

	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
	{
		static TCHAR szAppName[] = TEXT("Simple Chat");
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

		hwnd = CreateWindow(szAppName,				//window class name
							TEXT("Simple Chat Using Sockets: Alberto Martinez"),//window caption
							WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,	//window style
							CW_USEDEFAULT,			//initial x position
							CW_USEDEFAULT,			//initial y position
							ME_X,					//initial x size
							ME_Y,					//initial y size
							NULL,					//parent window handle
							NULL,					//window menu handle
							hInstance,				//program instance handles
							NULL);					//creation parameters
		ShowWindow( hwnd, iCmdShow );
		UpdateWindow( hwnd);

		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		return (int)msg.wParam;
	}

	LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		HDC hdc;
		PAINTSTRUCT ps;
		static RECT rect;
		static HINSTANCE hInstance;

		std::vector<std::string>* ptr_clientList;
		std::list<std::string>::iterator iter_i;
		wchar_t strFromWin[128];
		int iIndex;
		int iLength;
		int i;

		switch( message )
		{
			//Create our windows form here
			case WM_CREATE:
				hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

				//Connect Button
				vctWinObj.push_back( CreateWindow(	TEXT("button"),
													TEXT("Connect"),
													WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
													0,
													495,
													100,
													25,
													hwnd,
													(HMENU)BUTTON_CONNECT,
													hInstance,
													NULL
												  )
									);

				//Disconnect Button
				vctWinObj.push_back( CreateWindow(	TEXT("button"),
													TEXT("Disconnect"),
													WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
													0,
													520,
													100,
													25,
													hwnd,
													(HMENU)BUTTON_DISCONNECT,
													hInstance,
													NULL
												  )
									);

				//Send Button
				vctWinObj.push_back( CreateWindow(	TEXT("button"),
													TEXT("Send"),
													WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
													400,
													473,
													100,
													25,
													hwnd,
													(HMENU)BUTTON_SEND,
													hInstance,
													NULL
												  )
									);

				//Textbox for text to send
				vctWinObj.push_back( CreateWindow(	TEXT("edit"),
													NULL,
													WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
													10,
													473,
													385,
													20,
													hwnd,
													(HMENU)TXTBOX_SEND,
													hInstance,
													NULL
												  )
									);

				//ListBox For displaying clients
				vctWinObj.push_back( CreateWindow(	TEXT("listbox"),
													NULL,
													WS_CHILD | WS_VISIBLE | LBS_STANDARD,
													500,
													0,
													150,
													500,
													hwnd,
													(HMENU)LSTBOX_FRIENDS,
													hInstance,
													NULL
												  )
									);

				EnableWindow( vctWinObj[BUTTON_DISCONNECT], false );
				EnableWindow( vctWinObj[BUTTON_SEND], false );
			return 0;

			case WM_PAINT: 
				hdc = BeginPaint(hwnd, &ps );
				GetClientRect( hwnd, &rect );
				//--- Begin Paint ---

				SelectObject( hdc, GetStockObject( SYSTEM_FIXED_FONT ) );
				SetBkMode( hdc, OPAQUE );
				for( i = 0, iter_i = lstMessages.begin(); i < SIZE_CHAT; ++i, ++iter_i )
				{
					TextOut( hdc, 0, (ME_Y - 170) - (12*i), strFromWin, wsprintf( strFromWin, TEXT( "%S" ), (*iter_i).c_str() ) );
				}
				
				//handle listbox here
				if( Connection )
				{
					ptr_clientList = Connection->GetClientList();
					SendMessage( vctWinObj[LSTBOX_FRIENDS], LB_RESETCONTENT, 0, 0 );
					for( std::vector<std::string>::iterator iter_i = (*ptr_clientList).begin(); iter_i != (*ptr_clientList).end(); ++iter_i )
					{
						wsprintf( strFromWin, TEXT( "%S" ), (*iter_i).c_str() );
						SendMessage( vctWinObj[LSTBOX_FRIENDS], LB_ADDSTRING, 0, (LPARAM)strFromWin );
					}
					ptr_clientList = 0;
				}

				//--- End Paint ---
				EndPaint(hwnd, &ps);
			return 0;

			case WM_COMMAND:
				switch( LOWORD(wParam) )
				{
					case BUTTON_CONNECT:
						//--- Connect ---
						if( Connection != 0 )
						{
							AddToChat( "ERROR: Connection Already Open" );
						}
						else
						{
							Connection = new UDPCon( lstMessages, hwnd );
							if( Connection != 0 )
							{
								if( Connection->CreateThread() )
								{
									AddToChat( "Ready!" );
									EnableWindow( vctWinObj[BUTTON_CONNECT], false );
									EnableWindow( vctWinObj[BUTTON_DISCONNECT], true );
									EnableWindow( vctWinObj[BUTTON_SEND], true );
									SetTimer( hwnd, TIMER, 30000, NULL );
								}
								else
								{
									delete (UDPCon*)Connection;
									Connection = 0;
									AddToChat( "ERROR: Failed to Initialize Connection Thread" );
									EnableWindow( vctWinObj[BUTTON_CONNECT], true );
								}
							}
							else
							{
								AddToChat( "ERROR: Failed to Initialize Connection" );
								EnableWindow( vctWinObj[BUTTON_CONNECT], true );
							}
						}
						InvalidateRect( hwnd, NULL, true );
						//--- End Connect ---
					break;

					case BUTTON_DISCONNECT:
						//--- Disconnect ---
						if( Connection != 0 )
						{
							SendMessage( vctWinObj[LSTBOX_FRIENDS], LB_RESETCONTENT, 0, 0 );
							KillTimer( hwnd, TIMER );
							delete (UDPCon*)Connection;
							Connection = 0;
							AddToChat( "Connection Closed" );
						}
						else
						{
							AddToChat( "Connection Already Closed" );
						}
						EnableWindow( vctWinObj[BUTTON_CONNECT], true );
						EnableWindow( vctWinObj[BUTTON_DISCONNECT], false );
						EnableWindow( vctWinObj[BUTTON_SEND], false );
						//--- End Disconnect ---
					break;

					case BUTTON_SEND:
						//--- Send Message to Peer ---
						if( Connection != 0 )
						{
							iIndex = SendMessage( vctWinObj[LSTBOX_FRIENDS], LB_GETCURSEL, 0 ,0 );
							if( iIndex != LB_ERR )
							{
								//Target Address From ListBox
								iLength = SendMessage( vctWinObj[LSTBOX_FRIENDS], LB_GETTEXTLEN, iIndex, 0 );
								iLength = SendMessage( vctWinObj[LSTBOX_FRIENDS], LB_GETTEXT, iIndex, (LPARAM)strFromWin );

								lstStrings.push_front( UnicodeConvert( strFromWin ) );
								
								//Text to Send
								iLength = GetWindowTextLength( vctWinObj[TXTBOX_SEND] );
								if( iLength > 0 )
								{
									GetWindowText( vctWinObj[TXTBOX_SEND], strFromWin, iLength + 1);
									lstStrings.push_front( UnicodeConvert( strFromWin ) );
									//Send it and forget it!
									if( Connection->SendTo( lstStrings.front().c_str(), lstStrings.front().size() + 1, lstStrings.back() ) )
									{
										SetWindowText( vctWinObj[TXTBOX_SEND], TEXT("") );
									}
								}
								else
								{
									AddToChat( "No Text to Send" );
								}
							}
							else
							{
								AddToChat( "Please select a client from the list" );
							}
						}
						else
						{
							AddToChat( "Connection not Open" );
						}
						lstStrings.clear();
						InvalidateRect( hwnd, NULL, true );
						//--- End Send Message to Peer ---
					break;
				}
			return 0;

			case WM_TIMER:
				switch( wParam )
				{
					case TIMER:
						if( Connection )
						{
							Connection->SortPings();
							InvalidateRect( hwnd, NULL, true );
						}
						else
						{
							KillTimer( hwnd, TIMER );
						}
					break;
				}
			return 0;

			case WM_DESTROY:
				KillTimer( hwnd, TIMER );
				if( Connection )
				{
					delete (UDPCon*)Connection;
					Connection = 0;
					AddToChat( "Connection Closed" );
				}
				PostQuitMessage( 0 );
			return 0;
		}

		return DefWindowProc( hwnd, message, wParam, lParam );
	}

	void AddToChat( const std::string& strAdd )
	{
		if( !strAdd.empty() )
		{
			lstMessages.pop_back();
			lstMessages.push_front( strAdd );
		}
	}

	void AddToChat( const wchar_t* strAdd )
	{
		if( strAdd )
		{
			lstMessages.pop_back();
			lstMessages.push_front( UnicodeConvert( strAdd ) );
		}
	}

	std::string UnicodeConvert( const wchar_t* convertMe )
	{
		size_t origsize = wcslen( convertMe ) + 1;
		const size_t newSize = 100;
		size_t convertedChars = 0;
		char newString[newSize];
		wcstombs_s( &convertedChars, newString, origsize, convertMe, _TRUNCATE );
		newString[newSize - 1] = 0;

		return std::string( newString );
	}
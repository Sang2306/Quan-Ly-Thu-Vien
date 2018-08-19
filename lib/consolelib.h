#ifndef MYLIB_H
#define MYLIB_H
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <dos.h>
#include <cstring>
#include <windows.h>
//define KEY
#define ENTER 			13 
#define KEY_HOME        71
#define KEY_UP          72
#define KEY_PGUP        73
#define KEY_LEFT        75
#define KEY_CENTER      76
#define KEY_RIGHT       77
#define KEY_END         79
#define KEY_DOWN        80
#define KEY_PGDN        81
#define KEY_INSERT      82
#define KEY_DELETE      83
#define KEY_F1          59
#define KEY_F2          60
#define KEY_F3          61
#define KEY_F4          62
#define KEY_F5          63
#define KEY_F6          64
#define KEY_F7          65
#define KEY_F8          66
#define KEY_F9          67
#define KEY_ESC			27
#define BACK_SPACE		8
#define KEY_SPACE		32
using namespace std;
///initialize list color
enum colors { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
              LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE };
///there are function in consolelib
int CheckPwd ();										//check password
void Moveto(short x,short y);							//move cursor
void Clrscr( );											//clear screen at current position
void Setcolor(WORD color);								//set text color
void Setbkcolor(WORD color);							//set background color
template<class _Tp>
void Print_at(int x, int y, _Tp data);					//print at desired position
void ShowCursor(bool visible);							//hide cursor
void ChangeFont();										//change font style
void GetWindowSize(int &Width, int &Height);			//get window size
void Normal(short fontColor, short backgroundColor);	//set normal view
void HighLight(short fontColor, short backgroundColor);	//set highlight view
void DisableMaximizeButton();							//set fixed console window
void Moveto(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  
void Clrscr( ) {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
	  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
	Moveto(info.dwCursorPosition.X + 1, info.dwCursorPosition.Y + 1);
}
void Setcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Setbkcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
template<class _Tp>
void Print_at(int x, int y, _Tp data)
{
	Moveto(x, y);
	cout << data;
}
void ShowCursor(bool visible)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = visible;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void ChangeFont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 21;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void GetWindowSize(int &Width, int &Height) 
{ 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Normal(short fontColor, short backgroundColor)
{
	Setcolor(fontColor);
	Setbkcolor(backgroundColor);
}
void HighLight(short fontColor, short backgroundColor)
{
	Setcolor(fontColor);
	Setbkcolor(backgroundColor);
}

void DisableMaximizeButton()
{
	HWND consoleWindow  = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow , GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
#endif

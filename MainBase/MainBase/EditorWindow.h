#pragma once

/****************************************************/
/*  Basic Win32 Template                            */
/****************************************************/

/*
  Cpw link options:

  #define CPW_EXTERN        - link to the static lib
  #define CPWDLL_EXTERN     - link to the release dll's stub
  #define CPWDLLDBG_EXTERN  - link to the debug dll's stub
  #define CPWEXTDLL_EXTERN  - link to the release dll with cpw addons
*/

#define CPWDLL_EXTERN
#include <cpw.h>


/* handy window characteristics holder */
static CpwWindowInfo windowInfo = { 0,100,100,250,300 }; /* id,posx,posy,w,h */


void myDraw(void);
void forceDraw(void);

void initBox(void);
void set2DMatrix(void);
void set3DMatrix(void);
void drawWindowOne(pCpw cpw);
void draw(pCpw cpw, uint_32 winid);
void window(pCpw cpw, uint_32 winid, bool flag);
void reshape(pCpw cpw, uint_32 winid, uint_32 width, uint_32 height);
#ifdef _WINDOWS
int APIENTRY WinStart(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow);
#elif _CONSOLE
int RunWin(int argc, char* argv[]);
#endif
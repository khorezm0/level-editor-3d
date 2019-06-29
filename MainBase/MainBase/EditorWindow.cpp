#include <iostream>
#include "EditorWindow.h"
#include "InputSystem.h"

/****************************************************/
/*  OpenGL 2D Matrix Setup                          */
/****************************************************/

void set2DMatrix(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowInfo.width, 0, windowInfo.height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/****************************************************/
/*  OpenGL 3D Matrix Setup                          */
/****************************************************/

void set3DMatrix(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)windowInfo.width / (float)windowInfo.height, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };  /* Red diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

pCpw myWnd;
uint_32 myWinId;
CpwMouseInfo* inf;

void initBox()
{
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
}

/****************************************************/
/*  Draw Window One                                 */
/****************************************************/

void drawWindowOne(pCpw cpw)
{
	myDraw();
}
double rotX = 0;
double rotY = 0;
int mouse1=0, mouse2=0, mouse3=0;

void myDraw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	set3DMatrix();

	cpwMouseState(myWnd, inf);

	double deltaX = inf->x;
	double deltaY = inf->y;

	if (mouse1)
	{
		printf("a");
		rotY += -deltaX * 0.1;
		rotX += -deltaY * 0.1;
	}


	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(rotX, 1.0, 0, 0.0);
	glRotatef(rotY, 0.0, 1, 0.0);
	//glRotatef(-20, 0.0, 0.0, 1.0);

	/* draw something in the window with OpenGL */

	//std::cout << "Good";

	int i;

	for (i = 0; i < 6; i++) {
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void forceDraw() 
{
	drawWindowOne(myWnd);
	cpwSwapWindowBuffers(myWnd, myWinId);
}

void Idle(pCpw cpw) {
	testInputs();
	forceDraw();
}

/****************************************************/
/*  Window Draw Event callback                      */
/****************************************************/

void draw(pCpw cpw, uint_32 winid)
{
	drawWindowOne(cpw);
	cpwSwapWindowBuffers(cpw, winid);
}

/****************************************************/
/*  Window Create / Destroy Event callback          */
/****************************************************/

void window(pCpw cpw, uint_32 winid, bool flag)
{
	/* creation event */

	if (flag == true) {

		glShadeModel(GL_SMOOTH);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glClearColor(0.0, 0.0, 0.0, 1.0);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		myWnd = cpw;
		myWinId = winid;

		return;
	}

	/* window close event */

	if (flag == false) {
		cpwDestroyWindow(cpw, winid);
		return;
	}
}

/****************************************************/
/*  Window Resize Event callback                    */
/****************************************************/

void reshape(pCpw cpw, uint_32 winid, uint_32 width, uint_32 height)
{
	if (height == 0) { height = 1; }
	if (width == 0) { width = 1; }

	windowInfo.width = width;
	windowInfo.height = height;

	set2DMatrix();

	glViewport(0, 0, width, height);
}


void mouseCallback(pCpw cpw, uint_32 id, uint_32 button, uint_32 state, uint_32 x, uint_32 y)
{
	printf("%i %i; ", button, state);
	if (button == 0) {
		mouse1 = state;
	}
	else if (button == 1) {
		mouse3 = state;
	}
	else if (button == 2) {
		mouse2 = state;
	}
}


/****************************************************/
/*  Main                                            */
/****************************************************/

#ifdef _WINDOWS
int APIENTRY WinStart(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
#elif _CONSOLE
int RunWin(int argc, char* argv[])
#endif
{
	pCpw cpw = null;

	/****************************************************/
	/*  Init                                            */
	/****************************************************/

	initBox();
	inf = (CpwMouseInfo*)calloc(1, sizeof(CpwMouseInfo));
	if (!inf) std::cout << "CpwMouseInfo is null";


	cpwInitContext(&cpw);

	/****************************************************/
	/*  Creaing Windows                                 */
	/****************************************************/

	windowInfo.id =
		cpwCreateWindowEx(cpw, (char*)"Basic Template", windowInfo.x, windowInfo.y,
			windowInfo.width, windowInfo.height);

	/****************************************************/
	/*  Event Callbacks                                 */
	/****************************************************/

	cpwCreateCallback(cpw, window);
	cpwDisplayCallback(cpw, draw);
	cpwReshapeCallback(cpw, reshape);
	cpwIdleCallback(cpw, Idle);
	cpwMouseClickCallback(cpw, mouseCallback);

	/****************************************************/
	/*  MainLoop                                        */
	/****************************************************/

	cpwMainLoop(cpw);

	/****************************************************/
	/*  Exit and Free                                   */
	/****************************************************/

	cpwFreeContext(&cpw);

	return 0;
}


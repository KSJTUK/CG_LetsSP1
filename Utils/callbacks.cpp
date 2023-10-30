#include "pch.h"
#include "Utils\callbacks.h"
#include "Game.h"

extern class Engine e;

// 그리기 콜백함수
void renderFunc()
{
	// rendering function
	game->Render();
}

void reshapeFunc(int x, int y)
{
	game->ResizeWindow(x, y);
}

void idleFunc()
{
	game->Update();

	glutPostRedisplay();
}


void keyboardFunc(unsigned char key, int x, int y)
{
	game->Input(key, true);
}

void keyboardUpFunc(unsigned char key, int x, int y)
{
	game->Input(key, false);
}

void mouseFunc(int button, int state, int x, int y)
{

}

void mouseLeftDown(int state, int x, int y)
{
	
}

void mouseRightDown(int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{
	game->MouseMotion(x, y);
}

void mousePassiveMotion(int x, int y)
{
	game->MousePassiveMotion(x, y);
}
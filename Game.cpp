#include "pch.h"
#include "Game.h"
#include "callbacks.h"
#include "Graphics.h"

Game::Game() { }

Game::~Game() { }

void Game::Init(int* argc, char** argv) {
	// 윈도우 정보 설정
	m_windowInfo.x = 100;
	m_windowInfo.y = 100;
	m_windowInfo.width = 800;
	m_windowInfo.height = 600;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);
	m_windowInfo.windowTitle = "Let's SP1 2020180006";

	// glut라이브러리 초기화
	glutInit(argc, argv);

	// 윈도우 출력모드 설정(더블버퍼링, RGBA, 깊이버퍼)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// 윈도우 크기, 좌표 설정
	glutInitWindowPosition(m_windowInfo.x, m_windowInfo.y);
	glutInitWindowSize(m_windowInfo.width, m_windowInfo.height);

	// 윈도우 생성
	glutCreateWindow(m_windowInfo.windowTitle.c_str());
	
	SubscribeCallbacks();

	// glew 라이브러리 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	//((bool(__stdcall*)(int))wglGetProcAddress("wglSwapIntervalEXT"))(0); // 수직 동기화

	// 이곳에서 각종 변수들 초기화
	m_graphicsComponent = std::make_unique<Graphics>();
	m_graphicsComponent->Init();
}


void Game::Update() {
	m_graphicsComponent->Update(0.f);
}

void Game::Render() {
	glClearColor(m_backGroundColor.x, m_backGroundColor.y, m_backGroundColor.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 렌더링 코드
	m_graphicsComponent->Render();

	glutSwapBuffers();
}

void Game::ResizeWindow(int x, int y) {
	m_windowInfo.width = x;
	m_windowInfo.height = x;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);

	glViewport(0, 0, x, y);
}

void Game::Input(unsigned char key, bool down) {
	
}

void Game::MouseMotion(int x, int y) {
	m_mousePrevPos[0] = x;
	m_mousePrevPos[1] = y;
}

void Game::MousePassiveMotion(int x, int y) {
	m_mousePrevPos[0] = x;
	m_mousePrevPos[1] = y;
}

void Game::Loop() {
	glutMainLoop();
}

// 콜백함수들 등록
void Game::SubscribeCallbacks() {
	glutDisplayFunc(renderFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutIdleFunc(idleFunc);
}
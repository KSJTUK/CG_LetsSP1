#include "pch.h"
#include "Game.h"
#include "Utils\callbacks.h"
#include "Graphics\Shader.h"
#include "Graphics\Graphics.h"
#include "Graphics\GraphicBuffer.h"
#include "Line.h"

Game::Game() { }

Game::~Game() {
	if (m_mouseLine) {
		delete m_mouseLine;
		m_mouseLine = nullptr;
	}
}

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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

	//glEnable(GL_DEPTH_TEST);

	//((bool(__stdcall*)(int))wglGetProcAddress("wglSwapIntervalEXT"))(0); // 수직 동기화


	// 이곳에서 각종 변수들 초기화
	m_graphicsComponent = std::make_unique<Graphics>();
	m_graphicsComponent->Init();
	m_graphicsComponent->SetWindowInfo(m_windowInfo);
}


void Game::Update() {
	m_graphicsComponent->Update(0.f);
}

void Game::Render() {
	glClearColor(m_backGroundColor.x, m_backGroundColor.y, m_backGroundColor.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 렌더링 코드
	SHADER->UseProgram();
	m_graphicsComponent->Render();

	if (m_mouseLine) {
		m_mouseLine->Render();
	}
	SHADER->UnUseProgram();

	glutSwapBuffers();
}

void Game::ResizeWindow(int x, int y) {
	m_windowInfo.width = x;
	m_windowInfo.height = x;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);

	m_graphicsComponent->SetWindowInfo(m_windowInfo);
	glViewport(0, 0, x, y);
}

void Game::Input(unsigned char key, bool down) {
	
}

void Game::MouseMotion(int x, int y) {
	if (!m_mouseLine) {
		m_mouseLine = new Line{ std::pair<glm::vec3, glm::vec3>{ m_mousePrevPos, m_mouseCurPos }, m_mouseLineColor };
	}

	float halfW{ static_cast<float>(m_windowInfo.width) / 2.f }, halfH{ static_cast<float>(m_windowInfo.height) / 2.f };
	float mouseX{ static_cast<float>(x) - halfW }, mouseY{ static_cast<float>(-y) + halfH };

	m_mouseCurPos = glm::vec3{ mouseX, mouseY - 75.f, 0.f };
	m_mouseLine->Update(m_mouseCurPos);
}

void Game::MousePassiveMotion(int x, int y) {
	float halfW{ static_cast<float>(m_windowInfo.width) / 2.f }, halfH{ static_cast<float>(m_windowInfo.height) / 2.f };
	float mouseX{ static_cast<float>(x) - halfW }, mouseY{ static_cast<float>(-y) + halfH };

	m_mousePrevPos = glm::vec3{ mouseX, mouseY - 75.f, 0.f };
	m_mouseCurPos = m_mousePrevPos;
}

void Game::MouseUp(int x, int y) {
	if (m_mouseLine) {
		delete m_mouseLine;
		m_mouseLine = nullptr;
	}

	float halfW{ static_cast<float>(m_windowInfo.width) / 2.f }, halfH{ static_cast<float>(m_windowInfo.height) / 2.f };
	float mouseX{ static_cast<float>(x) - halfW }, mouseY{ static_cast<float>(-y) + halfH };

	glm::vec2 start{ m_mousePrevPos }, end{ m_mouseCurPos };
	m_graphicsComponent->MouseUp(std::pair<glm::vec2, glm::vec2>{ start, end });
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
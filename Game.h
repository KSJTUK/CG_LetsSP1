#pragma once

class Game {
public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	WindowInfo m_windowInfo{ };

	glm::vec3 m_mouseCurPos{ };
	glm::vec3 m_mousePrevPos{ };
	glm::vec3 m_mouseLineColor{ 1.f, 0.f, 0.f };

	class Line* m_mouseLine{ };

	float3 m_backGroundColor{ 0.5f, 0.5f, 0.5f };

	std::unique_ptr<class Graphics> m_graphicsComponent{ };

public:
	void Init(int* argc, char** argv);
	void Update();
	void Render();

public:
	void ResizeWindow(int x, int y);
	void Input(unsigned char key, bool down);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
	void MouseUp(int x, int y);

	void Loop();


	void SubscribeCallbacks();
};
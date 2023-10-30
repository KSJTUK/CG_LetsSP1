#pragma once

class Game {
public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	WindowInfo m_windowInfo{ };

	int32 m_mousePrevPos[2]{ };

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

	void Loop();


	void SubscribeCallbacks();
};
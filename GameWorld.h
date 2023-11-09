#pragma once

class GameWorld {
public:
	GameWorld();
	~GameWorld();

private:
	std::unique_ptr<class Graphics> m_graphicsEngine{ };

	std::list<class Poly*> m_worldObjectList{ };
	std::unordered_map<std::string, std::pair<std::list<class Poly*>, std::list<class Poly*>>> m_worldCollisionList{ };

public:
	void AddObject(class Poly* object);
	void AddCollisionObject(std::string& groub, class Poly* object1 = nullptr, class Poly* object2 = nullptr);
	bool HandleCollision();

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};
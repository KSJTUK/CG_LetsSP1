#pragma once

class Poly {
public:
	Poly();
	~Poly();

	Poly(const Poly& other);
	Poly& operator=(const Poly& other);

private:
	std::vector<Vertex> m_verticies{ };
	std::unique_ptr<class GraphicBuffers> m_graphicBuffer{ };

public:

public:
	void Update(float deltaTime);
	void Render();
};


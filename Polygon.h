#pragma once

class Poly {
public:
	Poly();
	~Poly();

	Poly(const std::vector<glm::vec3> otherVertex, const glm::vec3& color);
	Poly(const Poly& other);
	Poly& operator=(const Poly& other);

private:
	std::vector<Vertex> m_verticies{ };
	std::unique_ptr<class GraphicBuffers> m_graphicBuffer{ };

private:
	bool CalcIntersectParameter(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, float& resultParam);
	bool IntersectLine(const std::pair<glm::vec2, glm::vec2>& l1, const std::pair<glm::vec2, glm::vec2>& l2, glm::vec3& intersectionPoint);
	bool GetIntersectionPoint(const glm::vec2& ap1, const glm::vec2& ap2, const glm::vec2& bp1, const glm::vec2& bp2, glm::vec3& result);

public:
	bool CutPolygon(const std::pair<glm::vec2, glm::vec2>& line, Poly& newPoly);

public:
	void Update(float deltaTime);
	void Render();
};


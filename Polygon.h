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
	std::vector<uint32> m_indicies{ };
	std::unique_ptr<class GraphicBuffers> m_graphicBuffer{ };

private:
	bool IsCWPoint(const std::pair<glm::vec2, glm::vec2>& line, const Vertex& point);
	bool IsCCWPointVertex(const std::pair<glm::vec2, glm::vec2>& line, const Vertex& point);
	bool CCW(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
	void CW_CCWLinePoint(const std::pair<glm::vec2, glm::vec2>& line, std::vector<Vertex>& Points,
		std::vector<glm::vec3>& cwPoints, std::vector<glm::vec3>& ccwPoints, std::vector<uint32>& cwIndex, std::vector<uint32>& ccwIndex);
	bool CalcIntersectParameter(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, float& resultParam);
	bool IntersectLine(const std::pair<glm::vec2, glm::vec2>& l1, const std::pair<glm::vec2, glm::vec2>& l2, glm::vec3& intersectionPoint);
	bool GetIntersectionPoint(const glm::vec2& ap1, const glm::vec2& ap2, const glm::vec2& bp1, const glm::vec2& bp2, glm::vec3& result);
	void SortCCW(std::vector<Vertex>& verticies);
	void SortCCW(std::vector<glm::vec3>& verticies);

public:
	bool CutPolygon(const std::pair<glm::vec2, glm::vec2>& line, Poly& newPoly);
	void SeparateVertexCW_CCW();

public:
	void Update(float deltaTime);
	void Render();
};


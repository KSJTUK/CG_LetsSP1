#pragma once

class Line {
public:
	Line() = delete;
	Line(const std::pair<Vertex, Vertex>& startEnd);
	Line(const std::pair<glm::vec3, glm::vec3>& startEnd, const glm::vec3& color);
	Line(const std::pair<glm::vec2, glm::vec2>& startEnd, const glm::vec3& color);

	Line(const std::vector<Vertex>& startEnd);
	Line(const std::vector<glm::vec3>& points, const glm::vec3& color);
	Line(const std::vector<glm::vec2>& points, const glm::vec3& color);
	~Line();

private:
	std::unique_ptr<class GraphicBuffers> m_graphicBuffer{ };

	std::vector<Vertex> m_verticies{ };
	std::vector<uint32> m_indicies{ };

public:
	void Update(const glm::vec3& newEnd);
	void Render();
};

